// CLI "rekursif": alat bantu menghitung & memvisualisasikan rekursi.
//   ./rekursif faktorial 5      -> mode perintah tunggal
//   ./rekursif                  -> mode interaktif (REPL)
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "rekursif/deret.hpp"
#include "rekursif/hanoi.hpp"
#include "rekursif/jejak.hpp"
#include "rekursif/larik.hpp"
#include "rekursif/matematika.hpp"
#include "rekursif/teks.hpp"

using namespace rekursif;
using Args = std::vector<std::string>;

namespace {

long long ke_angka(const std::string& s) {
    try {
        std::size_t pos = 0;
        long long v = std::stoll(s, &pos);
        if (pos != s.size()) throw std::invalid_argument("");
        return v;
    } catch (...) {
        throw std::invalid_argument("'" + s + "' bukan bilangan bulat yang valid");
    }
}

double ke_desimal(const std::string& s) {
    try {
        std::size_t pos = 0;
        double v = std::stod(s, &pos);
        if (pos != s.size()) throw std::invalid_argument("");
        return v;
    } catch (...) {
        throw std::invalid_argument("'" + s + "' bukan bilangan yang valid");
    }
}

void butuh(const Args& a, std::size_t jumlah, const std::string& pakai) {
    if (a.size() < jumlah + 1) throw std::invalid_argument("Pemakaian: " + pakai);
}

void bantuan() {
    std::cout <<
        "Perintah yang tersedia:\n"
        "  faktorial <n>              n!  (n <= 20)\n"
        "  fib <n> [naif|memo]        bilangan Fibonacci ke-n (n <= 93)\n"
        "  banding <n>                adu kecepatan fib naif vs memo (n <= 40)\n"
        "  pangkat <a> <n>            a pangkat n (pangkat cepat)\n"
        "  fpb <a> <b>                Faktor Persekutuan Terbesar\n"
        "  kpk <a> <b>                Kelipatan Persekutuan Terkecil\n"
        "  digit <n>                  jumlah digit n\n"
        "  basis <n> <b>              konversi n ke basis b (2..36)\n"
        "  collatz <n>                jumlah langkah Collatz\n"
        "  kombinasi <n> <k>          C(n,k)  (n <= 60)\n"
        "  ackermann <m> <n>          fungsi Ackermann (m <= 3, n <= 10)\n"
        "  hanoi <n>                  langkah Menara Hanoi (n <= 20)\n"
        "  permutasi <teks>           semua permutasi (maks 8 karakter)\n"
        "  subset <teks>              semua himpunan bagian (maks 10 karakter)\n"
        "  balik <teks>               membalik teks\n"
        "  palindrom <teks...>        cek palindrom\n"
        "  cari <target> <a1 a2 ...>  pencarian biner (larik harus terurut)\n"
        "  jumlah <a1 a2 ...>         jumlah elemen larik\n"
        "  maks <a1 a2 ...>           elemen terbesar\n"
        "  jejak faktorial <n>        pohon pemanggilan faktorial (n <= 20)\n"
        "  jejak fib <n>              pohon pemanggilan fibonacci (n <= 8)\n"
        "  bantuan | keluar\n";
}

std::vector<long long> baca_larik(const Args& a, std::size_t mulai) {
    std::vector<long long> v;
    for (std::size_t i = mulai; i < a.size(); ++i) v.push_back(ke_angka(a[i]));
    return v;
}

std::string gabung(const Args& a, std::size_t mulai) {
    std::string s;
    for (std::size_t i = mulai; i < a.size(); ++i) s += (i > mulai ? " " : "") + a[i];
    return s;
}

// Mengembalikan false jika pengguna meminta keluar.
bool jalankan(const Args& a) {
    if (a.empty()) return true;
    const std::string& cmd = a[0];

    if (cmd == "keluar" || cmd == "exit" || cmd == "quit") return false;
    if (cmd == "bantuan" || cmd == "help" || cmd == "-h" || cmd == "--help") { bantuan(); return true; }

    if (cmd == "faktorial") {
        butuh(a, 1, "faktorial <n>");
        int n = static_cast<int>(ke_angka(a[1]));
        u64 hasil = faktorial(n);
        std::cout << n << "! = " << hasil << "\n";
    } else if (cmd == "fib") {
        butuh(a, 1, "fib <n> [naif|memo]");
        int n = static_cast<int>(ke_angka(a[1]));
        std::string mode = a.size() > 2 ? a[2] : "memo";
        if (mode == "naif") {
            if (n > 45) throw std::invalid_argument("versi naif dibatasi n <= 45 (terlalu lambat)");
            u64 panggilan = 0;
            u64 hasil = fibonacci_naif(n, panggilan);
            std::cout << "fib(" << n << ") = " << hasil << "  [" << panggilan << " pemanggilan]\n";
        } else if (mode == "memo") {
            u64 hasil = fibonacci_memo(n);
            std::cout << "fib(" << n << ") = " << hasil << "\n";
        } else {
            throw std::invalid_argument("mode harus 'naif' atau 'memo'");
        }
    } else if (cmd == "banding") {
        butuh(a, 1, "banding <n>");
        int n = static_cast<int>(ke_angka(a[1]));
        if (n < 0 || n > 40) throw std::invalid_argument("banding: n harus 0..40");
        using jam = std::chrono::steady_clock;
        u64 panggilan = 0;
        auto t0 = jam::now();
        u64 h1 = fibonacci_naif(n, panggilan);
        auto t1 = jam::now();
        u64 h2 = fibonacci_memo(n);
        auto t2 = jam::now();
        auto us = [](auto d) { return std::chrono::duration_cast<std::chrono::microseconds>(d).count(); };
        std::cout << "n = " << n << "\n"
                  << "naif : " << h1 << "  | " << panggilan << " pemanggilan | " << us(t1 - t0) << " us\n"
                  << "memo : " << h2 << "  | O(n) pemanggilan | " << us(t2 - t1) << " us\n";
    } else if (cmd == "pangkat") {
        butuh(a, 2, "pangkat <a> <n>");
        double hasil = pangkat(ke_desimal(a[1]), ke_angka(a[2]));
        std::cout << std::setprecision(15) << a[1] << "^" << a[2] << " = " << hasil << "\n";
    } else if (cmd == "fpb") {
        butuh(a, 2, "fpb <a> <b>");
        std::cout << "FPB(" << a[1] << ", " << a[2] << ") = " << fpb(ke_angka(a[1]), ke_angka(a[2])) << "\n";
    } else if (cmd == "kpk") {
        butuh(a, 2, "kpk <a> <b>");
        std::cout << "KPK(" << a[1] << ", " << a[2] << ") = " << kpk(ke_angka(a[1]), ke_angka(a[2])) << "\n";
    } else if (cmd == "digit") {
        butuh(a, 1, "digit <n>");
        long long n = ke_angka(a[1]);
        if (n < 0) throw std::invalid_argument("digit: n tidak boleh negatif");
        std::cout << "jumlah digit " << n << " = " << jumlah_digit(static_cast<u64>(n)) << "\n";
    } else if (cmd == "basis") {
        butuh(a, 2, "basis <n> <b>");
        long long n = ke_angka(a[1]);
        if (n < 0) throw std::invalid_argument("basis: n tidak boleh negatif");
        std::string hasil = konversi_basis(static_cast<u64>(n), static_cast<int>(ke_angka(a[2])));
        std::cout << n << " (basis 10) = " << hasil << " (basis " << a[2] << ")\n";
    } else if (cmd == "collatz") {
        butuh(a, 1, "collatz <n>");
        long long n = ke_angka(a[1]);
        if (n < 1) throw std::invalid_argument("collatz: n harus >= 1");
        u64 hasil = collatz(static_cast<u64>(n));
        std::cout << "collatz(" << n << ") = " << hasil << " langkah\n";
    } else if (cmd == "kombinasi") {
        butuh(a, 2, "kombinasi <n> <k>");
        int n = static_cast<int>(ke_angka(a[1])), k = static_cast<int>(ke_angka(a[2]));
        u64 hasil = kombinasi(n, k);
        std::cout << "C(" << n << "," << k << ") = " << hasil << "\n";
    } else if (cmd == "ackermann") {
        butuh(a, 2, "ackermann <m> <n>");
        long long m = ke_angka(a[1]), n = ke_angka(a[2]);
        if (m < 0 || n < 0) throw std::invalid_argument("ackermann: m dan n harus >= 0");
        u64 hasil = ackermann(static_cast<u64>(m), static_cast<u64>(n));
        std::cout << "A(" << m << "," << n << ") = " << hasil << "\n";
    } else if (cmd == "hanoi") {
        butuh(a, 1, "hanoi <n>");
        int n = static_cast<int>(ke_angka(a[1]));
        auto langkah = hanoi(n);
        const std::size_t batas = 64;
        for (std::size_t i = 0; i < langkah.size() && i < batas; ++i)
            std::cout << (i + 1) << ". pindahkan cakram " << langkah[i].cakram << " dari "
                      << langkah[i].dari << " ke " << langkah[i].ke << "\n";
        if (langkah.size() > batas) std::cout << "... (" << langkah.size() - batas << " langkah lagi)\n";
        std::cout << "Total: " << langkah.size() << " langkah\n";
    } else if (cmd == "permutasi") {
        butuh(a, 1, "permutasi <teks>");
        if (a[1].size() > 8) throw std::invalid_argument("permutasi: maksimal 8 karakter");
        auto hasil = permutasi(a[1]);
        for (const auto& s : hasil) std::cout << s << "\n";
        std::cout << "Total: " << hasil.size() << " permutasi unik\n";
    } else if (cmd == "subset") {
        butuh(a, 1, "subset <teks>");
        if (a[1].size() > 10) throw std::invalid_argument("subset: maksimal 10 karakter");
        auto hasil = himpunan_bagian(a[1]);
        for (const auto& s : hasil) {
            std::cout << "{";
            for (std::size_t i = 0; i < s.size(); ++i) std::cout << (i ? "," : "") << s[i];
            std::cout << "}\n";
        }
        std::cout << "Total: " << hasil.size() << " himpunan bagian\n";
    } else if (cmd == "balik") {
        butuh(a, 1, "balik <teks>");
        std::cout << balik(gabung(a, 1)) << "\n";
    } else if (cmd == "palindrom") {
        butuh(a, 1, "palindrom <teks>");
        std::string s = gabung(a, 1);
        std::cout << "\"" << s << "\" " << (palindrom(s) ? "adalah" : "bukan") << " palindrom\n";
    } else if (cmd == "cari") {
        butuh(a, 2, "cari <target> <a1 a2 ...>");
        long long target = ke_angka(a[1]);
        auto v = baca_larik(a, 2);
        long idx = cari_biner(v, target);
        if (idx >= 0) std::cout << target << " ditemukan pada indeks " << idx << "\n";
        else std::cout << target << " tidak ditemukan\n";
    } else if (cmd == "jumlah") {
        butuh(a, 1, "jumlah <a1 a2 ...>");
        std::cout << "jumlah = " << jumlah_larik(baca_larik(a, 1)) << "\n";
    } else if (cmd == "maks") {
        butuh(a, 1, "maks <a1 a2 ...>");
        std::cout << "maks = " << maks_larik(baca_larik(a, 1)) << "\n";
    } else if (cmd == "jejak") {
        butuh(a, 2, "jejak faktorial|fib <n>");
        int n = static_cast<int>(ke_angka(a[2]));
        if (a[1] == "faktorial") faktorial_jejak(n, std::cout);
        else if (a[1] == "fib") {
            if (n > 8) throw std::invalid_argument("jejak fib dibatasi n <= 8 agar output terbaca");
            fibonacci_jejak(n, std::cout);
        } else throw std::invalid_argument("Pemakaian: jejak faktorial|fib <n>");
    } else {
        throw std::invalid_argument("perintah '" + cmd + "' tidak dikenal. Ketik 'bantuan'.");
    }
    return true;
}

bool jalankan_aman(const Args& a) {
    try {
        return jalankan(a);
    } catch (const std::exception& e) {
        std::cerr << "Galat: " << e.what() << "\n";
        return true;
    }
}

}  // namespace

int main(int argc, char** argv) {
    if (argc > 1) {
        Args a(argv + 1, argv + argc);
        try {
            jalankan(a);
        } catch (const std::exception& e) {
            std::cerr << "Galat: " << e.what() << "\n";
            return 1;
        }
        return 0;
    }

    std::cout << "rekursif-tools - kalkulator rekursi C++. Ketik 'bantuan' untuk daftar perintah.\n";
    std::string baris;
    while (std::cout << "rekursif> " && std::getline(std::cin, baris)) {
        std::istringstream iss(baris);
        Args a;
        for (std::string t; iss >> t;) a.push_back(t);
        if (!jalankan_aman(a)) break;
    }
    std::cout << "\nSampai jumpa!\n";
    return 0;
}
