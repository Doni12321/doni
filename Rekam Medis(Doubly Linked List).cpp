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

struct RekamMedis {
    string idHewan;
    string tanggal;
    string diagnosis;
    string obat;
    string saran;
    string jenisCatatan; 
    RekamMedis* next;
    RekamMedis* prev;
};

// Class untuk manajemen janji temu
class PetCompanyJanjiTemu {
private:
    JanjiTemu* headJanji;
    JanjiTemu* tailJanji;
    int totalJanji;
    
public:
    PetCompanyJanjiTemu(){
        headJanji = NULL;
        tailJanji = NULL;
        totalJanji = 0;
    }
    
    ~PetCompanyJanjiTemu(){
        bersihkanSemuaJanji();
    }
    
    JanjiTemu* getHeadJanji() { return headJanji; }
    
    string statusKestring(Status status) {
        switch(status) {
            case MENUNGGU: return "MENUNGGU";
            case DITERIMA: return "DITERIMA";
            case SELESAI: return "SELESAI";
            case DIBATALKAN: return "DIBATALKAN";
            default: return "TIDAK DIKETAHUI";
        }
    }
    
    JanjiTemu* cariJanjiByID(string idHewan){
        JanjiTemu* current = headJanji;
        while(current != NULL){
            if(current->idHewan == idHewan){
                return current;
            }
            current = current->next;
        }
        return NULL;
    }
    
    void bersihkanSemuaJanji() {
        JanjiTemu* current = headJanji;
        while (current != NULL) {
            JanjiTemu* next = current->next;
            delete current;
            current = next;
        }
        headJanji = NULL;
        tailJanji = NULL;
        totalJanji = 0;
    }
};

// Class untuk manajemen rekam medis
class RekamMedisManager {
private:
    RekamMedis* headRekam;
    RekamMedis* tailRekam;
    int totalRekam;
    
public:
    RekamMedisManager(){
        headRekam = NULL;
        tailRekam = NULL;
        totalRekam = 0;
    }
    
    ~RekamMedisManager(){
        bersihkanSemuaRekam();
    }
    
    void tambahRekamMedis(JanjiTemu* janji = NULL) {
        RekamMedis* rekamBaru = new RekamMedis;
        
        cout << "\n====================================================\n";
        cout << "               TAMBAH REKAM MEDIS BARU\n";
        cout << "====================================================\n";
        
        string idHewanInput;
        
        if (janji != NULL) {
            idHewanInput = janji->idHewan;
            cout << "ID Hewan (dari janji temu): " << idHewanInput << endl;
        } else {
            cout << "ID Hewan: ";
            cin.ignore();
            getline(cin, idHewanInput);
        }
        
        rekamBaru->idHewan = idHewanInput;
        
        cout << "\nJENIS CATATAN:\n";
        cout << "  1. Pemeriksaan Kesehatan\n";
        cout << "  2. Vaksinasi\n";
        cout << "  3. Perawatan Rutin\n";
        cout << "  Pilihan (1-3): ";
        
        int pilihanJenis;
        cin >> pilihanJenis;
        cin.ignore();
        
        switch(pilihanJenis) {
            case 1: rekamBaru->jenisCatatan = "Pemeriksaan Kesehatan"; break;
            case 2: rekamBaru->jenisCatatan = "Vaksinasi"; break;
            case 3: rekamBaru->jenisCatatan = "Perawatan Rutin"; break;
            default: rekamBaru->jenisCatatan = "Pemeriksaan Kesehatan";
        }
        
        cout << "\nTanggal Pemeriksaan (DD-MM-YYYY): ";
        getline(cin, rekamBaru->tanggal);
        
        cout << "Diagnosis: ";
        getline(cin, rekamBaru->diagnosis);
        
        cout << "Obat yang diresepkan: ";
        getline(cin, rekamBaru->obat);
       
        cout << "Saran dan perawatan: ";
        getline(cin, rekamBaru->saran);
        
        rekamBaru->next = NULL;
        rekamBaru->prev = NULL;
        
        if (headRekam == NULL) {
            headRekam = rekamBaru;
            tailRekam = rekamBaru;
        } else {
            tailRekam->next = rekamBaru;
            rekamBaru->prev = tailRekam;
            tailRekam = rekamBaru;
        }
        
        totalRekam++;
        
        cout << "\n====================================================\n";
        cout << "      REKAM MEDIS BERHASIL DITAMBAHKAN!\n";
        cout << "      Total rekam medis: " << totalRekam << endl;
        cout << "====================================================\n";
    }
    
