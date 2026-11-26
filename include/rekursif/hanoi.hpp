// Menara Hanoi.
#pragma once
#include <stdexcept>
#include <vector>

namespace rekursif {

struct Langkah {
    int cakram;
    char dari;
    char ke;
};

namespace detail {
inline void hanoi_dalam(int n, char dari, char ke, char bantu, std::vector<Langkah>& hasil) {
    if (n == 0) return;
    hanoi_dalam(n - 1, dari, bantu, ke, hasil);
    hasil.push_back({n, dari, ke});
    hanoi_dalam(n - 1, bantu, ke, dari, hasil);
}
}  // namespace detail

// Daftar langkah memindahkan n cakram dari tiang A ke C (2^n - 1 langkah).
inline std::vector<Langkah> hanoi(int n) {
    if (n < 0 || n > 20) throw std::invalid_argument("hanoi: n harus 0..20");
    std::vector<Langkah> hasil;
    hasil.reserve((1u << n) - 1);
    detail::hanoi_dalam(n, 'A', 'C', 'B', hasil);
    return hasil;
}

}  // namespace rekursif
