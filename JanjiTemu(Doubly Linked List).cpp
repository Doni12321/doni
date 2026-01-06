#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include <iomanip>
#include <cctype>

using namespace std;

enum Status { MENUNGGU, DITERIMA, SELESAI, DIBATALKAN };

struct JanjiTemu {
    string idHewan;
    string namaHewan;
    string jenisHewan;
    string pemilik;
    string dokter;
    string tanggal;
    string waktu;
    string keluhan;
    Status status;
    JanjiTemu* next;
    JanjiTemu* prev;
};

class petCompanyJanjiTemu {
private:
    JanjiTemu* head;
    JanjiTemu* tail;
    int totalJanji;
    
public:
    petCompanyJanjiTemu(){
        head = NULL;
        tail = NULL;
        totalJanji = 0;
    }
    
    ~petCompanyJanjiTemu(){
        bersihkanSemuaJanji();
    }
    
    string statusKestring(Status status) {
        switch(status) {
            case MENUNGGU: return "MENUNGGU";
            case DITERIMA: return "DITERIMA";
            case SELESAI: return "SELESAI";
            case DIBATALKAN: return "DIBATALKAN";
            default: return "TIDAK DIKETAHUI";
        }
    }
    
    string getTanggalHariIni() {
        time_t sekarang = time(0);
        tm* waktuLokal = localtime(&sekarang);
        
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y", waktuLokal);
        return string(buffer);
    }
    
    // fungsi untuk menambah janji temu baru
    void daftarJanjiTemu(){
        JanjiTemu* janjiBaru = new JanjiTemu;
        
        cout << "===================================================\n";
        cout << "            PENDAFTARAN JANJI TEMU BARU\n";
        cout << "===================================================\n";
        
        // menginput data hewan dan pemilik
        cout << "DATA HEWAN DAN PEMILIK\n";
        cout << " ID Hewan (unik): ";
        cin.ignore();
        getline(cin, janjiBaru->idHewan);
        
        if(cariJanjiByID(janjiBaru->idHewan) != NULL){
            cout << "\n ID hewan sudah terdaftar! Gunakan ID yang berbeda.\n";
            delete janjiBaru;
            return;
        }
        
        cout << " Nama Hewan: ";
        getline(cin, janjiBaru->namaHewan);
        
        cout << " Jenis Hewan (Anjing/Kucing/Kelinci/Burung/Dll): ";
        getline(cin, janjiBaru->jenisHewan);
        
        cout << " Nama Pemilik: ";
        getline(cin, janjiBaru->pemilik);
        
        // pilih Dokter
        cout << "\n PILIH DOKTER HEWAN\n";
        cout << "  1. Dr. Andi Wijaya (Spesialis Bedah)\n";
        cout << "  2. Dr. Budi Santoso (Spesialis Kulit & Alergi)\n";
        cout << "  3. Dr. Citra Dewi (Spesialis Gigi & Mulut)\n";
        cout << "  4. Dr. Dian Permata (Spesialis Umum & Vaksinasi)\n";
        cout << "  5. Dr. Eko Pratama (Spesialis Mata & THT)\n";
        cout << "  Pilihan (1-5): ";
        
        int pilihanDokter;
        cin >> pilihanDokter;
        
        // validasi input
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            janjiBaru->dokter = "Dr. Dian Permata (Spesialis Umum & Vaksinasi)";
        } else {
            switch(pilihanDokter){
                case 1: janjiBaru->dokter = "Dr. Andi Wijaya (Spesialis Bedah)";
                break;
                case 2: janjiBaru->dokter = "Dr. Budi Santoso (Spesialis Kulit & Alergi)";
                break;
                case 3: janjiBaru->dokter = "Dr. Citra Dewi (Spesialis Gigi & Mulut)";
                break;
                case 4: janjiBaru->dokter = "Dr. Dian Permata (Spesialis Umum & Vaksinasi)";
                break;
                case 5: janjiBaru->dokter = "Dr. Eko Pratama (Spesialis Mata & THT)";
                break;
                
                default:
                    cout << "Pilihan tidak valid! Dokter diatur ke default.\n";
                    janjiBaru->dokter = "Dr. Dian Permata (Spesialis Umum & Vaksinasi)";
            }
        }
        
