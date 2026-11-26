// Operasi teks secara rekursif.
#pragma once
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace rekursif {

// Membalik string: "abc" -> "cba".
inline std::string balik(const std::string& s) {
    if (s.size() <= 1) return s;
    return balik(s.substr(1)) + s[0];
}

namespace detail {
inline bool palindrom_dalam(const std::string& s, long i, long j) {
    if (i >= j) return true;
    if (!std::isalnum(static_cast<unsigned char>(s[i]))) return palindrom_dalam(s, i + 1, j);
    if (!std::isalnum(static_cast<unsigned char>(s[j]))) return palindrom_dalam(s, i, j - 1);
    if (std::tolower(static_cast<unsigned char>(s[i])) != std::tolower(static_cast<unsigned char>(s[j])))
        return false;
    return palindrom_dalam(s, i + 1, j - 1);
}

inline void permutasi_dalam(const std::string& awalan, const std::string& sisa,
                            std::vector<std::string>& hasil) {
    if (sisa.empty()) {
        hasil.push_back(awalan);
        return;
    }
    for (std::size_t i = 0; i < sisa.size(); ++i) {
        if (i > 0 && sisa[i] == sisa[i - 1]) continue;  // lewati duplikat
        std::string baru = sisa;
        baru.erase(i, 1);
        permutasi_dalam(awalan + sisa[i], baru, hasil);
    }
}

inline void subset_dalam(const std::string& s, std::size_t i, std::string& saat,
                         std::vector<std::string>& hasil) {
    if (i == s.size()) {
        hasil.push_back(saat);
        return;
    }
    subset_dalam(s, i + 1, saat, hasil);  // tanpa s[i]
    saat.push_back(s[i]);
    subset_dalam(s, i + 1, saat, hasil);  // dengan s[i]
    saat.pop_back();
}
}  // namespace detail

// Palindrom, mengabaikan huruf besar/kecil, spasi, dan tanda baca.
inline bool palindrom(const std::string& s) {
    return detail::palindrom_dalam(s, 0, static_cast<long>(s.size()) - 1);
}

// Semua permutasi unik, terurut leksikografis.
inline std::vector<std::string> permutasi(std::string s) {
    std::sort(s.begin(), s.end());
    std::vector<std::string> hasil;
    detail::permutasi_dalam("", s, hasil);
    return hasil;
}

// Semua himpunan bagian (2^n) dari karakter-karakter s.
inline std::vector<std::string> himpunan_bagian(const std::string& s) {
    std::vector<std::string> hasil;
    std::string saat;
    detail::subset_dalam(s, 0, saat, hasil);
    return hasil;
}

}  // namespace rekursif
