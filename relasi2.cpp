#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

class RumahSakit {
private:
    string pasien[MAX];
    string dokter[MAX];
    int relasi[MAX][MAX]; // baris: pasien, kolom: dokter
    int jumlahPasien, jumlahDokter;

public:
    void inputData() {
        cout << "Masukkan jumlah pasien (maks 10): ";
        cin >> jumlahPasien;
        cin.ignore();

        for (int i = 0; i < jumlahPasien; i++) {
            cout << "Nama pasien ke-" << (i + 1) << ": ";
            getline(cin, pasien[i]);
        }

        cout << "\nMasukkan jumlah dokter (maks 10): ";
        cin >> jumlahDokter;
        cin.ignore();

        for (int i = 0; i < jumlahDokter; i++) {
            cout << "Nama dokter ke-" << (i + 1) << ": ";
            getline(cin, dokter[i]);
        }

        // Inisialisasi relasi dengan 0
        for (int i = 0; i < jumlahPasien; i++)
            for (int j = 0; j < jumlahDokter; j++)
                relasi[i][j] = 0;

        int rel;
        cout << "\nMasukkan jumlah relasi pasien ke dokter: ";
        cin >> rel;

        cout << "Masukkan relasi (format: nomor_pasien nomor_dokter):\n";
        for (int i = 0; i < rel; i++) {
            int p, d;
            cin >> p >> d;
            if (p >= 1 && p <= jumlahPasien && d >= 1 && d <= jumlahDokter) {
                relasi[p - 1][d - 1] = 1;
            } else {
                cout << "Indeks tidak valid!\n";
            }
        }
    }

    void tampilkanMatriks() {
        cout << "\nMatriks Relasi (Pasien ke Dokter):\n    ";
        for (int i = 0; i < jumlahDokter; i++)
            cout << i + 1 << " ";
        cout << endl;

        for (int i = 0; i < jumlahPasien; i++) {
            cout << i + 1 << " | ";
            for (int j = 0; j < jumlahDokter; j++)
                cout << relasi[i][j] << " ";
            cout << endl;
        }
    }

    void tampilkanRelasiLangsung() {
        cout << "\nDaftar Pasien dan Dokternya:\n";
        for (int i = 0; i < jumlahPasien; i++) {
            cout << pasien[i] << " ditangani oleh: ";
            bool found = false;
            for (int j = 0; j < jumlahDokter; j++) {
                if (relasi[i][j]) {
                    cout << dokter[j] << " ";
                    found = true;
                }
            }
            if (!found) cout << "Belum ada dokter";
            cout << endl;
        }
    }

    bool isFungsi() {
        // Fungsi: Setiap pasien hanya ke 1 dokter
        for (int i = 0; i < jumlahPasien; i++) {
            int count = 0;
            for (int j = 0; j < jumlahDokter; j++)
                if (relasi[i][j]) count++;
            if (count != 1)
                return false;
        }
        return true;
    }

    bool isInjektif() {
        // Injektif: Tidak ada 2 pasien ke dokter yang sama
        for (int j = 0; j < jumlahDokter; j++) {
            int count = 0;
            for (int i = 0; i < jumlahPasien; i++)
                if (relasi[i][j]) count++;
            if (count > 1)
                return false;
        }
        return true;
    }

    bool isSurjektif() {
        // Surjektif: Semua dokter punya minimal 1 pasien
        for (int j = 0; j < jumlahDokter; j++) {
            bool found = false;
            for (int i = 0; i < jumlahPasien; i++) {
                if (relasi[i][j]) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return true;
    }

    void analisaSifatRelasi() {
        cout << "\nAnalisis Sifat Relasi Pasien-Dokter:\n";
        cout << "Apakah relasi fungsi (1 pasien ? 1 dokter)? " << (isFungsi() ? "Ya" : "Tidak") << endl;
        cout << "Apakah relasi injektif (1 dokter tidak melayani 2 pasien)? " << (isInjektif() ? "Ya" : "Tidak") << endl;
        cout << "Apakah relasi surjektif (semua dokter melayani)? " << (isSurjektif() ? "Ya" : "Tidak") << endl;
    }
};

int main() {
    RumahSakit rs;
    rs.inputData();
    rs.tampilkanMatriks();
    rs.tampilkanRelasiLangsung();
    rs.analisaSifatRelasi();
    return 0;
}

