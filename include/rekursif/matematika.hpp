// Fungsi matematika rekursif.
#pragma once
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace rekursif {

using u64 = std::uint64_t;

// n! (0 <= n <= 20, batas aman untuk u64).
inline u64 faktorial(int n) {
    if (n < 0) throw std::invalid_argument("faktorial: n tidak boleh negatif");
    if (n > 20) throw std::overflow_error("faktorial: n > 20 melebihi batas u64");
    return n <= 1 ? 1 : static_cast<u64>(n) * faktorial(n - 1);
}

// a^n dengan metode "pangkat cepat" (divide and conquer), O(log n).
inline double pangkat(double a, long long n) {
    if (n < 0) return 1.0 / pangkat(a, -n);
    if (n == 0) return 1.0;
    double setengah = pangkat(a, n / 2);
    return (n % 2 == 0) ? setengah * setengah : setengah * setengah * a;
}

// Faktor Persekutuan Terbesar (algoritma Euclid).
inline long long fpb(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return b == 0 ? a : fpb(b, a % b);
}

// Kelipatan Persekutuan Terkecil.
inline long long kpk(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    long long g = fpb(a, b);
    long long hasil = (a / g) * b;
    return hasil < 0 ? -hasil : hasil;
}

// Jumlah digit dari n, mis. 12345 -> 15.
inline u64 jumlah_digit(u64 n) {
    return n < 10 ? n : (n % 10) + jumlah_digit(n / 10);
}

// Konversi bilangan ke basis 2..36, mis. (10, 2) -> "1010".
inline std::string konversi_basis(u64 n, int basis) {
    if (basis < 2 || basis > 36) throw std::invalid_argument("basis harus 2..36");
    static const char* digit = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (n < static_cast<u64>(basis)) return std::string(1, digit[n]);
    return konversi_basis(n / basis, basis) + digit[n % basis];
}

// Jumlah langkah Collatz sampai mencapai 1.
inline u64 collatz(u64 n) {
    if (n == 0) throw std::invalid_argument("collatz: n harus >= 1");
    if (n > 1000000000000ULL) throw std::overflow_error("collatz: n terlalu besar (maks 1e12)");
    if (n == 1) return 0;
    return 1 + collatz(n % 2 == 0 ? n / 2 : 3 * n + 1);
}

namespace detail {
inline u64 ackermann_dalam(u64 m, u64 n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermann_dalam(m - 1, 1);
    return ackermann_dalam(m - 1, ackermann_dalam(m, n - 1));
}
}  // namespace detail

// Fungsi Ackermann (tumbuh sangat cepat, input dibatasi m <= 3 dan n <= 10).
inline u64 ackermann(u64 m, u64 n) {
    if (m > 3 || n > 10) throw std::overflow_error("ackermann: dibatasi m <= 3 dan n <= 10");
    return detail::ackermann_dalam(m, n);
}

namespace detail {
inline u64 kombinasi_memo(int n, int k, std::vector<std::vector<u64>>& memo) {
    if (k == 0 || k == n) return 1;
    u64& sel = memo[n][k];
    if (sel != 0) return sel;
    return sel = kombinasi_memo(n - 1, k - 1, memo) + kombinasi_memo(n - 1, k, memo);
}
}  // namespace detail

// C(n, k) lewat identitas Pascal C(n,k) = C(n-1,k-1) + C(n-1,k), dengan memoization.
inline u64 kombinasi(int n, int k) {
    if (n < 0 || k < 0 || k > n) throw std::invalid_argument("kombinasi: syarat 0 <= k <= n");
    if (n > 60) throw std::overflow_error("kombinasi: n > 60 melebihi batas u64");
    std::vector<std::vector<u64>> memo(n + 1, std::vector<u64>(k + 1, 0));
    return detail::kombinasi_memo(n, k, memo);
}

}  // namespace rekursif
