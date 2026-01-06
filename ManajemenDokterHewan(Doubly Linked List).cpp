#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

struct Dokter{
	char nama[50];
	char spesialisasi[50];
	char jadwal[100];
	char kontak[50];
	Dokter* next;
	Dokter* prev;
};

const char* HARI[] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};

Dokter** daftarDokter = NULL;
int jumlahDokter = 0;
int kapasitas = 0;

// head untuk linked list pencarian
Dokter* headPencarian = NULL;
Dokter* tailPencarian = NULL;

// head untuk linked list antrian
Dokter* headAntrian = NULL;
Dokter* tailAntrian = NULL;

void toLower(char* str){
	for(int i = 0; str[i]; i++){
		str[i] = tolower(str[i]);
	}
}

void tambahDokterArray(Dokter* dokter) {
	if(jumlahDokter >= kapasitas){
		kapasitas = kapasitas == 0 ? 5 : kapasitas * 2;
		Dokter** newArray = new Dokter*[kapasitas];
		
		for (int i = 0; i < jumlahDokter; i++){
			newArray[i] = daftarDokter[i];
		}
		
		delete[] daftarDokter;
		daftarDokter = newArray;
	}
	
	daftarDokter[jumlahDokter] = dokter;
	jumlahDokter;
}

void tambahDokter(){
	Dokter* dokterBaru = new Dokter;
	
	cout << "Nama: ";
	cin.ignore();
	cin.getline(dokterBaru->nama, 50);
	
	cout << "Spesialisasi: ";
	cin.getline(dokterBaru->spesialisasi, 50);
	
	cout << "Jadwal Praktik: ";
	cin.getline(dokterBaru->jadwal, 100);
	
	cout << "Kontak: ";
	cin.getline(dokterBaru->kontak, 20);
	
	dokterBaru->next = NULL;
	dokterBaru->prev = NULL;
	
	tambahDokterArray(dokterBaru);
	
	// menambahkan ke doubly linked list untuk antrian
	if(headAntrian == NULL){
		headAntrian = dokterBaru;
		tailAntrian = dokterBaru;
		headAntrian->next = headAntrian;
		tailAntrian->prev = tailAntrian;
	} else {
		tailAntrian->next = dokterBaru;
		dokterBaru->prev = tailAntrian;
		dokterBaru->next = headAntrian;
		headAntrian->prev = dokterBaru;
		tailAntrian = dokterBaru;
	}
	
	cout << "Dokter berhasil ditambahkan!\n";
}

void editDokter(){
	if(jumlahDokter == 0){
		cout << "Tidak ada data dokter!\n";
		return;
	}
	
	char namaCari[50];
	cout << "Masukkan nama dokter yang akan diedit: ";
	cin.ignore();
	cin.getline(namaCari, 50);
	
	for(int i = 0; i < jumlahDokter; i++){
		if(strcmp(daftarDokter[i]->nama, namaCari) == 0) {
			cout << "Data ditemukan. Masukkan data baru:\n";
			
			cout << "Nama: ";
			cin.getline(daftarDokter[i]->nama, 50);
			
			cout << "Speasialisasi: ";
			cin.getline(daftarDokter[i]->spesialisasi, 50);
			
			cout << "Jadwal Praktik: ";
			cin.getline(daftarDokter[i]->jadwal, 100);
			
			cout << "Kontak: ";
			cin.getline(daftarDokter[i]->kontak, 20);
			
			cout << "Data berhasil diupdate!\n";
			return;
		}
	}
	
	cout << "Dokter tidak ditemukan!\n";
}