    // Fungsi untuk mencari rekam medis berdasarkan ID hewan
    void cariRekamMedisByID(string idHewan) {
        if (headRekam == NULL) {
            cout << "\nTidak ada rekam medis yang tersimpan!\n";
            return;
        }
        
        RekamMedis* current = headRekam;
        bool ditemukan = false;
        int count = 0;
        
        cout << "\n====================================================\n";
        cout << "      RIWAYAT REKAM MEDIS - ID: " << idHewan << "\n";
        cout << "====================================================\n";
        
        while (current != NULL) {
            if (current->idHewan == idHewan) {
                ditemukan = true;
                count++;
                
                cout << "\nREKAM #" << count << ":\n";
                cout << left << setw(20) << "  Jenis Catatan" << ": " << current->jenisCatatan << endl;
                cout << left << setw(20) << "  Tanggal" << ": " << current->tanggal << endl;
                cout << left << setw(20) << "  Diagnosis" << ": " << current->diagnosis << endl;
                cout << left << setw(20) << "  Obat" << ": " << current->obat << endl;
                cout << left << setw(20) << "  Saran" << ": " << current->saran << endl;
                cout << "  ---------------------------------------------\n";
            }
            current = current->next;
        }
        
        if (!ditemukan) {
            cout << "\nTidak ditemukan rekam medis untuk hewan dengan ID: " << idHewan << endl;
        } else {
            cout << "\nTOTAL REKAM DITEMUKAN: " << count << endl;
        }
        cout << "====================================================\n";
    }
    
    // Fungsi untuk menampilkan semua rekam medis (dari depan)
    void tampilkanSemuaRekamMedis() {
        if (headRekam == NULL) {
            cout << "\nTidak ada rekam medis yang tersimpan!\n";
            return;
        }
        
        RekamMedis* current = headRekam;
        int nomor = 1;
        
        cout << "\n====================================================\n";
        cout << "           DAFTAR SEMUA REKAM MEDIS\n";
        cout << "====================================================\n";
        
        while (current != NULL) {
            cout << "\nREKAM #" << nomor << ":\n";
            cout << left << setw(20) << "  ID Hewan" << ": " << current->idHewan << endl;
            cout << left << setw(20) << "  Jenis Catatan" << ": " << current->jenisCatatan << endl;
            cout << left << setw(20) << "  Tanggal" << ": " << current->tanggal << endl;
            cout << left << setw(20) << "  Diagnosis" << ": " << current->diagnosis << endl;
            cout << left << setw(20) << "  Obat" << ": " << current->obat << endl;
            cout << left << setw(20) << "  Saran" << ": " << current->saran << endl;
            cout << "====================================================\n";
            
            current = current->next;
            nomor++;
        }
        
        cout << "\nTOTAL REKAM MEDIS: " << totalRekam << endl;
        cout << "====================================================\n";
    }
    
    void tampilkanRekamMedisTerbalik() {
        if (tailRekam == NULL) {
            cout << "\nTidak ada rekam medis yang tersimpan!\n";
            return;
        }
        
        RekamMedis* current = tailRekam;
        int nomor = totalRekam;
        
        cout << "\n====================================================\n";
        cout << "     DAFTAR REKAM MEDIS (TERBARU KE TERLAMA)\n";
        cout << "====================================================\n";
        
        while (current != NULL) {
            cout << "\nREKAM #" << nomor << ":\n";
            cout << left << setw(20) << "  ID Hewan" << ": " << current->idHewan << endl;
            cout << left << setw(20) << "  Jenis Catatan" << ": " << current->jenisCatatan << endl;
            cout << left << setw(20) << "  Tanggal" << ": " << current->tanggal << endl;
            cout << left << setw(20) << "  Diagnosis" << ": " << current->diagnosis << endl;
            cout << left << setw(20) << "  Obat" << ": " << current->obat << endl;
            cout << left << setw(20) << "  Saran" << ": " << current->saran << endl;
            cout << "====================================================\n";
            
            current = current->prev;
            nomor--;
        }
        
        cout << "\nTOTAL REKAM MEDIS: " << totalRekam << endl;
        cout << "====================================================\n";
    }
    
