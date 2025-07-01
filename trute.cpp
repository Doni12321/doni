#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nama;
    float nilai;
};

int main() {
    int jumlah;

    cout << "Masukkan jumlah mahasiswa: ";
    cin >> jumlah;

    // Alokasi dinamis array struct Mahasiswa
    Mahasiswa* mhs = new Mahasiswa[jumlah];

    float total = 0.0;

    // Input data mahasiswa
    for (int i = 0; i < jumlah; i++) {
        cout << "Masukkan nama mahasiswa ke-" << i + 1 << ": ";
        cin.ignore(); // Menghindari masalah getline setelah cin
        getline(cin, (mhs + i)->nama);

        cout << "Masukkan nilai " << (mhs + i)->nama << ": ";
        cin >> (mhs + i)->nilai;

        total += (mhs + i)->nilai;
    }

    float rata_rata = total / jumlah;

    cout << "\nRata-rata nilai: " << rata_rata << endl;

    cout << "\nMahasiswa dengan nilai di atas rata-rata:\n";
    for (int i = 0; i < jumlah; i++) {
        if ((mhs + i)->nilai > rata_rata) {
            cout << (mhs + i)->nama << " (" << (mhs + i)->nilai << ")" << endl;
        }
    }

    // Hapus memori yang dialokasikan
    delete[] mhs;

    return 0;
}