void hapusDokter(){
	if(jumlahDokter == 0){
		cout << "Tidak ada data dokter!\n";
		return;
	}
	
	char namaCari[50];
	cout << "Masukkan nama dokter yang akan dihapus: ";
	cin.ignore();
	cin.getline(namaCari, 50);
	
	for(int i = 0; i < jumlahDokter; i++){
		if(strcmp(daftarDokter[i]->nama, namaCari) == 0){
			// hapus dari doubly linked list antrian jika ada
			Dokter* current = headAntrian;
			if(current != NULL){
				do{
					if (current == daftarDokter[i]) {
                        if (current == headAntrian && current == tailAntrian) {
                            // Hanya satu elemen dalam list
                            headAntrian = NULL;
                            tailAntrian = NULL;
                        } else if (current == headAntrian) {
                            // Hapus dari awal
                            headAntrian = headAntrian->next;
                            headAntrian->prev = tailAntrian;
                            tailAntrian->next = headAntrian;
                        } else if (current == tailAntrian) {
                            // Hapus dari akhir
                            tailAntrian = tailAntrian->prev;
                            tailAntrian->next = headAntrian;
                            headAntrian->prev = tailAntrian;
                        } else {
                            // Hapus dari tengah
                            current->prev->next = current->next;
                            current->next->prev = current->prev;
						}
						break;
					}
					current = current->next;
				} while(current != headAntrian);
			}
			
			delete daftarDokter[i];
			
			for(int j = 0; j < jumlahDokter - 1; j++){
				daftarDokter[j] = daftarDokter[j + 1];
			}
			
			jumlahDokter--;
			cout << "Dokter berhasil dihapus!\n";
			return;
		}
	}
	
	cout << "Dokter tidak ditemukan!\n";
}

void tambahKePencarian(Dokter* dokter){
	Dokter* newNode = new Dokter;
	*newNode = *dokter;
	newNode->next = headPencarian;
	newNode->prev = NULL;
	
	if(headPencarian != NULL){
		headPencarian->prev = newNode;
	} else {
		tailPencarian = newNode;
	}
	
	headPencarian = newNode;
}

void cariBerdasarkanNama(){
	if(jumlahDokter == 0) {
		cout << "Tidak ada data dokter!\n";
		return;
	}
	
	char namaCari[50];
	cout << "Masukkan nama dokter: ";
	cin.ignore();
	cin.getline(namaCari, 50);
	
	char namaCariLower[50];
	strcpy(namaCariLower, namaCari);
	toLower(namaCariLower);
	
	bool ditemukan = false;
	
	for(int i = 0; i < jumlahDokter; i++){
		char namaDokterLower[50];
		strcpy(namaDokterLower, daftarDokter[i]->nama);
		toLower(namaDokterLower);
		
		if(strstr(namaDokterLower, namaCariLower) != NULL){
			if(!ditemukan){
				cout << "\nHasil pencarian:\n";
				cout << "=====================================\n";
				ditemukan = true;
			}
			
			cout << "Nama: " << daftarDokter[i]->nama << endl;
			cout << "Spesialisasi: " << daftarDokter[i]->spesialisasi << endl;
			cout << "Jadwal: " << daftarDokter[i]->jadwal << endl;
			cout << "Kontak: " << daftarDokter[i]->kontak << endl;
			cout << "=========================================\n";
			
			tambahKePencarian(daftarDokter[i]);
		}
	}
	
	if(!ditemukan){
		cout << "Dokter tidak ditemukan!\n";
	}
}

void cariBerdasarkanSpesialisasi(){
	if(jumlahDokter == 0){
		cout << "Tidak ada data dokter!\n";
		return;
	}
	
	char spesialisasiCari[50];
	cout << "Masukkan spesialisasi: ";
	cin.ignore();
	cin.getline(spesialisasiCari, 50);
	
	char spesialisasiCariLower[50];
	strcpy(spesialisasiCariLower, spesialisasiCari);
	toLower(spesialisasiCariLower);
	
	bool ditemukan = false;
	
	for(int i = 0; i < jumlahDokter; i++){
		char spesialisasiDokterLower[50];
		strcpy(spesialisasiDokterLower, daftarDokter[i]->spesialisasi);
		toLower(spesialisasiDokterLower);
		
		
		if(strstr(spesialisasiDokterLower, spesialisasiCariLower) != NULL) {
			if(!ditemukan){
				cout << "\nHasil pencarian:\n";
				cout << "==================================\n";
				ditemukan = true;
			}
			
			cout << "Nama: " << daftarDokter[i]->nama << endl;
			cout << "Spesialisasi: " << daftarDokter[i]->spesialisasi << endl;
			cout << "Jadwal: " << daftarDokter[i]->jadwal << endl;
			cout << "Kontak: " << daftarDokter[i]->kontak << endl;
			cout << "====================================\n";
			
			tambahKePencarian(daftarDokter[i]);
		}
	}
	
	if(!ditemukan){
		cout << "Dokter dengan spesialisasi tersebut tidak ditemukan!\n";
	}
}