        // menginput tanggal dan waktu
        cout << "\nTANGGAL DAN WAKTU\n";
        cout << "Tanggal Janji (DD-MM-YYYY): ";
        cin >> janjiBaru->tanggal;
        
        cout << "Waktu Janji (HH:MM): ";
        cin >> janjiBaru->waktu;
        
        // menginput sebuah keluhan
        cout << "\nKELUHAN\n";
        cout << "Deskripsi Keluhan: ";
        cin.ignore();
        getline(cin, janjiBaru->keluhan);
        
        janjiBaru->status = MENUNGGU;
        janjiBaru->next = NULL;
        janjiBaru->prev = NULL;
        
        tambahJanjiTerurut(janjiBaru);
        
        totalJanji++;
        cout << "\n=========================================================\n";
        cout << "PENDAFTARAN BERHASIL! Total janji: " << totalJanji << endl;
        cout << "=========================================================\n";
        
        cetakBuktiPendaftaran(janjiBaru);
    }
    
    void tambahJanjiTerurut(JanjiTemu* janjiBaru){
        // list kosong 
        if(head == NULL){
            head = janjiBaru;
            tail = janjiBaru;
            return;
        }
        
        JanjiTemu* current = head;
        
        while (current != NULL){
            // bandingkan tanggal dan waktu
            if(current->tanggal > janjiBaru->tanggal || (current->tanggal == janjiBaru->tanggal && current->waktu > janjiBaru->waktu)){
                if(current == head){
                    janjiBaru->next = head;
                    head->prev = janjiBaru;
                    head = janjiBaru;
                } else {
                    janjiBaru->prev = current->prev;
                    janjiBaru->next = current;
                    current->prev->next = janjiBaru;
                    current->prev = janjiBaru;
                }
                return;
            }
            current = current->next;
        }
        
        tail->next = janjiBaru;
        janjiBaru->prev = tail;
        tail = janjiBaru;
    }
    
    void cetakBuktiPendaftaran(JanjiTemu* janji){
        cout << "\n=====================================================\n";
        cout << "                PET COMPANY - BUKTI PENDAFTARAN\n";
        cout << "=====================================================\n";
        cout << left << setw(20) << "ID Hewan" << ": " << janji->idHewan << endl;
        cout << left << setw(20) << "Nama Hewan" << ": " << janji->namaHewan << endl;
        cout << left << setw(20) << "Jenis Hewan" << ": " << janji->jenisHewan << endl;
        cout << left << setw(20) << "Pemilik" << ": " << janji->pemilik << endl;
        cout << left << setw(20) << "Dokter" << ": " << janji->dokter << endl;
        cout << left << setw(20) << "Tanggal" << ": " << janji->tanggal << endl;
        cout << left << setw(20) << "Waktu" << ": " << janji->waktu << endl;
        cout << left << setw(20) << "Keluhan" << ": " << janji->keluhan << endl;
        cout << left << setw(20) << "Status" << ": " << statusKestring(janji->status) << endl;
        
        cout << "=====================================================\n";
        cout << " *Tunjukan bukti ini saat datang ke klinik\n";
        cout << " *Hubungi 1500-123 untuk informasi lebih lanjut*\n";
        cout << "=====================================================\n";
    }
    
    JanjiTemu* cariJanjiByID(string idHewan){
        JanjiTemu* current = head;
        
        while(current != NULL){
            if(current->idHewan == idHewan){
                return current;
            }
            current = current->next;
        }
        return NULL;
    }
    
    void perbaruiStatusJanji(){
        if(head == NULL){
            cout << "\nTidak ada janji temu yang terdaftar!\n";
            return;
        }
        
        string idHewan;
        cout << "====================================================\n";
        cout << "                PERBARUI STATUS JANJI TEMU\n";
        cout << "====================================================\n";
        cout << " Masukkan ID Hewan: ";
        cin.ignore();
        getline(cin, idHewan);
        
        JanjiTemu* janji = cariJanjiByID(idHewan);
        
        if(janji == NULL){
            cout << "\nJanji temu dengan ID " << idHewan << " tidak ditemukan!\n";
            return;
        }
        
        cout << "\nDATA DITEMUKAN:\n";
        cout << "  Nama Hewan : " << janji->namaHewan << endl;
        cout << "  Pemilik    : " << janji->pemilik << endl;
        cout << "  Dokter     : " << janji->dokter << endl;
        cout << "  Tanggal    : " << janji->tanggal << endl;
        cout << "  Waktu      : " << janji->waktu << endl;
        cout << "  Status     : " << statusKestring(janji->status) << endl;
        
        cout << "\nPILIH STATUS BARU:\n";
        cout << "  1. Menunggu\n";
        cout << "  2. Diterima\n";
        cout << "  3. Selesai\n";
        cout << "  4. Dibatalkan\n";
        cout << "  Pilihan (1-4): ";
        
        int pilihan;
        cin >> pilihan;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n? Input tidak valid!\n";
            return;
        }
        
        // Update status
        Status statusLama = janji->status;
        
        switch(pilihan){
            case 1: janji->status = MENUNGGU;
            break;
            case 2: janji->status = DITERIMA;
            break;
            case 3: janji->status = SELESAI;
            break;
            case 4: janji->status = DIBATALKAN;
            break;
            default:
                cout << "\nPilihan tidak valid!\n";
                return;
        }
        
        cout << "====================================================\n";
        cout << "STATUS BERHASIL DIPERBARUI!\n";
        cout << " Dari: " << statusKestring(statusLama) << endl;
        cout << " Menjadi: " << statusKestring(janji->status) << endl;
        cout << "====================================================\n";
    }
    
    // fungsi menampilkan semua janji temu (dari depan)
    void tampilkanSemuaJanji(){
        if(head == NULL){
            cout << "\nTidak ada janji temu yang terdaftar!\n";
            return;
        }
        
        cout << "\n====================================================\n";
        cout << "            DAFTAR SEMUA JANJI TEMU (DARI DEPAN)\n";
        cout << "====================================================\n";
        
        JanjiTemu* current = head;
        int nomor = 1;
        
        while(current != NULL){
            cout << "\n JANJI #" << nomor << ":\n";
            cout << left << setw(15) << "  ID Hewan" << ": " << current->idHewan << endl;
            cout << left << setw(15) << "  Nama Hewan" << ": " << current->namaHewan << endl;
            cout << left << setw(15) << "  Dokter" << ": " << current->dokter << endl;
            cout << left << setw(15) << "  Tanggal" << ": " << current->tanggal << endl;
            cout << left << setw(15) << "  Waktu" << ": " << current->waktu << endl;
            cout << left << setw(15) << "  Status" << ": " << statusKestring(current->status) << endl;
            cout << "====================================================\n";
            
            current = current->next;
            nomor++;
        }
        
        cout << "\n TOTAL JANJI: " << totalJanji << endl;
        cout << "====================================================\n";
    }
    
    void tampilkanSemuaJanjiTerbalik(){
        if(tail == NULL){
            cout << "\nTidak ada janji temu yang terdaftar!\n";
            return;
        }
        
        cout << "\n====================================================\n";
        cout << "            DAFTAR SEMUA JANJI TEMU (DARI BELAKANG)\n";
        cout << "====================================================\n";
        
        JanjiTemu* current = tail;
        int nomor = totalJanji;
        
        while(current != NULL){
            cout << "\n JANJI #" << nomor << ":\n";
            cout << left << setw(15) << "  ID Hewan" << ": " << current->idHewan << endl;
            cout << left << setw(15) << "  Nama Hewan" << ": " << current->namaHewan << endl;
            cout << left << setw(15) << "  Dokter" << ": " << current->dokter << endl;
            cout << left << setw(15) << "  Tanggal" << ": " << current->tanggal << endl;
            cout << left << setw(15) << "  Waktu" << ": " << current->waktu << endl;
            cout << left << setw(15) << "  Status" << ": " << statusKestring(current->status) << endl;
            cout << "====================================================\n";
            
            current = current->prev;
            nomor--;
        }
        
        cout << "\n TOTAL JANJI: " << totalJanji << endl;
        cout << "====================================================\n";
    }
    
    void cariDanTampilkanJanji() {
        if(head == NULL){
            cout << "\nTidak ada janji temu yang terdaftar!\n";
            return;
        }
        
        string idHewan;
        cout << "\n====================================================\n";
        cout << "                CARI JANJI TEMU\n";
        cout << "====================================================\n";
        cout << "Masukkan ID Hewan: ";
        cin.ignore();
        getline(cin, idHewan);
        
        JanjiTemu* janji = cariJanjiByID(idHewan);
        
        if(janji == NULL){
            cout << "\nJanji temu dengan ID " << idHewan << " tidak ditemukan!\n";
            return;
        }
        
        cout << "\nDATA DITEMUKAN:\n";
        cout << left << setw(20) << "  ID Hewan" << ": " << janji->idHewan << endl;
        cout << left << setw(20) << "  Nama Hewan" << ": " << janji->namaHewan << endl;
        cout << left << setw(20) << "  Jenis Hewan" << ": " << janji->jenisHewan << endl;
        cout << left << setw(20) << "  Pemilik" << ": " << janji->pemilik << endl;
        cout << left << setw(20) << "  Dokter" << ": " << janji->dokter << endl;
        cout << left << setw(20) << "  Tanggal" << ": " << janji->tanggal << endl;
        cout << left << setw(20) << "  Waktu" << ": " << janji->waktu << endl;
        cout << left << setw(20) << "  Keluhan" << ": " << janji->keluhan << endl;
        cout << left << setw(20) << "  Status" << ": " << statusKestring(janji->status) << endl;
        cout << "====================================================\n";
    }
    
    void hapusJanjiTemu(){
        if(head == NULL){
            cout << "\nTidak ada janji temu yang terdaftar!\n";
            return;
        }
        
        string idHewan;
        cout << "\n====================================================\n";
        cout << "                HAPUS JANJI TEMU\n";
        cout << "====================================================\n";
        cout << "Masukkan ID Hewan yang akan dihapus: ";
        cin.ignore();
        getline(cin, idHewan);
        
        JanjiTemu* current = cariJanjiByID(idHewan);
        
        if(current == NULL){
            cout << "\nJanji temu dengan ID " << idHewan << " tidak ditemukan!\n";
            return;
        }
        
        cout << "\nDATA YANG AKAN DIHAPUS:\n";
        cout << " ID Hewan     : " << current->idHewan << endl;
        cout << " Nama Hewan   : " << current->namaHewan << endl;
        cout << " Dokter       : " << current->dokter << endl;
        cout << " Tanggal      : " << current->tanggal << endl;
        cout << " Status       : " << statusKestring(current->status) << endl;
        
        cout << "\nAPAKAH ANDA YAKIN INGIN MENGHAPUS? (y/n): ";
        char konfirmasi;
        cin >> konfirmasi;
        
        if(konfirmasi != 'y' && konfirmasi != 'Y'){
            cout << "\nPenghapusan dibatalkan.\n";
            return;
        }
        
        if(current->prev != NULL){
            current->prev->next = current->next;
        } else {
            head = current->next;
        }
        
        if(current->next != NULL){
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
        
        delete current;
        totalJanji--;
        
        cout << "\n====================================================\n";
        cout << "    JANJI TEMU BERHASIL DIHAPUS!\n";
        cout << "    Total janji saat ini: " << totalJanji << endl;
        cout << "====================================================\n";
    }
    
    void tampilkanPengingat(){
        if(head == NULL){
            cout << "\nTidak ada janji temu yang terdaftar!\n";
            return;
        }
        
        string tanggalSekarang = getTanggalHariIni();
        cout << "\n====================================================\n";
        cout << "            PENGINGAT JANJI TEMU HARI INI\n";
        cout << "====================================================\n";
        
        JanjiTemu* current = head;
        bool ditemukan = false;
        int count = 0;
        
        while (current != NULL){
            if(current->tanggal == tanggalSekarang && 
                current->status != DIBATALKAN && 
                current->status != SELESAI) {
                
                ditemukan = true;
                count++;
                
                cout << "\n JANJI #" << count << ":\n";
                cout << left << setw(15) << "  ID Hewan" << ": " << current->idHewan << endl;
                cout << left << setw(15) << "  Nama Hewan" << ": " << current->namaHewan << endl;
                cout << left << setw(15) << "  Jenis Hewan" << ": " << current->jenisHewan << endl;
                cout << left << setw(15) << "  Dokter" << ": " << current->dokter << endl;
                cout << left << setw(15) << "  Waktu" << ": " << current->waktu << endl;
                cout << left << setw(15) << "  Keluhan" << ": " << current->keluhan << endl;
                cout << left << setw(15) << "  Status" << ": " << statusKestring(current->status) << endl;
                cout << "   Silakan datang 15 menit lebih awal!\n";
                cout << "====================================================\n";
            }
            current = current->next;
        }
        
        if(!ditemukan){
            cout << "\nTidak ada janji temu untuk hari ini (" << tanggalSekarang << ").\n";
            cout << "Semua hewan peliharaan Anda sehat hari ini!\n";
        } else {
            cout << "TOTAL PENGINGAT: " << count << " janji temu\n";
            cout << " Alamat: Jl. Kyi Haji Ahmad Dahlan No. 112, Kota Bantul\n";
            cout << " Telepon: 1255-1244\n";
        }
        
        cout << "====================================================\n";
    }
    
    void tampilkanStatistik() {
        if (head == NULL) {
            cout << "\nTidak ada janji temu yang terdaftar!\n";
            return;
        }
        
        int menunggu = 0, diterima = 0, selesai = 0, dibatalkan = 0;
        int anjing = 0, kucing = 0, kelinci = 0, burung = 0, lainnya = 0;
        
        JanjiTemu* current = head;
        
        while (current != NULL) {
            // Hitung berdasarkan status
            switch(current->status) {
                case MENUNGGU: menunggu++; break;
                case DITERIMA: diterima++; break;
                case SELESAI: selesai++; break;
                case DIBATALKAN: dibatalkan++; break;
            }
            
            // Hitung berdasarkan jenis hewan
            string jenis = current->jenisHewan;
            // Konversi ke lowercase untuk perbandingan
            for (size_t i = 0; i < jenis.length(); i++) {
                jenis[i] = tolower(jenis[i]);
            }
            
            if (jenis.find("anjing") != string::npos) anjing++;
            else if (jenis.find("kucing") != string::npos) kucing++;
            else if (jenis.find("kelinci") != string::npos) kelinci++;
            else if (jenis.find("burung") != string::npos) burung++;
            else lainnya++;
            
            current = current->next;
        }
        
        cout << "\n====================================================\n";
        cout << "              STATISTIK PET COMPANY\n";
        cout << "====================================================\n";
        cout << "\n STATUS JANJI TEMU:\n";
        cout << left << setw(20) << "  Menunggu" << ": " << menunggu << endl;
        cout << left << setw(20) << "  Diterima" << ": " << diterima << endl;
        cout << left << setw(20) << "  Selesai" << ": " << selesai << endl;
        cout << left << setw(20) << "  Dibatalkan" << ": " << dibatalkan << endl;
        cout << left << setw(20) << "  TOTAL" << ": " << totalJanji << endl;
        
        cout << "\n JENIS HEWAN:\n";
        cout << left << setw(20) << "  Anjing" << ": " << anjing << endl;
        cout << left << setw(20) << "  Kucing" << ": " << kucing << endl;
        cout << left << setw(20) << "  Kelinci" << ": " << kelinci << endl;
        cout << left << setw(20) << "  Burung" << ": " << burung << endl;
        cout << left << setw(20) << "  Lainnya" << ": " << lainnya << endl;
        
        cout << "\n====================================================\n";
    }
    
    // Fungsi untuk membersihkan semua janji
    void bersihkanSemuaJanji() {
        JanjiTemu* current = head;
        
        while (current != NULL) {
            JanjiTemu* next = current->next;
            delete current;
            current = next;
        }
        
        head = NULL;
        tail = NULL;
        totalJanji = 0;
    }
    
    // Getter untuk total janji
    int getTotalJanji() {
        return totalJanji;
    }
    
    void tampilkanMenu() {
        cout << "\n=======================================================\n";
        cout << "            PET COMPANY - SISTEM JANJI TEMU\n";
        cout << "                    (Doubly Linked List)\n";
        cout << "=======================================================\n";
        cout << "  1. Daftar Janji Temu Baru\n";
        cout << "  2. Perbarui Status Janji\n";
        cout << "  3. Tampilkan Semua Janji (dari depan)\n";
        cout << "  4. Tampilkan Semua Janji (dari belakang)\n";
        cout << "  5. Cari Janji Temu\n";
        cout << "  6. Hapus Janji Temu\n";
        cout << "  7. Pengingat Janji Hari Ini\n";
        cout << "  8. Tampilkan Statistik\n";
        cout << "  9. Keluar\n";
        cout << "=======================================================\n";
        cout << "  Pilihan Anda (1-9): ";
    }
};

