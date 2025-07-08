#include <iostream>
#include <string>
using namespace std;

const int MAKS = 100;

// Struktur data mahasiswa
struct Mahasiswa {
    string nim;
    string nama;
};

// Fungsi untuk input data
void inputData(Mahasiswa data[], int& jumlah) {
    cout << "Masukkan jumlah data mahasiswa (minimal 5): ";
    cin >> jumlah;
    cin.ignore();

    while (jumlah < 5) {
        cout << "Jumlah minimal 5 data! Masukkan ulang: ";
        cin >> jumlah;
        cin.ignore();
    }

    for (int i = 0; i < jumlah; i++) {
        cout << "\nData Mahasiswa ke-" << i + 1 << endl;
        cout << "NIM   : "; getline(cin, data[i].nim);
        cout << "Nama  : "; getline(cin, data[i].nama);
    }
}

// Fungsi untuk menampilkan data
void tampilkanData(Mahasiswa data[], int jumlah) {
    cout << "\n===== DAFTAR MAHASISWA =====\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "NIM   : " << data[i].nim << endl;
        cout << "Nama  : " << data[i].nama << endl;
        cout << "---------------------------\n";
    }
}

// Fungsi untuk mengurutkan data berdasarkan NIM (ascending)
void sortNIM(Mahasiswa data[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (data[j].nim > data[j + 1].nim) {
                swap(data[j], data[j + 1]);
            }
        }
    }
    cout << "Data berhasil diurutkan berdasarkan NIM (Ascending).\n";
}

// Fungsi binary search berdasarkan NIM
int binarySearch(Mahasiswa data[], int jumlah, string cariNIM) {
    int kiri = 0, kanan = jumlah - 1;

    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;

        if (data[tengah].nim == cariNIM)
            return tengah;
        else if (data[tengah].nim < cariNIM)
            kiri = tengah + 1;
        else
            kanan = tengah - 1;
    }
    return -1; // Tidak ditemukan
}

int main() {
    Mahasiswa data[MAKS];
    int jumlah;
    int pilihan;

    inputData(data, jumlah);

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Tampilkan Data Mahasiswa\n";
        cout << "2. Urutkan NIM (Ascending)\n";
        cout << "3. Cari Mahasiswa Berdasarkan NIM\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tampilkanData(data, jumlah);
                break;
            case 2:
                sortNIM(data, jumlah);
                break;
            case 3: {
                string cari;
                cout << "Masukkan NIM yang dicari: ";
                getline(cin, cari);

                // Urutkan dulu sebelum binary search
                sortNIM(data, jumlah);

                int index = binarySearch(data, jumlah, cari);
                if (index != -1) {
                    cout << "\nData Ditemukan:\n";
                    cout << "NIM   : " << data[index].nim << endl;
                    cout << "Nama  : " << data[index].nama << endl;
                } else {
                    cout << "Data dengan NIM " << cari << " tidak ditemukan.\n";
                }
                break;
            }
            case 0:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}

