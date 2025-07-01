#include <iostream>
#include <string>
using namespace std;

class Mahasiswa {
private:
    string nama;
    float nilai;

public:
    // Constructor
    Mahasiswa(string n = "", float ni = 0.0) {
        nama = n;
        nilai = ni;
    }

    // Setter
    void setData(string n, float ni) {
        nama = n;
        nilai = ni;
    }

    // Getter
    string getNama() {
        return nama;
    }

    float getNilai() {
        return nilai;
    }

    // Fungsi untuk cek apakah nilai di atas rata-rata
    bool diAtasRataRata(float rata2) {
        return nilai > rata2;
    }
};

int main() {
    int jumlah;
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> jumlah;

    // Alokasi memori dengan pointer
    Mahasiswa* daftar = new Mahasiswa[jumlah];

    string nama;
    float nilai, total = 0.0;

    // Input data mahasiswa
    for (int i = 0; i < jumlah; i++) {
        cout << "Masukkan nama mahasiswa ke-" << i + 1 << ": ";
        cin.ignore();
        getline(cin, nama);
        cout << "Masukkan nilai: ";
        cin >> nilai;

        (daftar + i)->setData(nama, nilai);  // menggunakan pointer
        total += nilai;
    }

    float rata2 = total / jumlah;
    cout << "\nRata-rata nilai: " << rata2 << endl;

    cout << "\nMahasiswa dengan nilai di atas rata-rata:\n";
    for (int i = 0; i < jumlah; i++) {
        if ((daftar + i)->diAtasRataRata(rata2)) {
            cout << "- " << (daftar + i)->getNama() << " (" << (daftar + i)->getNilai() << ")\n";
        }
    }

    // Dealokasi memori
    delete[] daftar;

    return 0;
}