// Fungsi utama
int main() {
    petCompanyJanjiTemu sistem;
    int pilihan;
    
    cout << "=========================================================\n";
    cout << "     SELAMAT DATANG DI PET COMPANY\n";
    cout << "     Kesehatan Hewan Peliharaan Anda Prioritas Kami\n";
    cout << "=========================================================\n";
    
    do {
        sistem.tampilkanMenu();
        cin >> pilihan;
        
        // Validasi input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInput tidak valid! Masukkan angka 1-9.\n";
            continue;
        }
        
        switch(pilihan) {
            case 1:
                sistem.daftarJanjiTemu();
                break;
            case 2:
                sistem.perbaruiStatusJanji();
                break;
            case 3:
                sistem.tampilkanSemuaJanji();
                break;
            case 4:
                sistem.tampilkanSemuaJanjiTerbalik();
                break;
            case 5:
                sistem.cariDanTampilkanJanji();
                break;
            case 6:
                sistem.hapusJanjiTemu();
                break;
            case 7:
                sistem.tampilkanPengingat();
                break;
            case 8:
                sistem.tampilkanStatistik();
                break;
            case 9:
                cout << "\n============================================================\n";
                cout << "    Terima kasih telah menggunakan sistem Pet Company!\n";
                cout << "         Semoga hewan peliharaan sehat selalu!\n";
                cout << "============================================================\n";
                break;
            default:
                cout << "\nPilihan tidak valid! Masukkan angka 1-9.\n";
                break;
        }
        
        // Tunggu user menekan enter untuk melanjutkan
        if (pilihan != 9) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        
    } while (pilihan != 9);
    
    return 0;
}
