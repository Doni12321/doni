#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

class Sekolah {
private:
    string siswa[MAX];
    string pelajaran[MAX];
    int relasi[MAX][MAX]; 
    int jumlahSiswa, jumlahPelajaran;

public:
    void inputData() {
        cout << "Masukkan jumlah siswa (maks 11): ";
        cin >> jumlahSiswa;
        cin.ignore();

        for (int i = 0; i < jumlahSiswa; i++) {
            cout << "Nama siswa ke-" << (i + 1) << ": ";
            getline(cin, siswa[i]);
        }

        cout << "\nMasukkan jumlah mata pelajaran (maks 11): ";
        cin >> jumlahPelajaran;
        cin.ignore();

        for (int i = 0; i < jumlahPelajaran; i++) {
            cout << "Nama pelajaran ke-" << (i + 1) << ": ";
            getline(cin, pelajaran[i]);
        }

        for (int i = 0; i < jumlahSiswa; i++)
            for (int j = 0; j < jumlahPelajaran; j++)
                relasi[i][j] = 0;

        int totalRelasi;
        cout << "\nMasukkan jumlah relasi siswa-mata pelajaran: ";
        cin >> totalRelasi;

        cout << "Masukkan relasi (format: nomor_siswa nomor_pelajaran):\n";
        for (int i = 0; i < totalRelasi; i++) {
            int s, p;
            cin >> s >> p;
            if (s >= 1 && s <= jumlahSiswa && p >= 1 && p <= jumlahPelajaran)
                relasi[s - 1][p - 1] = 1;
            else
                cout << "Indeks tidak valid.\n";
        }
    }

    void tampilkanMatriks() {
        cout << "\nMatriks Relasi (Siswa ? Mata Pelajaran):\n    ";
        for (int j = 0; j < jumlahPelajaran; j++) {
            cout << j + 1 << " ";
        }
        cout << endl;

        for (int i = 0; i < jumlahSiswa; i++) {
            cout << i + 1 << " | ";
            for (int j = 0; j < jumlahPelajaran; j++) {
                cout << relasi[i][j] << " ";
            }
            cout << endl;
        }
    }

    void tampilkanRelasi() {
        cout << "\nDaftar Siswa dan Mata Pelajaran yang Diambil:\n";
        for (int i = 0; i < jumlahSiswa; i++) {
            cout << siswa[i] << " mengambil: ";
            bool ada = false;
            for (int j = 0; j < jumlahPelajaran; j++) {
                if (relasi[i][j]) {
                    cout << pelajaran[j] << ", ";
                    ada = true;
                }
            }
            if (!ada)
                cout << "Tidak mengambil pelajaran";
            cout << endl;
        }
    }

    bool isTotalRelasi() {
        for (int i = 0; i < jumlahSiswa; i++) {
            bool found = false;
            for (int j = 0; j < jumlahPelajaran; j++)
                if (relasi[i][j])
                    found = true;
            if (!found) return false;
        }
        return true;
    }

    bool isFungsi() {
        for (int i = 0; i < jumlahSiswa; i++) {
            int count = 0;
            for (int j = 0; j < jumlahPelajaran; j++)
                if (relasi[i][j]) count++;
            if (count != 1)
                return false;
        }
        return true;
    }

    bool isSurjektif() {
        for (int j = 0; j < jumlahPelajaran; j++) {
            bool used = false;
            for (int i = 0; i < jumlahSiswa; i++)
                if (relasi[i][j])
                    used = true;
            if (!used) return false;
        }
        return true;
    }

    void analisaRelasi() {
        cout << "\nAnalisis Relasi:\n";
        cout << "Apakah semua siswa mengambil pelajaran? " << (isTotalRelasi() ? "Ya" : "Tidak") << endl;
        cout << "Apakah relasi adalah fungsi (1 siswa ? 1 pelajaran)? " << (isFungsi() ? "Ya" : "Tidak") << endl;
        cout << "Apakah relasi surjektif (semua pelajaran diambil)? " << (isSurjektif() ? "Ya" : "Tidak") << endl;
    }
};

int main() {
    Sekolah sekolah;
    sekolah.inputData();
    sekolah.tampilkanMatriks();
    sekolah.tampilkanRelasi();
    sekolah.analisaRelasi();
    return 0;
}

