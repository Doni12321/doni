#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

class JejaringSosial {
private:
    string pengguna[MAX];
    int relasi[MAX][MAX];
    int jumlahPengguna;

public:
    void inputPengguna() {
        cout << "Masukkan jumlah pengguna (maks 10): ";
        cin >> jumlahPengguna;
        cin.ignore();

        for (int i = 0; i < jumlahPengguna; i++) {
            cout << "Nama pengguna ke-" << (i + 1) << ": ";
            getline(cin, pengguna[i]);
        }

        // Inisialisasi relasi ke 0
        for (int i = 0; i < jumlahPengguna; i++)
            for (int j = 0; j < jumlahPengguna; j++)
                relasi[i][j] = 0;

        int jmlRelasi;
        cout << "\nMasukkan jumlah pasangan pertemanan: ";
        cin >> jmlRelasi;

        cout << "Masukkan pasangan pertemanan (contoh: 1 2 artinya pengguna 1 berteman dengan pengguna 2):\n";
        for (int i = 0; i < jmlRelasi; i++) {
            int a, b;
            cin >> a >> b;
            if (a >= 1 && b >= 1 && a <= jumlahPengguna && b <= jumlahPengguna) {
                relasi[a - 1][b - 1] = 1;
            } else {
                cout << "Indeks pengguna tidak valid.\n";
            }
        }
    }

    void tampilkanMatriks() {
        cout << "\nMatriks Relasi Pertemanan:\n    ";
        for (int i = 0; i < jumlahPengguna; i++) {
            cout << i + 1 << " ";
        }
        cout << endl;

        for (int i = 0; i < jumlahPengguna; i++) {
            cout << i + 1 << " | ";
            for (int j = 0; j < jumlahPengguna; j++) {
                cout << relasi[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isSimetris() {
        for (int i = 0; i < jumlahPengguna; i++) {
            for (int j = 0; j < jumlahPengguna; j++) {
                if (relasi[i][j] != relasi[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isRefleksif() {
        for (int i = 0; i < jumlahPengguna; i++) {
            if (relasi[i][i] != 1)
                return false;
        }
        return true;
    }

    bool isTransitif() {
        for (int i = 0; i < jumlahPengguna; i++) {
            for (int j = 0; j < jumlahPengguna; j++) {
                if (relasi[i][j]) {
                    for (int k = 0; k < jumlahPengguna; k++) {
                        if (relasi[j][k] && !relasi[i][k])
                            return false;
                    }
                }
            }
        }
        return true;
    }

    void cekSifatRelasi() {
        cout << "\nAnalisis Sifat Relasi Pertemanan:\n";
        cout << "Refleksif   : " << (isRefleksif() ? "Ya" : "Tidak") << endl;
        cout << "Simetris    : " << (isSimetris() ? "Ya" : "Tidak") << endl;
        cout << "Transitif   : " << (isTransitif() ? "Ya" : "Tidak") << endl;
    }
};

int main() {
    JejaringSosial js;
    js.inputPengguna();
    js.tampilkanMatriks();
    js.cekSifatRelasi();
    return 0;
}

