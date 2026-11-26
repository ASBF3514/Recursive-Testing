// Pelacak pohon pemanggilan: memperlihatkan bagaimana rekursi bekerja.
#pragma once
#include <ostream>
#include <string>

#include "deret.hpp"
#include "matematika.hpp"

namespace rekursif {

inline u64 faktorial_jejak(int n, std::ostream& os, int dalam = 0) {
    if (n < 0 || n > 20) throw std::invalid_argument("faktorial_jejak: n harus 0..20");
    const std::string indent(static_cast<std::size_t>(dalam) * 2, ' ');
    os << indent << "faktorial(" << n << ")\n";
    u64 hasil = n <= 1 ? 1 : static_cast<u64>(n) * faktorial_jejak(n - 1, os, dalam + 1);
    os << indent << "=> " << hasil << "\n";
    return hasil;
}

inline u64 fibonacci_jejak(int n, std::ostream& os, int dalam = 0) {
    if (n < 0 || n > FIB_MAKS) throw std::invalid_argument("fibonacci_jejak: n harus 0..93");
    const std::string indent(static_cast<std::size_t>(dalam) * 2, ' ');
    os << indent << "fib(" << n << ")\n";
    u64 hasil = n < 2 ? static_cast<u64>(n)
                      : fibonacci_jejak(n - 1, os, dalam + 1) + fibonacci_jejak(n - 2, os, dalam + 1);
    os << indent << "=> " << hasil << "\n";
    return hasil;
}

}  // namespace rekursif
