#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> n;
    cin.ignore();  // membersihkan newline setelah input angka

    string* nama = new string[n];
    int* nilai = new int[n];

    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "Masukkan nama mahasiswa ke-" << i+1 << ": ";
        getline(cin, *(nama + i));
        cout << "Masukkan nilai mahasiswa ke-" << i+1 << ": ";
        cin >> *(nilai + i);
        cin.ignore();
    }

    // Menghitung rata-rata
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += *(nilai + i);
    }
    double rata_rata = (double) total / n;

    cout << "\nRata-rata nilai: " << rata_rata << endl;
    cout << "Mahasiswa dengan nilai di atas rata-rata:\n";

    // Menampilkan mahasiswa dengan nilai di atas rata-rata
    for (int i = 0; i < n; i++) {
        if (*(nilai + i) > rata_rata) {
            cout << *(nama + i) << " dengan nilai " << *(nilai + i) << endl;
        }
    }

    // Menghapus memory yang dialokasikan
    delete[] nama;
    delete[] nilai;

    return 0;
}