    // Fungsi untuk menghapus rekam medis
    void hapusRekamMedis() {
        if (headRekam == NULL) {
            cout << "\nTidak ada rekam medis yang tersimpan!\n";
            return;
        }
        
        string idHewan;
        string tanggal;
        
        cout << "\n====================================================\n";
        cout << "               HAPUS REKAM MEDIS\n";
        cout << "====================================================\n";
        cout << "ID Hewan: ";
        cin.ignore();
        getline(cin, idHewan);
        cout << "Tanggal Rekam Medis (DD-MM-YYYY): ";
        getline(cin, tanggal);
        
        RekamMedis* current = headRekam;
        bool ditemukan = false;
        
        while (current != NULL) {
            if (current->idHewan == idHewan && current->tanggal == tanggal) {
                ditemukan = true;
                
                cout << "\nDATA YANG AKAN DIHAPUS:\n";
                cout << left << setw(20) << "  ID Hewan" << ": " << current->idHewan << endl;
                cout << left << setw(20) << "  Jenis Catatan" << ": " << current->jenisCatatan << endl;
                cout << left << setw(20) << "  Tanggal" << ": " << current->tanggal << endl;
                cout << left << setw(20) << "  Diagnosis" << ": " << current->diagnosis << endl;
                
                cout << "\nAPAKAH ANDA YAKIN INGIN MENGHAPUS? (y/n): ";
                char konfirmasi;
                cin >> konfirmasi;
                
                if (konfirmasi == 'y' || konfirmasi == 'Y') {
                    // Hapus node dari linked list
                    if (current->prev != NULL) {
                        current->prev->next = current->next;
                    } else {
                        headRekam = current->next;
                    }
                    
                    if (current->next != NULL) {
                        current->next->prev = current->prev;
                    } else {
                        tailRekam = current->prev;
                    }
                    
                    delete current;
                    totalRekam--;
                    
                    cout << "\nREKAM MEDIS BERHASIL DIHAPUS!\n";
                    cout << "Total rekam medis saat ini: " << totalRekam << endl;
                } else {
                    cout << "\nPenghapusan dibatalkan.\n";
                }
                break;
            }
            current = current->next;
        }
        
        if (!ditemukan) {
            cout << "\nRekam medis tidak ditemukan!\n";
        }
        cout << "====================================================\n";
    }
    
    // Fungsi untuk membersihkan semua rekam medis
    void bersihkanSemuaRekam() {
        RekamMedis* current = headRekam;
        while (current != NULL) {
            RekamMedis* next = current->next;
            delete current;
            current = next;
        }
        headRekam = NULL;
        tailRekam = NULL;
        totalRekam = 0;
    }
    
    // Fungsi untuk menambah catatan vaksin khusus
    void tambahCatatanVaksin() {
        RekamMedis* rekamBaru = new RekamMedis;
        
        cout << "\n====================================================\n";
        cout << "               CATATAN VAKSINASI\n";
        cout << "====================================================\n";
        
        cout << "ID Hewan: ";
        cin.ignore();
        getline(cin, rekamBaru->idHewan);
        
        rekamBaru->jenisCatatan = "Vaksinasi";
        
        cout << "Tanggal Vaksinasi (DD-MM-YYYY): ";
        getline(cin, rekamBaru->tanggal);
        
        cout << "Jenis Vaksin: ";
        getline(cin, rekamBaru->diagnosis); // Gunakan diagnosis field untuk jenis vaksin
        
        cout << "Dosis: ";
        getline(cin, rekamBaru->obat); // Gunakan obat field untuk dosis
        
        cout << "Catatan Tambahan: ";
        getline(cin, rekamBaru->saran);
        
        // Tambahkan ke linked list
        rekamBaru->next = NULL;
        rekamBaru->prev = NULL;
        
        if (headRekam == NULL) {
            headRekam = rekamBaru;
            tailRekam = rekamBaru;
        } else {
            tailRekam->next = rekamBaru;
            rekamBaru->prev = tailRekam;
            tailRekam = rekamBaru;
        }
        
        totalRekam++;
        
        cout << "\n====================================================\n";
        cout << "      CATATAN VAKSINASI BERHASIL DITAMBAHKAN!\n";
        cout << "====================================================\n";
    }
    
    // Fungsi untuk menambah catatan perawatan rutin
    void tambahCatatanPerawatanRutin() {
        RekamMedis* rekamBaru = new RekamMedis;
        
        cout << "\n====================================================\n";
        cout << "           CATATAN PERAWATAN RUTIN\n";
        cout << "====================================================\n";
        
        cout << "ID Hewan: ";
        cin.ignore();
        getline(cin, rekamBaru->idHewan);
        
        rekamBaru->jenisCatatan = "Perawatan Rutin";
        
        cout << "Tanggal Perawatan (DD-MM-YYYY): ";
        getline(cin, rekamBaru->tanggal);
        
        cout << "Jenis Perawatan (Grooming/Pembersihan Telinga/dll): ";
        getline(cin, rekamBaru->diagnosis);
        
        cout << "Produk yang Digunakan: ";
        getline(cin, rekamBaru->obat);
        
        cout << "Catatan dan Saran: ";
        getline(cin, rekamBaru->saran);
        
        // Tambahkan ke linked list
        rekamBaru->next = NULL;
        rekamBaru->prev = NULL;
        
        if (headRekam == NULL) {
            headRekam = rekamBaru;
            tailRekam = rekamBaru;
        } else {
            tailRekam->next = rekamBaru;
            rekamBaru->prev = tailRekam;
            tailRekam = rekamBaru;
        }
        
        totalRekam++;
        
        cout << "\n====================================================\n";
        cout << "   CATATAN PERAWATAN RUTIN BERHASIL DITAMBAHKAN!\n";
        cout << "====================================================\n";
    }
    
