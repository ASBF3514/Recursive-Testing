# rekursif-tools

Kumpulan alat **menghitung dan memvisualisasikan rekursi** dalam C++17. Berisi pustaka *header-only* yang bisa dipakai di proyek lain, CLI interaktif, unit test, dan CI GitHub Actions. Cocok untuk belajar, mengajar, atau referensi cepat algoritma rekursif klasik.

## Fitur

| Kategori | Fungsi | Catatan |
|---|---|---|
| Matematika | `faktorial`, `pangkat`, `fpb`, `kpk`, `jumlah_digit`, `konversi_basis`, `collatz`, `kombinasi`, `ackermann` | `pangkat` memakai divide and conquer O(log n) |
| Deret | `fibonacci_naif`, `fibonacci_memo` | naif menghitung jumlah pemanggilan; memo O(n) |
| Teks | `balik`, `palindrom`, `permutasi`, `himpunan_bagian` | permutasi unik dan terurut |
| Hanoi | `hanoi(n)` | mengembalikan daftar langkah (2^n - 1) |
| Larik | `cari_biner`, `jumlah_larik`, `maks_larik` | template, berlaku untuk tipe apa pun |
| Visualisasi | `faktorial_jejak`, `fibonacci_jejak` | mencetak pohon pemanggilan berindentasi |

## Struktur

```
rekursif-tools/
├── include/rekursif/   # pustaka header-only
│   ├── matematika.hpp  deret.hpp  teks.hpp
│   ├── hanoi.hpp       larik.hpp  jejak.hpp
├── src/main.cpp        # CLI
├── tests/test_rekursif.cpp
├── CMakeLists.txt  Makefile
└── .github/workflows/ci.yml
```

## Build

Butuh kompilator C++17 (g++ 7+, clang 5+, MSVC 2017+).

```bash
# Opsi 1: Make
make          # membangun build/rekursif
make test     # menjalankan unit test
make run      # membuka mode interaktif

# Opsi 2: CMake (Linux/macOS/Windows)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

## Memakai CLI

Mode perintah tunggal:

```console
$ ./build/rekursif faktorial 10
10! = 3628800
$ ./build/rekursif fib 40 naif
fib(40) = 102334155  [331160281 pemanggilan]
$ ./build/rekursif fib 90
fib(90) = 2880067194370816120
$ ./build/rekursif basis 255 2
255 (basis 10) = 11111111 (basis 2)
$ ./build/rekursif jejak faktorial 3
faktorial(3)
  faktorial(2)
    faktorial(1)
    => 1
  => 2
=> 6
```

Tanpa argumen, program masuk **mode interaktif** (`rekursif>`). Ketik `bantuan` untuk daftar lengkap perintah, dan `keluar` untuk berhenti.

Perintah yang tersedia: `faktorial`, `fib`, `banding`, `pangkat`, `fpb`, `kpk`, `digit`, `basis`, `collatz`, `kombinasi`, `ackermann`, `hanoi`, `permutasi`, `subset`, `balik`, `palindrom`, `cari`, `jumlah`, `maks`, `jejak`.

`banding <n>` memperlihatkan mengapa memoization penting: pada n = 35, versi naif butuh sekitar 30 juta pemanggilan, sedangkan versi memo hanya O(n).

## Memakai sebagai pustaka

Salin folder `include/rekursif` ke proyek Anda (atau `target_link_libraries(proyek PRIVATE rekursif)` bila memakai CMake):

```cpp
#include <iostream>
#include "rekursif/matematika.hpp"
#include "rekursif/hanoi.hpp"

int main() {
    std::cout << rekursif::faktorial(5) << "\n";          // 120
    std::cout << rekursif::hanoi(3).size() << " langkah\n"; // 7 langkah
}
```

## Batas dan penanganan galat

Fungsi melempar `std::invalid_argument` untuk input tidak valid dan `std::overflow_error` bila hasil melebihi `uint64_t`:

| Fungsi | Batas |
|---|---|
| `faktorial` | n <= 20 |
| `fibonacci_*` | n <= 93 (versi naif di CLI dibatasi n <= 45) |
| `kombinasi` | n <= 60 |
| `ackermann` | m <= 3, n <= 10 |
| `collatz` | n <= 1e12 |
| `hanoi` | n <= 20 |

## Kompleksitas

| Algoritma | Waktu | Kedalaman rekursi |
|---|---|---|
| `faktorial`, `jumlah_digit`, `balik` | O(n) | O(n) |
| `fibonacci_naif` | O(2^n) | O(n) |
| `fibonacci_memo` | O(n) | O(n) |
| `pangkat` | O(log n) | O(log n) |
| `fpb` | O(log min(a,b)) | O(log min(a,b)) |
| `cari_biner` | O(log n) | O(log n) |
| `hanoi` | O(2^n) | O(n) |
| `permutasi` | O(n! * n) | O(n) |
| `himpunan_bagian` | O(2^n * n) | O(n) |

## Menambah fungsi baru

1. Tambahkan fungsi `inline` (atau template) pada header yang sesuai di `include/rekursif/`.
2. Tambahkan pengujian dengan makro `CEK(...)` di `tests/test_rekursif.cpp`.
3. Daftarkan perintahnya di `jalankan()` dan `bantuan()` pada `src/main.cpp`.
4. Jalankan `make test`.

## Lisensi

MIT. Lihat berkas `LICENSE`.
