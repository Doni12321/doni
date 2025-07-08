#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    int umur;
};

int main() {
    const int JUMLAH = 3;
    Mahasiswa data[JUMLAH];  // Array of struct

    // Input data mahasiswa
    for (int i = 0; i < JUMLAH; i++) {
        cout << "\nData Mahasiswa ke-" << i + 1 << endl;
        cout << "NIM   : "; getline(cin, data[i].nim);
        cout << "Nama  : "; getline(cin, data[i].nama);
        cout << "Umur  : "; cin >> data[i].umur;
        cin.ignore(); // membersihkan newline
    }

    // Tampilkan data mahasiswa
    cout << "\n===== DAFTAR MAHASISWA =====\n";
    for (int i = 0; i < JUMLAH; i++) {
        cout << "NIM   : " << data[i].nim << endl;
        cout << "Nama  : " << data[i].nama << endl;
        cout << "Umur  : " << data[i].umur << endl;
        cout << "---------------------------\n";
    }

    return 0;
}

