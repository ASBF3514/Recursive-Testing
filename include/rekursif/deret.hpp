// Deret Fibonacci: versi naif (eksponensial) dan memoization (linear).
#pragma once
#include <stdexcept>
#include <vector>

#include "matematika.hpp"

namespace rekursif {

// Batas n agar F(n) muat dalam u64.
constexpr int FIB_MAKS = 93;

// Versi naif O(2^n). `panggilan` bertambah 1 setiap fungsi dipanggil.
inline u64 fibonacci_naif(int n, u64& panggilan) {
    if (n < 0 || n > FIB_MAKS) throw std::invalid_argument("fibonacci: n harus 0..93");
    ++panggilan;
    if (n < 2) return static_cast<u64>(n);
    return fibonacci_naif(n - 1, panggilan) + fibonacci_naif(n - 2, panggilan);
}

namespace detail {
inline u64 fib_memo(int n, std::vector<u64>& memo) {
    if (n < 2) return static_cast<u64>(n);
    if (memo[n] != 0) return memo[n];
    return memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
}
}  // namespace detail

// Versi memoization O(n).
inline u64 fibonacci_memo(int n) {
    if (n < 0 || n > FIB_MAKS) throw std::invalid_argument("fibonacci: n harus 0..93");
    std::vector<u64> memo(static_cast<std::size_t>(n) + 1, 0);
    return detail::fib_memo(n, memo);
}

}  // namespace rekursif
