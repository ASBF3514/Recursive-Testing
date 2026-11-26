// Unit test ringan tanpa dependensi eksternal.
#include <iostream>
#include <sstream>

#include "rekursif/deret.hpp"
#include "rekursif/hanoi.hpp"
#include "rekursif/jejak.hpp"
#include "rekursif/larik.hpp"
#include "rekursif/matematika.hpp"
#include "rekursif/teks.hpp"

using namespace rekursif;

static int gagal = 0, total = 0;
#define CEK(kond)                                                                   \
    do {                                                                            \
        ++total;                                                                    \
        if (!(kond)) { ++gagal; std::cerr << "GAGAL " << __FILE__ << ":" << __LINE__ \
                                          << "  " #kond "\n"; }                    \
    } while (0)

template <class F>
static bool melempar(F f) {
    try { f(); } catch (...) { return true; }
    return false;
}

int main() {
    // faktorial
    CEK(faktorial(0) == 1);
    CEK(faktorial(1) == 1);
    CEK(faktorial(5) == 120);
    CEK(faktorial(20) == 2432902008176640000ULL);
    CEK(melempar([] { faktorial(21); }));
    CEK(melempar([] { faktorial(-1); }));

    // fibonacci
    u64 c = 0;
    CEK(fibonacci_naif(10, c) == 55);
    CEK(c == 177);  // jumlah pemanggilan fib(10) = 2*F(11) - 1
    CEK(fibonacci_memo(0) == 0);
    CEK(fibonacci_memo(1) == 1);
    CEK(fibonacci_memo(50) == 12586269025ULL);
    CEK(fibonacci_memo(93) == 12200160415121876738ULL);
    CEK(melempar([] { fibonacci_memo(94); }));
    for (int i = 0; i <= 20; ++i) { u64 k = 0; CEK(fibonacci_naif(i, k) == fibonacci_memo(i)); }

    // pangkat, fpb, kpk
    CEK(pangkat(2, 10) == 1024.0);
    CEK(pangkat(2, -2) == 0.25);
    CEK(pangkat(5, 0) == 1.0);
    CEK(fpb(48, 18) == 6);
    CEK(fpb(-48, 18) == 6);
    CEK(fpb(7, 0) == 7);
    CEK(kpk(4, 6) == 12);
    CEK(kpk(0, 5) == 0);

    // digit, basis, collatz, kombinasi, ackermann
    CEK(jumlah_digit(12345) == 15);
    CEK(jumlah_digit(0) == 0);
    CEK(konversi_basis(10, 2) == "1010");
    CEK(konversi_basis(255, 16) == "FF");
    CEK(konversi_basis(0, 2) == "0");
    CEK(melempar([] { konversi_basis(5, 1); }));
    CEK(collatz(1) == 0);
    CEK(collatz(27) == 111);
    CEK(kombinasi(5, 2) == 10);
    CEK(kombinasi(10, 0) == 1);
    CEK(kombinasi(60, 30) == 118264581564861424ULL);
    CEK(melempar([] { kombinasi(3, 5); }));
    CEK(ackermann(2, 3) == 9);
    CEK(ackermann(3, 3) == 61);
    CEK(melempar([] { ackermann(4, 1); }));

    // teks
    CEK(balik("abc") == "cba");
    CEK(balik("") == "");
    CEK(palindrom("Kasur ini rusak"));
    CEK(palindrom("A man, a plan, a canal: Panama"));
    CEK(!palindrom("rekursi"));
    CEK(palindrom(""));
    CEK(permutasi("abc").size() == 6);
    CEK(permutasi("aab").size() == 3);
    CEK(permutasi("abc").front() == "abc" && permutasi("abc").back() == "cba");
    CEK(himpunan_bagian("abc").size() == 8);
    CEK(himpunan_bagian("").size() == 1);

    // hanoi
    CEK(hanoi(0).empty());
    CEK(hanoi(3).size() == 7);
    CEK(hanoi(10).size() == 1023);
    CEK(hanoi(1)[0].dari == 'A' && hanoi(1)[0].ke == 'C');

    // larik
    std::vector<int> v{1, 3, 5, 7, 9, 11};
    CEK(cari_biner(v, 7) == 3);
    CEK(cari_biner(v, 1) == 0);
    CEK(cari_biner(v, 11) == 5);
    CEK(cari_biner(v, 4) == -1);
    CEK(cari_biner(std::vector<int>{}, 1) == -1);
    CEK(jumlah_larik(v) == 36);
    CEK(maks_larik(v) == 11);
    CEK(melempar([] { maks_larik(std::vector<int>{}); }));

    // jejak
    std::ostringstream os;
    CEK(faktorial_jejak(3, os) == 6);
    CEK(os.str().find("faktorial(1)") != std::string::npos);
    std::ostringstream os2;
    CEK(fibonacci_jejak(4, os2) == 3);

    std::cout << (total - gagal) << "/" << total << " pengujian lulus\n";
    return gagal == 0 ? 0 : 1;
}
