#include <iostream>
#include <string>
using namespace std;

// Struktur data karyawan
struct Karyawan {
    string id;
    string nama;
    string jabatan;
    string no_telp;
};

// Fungsi untuk menampilkan semua data
void tampilkanData(Karyawan data[], int jumlah) {
    cout << "\n===== DATA KARYAWAN =====\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "ID      : " << data[i].id << endl;
        cout << "Nama    : " << data[i].nama << endl;
        cout << "Jabatan : " << data[i].jabatan << endl;
        cout << "No Telp : " << data[i].no_telp << endl;
        cout << "-----------------------------\n";
    }
}

// Sorting berdasarkan ID (ascending atau descending)
void sortID(Karyawan data[], int jumlah, bool ascending) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if ((ascending && data[j].id > data[j + 1].id) ||
                (!ascending && data[j].id < data[j + 1].id)) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

// Binary search berdasarkan ID
int binarySearch(Karyawan data[], int jumlah, string targetID) {
    int kiri = 0, kanan = jumlah - 1;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        if (data[tengah].id == targetID) {
            return tengah;
        } else if (data[tengah].id < targetID) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    return -1; // Tidak ditemukan
}

int main() {
    const int MAX = 100;
    Karyawan data[MAX];
    int jumlah;

    cout << "Masukkan jumlah data karyawan: ";
    cin >> jumlah;
    cin.ignore();

    // Input data
    for (int i = 0; i < jumlah; i++) {
        cout << "\nData Karyawan ke-" << i + 1 << endl;
        cout << "ID      : "; getline(cin, data[i].id);
        cout << "Nama    : "; getline(cin, data[i].nama);
        cout << "Jabatan : "; getline(cin, data[i].jabatan);
        cout << "No Telp : "; getline(cin, data[i].no_telp);
    }

    int pilihan;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Tampilkan Data Karyawan\n";
        cout << "2. Urutkan ID Ascending\n";
        cout << "3. Urutkan ID Descending\n";
        cout << "4. Cari Data Karyawan Berdasarkan ID\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tampilkanData(data, jumlah);
                break;
            case 2:
                sortID(data, jumlah, true);
                cout << "Data telah diurutkan secara ASCENDING.\n";
                break;
            case 3:
                sortID(data, jumlah, false);
                cout << "Data telah diurutkan secara DESCENDING.\n";
                break;
            case 4: {
                string cariID;
                cout << "Masukkan ID yang dicari: ";
                getline(cin, cariID);

                // Sebelum binary search, urutkan ASC
                sortID(data, jumlah, true);

                int hasil = binarySearch(data, jumlah, cariID);
                if (hasil != -1) {
                    cout << "\nData Ditemukan:\n";
                    cout << "ID      : " << data[hasil].id << endl;
                    cout << "Nama    : " << data[hasil].nama << endl;
                    cout << "Jabatan : " << data[hasil].jabatan << endl;
                    cout << "No Telp : " << data[hasil].no_telp << endl;
                } else {
                    cout << "Data dengan ID " << cariID << " tidak ditemukan.\n";
                }
                break;
            }
            case 0:
                cout << "Program selesai. Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}