void tampilkanDokterAktifHariIni(){
	if(jumlahDokter == 0){
		cout << "Tidak ada data dokter!\n";
		return;
	}
	
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int hariIni = ltm->tm_wday;
	
	int indexHari = (hariIni + 6) % 7;
	
	cout << "Dokter Aktif Hari Ini (" << HARI[indexHari] << "):\n";
	cout << "=========================================\n";
	
	bool adaDokterAktif = false;
	
	for(int i = 0; i < jumlahDokter; i++){
		char jadwalLower[100];
		strcpy(jadwalLower, daftarDokter[i]->jadwal);
		toLower(jadwalLower);
		
		char hariIniLower[20];
		strcpy(hariIniLower, HARI[indexHari]);
		toLower(hariIniLower);
		
		if(strstr(jadwalLower, hariIniLower) != NULL){
			cout << "Nama: " << daftarDokter[i]->nama << endl;
			cout << "Spesialisasi: " << daftarDokter[i]->spesialisasi << endl;
			cout << "Jadwal: " << daftarDokter[i]->jadwal << endl;
			cout << "Kontak: " << daftarDokter[i]->kontak << endl;
			adaDokterAktif = true;
		}
	}
	
	if(!adaDokterAktif){
		cout << "Tidak ada dokter yang aktif hari ini.\n";
	}
}

void tampilkanSemuaDokter(){
	if(jumlahDokter == 0){
		cout << "Tidak ada data dokter!\n";
		return;
	}
	
	cout << "Daftar Semua Dokter:\n";
	cout << "=====================================\n";
	
	for (int i = 0; i < jumlahDokter; i++){
		cout << "Dokter #" << i + 1 << endl;
        cout << "Nama: " << daftarDokter[i]->nama << endl;
        cout << "Spesialisasi: " << daftarDokter[i]->spesialisasi << endl;
        cout << "Jadwal: " << daftarDokter[i]->jadwal << endl;
        cout << "Kontak: " << daftarDokter[i]->kontak << endl;
        cout << "=========================================\n";
	}
}

void tampilkanRiwayatPencarian(){
	if(headPencarian == NULL){
		cout << "Belum ada riwayat pencarian!\n";
		return;
	}
	
	cout << "Riwayat pencarian (dari yang terbaru):\n";
	cout << "=========================================\n";
	
	Dokter* current = headPencarian;
	int counter = 1;
	
	while (current != NULL){
		cout << "Pencarian #" << counter << endl;
		cout << "Nama: " << current->nama << endl;
		cout << "Spesialisasi: " << current->spesialisasi << endl;
		cout << "Jadwal: " << current->jadwal << endl;
		cout << "Kontak: " << current->kontak << endl;
		cout << "=========================================\n";
		
		current = current->next;
		counter++;
	}
}

void tampilkanRiwayatPencarianTerbalik(){
	if(tailPencarian == NULL){
		cout << "Belum ada riwayat pencarian!\n";
		return;
	}
	
	cout << "Riwayat pencarian (dari yang terlama):\n";
	cout << "=========================================\n";
	
	Dokter* current = tailPencarian;
	int counter = 1;
	
	while(current != NULL){
		cout << "Pencarian #" << counter << endl;
		cout << "Nama: " << current->nama << endl;
		cout << "Spesialisasi: " << current->spesialisasi << endl;
		cout << "Jadwal: " << current->jadwal << endl;
		cout << "Kontak: " << current->kontak << endl;
		cout << "=========================================\n";
		
		current = current->prev;
		counter++;
	}
}