    // Getter untuk total rekam medis
    int getTotalRekam() {
        return totalRekam;
    }
};

// Fungsi untuk menampilkan menu utama
void tampilkanMenuUtama() {
    cout << "\n=======================================================\n";
    cout << "            PET COMPANY - SISTEM TERPADU\n";
    cout << "           (Janji Temu & Rekam Medis Hewan)\n";
    cout << "=======================================================\n";
    cout << "  1. Kelola Janji Temu\n";
    cout << "  2. Kelola Rekam Medis\n";
    cout << "  3. Keluar\n";
    cout << "=======================================================\n";
    cout << "  Pilihan Anda (1-3): ";
}

// Fungsi untuk menampilkan menu janji temu
void tampilkanMenuJanjiTemu() {
    cout << "\n=======================================================\n";
    cout << "            SISTEM JANJI TEMU HEWAN\n";
    cout << "=======================================================\n";
    cout << "  1. Daftar Janji Temu Baru\n";
    cout << "  2. Perbarui Status Janji\n";
    cout << "  3. Tampilkan Semua Janji (dari depan)\n";
    cout << "  4. Tampilkan Semua Janji (dari belakang)\n";
    cout << "  5. Cari Janji Temu\n";
    cout << "  6. Hapus Janji Temu\n";
    cout << "  7. Pengingat Janji Hari Ini\n";
    cout << "  8. Tampilkan Statistik\n";
    cout << "  9. Kembali ke Menu Utama\n";
    cout << "=======================================================\n";
    cout << "  Pilihan Anda (1-9): ";
}

// Fungsi untuk menampilkan menu rekam medis
void tampilkanMenuRekamMedis() {
    cout << "\n=======================================================\n";
    cout << "            SISTEM REKAM MEDIS HEWAN\n";
    cout << "=======================================================\n";
    cout << "  1. Tambah Rekam Medis Baru\n";
    cout << "  2. Cari Rekam Medis Berdasarkan ID Hewan\n";
    cout << "  3. Tampilkan Semua Rekam Medis\n";
    cout << "  4. Tampilkan Rekam Medis (Terbaru ke Terlama)\n";
    cout << "  5. Tambah Catatan Vaksinasi\n";
    cout << "  6. Tambah Catatan Perawatan Rutin\n";
    cout << "  7. Hapus Rekam Medis\n";
    cout << "  8. Kembali ke Menu Utama\n";
    cout << "=======================================================\n";
    cout << "  Pilihan Anda (1-8): ";
}

