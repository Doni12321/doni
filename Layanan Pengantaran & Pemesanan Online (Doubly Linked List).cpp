#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Enum untuk status pesanan
enum StatusPesanan {
    DIPROSES,
    DIKIRIM,
    DITERIMA
};

// Enum untuk metode pengiriman
enum MetodePengiriman {
    ANTAR,
    AMBIL_DI_TOKO
};

// Struct untuk data pesanan
struct Pesanan {
    int id;
    string namaPelanggan;
    string namaProduk;
    MetodePengiriman metode;
    StatusPesanan status;
    int estimasiWaktu; // dalam menit
    Pesanan* next;
    Pesanan* prev;
};

// Class untuk mengelola doubly linked list pesanan
class ManajemenPesanan {
private:
    Pesanan* head;
    Pesanan* tail;
    int idCounter;
    
    // Fungsi untuk mengonversi enum ke string
    string statusToString(StatusPesanan status) {
        switch(status) {
            case DIPROSES: return "Diproses";
            case DIKIRIM: return "Dikirim";
            case DITERIMA: return "Diterima";
            default: return "Tidak Diketahui";
        }
    }
    
    string metodeToString(MetodePengiriman metode) {
        switch(metode) {
            case ANTAR: return "Antar";
            case AMBIL_DI_TOKO: return "Ambil di Toko";
            default: return "Tidak Diketahui";
        }
    }
    
    // Generate estimasi waktu otomatis berdasarkan metode
    int generateEstimasiWaktu(MetodePengiriman metode) {
        // Gunakan waktu saat ini sebagai seed untuk random
        if (metode == ANTAR) {
            // Estimasi antar: 30-120 menit
            return 30 + (rand() % 91);
        } else {
            // Ambil di toko: 0 menit
            return 0;
        }
    }

public:
    // Constructor
    ManajemenPesanan() {
        head = NULL;
        tail = NULL;
        idCounter = 1000;
        srand(time(0));
    }
    
    // Destructor
    ~ManajemenPesanan() {
        Pesanan* current = head;
        while (current != NULL) {
            Pesanan* next = current->next;
            delete current;
            current = next;
        }
    }
    
    // Fungsi untuk membuat pesanan baru
    void buatPesanan() {
        Pesanan* pesananBaru = new Pesanan();
        pesananBaru->id = idCounter++;
        
        cout << "\n=== BUAT PESANAN BARU ===\n";
        cin.ignore();
        cout << "Nama Pelanggan: ";
        getline(cin, pesananBaru->namaPelanggan);
        
        cout << "Nama Produk: ";
        getline(cin, pesananBaru->namaProduk);
        
        int pilihan;
        cout << "\nPilih Metode Pengiriman:\n";
        cout << "1. Antar ke Rumah\n";
        cout << "2. Ambil di Toko\n";
        cout << "Pilihan (1-2): ";
        cin >> pilihan;
        
        if (pilihan == 1) {
            pesananBaru->metode = ANTAR;
        } else {
            pesananBaru->metode = AMBIL_DI_TOKO;
        }
        
        pesananBaru->status = DIPROSES;
        pesananBaru->estimasiWaktu = generateEstimasiWaktu(pesananBaru->metode);
        
        // Inisialisasi pointer
        pesananBaru->next = NULL;
        pesananBaru->prev = NULL;
        
        // Tambahkan ke linked list
        if (head == NULL) {
            // List kosong
            head = pesananBaru;
            tail = pesananBaru;
        } else {
            // Tambah di akhir
            tail->next = pesananBaru;
            pesananBaru->prev = tail;
            tail = pesananBaru;
        }
        
        cout << "\nPesanan berhasil dibuat!\n";
        cout << "ID Pesanan: " << pesananBaru->id << endl;
        cout << "Estimasi Waktu: " << pesananBaru->estimasiWaktu << " menit\n";
    }
    
    // Fungsi untuk menampilkan semua pesanan
    void tampilkanSemuaPesanan() {
        if (head == NULL) {
            cout << "\nBelum ada pesanan.\n";
            return;
        }
        
        cout << "\n=== DAFTAR SEMUA PESANAN ===\n";
        Pesanan* current = head;
        while (current != NULL) {
            cout << "\nID: " << current->id << endl;
            cout << "Pelanggan: " << current->namaPelanggan << endl;
            cout << "Produk: " << current->namaProduk << endl;
            cout << "Metode: " << metodeToString(current->metode) << endl;
            cout << "Status: " << statusToString(current->status) << endl;
            cout << "Estimasi: " << current->estimasiWaktu << " menit\n";
            cout << "---------------------------\n";
            current = current->next;
        }
    }
    
    // Fungsi untuk mencari pesanan berdasarkan ID
    Pesanan* cariPesanan(int id) {
        Pesanan* current = head;
        while (current != NULL) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }
    