void tampilkanAntrian(){
	if(headAntrian == NULL){
		cout << "Tidak ada dokter dalam antrian!\n";
		return;
	}
	
	cout << "Antrian Dokter(circular Doubly Linked List):\n";
	cout << "=========================================\n";
	
	Dokter* current = headAntrian;
	int counter = 1;
	
	do {
		cout << "Antrian #" << counter << endl;
		cout << "Nama: " << current->nama << endl;
		cout << "Spesialisasi: " << current->spesialisasi << endl;
		cout << "Jadwal: " << current->jadwal << endl;
		cout << "Kontak: " << current->kontak << endl;
		cout << "=========================================\n";
		
		current = current->next;
		counter++; 
	} while (current != headAntrian);
}

void tampilkanAntrianTerbalik(){
	if(tailAntrian == NULL){
		cout << "Tidak ada dokter dalam antrian!\n";
		return;
	}
	
	cout << "Antrian Dokter (Terbalik - Circular Doubly Linked list):\n";
	cout << "=========================================\n";
	
	Dokter* current = tailAntrian;
	int counter = 1;
	
	do {
		cout << "Antrian #" << counter << endl;
		cout << "Nama: " << current->nama << endl;
		cout << "Spesialisasi: " << current->spesialisasi << endl;
		cout << "Jadwal: " << current->jadwal << endl;
		cout << "Kontak: " << current->kontak << endl;
		cout << "=========================================\n";
		
		current = current->prev;
		counter++;
	} while (current != tailAntrian);
}

void bersihkanMemory(){
	for(int i = 0; i < jumlahDokter; i++){
		delete daftarDokter[i];
	}
	
	delete[] daftarDokter;
	
	// hapus doubly linked list pencarian
	Dokter* current = headPencarian;
	while (current != NULL){
		Dokter* temp = current;
		current = current->next;
		delete temp;
	}
	
	headPencarian = NULL;
	tailPencarian = NULL;
	
	// hapus circular doubly linked list antrian
	if(headAntrian != NULL){
		tailAntrian->next = NULL;
		headAntrian->prev = NULL;
		
		current = headAntrian;
		while (current != NULL){
			Dokter* temp = current;
			current = current->next;
			delete temp;
		}
		
		headAntrian = NULL;
		tailAntrian = NULL;
	}
}

int main(){
	int pilihan;
	
	do {
		cout << "\n==== SISTEM MANAJEMEN DOKTER HEWAN (DOUBLY LINKED LIST) ====\n";
		cout << "1. Tambah Dokter\n";
		cout << "2. Edit Dokter\n";
		cout << "3. Hapus Dokter\n";
		cout << "4. Cari Dokter Berdasarkan Nama\n";
		cout << "5. Cari Dokter Berdasarkan Spesialisasi\n";
		cout << "6. Tampilkan Dokter Aktif Hari ini\n";
		cout << "7. Tampilkan Semua Dokter\n";
		cout << "8. Tampilkan Riwayat Pencarian (dari terbaru)\n";
		cout << "9. Tampilkan Riwayat Pencarian (dari terlama)\n";
		cout << "10. Tampilkan Antrian Dokter\n";
		cout << "11. Tampilkan Antrian Dokter (Terbalik)\n";
		cout << "0. Keluar\n";
		cout << "Pilihan: ";
		cin >> pilihan;
		
		switch (pilihan) {
			case 1:
				tambahDokter();
				break;
			case 2:
				editDokter();
				break;
			case 3:
				hapusDokter();
				break;
			case 4:
				cariBerdasarkanNama();
				break;
			case 5:
				cariBerdasarkanSpesialisasi();
				break;
			case 6:
				tampilkanDokterAktifHariIni;
				break;
			case 7:
				tampilkanSemuaDokter();
				break;
			case 8:
				tampilkanRiwayatPencarian();
				break;
			case 9:
				tampilkanRiwayatPencarianTerbalik();
				break;
			case 10:
				tampilkanAntrian();
				break;
			case 11:
				tampilkanAntrianTerbalik();
				break;
			case 0:
				cout << "Terima Kasih\n";
				break;
			default:
				cout << "Pilihan tidak valid\n";
		}
	} while (pilihan != 0);
	
	bersihkanMemory();
	return 0;
}
