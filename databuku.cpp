#include <iostream>
#include <string>
using namespace std;

class Buku {
public:
    string judul;
    string pengarang;
    int tahun;

    void tampil() {
        cout << "Judul     : " << judul << endl;
        cout << "Pengarang : " << pengarang << endl;
        cout << "Tahun     : " << tahun << endl;
        cout << "---------------------------\n";
    }
};

int main() {
    const int JUMLAH = 2;
    Buku koleksi[JUMLAH];  // Array of class

    // Input data buku
    for (int i = 0; i < JUMLAH; i++) {
        cout << "\nData Buku ke-" << i + 1 << endl;
        cout << "Judul     : "; getline(cin, koleksi[i].judul);
        cout << "Pengarang : "; getline(cin, koleksi[i].pengarang);
        cout << "Tahun     : "; cin >> koleksi[i].tahun;
        cin.ignore(); // newline clear
    }

    // Tampilkan data
    cout << "\n===== KOLEKSI BUKU =====\n";
    for (int i = 0; i < JUMLAH; i++) {
        koleksi[i].tampil();  // Memanggil method dalam class
    }

    return 0;
}

