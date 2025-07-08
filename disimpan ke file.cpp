#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
	ofstream file("output.txt");
	
	if(!file.is_open()){
		cout << "Gagal membuka file untuk menulis.";
		return 1;
	}
	
	string nama;
	int umur;
	
	cout << "Masukkan nama: ";
	getline(cin, nama);
	cout << "Masukkan umur: ";
	cin >> umur;
	
	file << "Nama: " << nama << endl;
	file << "Umur: " << umur << endl;
	
	cout << "Data berhasil disimpan ke output.txt" << endl;
	return 0;
}