    // Fungsi untuk mengupdate status pesanan
    void updateStatusPesanan() {
        if (head == NULL) {
            cout << "\nBelum ada pesanan.\n";
            return;
        }
        
        int id;
        cout << "\nMasukkan ID Pesanan yang akan diupdate: ";
        cin >> id;
        
        Pesanan* pesanan = cariPesanan(id);
        if (pesanan == NULL) {
            cout << "Pesanan dengan ID " << id << " tidak ditemukan.\n";
            return;
        }
        
        cout << "\nStatus saat ini: " << statusToString(pesanan->status) << endl;
        cout << "\nPilih status baru:\n";
        cout << "1. Diproses\n";
        cout << "2. Dikirim\n";
        cout << "3. Diterima\n";
        cout << "Pilihan (1-3): ";
        
        int pilihan;
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                pesanan->status = DIPROSES;
                break;
            case 2:
                pesanan->status = DIKIRIM;
                break;
            case 3:
                pesanan->status = DITERIMA;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                return;
        }
        
        cout << "Status berhasil diupdate!\n";
    }
    
    // Fungsi untuk menghapus pesanan
    void hapusPesanan() {
        if (head == NULL) {
            cout << "\nBelum ada pesanan.\n";
            return;
        }
        
        int id;
        cout << "\nMasukkan ID Pesanan yang akan dihapus: ";
        cin >> id;
        
        Pesanan* pesanan = cariPesanan(id);
        if (pesanan == NULL) {
            cout << "Pesanan dengan ID " << id << " tidak ditemukan.\n";
            return;
        }
        
        // Hapus dari linked list
        if (pesanan == head && pesanan == tail) {
            // Hanya satu elemen
            head = NULL;
            tail = NULL;
        } else if (pesanan == head) {
            // Hapus dari awal
            head = pesanan->next;
            head->prev = NULL;
        } else if (pesanan == tail) {
            // Hapus dari akhir
            tail = pesanan->prev;
            tail->next = NULL;
        } else {
            // Hapus dari tengah
            pesanan->prev->next = pesanan->next;
            pesanan->next->prev = pesanan->prev;
        }
        
        delete pesanan;
        cout << "Pesanan berhasil dihapus!\n";
    }
    
    // Fungsi untuk menampilkan pesanan berdasarkan status
    void tampilkanPesananByStatus() {
        if (head == NULL) {
            cout << "\nBelum ada pesanan.\n";
            return;
        }
        
        cout << "\nPilih status yang ingin ditampilkan:\n";
        cout << "1. Diproses\n";
        cout << "2. Dikirim\n";
        cout << "3. Diterima\n";
        cout << "Pilihan (1-3): ";
        
        int pilihan;
        cin >> pilihan;
        
        StatusPesanan statusPilihan;
        switch(pilihan) {
            case 1:
                statusPilihan = DIPROSES;
                break;
            case 2:
                statusPilihan = DIKIRIM;
                break;
            case 3:
                statusPilihan = DITERIMA;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                return;
        }
        
        cout << "\n=== PESANAN DENGAN STATUS " << statusToString(statusPilihan) << " ===\n";
        Pesanan* current = head;
        bool ditemukan = false;
        
        while (current != NULL) {
            if (current->status == statusPilihan) {
                ditemukan = true;
                cout << "\nID: " << current->id << endl;
                cout << "Pelanggan: " << current->namaPelanggan << endl;
                cout << "Produk: " << current->namaProduk << endl;
                cout << "Metode: " << metodeToString(current->metode) << endl;
                cout << "Estimasi: " << current->estimasiWaktu << " menit\n";
                cout << "---------------------------\n";
            }
            current = current->next;
        }
        
        if (!ditemukan) {
            cout << "Tidak ada pesanan dengan status tersebut.\n";
        }
    }
    
    // Fungsi untuk menampilkan menu
    void tampilkanMenu() {
        cout << "\n=== SISTEM PENGANTARAN & PEMESANAN ONLINE ===\n";
        cout << "1. Buat Pesanan Baru\n";
        cout << "2. Tampilkan Semua Pesanan\n";
        cout << "3. Update Status Pesanan\n";
        cout << "4. Hapus Pesanan\n";
        cout << "5. Tampilkan Pesanan Berdasarkan Status\n";
        cout << "6. Keluar\n";
        cout << "Pilihan (1-6): ";
    }
};

// Fungsi utama
int main() {
    ManajemenPesanan sistem;
    int pilihan;
    
    do {
        sistem.tampilkanMenu();
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                sistem.buatPesanan();
                break;
            case 2:
                sistem.tampilkanSemuaPesanan();
                break;
            case 3:
                sistem.updateStatusPesanan();
                break;
            case 4:
                sistem.hapusPesanan();
                break;
            case 5:
                sistem.tampilkanPesananByStatus();
                break;
            case 6:
                cout << "\nTerima kasih telah menggunakan sistem kami!\n";
                break;
            default:
                cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 6);
    
    return 0;
}
