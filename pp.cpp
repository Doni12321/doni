#include <iostream>
#include <string>
using namespace std;

int login(){
	string username = "admin";
	int password = 1994;
	
	string username;
	int password;
	
	cout << "Masukkan Username\n";
	cin >> Username;
	cout << "Masukkan Password\n";
	cin >> Password;
	
		if(Username != username){
		cout << "Username yang anda masukkan salah...!";
		cout << "\n\n";
		system("pause");
		system("cls");
		login();
	}
	else if(Password != password){
		cout << "Password yang anda masukkan salah...!";
		cout << "\n\n";
		system("pause");
		system("cls");
		login();
	}
	else{
		cout << "\n";
		cout << "Anda Berhasil Login";
		cout << "\n\n";
		system("pause");
		system("cls");
	}
}

int kapasitas(){
	cout << "Besar\n";
	cin >> Besar;
	cout << "Nyaman\n";
	cin >> Nyaman;
}

int lokasi(){
	cout << "Bertingkat\n";
	cin >> Bertingkat;
	cout << "Berbaris dengan kelas lain\n";
	cin >> Berbaris dengan kelas lain;
	cout << "Dilantai yang berbeda\n";
	cin >> Dilantai yang berbeda;
}

int fasilitas(){
	cout << "Meja/n";
	cin >> Meja;
	cout << "Kursi\n";
	cin >> Kursi;
	cout << "Proyektor\n";
	cin >> Proyektor;
	cout << "Ac\n";
	cin >> Ac;
	cout << "Papan tulis\n";
	cin >> Papan tulis;
	cout << "Jendela\n";
	cin >> Jendela;
	cout << "Hordeng\n";
	cin >> Hordeng;
	cout << "Speaker\n";
	cin >> Speaker;
	cout << "Mic\n";
	cin >> Mic;
	cout << "Lampu\n";
	cin >> Lampu;
}

int main(){
	string username;
	int password;
	int kapasitas;
	int lokasi;
	int fasilitas;
	
}

