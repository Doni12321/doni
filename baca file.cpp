#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("data.txt");

    if (!file.is_open()) {
        cout << "Gagal membuka file.\n";
        return 1;
    }

    string nama;
    int umur;

    while (file >> nama >> umur) {
        cout << "Nama: " << nama << ", Umur: " << umur << endl;
    }

    file.close();
    return 0;
}

