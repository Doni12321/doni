#include <iostream>
using namespace std;

// Fungsi untuk mengubah nilai variabel menggunakan pointer
void ubahNilai(int* x) {
    *x = 20; // Mengubah nilai yang ditunjuk oleh pointer
}

int main() {
    int a = 10;
    cout << "Sebelum fungsi: " << a << endl; // Output: 10

    ubahNilai(&a); // Mengirim alamat dari a ke fungsi
    cout << "Setelah fungsi: " << a << endl; // Output: 20 (berubah)

    return 0;
}