// Fungsi utama
int main() {
    PetCompanyJanjiTemu sistemJanji;
    RekamMedisManager sistemRekam;
    int pilihanUtama, pilihanSub;
    
    cout << "=========================================================\n";
    cout << "     SELAMAT DATANG DI PET COMPANY\n";
    cout << "     Kesehatan Hewan Peliharaan Anda Prioritas Kami\n";
    cout << "=========================================================\n";
    
    do {
        tampilkanMenuUtama();
        cin >> pilihanUtama;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInput tidak valid! Masukkan angka 1-3.\n";
            continue;
        }
        
        switch(pilihanUtama) {
            case 1: // Menu Janji Temu
                do {
                    tampilkanMenuJanjiTemu();
                    cin >> pilihanSub;
                    
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nInput tidak valid!\n";
                        continue;
                    }
                    
                    // Di sini Anda perlu menambahkan implementasi fungsi-fungsi
                    // untuk sistem janji temu yang sudah ada sebelumnya
                    // Karena kode sudah panjang, saya berasumsi Anda sudah punya
                    // implementasi lengkap untuk fungsi-fungsi janji temu
                    
                    switch(pilihanSub) {
                        case 1:
                            cout << "\nFitur Daftar Janji Temu Baru\n";
                            // sistemJanji.daftarJanjiTemu();
                            break;
                        case 2:
                            cout << "\nFitur Perbarui Status Janji\n";
                            // sistemJanji.perbaruiStatusJanji();
                            break;
                        case 3:
                            cout << "\nFitur Tampilkan Semua Janji (dari depan)\n";
                            // sistemJanji.tampilkanSemuaJanji();
                            break;
                        case 4:
                            cout << "\nFitur Tampilkan Semua Janji (dari belakang)\n";
                            // sistemJanji.tampilkanSemuaJanjiTerbalik();
                            break;
                        case 5:
                            cout << "\nFitur Cari Janji Temu\n";
                            // sistemJanji.cariDanTampilkanJanji();
                            break;
                        case 6:
                            cout << "\nFitur Hapus Janji Temu\n";
                            // sistemJanji.hapusJanjiTemu();
                            break;
                        case 7:
                            cout << "\nFitur Pengingat Janji Hari Ini\n";
                            // sistemJanji.tampilkanPengingat();
                            break;
                        case 8:
                            cout << "\nFitur Tampilkan Statistik\n";
                            // sistemJanji.tampilkanStatistik();
                            break;
                        case 9:
                            cout << "\nKembali ke Menu Utama...\n";
                            break;
                        default:
                            cout << "\nPilihan tidak valid! Masukkan angka 1-9.\n";
                    }
                    
                    if (pilihanSub != 9) {
                        cout << "\nTekan Enter untuk melanjutkan...";
                        cin.ignore();
                        cin.get();
                    }
                    
                } while (pilihanSub != 9);
                break;
                
            case 2: // Menu Rekam Medis
                do {
                    tampilkanMenuRekamMedis();
                    cin >> pilihanSub;
                    
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nInput tidak valid!\n";
                        continue;
                    }
                    
                    switch(pilihanSub) {
                        case 1: // Tambah Rekam Medis Baru
                            {
                                string idHewan;
                                cout << "\nApakah ini lanjutan dari janji temu? (y/n): ";
                                char pilihan;
                                cin >> pilihan;
                                
                                if (pilihan == 'y' || pilihan == 'Y') {
                                    cout << "Masukkan ID Hewan dari janji temu: ";
                                    cin.ignore();
                                    getline(cin, idHewan);
                                    
                                    // Cari janji temu berdasarkan ID
                                    JanjiTemu* janji = sistemJanji.cariJanjiByID(idHewan);
                                    if (janji != NULL) {
                                        sistemRekam.tambahRekamMedis(janji);
                                    } else {
                                        cout << "\nJanji temu tidak ditemukan. Tambah rekam medis secara manual.\n";
                                        sistemRekam.tambahRekamMedis();
                                    }
                                } else {
                                    sistemRekam.tambahRekamMedis();
                                }
                            }
                            break;
                            
                        case 2: // Cari Rekam Medis Berdasarkan ID Hewan
                            {
                                string idHewan;
                                cout << "\nMasukkan ID Hewan: ";
                                cin.ignore();
                                getline(cin, idHewan);
                                sistemRekam.cariRekamMedisByID(idHewan);
                            }
                            break;
                            
                        case 3: // Tampilkan Semua Rekam Medis
                            sistemRekam.tampilkanSemuaRekamMedis();
                            break;
                            
                        case 4: // Tampilkan Rekam Medis (Terbaru ke Terlama)
                            sistemRekam.tampilkanRekamMedisTerbalik();
                            break;
                            
                        case 5: // Tambah Catatan Vaksinasi
                            sistemRekam.tambahCatatanVaksin();
                            break;
                            
                        case 6: // Tambah Catatan Perawatan Rutin
                            sistemRekam.tambahCatatanPerawatanRutin();
                            break;
                            
                        case 7: // Hapus Rekam Medis
                            sistemRekam.hapusRekamMedis();
                            break;
                            
                        case 8: // Kembali ke Menu Utama
                            cout << "\nKembali ke Menu Utama...\n";
                            break;
                            
                        default:
                            cout << "\nPilihan tidak valid! Masukkan angka 1-8.\n";
                    }
                    
                    if (pilihanSub != 8) {
                        cout << "\nTekan Enter untuk melanjutkan...";
                        cin.ignore();
                        cin.get();
                    }
                    
                } while (pilihanSub != 8);
                break;
                
            case 3: // Keluar
                cout << "\n============================================================\n";
                cout << "    Terima kasih telah menggunakan sistem Pet Company!\n";
                cout << "         Semoga hewan peliharaan sehat selalu!\n";
                cout << "============================================================\n";
                break;
                
            default:
                cout << "\nPilihan tidak valid! Masukkan angka 1-3.\n";
        }
        
        if (pilihanUtama != 3) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        
    } while (pilihanUtama != 3);
    
    return 0;
}
