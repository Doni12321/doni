#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>
#include <cstdlib>
#include <sstream>  // Tambahkan ini

using namespace std;

struct Produk {
    string id;
    string nama;
    string kategori; 
    int stok;
    double harga;
    string deskripsi;
    Produk* prev;
    Produk* next;
};

struct TransaksiDetail {
    string id_produk;
    string nama_produk;
    int jumlah;
    double harga;
    double subtotal;
    TransaksiDetail* next;
};

struct Transaksi {
    int id_transaksi;
    string tanggal;
    string waktu;
    double total;
    TransaksiDetail* detail;
    Transaksi* prev;
    Transaksi* next;
};

class PetCompany {
private:
    Produk* head_produk;
    Produk* tail_produk;
    Transaksi* head_transaksi;
    Transaksi* tail_transaksi;
    int transaksi_counter;
    
    bool isIdExist(string id) {
        Produk* current = head_produk;
        while (current != NULL) {
            if (current->id == id) 
                return true;
            current = current->next;
        }
        return false;
    }
    
    // Fungsi untuk konversi int ke string (alternatif to_string)
    string intToString(int num) {
        stringstream ss;
        ss << num;
        return ss.str();
    }
    
    string generateId(string kategori) {
        string prefix;
        if (kategori == "makanan") prefix = "FD";
        else if (kategori == "vitamin") prefix = "VT";
        else if (kategori == "obat") prefix = "OB";
        else if (kategori == "aksesoris") prefix = "AC";
        else if (kategori == "mainan") prefix = "TN";
        else prefix = "PR";
        
        int num = 1;
        string id;
        do {
            id = prefix + intToString(num);
            num++;
        } while (isIdExist(id));
        
        return id;
    }
    
    string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        
        stringstream ss;
        ss << ltm->tm_mday << "-" 
           << (1 + ltm->tm_mon) << "-" 
           << (1900 + ltm->tm_year);
        
