// Operasi pada larik (vector) secara rekursif.
#pragma once
#include <stdexcept>
#include <vector>

namespace rekursif {

namespace detail {
template <class T>
long cari_biner_dalam(const std::vector<T>& v, const T& target, long kiri, long kanan) {
    if (kiri > kanan) return -1;
    long tengah = kiri + (kanan - kiri) / 2;
    if (v[tengah] == target) return tengah;
    return target < v[tengah] ? cari_biner_dalam(v, target, kiri, tengah - 1)
                              : cari_biner_dalam(v, target, tengah + 1, kanan);
}
template <class T>
T jumlah_dalam(const std::vector<T>& v, std::size_t i) {
    return i == v.size() ? T{} : v[i] + jumlah_dalam(v, i + 1);
}
template <class T>
T maks_dalam(const std::vector<T>& v, std::size_t i) {
    if (i + 1 == v.size()) return v[i];
    T sisa = maks_dalam(v, i + 1);
    return v[i] > sisa ? v[i] : sisa;
}
}  // namespace detail

// Pencarian biner; `v` harus terurut naik. Mengembalikan indeks atau -1.
template <class T>
long cari_biner(const std::vector<T>& v, const T& target) {
    return detail::cari_biner_dalam(v, target, 0, static_cast<long>(v.size()) - 1);
}

template <class T>
T jumlah_larik(const std::vector<T>& v) {
    return detail::jumlah_dalam(v, 0);
}

template <class T>
T maks_larik(const std::vector<T>& v) {
    if (v.empty()) throw std::invalid_argument("maks_larik: larik kosong");
    return detail::maks_dalam(v, 0);
}

}  // namespace rekursif