        return ss.str();
    }
    
    string getCurrentTime() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        
        stringstream ss;
        ss << ltm->tm_hour << ":" 
           << ltm->tm_min << ":" 
           << ltm->tm_sec;
        
        return ss.str();
    }
    
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
public:
    PetCompany() {
        head_produk = tail_produk = NULL;
        head_transaksi = tail_transaksi = NULL;
        transaksi_counter = 1000;
    }
    
    ~PetCompany() {
        Produk* current_produk = head_produk;
        while (current_produk != NULL) {
            Produk* temp = current_produk;
            current_produk = current_produk->next;
            delete temp;
        }
        
        Transaksi* current_trans = head_transaksi;
        while (current_trans != NULL) {
            TransaksiDetail* current_detail = current_trans->detail;
            while (current_detail != NULL) {
                TransaksiDetail* temp = current_detail;
                current_detail = current_detail->next;
                delete temp;
            }
            
            Transaksi* temp = current_trans;
            current_trans = current_trans->next;
            delete temp;
        }
    }
    
    void tambahProduk() {
        Produk* baru = new Produk;
        
        cout << "\n=== TAMBAH PRODUK BARU ===\n";
        
        cout << "Kategori (makanan/vitamin/obat/aksesoris/mainan): ";
        getline(cin, baru->kategori);
        
        if (baru->kategori != "makanan" && baru->kategori != "vitamin" && 
            baru->kategori != "obat" && baru->kategori != "aksesoris" && 
            baru->kategori != "mainan") {
            cout << "Kategori tidak valid!\n";
            delete baru;
            return;
        }
        
        baru->id = generateId(baru->kategori);
        cout << "ID Produk: " << baru->id << endl;
        
        cout << "Nama Produk: ";
        getline(cin, baru->nama);
        
        cout << "Stok: ";
        cin >> baru->stok;
        
        cout << "Harga: ";
        cin >> baru->harga;
        
        clearInputBuffer();
        
        cout << "Deskripsi: ";
        getline(cin, baru->deskripsi);
        
        baru->prev = NULL;
        baru->next = NULL;
        
        if (head_produk == NULL) {
            head_produk = tail_produk = baru;
        } else {
            tail_produk->next = baru;
            baru->prev = tail_produk;
            tail_produk = baru;
        }
        
        cout << "\nProduk berhasil ditambahkan!\n";
    }
    
    void tampilkanSemuaProduk() {
        if (head_produk == NULL) {
            cout << "\nTidak ada produk yang terdaftar.\n";
            return;
        }
        
        cout << "\n=== DAFTAR SEMUA PRODUK ===\n";
        cout << "=============================================================================================================\n";
        cout << left << setw(10) << "ID" 
             << setw(20) << "Nama" 
             << setw(15) << "Kategori" 
             << setw(10) << "Stok" 
             << setw(15) << "Harga" 
             << "Deskripsi\n";
        cout << "=============================================================================================================\n";
        
        Produk* current = head_produk;
        while (current != NULL) {
            cout << left << setw(10) << current->id
                 << setw(20) << current->nama
                 << setw(15) << current->kategori
                 << setw(10) << current->stok
                 << "Rp" << setw(13) << fixed << setprecision(2) << current->harga
                 << current->deskripsi << endl;
            current = current->next;
        }
        cout << "=============================================================================================================\n";
    }
    
    Produk* cariProdukById(string id) {
        Produk* current = head_produk;
        while (current != NULL) {
            if (current->id == id) return current;
            current = current->next;
        }
        return NULL;
    }
    
    void editProduk() {
        string id;
        cout << "\n=== EDIT PRODUK ===\n";
        cout << "Masukkan ID produk yang akan diedit: ";
        cin >> id;
        clearInputBuffer();
        
        Produk* produk = cariProdukById(id);
        if (produk == NULL) {
            cout << "Produk dengan ID " << id << " tidak ditemukan!\n";
            return;
        }
        
        cout << "\nData saat ini:\n";
        cout << "ID: " << produk->id << endl;
        cout << "Nama: " << produk->nama << endl;
        cout << "Kategori: " << produk->kategori << endl;
        cout << "Stok: " << produk->stok << endl;
        cout << "Harga: Rp" << fixed << setprecision(2) << produk->harga << endl;
        cout << "Deskripsi: " << produk->deskripsi << endl;
        
        cout << "\nMasukkan data baru (kosongkan jika tidak ingin mengubah):\n";
        
        cout << "Nama Produk [" << produk->nama << "]: ";
        string input;
        getline(cin, input);
        if (!input.empty()) produk->nama = input;
        
        cout << "Kategori [" << produk->kategori << "]: ";
        getline(cin, input);
        if (!input.empty()) produk->kategori = input;
        
        cout << "Stok [" << produk->stok << "]: ";
        getline(cin, input);
        if (!input.empty()) produk->stok = atoi(input.c_str());
        
        cout << "Harga [" << produk->harga << "]: ";
        getline(cin, input);
        if (!input.empty()) produk->harga = atof(input.c_str());
        
        cout << "Deskripsi [" << produk->deskripsi << "]: ";
        getline(cin, input);
        if (!input.empty()) produk->deskripsi = input;
        
        cout << "\nProduk berhasil diupdate!\n";
    }
    
    void hapusProduk() {
        string id;
        cout << "\n=== HAPUS PRODUK ===\n";
        cout << "Masukkan ID produk yang akan dihapus: ";
        cin >> id;
        clearInputBuffer();
        
        Produk* produk = cariProdukById(id);
        if (produk == NULL) {
            cout << "Produk dengan ID " << id << " tidak ditemukan!\n";
            return;
        }
        
        cout << "\nAnda akan menghapus produk:\n";
        cout << "ID: " << produk->id << endl;
        cout << "Nama: " << produk->nama << endl;
        cout << "Kategori: " << produk->kategori << endl;
        cout << "Yakin? (y/n): ";
        char confirm;
        cin >> confirm;
        clearInputBuffer();
        
        if (confirm != 'y' && confirm != 'Y') {
            cout << "Penghapusan dibatalkan.\n";
            return;
        }
        
        if (produk->prev != NULL) {
            produk->prev->next = produk->next;
        } else {
            head_produk = produk->next;
        }
        
        if (produk->next != NULL) {
            produk->next->prev = produk->prev;
        } else {
            tail_produk = produk->prev;
        }
        
        delete produk;
        cout << "Produk berhasil dihapus!\n";
    }
    
    void cariProduk() {
        int pilihan;
        cout << "\n=== PENCARIAN PRODUK ===\n";
        cout << "1. Cari berdasarkan nama\n";
        cout << "2. Cari berdasarkan kategori\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        clearInputBuffer();
        
        if (pilihan == 1) {
            string keyword;
            cout << "Masukkan nama produk: ";
            getline(cin, keyword);
            
            cout << "\n=== HASIL PENCARIAN ===\n";
            cout << "=============================================================================================================\n";
            cout << left << setw(10) << "ID" 
                 << setw(20) << "Nama" 
                 << setw(15) << "Kategori" 
                 << setw(10) << "Stok" 
                 << setw(15) << "Harga" 
                 << "Deskripsi\n";
            cout << "=============================================================================================================\n";
            
            Produk* current = head_produk;
            bool found = false;
            while (current != NULL) {
                if (current->nama.find(keyword) != string::npos) {
                    cout << left << setw(10) << current->id
                         << setw(20) << current->nama
                         << setw(15) << current->kategori
                         << setw(10) << current->stok
                         << "Rp" << setw(13) << fixed << setprecision(2) << current->harga
                         << current->deskripsi << endl;
                    found = true;
                }
                current = current->next;
            }
            
            if (!found) {
                cout << "Tidak ditemukan produk dengan nama mengandung '" << keyword << "'\n";
            }
            cout << "=============================================================================================================\n";
            
        } else if (pilihan == 2) {
            string kategori;
            cout << "Masukkan kategori (makanan/vitamin/obat/aksesoris/mainan): ";
            getline(cin, kategori);
            
            cout << "\n=== PRODUK DALAM KATEGORI " << kategori << " ===\n";
            cout << "=============================================================================================================\n";
            cout << left << setw(10) << "ID" 
                 << setw(20) << "Nama" 
                 << setw(15) << "Kategori" 
                 << setw(10) << "Stok" 
                 << setw(15) << "Harga" 
                 << "Deskripsi\n";
            cout << "=============================================================================================================\n";
            
            Produk* current = head_produk;
            bool found = false;
            while (current != NULL) {
                if (current->kategori == kategori) {
                    cout << left << setw(10) << current->id
                         << setw(20) << current->nama
                         << setw(15) << current->kategori
                         << setw(10) << current->stok
                         << "Rp" << setw(13) << fixed << setprecision(2) << current->harga
                         << current->deskripsi << endl;
                    found = true;
                }
                current = current->next;
            }
            
            if (!found) {
                cout << "Tidak ditemukan produk dalam kategori '" << kategori << "'\n";
            }
            cout << "=============================================================================================================\n";
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    }
    
    void simulasiPembelian() {
        cout << "\n=== SIMULASI PEMBELIAN ===\n";
        
        Transaksi* transaksi = new Transaksi;
        transaksi->id_transaksi = transaksi_counter++;
        transaksi->tanggal = getCurrentDate();
        transaksi->waktu = getCurrentTime();
        transaksi->total = 0;
        transaksi->detail = NULL;
        transaksi->prev = NULL;
        transaksi->next = NULL;
        
        TransaksiDetail* tail_detail = NULL;
        char lanjut = 'y';
        
        while (lanjut == 'y' || lanjut == 'Y') {
            string id;
            int jumlah;
            
            cout << "\nMasukkan ID produk: ";
            cin >> id;
            
            Produk* produk = cariProdukById(id);
            if (produk == NULL) {
                cout << "Produk dengan ID " << id << " tidak ditemukan!\n";
                continue;
            }
            
            cout << "Produk: " << produk->nama << endl;
            cout << "Stok tersedia: " << produk->stok << endl;
            cout << "Harga: Rp" << fixed << setprecision(2) << produk->harga << endl;
            cout << "Jumlah yang dibeli: ";
            cin >> jumlah;
            
            if (jumlah <= 0) {
                cout << "Jumlah tidak valid!\n";
                continue;
            }
            
            if (jumlah > produk->stok) {
                cout << "Stok tidak cukup! Stok tersedia: " << produk->stok << endl;
                continue;
            }
            
            produk->stok -= jumlah;
            
            TransaksiDetail* detail = new TransaksiDetail;
            detail->id_produk = produk->id;
            detail->nama_produk = produk->nama;
            detail->jumlah = jumlah;
            detail->harga = produk->harga;
            detail->subtotal = produk->harga * jumlah;
            detail->next = NULL;
            
            if (transaksi->detail == NULL) {
                transaksi->detail = detail;
                tail_detail = detail;
            } else {
                tail_detail->next = detail;
                tail_detail = detail;
            }
            
            transaksi->total += detail->subtotal;
            
            cout << "Ditambahkan: " << produk->nama << " x" << jumlah 
                 << " = Rp" << fixed << setprecision(2) << detail->subtotal << endl;
            
            cout << "\nTambah produk lain? (y/n): ";
            cin >> lanjut;
        }
        
        if (head_transaksi == NULL) {
            head_transaksi = tail_transaksi = transaksi;
        } else {
            tail_transaksi->next = transaksi;
            transaksi->prev = tail_transaksi;
            tail_transaksi = transaksi;
        }
        
        cout << "\nPembelian selesai! Total: Rp" << fixed << setprecision(2) << transaksi->total << endl;
        cout << "ID Transaksi: " << transaksi->id_transaksi << endl;
        
        cout << "\nCetak nota? (y/n): ";
        char cetak;
        cin >> cetak;
        clearInputBuffer();
        
        if (cetak == 'y' || cetak == 'Y') {
            cetakNota(transaksi->id_transaksi);
        }
    }
    
    void cetakNota(int id_transaksi) {
        Transaksi* transaksi = NULL;
        Transaksi* current = head_transaksi;
        
        while (current != NULL) {
            if (current->id_transaksi == id_transaksi) {
                transaksi = current;
                break;
            }
            current = current->next;
        }
        
        if (transaksi == NULL) {
            cout << "Transaksi dengan ID " << id_transaksi << " tidak ditemukan!\n";
            return;
        }
        
        cout << "\n";
        cout << "==========================================\n";
        cout << "           PET COMPANY SHOP\n";
        cout << "        NOTA PEMBELIAN\n";
        cout << "==========================================\n";
        cout << "ID Transaksi : " << transaksi->id_transaksi << endl;
        cout << "Tanggal      : " << transaksi->tanggal << endl;
        cout << "Waktu        : " << transaksi->waktu << endl;
        cout << "------------------------------------------\n";
        cout << left << setw(5) << "No" 
             << setw(20) << "Produk" 
             << setw(10) << "Jumlah" 
             << setw(15) << "Harga" 
             << setw(15) << "Subtotal\n";
        cout << "------------------------------------------\n";
        
        TransaksiDetail* detail = transaksi->detail;
        int no = 1;
        while (detail != NULL) {
            cout << left << setw(5) << no++
                 << setw(20) << detail->nama_produk
                 << setw(10) << detail->jumlah
                 << "Rp" << setw(13) << fixed << setprecision(2) << detail->harga
                 << "Rp" << setw(13) << fixed << setprecision(2) << detail->subtotal << endl;
            detail = detail->next;
        }
        
        cout << "------------------------------------------\n";
        cout << right << setw(50) << "Total: Rp" << fixed << setprecision(2) << transaksi->total << endl;
        cout << "==========================================\n";
        cout << "      Terima kasih atas pembelian Anda!\n";
        cout << "==========================================\n\n";
    }
    
    void laporanPenjualan() {
        int pilihan;
        cout << "\n=== LAPORAN PENJUALAN ===\n";
        cout << "1. Laporan Harian\n";
        cout << "2. Laporan Bulanan\n";
        cout << "3. Semua Transaksi\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        clearInputBuffer();
        
        if (pilihan == 1) {
            string tanggal;
            cout << "Masukkan tanggal (dd-mm-yyyy): ";
            getline(cin, tanggal);
            
            cout << "\n=== LAPORAN HARIAN " << tanggal << " ===\n";
            tampilkanTransaksiByDate(tanggal, "harian");
            
        } else if (pilihan == 2) {
            string bulan;
            cout << "Masukkan bulan (mm-yyyy): ";
            getline(cin, bulan);
            
            cout << "\n=== LAPORAN BULANAN " << bulan << " ===\n";
            tampilkanTransaksiByDate(bulan, "bulanan");
            
        } else if (pilihan == 3) {
            cout << "\n=== SEMUA TRANSAKSI ===\n";
            tampilkanSemuaTransaksi();
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    }
    
    void tampilkanTransaksiByDate(string date_filter, string jenis) {
        if (head_transaksi == NULL) {
            cout << "Tidak ada transaksi.\n";
            return;
        }
        
        cout << "========================================================================================\n";
        cout << left << setw(12) << "ID Transaksi" 
             << setw(12) << "Tanggal" 
             << setw(10) << "Waktu" 
             << setw(35) << "Detail Produk" 
             << setw(15) << "Total\n";
        cout << "========================================================================================\n";
        
        Transaksi* current = head_transaksi;
        double total_harian = 0;
        bool found = false;
        
        while (current != NULL) {
            bool tampil = false;
            
            if (jenis == "harian" && current->tanggal == date_filter) {
                tampil = true;
            } else if (jenis == "bulanan") {
                size_t dash_pos = current->tanggal.find('-');
                if (dash_pos != string::npos) {
                    string bulan_tahun = current->tanggal.substr(dash_pos + 1);
                    if (bulan_tahun == date_filter) {
                        tampil = true;
                    }
                }
            } else if (jenis == "semua") {
                tampil = true;
            }
            
            if (tampil) {
                found = true;
                total_harian += current->total;
                
                string detail_str = "";
                TransaksiDetail* detail = current->detail;
                while (detail != NULL) {
                    detail_str += detail->nama_produk + "(" + intToString(detail->jumlah) + ") ";
                    detail = detail->next;
                }
                
                cout << left << setw(12) << current->id_transaksi
                     << setw(12) << current->tanggal
                     << setw(10) << current->waktu
                     << setw(35) << (detail_str.length() > 35 ? detail_str.substr(0, 32) + "..." : detail_str)
                     << "Rp" << fixed << setprecision(2) << current->total << endl;
            }
            
            current = current->next;
        }
        
        if (!found) {
            cout << "Tidak ada transaksi untuk periode tersebut.\n";
        } else {
            cout << "========================================================================================\n";
            cout << "Total " << jenis << ": Rp" << fixed << setprecision(2) << total_harian << endl;
        }
    }
    
    void tampilkanSemuaTransaksi() {
        tampilkanTransaksiByDate("", "semua");
    }
    
    void buatDataDummy() {
        Produk* current = head_produk;
        while (current != NULL) {
            Produk* temp = current;
            current = current->next;
            delete temp;
        }
        head_produk = tail_produk = NULL;
        
        string categories[] = {"makanan", "vitamin", "obat", "aksesoris", "mainan"};
        string names[][5] = {
            {"Royal Canin Kitten", "Whiskas Adult", "Pro Plan Salmon", "Friskies Ocean", "Pedigree Puppy"},
            {"Vitamin A Kucing", "Vitamin B Anjing", "Calcium Plus", "Vitamin C Hewan", "Multivitamin"},
            {"Obat Cacing", "Obat Kutu", "Antiseptik", "Salep Mata", "Obat Diare"},
            {"Kandang Burung", "Tali Tuntun", "Keranjang Tidur", "Mangkuk Makan", "Kandang Kelinci"},
            {"Bola Berdenting", "Tali Tarik", "Boneka Tikus", "Frisbee", "Tongkat Interaktif"}
        };
        
        string descriptions[] = {
            "Makanan premium untuk pertumbuhan optimal",
            "Suplemen kesehatan untuk hewan peliharaan",
            "Obat untuk menjaga kesehatan hewan",
            "Aksesoris untuk kenyamanan hewan",
            "Mainan untuk melatih dan menghibur hewan"
        };
        
        double prices[] = {85000, 45000, 35000, 120000, 25000};
        int stocks[] = {50, 30, 40, 20, 60};
        
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                Produk* baru = new Produk;
                baru->kategori = categories[i];
                baru->id = generateId(categories[i]);
                baru->nama = names[i][j];
                baru->stok = stocks[i];
                baru->harga = prices[i] + (j * 5000);
                baru->deskripsi = descriptions[i];
                baru->prev = NULL;
                baru->next = NULL;
                
                if (head_produk == NULL) {
                    head_produk = tail_produk = baru;
                } else {
                    tail_produk->next = baru;
                    baru->prev = tail_produk;
                    tail_produk = baru;
                }
            }
        }
        
        cout << "Data dummy berhasil dibuat (25 produk)\n";
    }
    
    void tampilkanMenu() {
        cout << "\n=== SISTEM MANAJEMEN PET COMPANY ===\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Tampilkan Semua Produk\n";
        cout << "3. Edit Produk\n";
        cout << "4. Hapus Produk\n";
        cout << "5. Cari Produk (Nama/Kategori)\n";
        cout << "6. Simulasi Pembelian\n";
        cout << "7. Cetak Nota Pembelian\n";
        cout << "8. Laporan Penjualan\n";
        cout << "9. Buat Data Dummy (Testing)\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
    }
};

int main() {
    PetCompany petShop;
    int pilihan;
    
    petShop.buatDataDummy();
    
    do {
        petShop.tampilkanMenu();
        cin >> pilihan;
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (pilihan) {
            case 1:
                petShop.tambahProduk();
                break;
            case 2:
                petShop.tampilkanSemuaProduk();
                break;
            case 3:
                petShop.editProduk();
                break;
            case 4:
                petShop.hapusProduk();
                break;
            case 5:
                petShop.cariProduk();
                break;
            case 6:
                petShop.simulasiPembelian();
                break;
            case 7: {
                int id;
                cout << "Masukkan ID Transaksi: ";
                cin >> id;
                petShop.cetakNota(id);
                break;
            }
            case 8:
                petShop.laporanPenjualan();
                break;
            case 9:
                petShop.buatDataDummy();
                break;
            case 0:
                cout << "\nTerima kasih telah menggunakan sistem Pet Company!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
        
        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
        }
        
    } while (pilihan != 0);
    
    return 0;
}
