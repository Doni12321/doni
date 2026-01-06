#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <cstdlib>

using namespace std;

// Struct untuk item dalam transaksi doubly linked list
struct ItemTransaksi {
    string namaItem;
    int jumlah;
    double harga;
    double subtotal;
    ItemTransaksi* next;
    ItemTransaksi* prev;
};

// Struct untuk transaksi doubly linked list
struct Transaksi {
    string idTransaksi;
    string idHewan;
    string namaHewan;
    string pemilik;
    string tanggal;
    string waktu;
    string metodePembayaran;
    string statusPembayaran;
    double totalBiaya;
    double pembayaranDiterima;
    double kembalian;
    ItemTransaksi* itemHead;
    ItemTransaksi* itemTail;
    int jumlahItem;
    Transaksi* next;
    Transaksi* prev;
};

// Class untuk manajemen transaksi doubly linked list
class TransaksiManager {
private:
    Transaksi* headTransaksi;
    Transaksi* tailTransaksi;
    int totalTransaksi;
    int counterID;
    
    // Fungsi untuk generate ID transaksi
    string generateID() {
        time_t sekarang = time(0);
        tm* waktuLokal = localtime(&sekarang);
        
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y%m%d", waktuLokal);
        string tanggal = buffer;
        
        stringstream ss;
        ss << "TRX" << tanggal << "-" << setw(4) << setfill('0') << counterID;
        counterID++;
        return ss.str();
    }
    
    // Fungsi untuk mendapatkan tanggal sekarang
    string getTanggalSekarang() {
        time_t sekarang = time(0);
        tm* waktuLokal = localtime(&sekarang);
        
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y", waktuLokal);
        return string(buffer);
    }
    
    // Fungsi untuk mendapatkan waktu sekarang
    string getWaktuSekarang() {
        time_t sekarang = time(0);
        tm* waktuLokal = localtime(&sekarang);
        
        char buffer[9];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", waktuLokal);
        return string(buffer);
    }
    
    // Fungsi untuk menghapus semua item dalam transaksi
    void hapusItemTransaksi(ItemTransaksi* head) {
        ItemTransaksi* current = head;
        while (current != NULL) {
            ItemTransaksi* next = current->next;
            delete current;
            current = next;
        }
    }
    
public:
    TransaksiManager() {
        headTransaksi = NULL;
        tailTransaksi = NULL;
        totalTransaksi = 0;
        counterID = 1;
    }
    
    ~TransaksiManager() {
        bersihkanSemuaTransaksi();
    }
    
    // Fungsi untuk membuat transaksi baru
    void buatTransaksiBaru() {
        Transaksi* transaksiBaru = new Transaksi;
        
        cout << "\n====================================================\n";
        cout << "              TRANSAKSI BARU - PET COMPANY\n";
        cout << "====================================================\n";
        
        // Generate ID transaksi
        transaksiBaru->idTransaksi = generateID();
        cout << "ID Transaksi: " << transaksiBaru->idTransaksi << endl;
        
        // Input data hewan dan pemilik
        cout << "\nDATA HEWAN DAN PEMILIK:\n";
        cout << "ID Hewan: ";
        cin.ignore();
        getline(cin, transaksiBaru->idHewan);
        
        cout << "Nama Hewan: ";
        getline(cin, transaksiBaru->namaHewan);
        
        cout << "Nama Pemilik: ";
        getline(cin, transaksiBaru->pemilik);
        
        // Set tanggal dan waktu
        transaksiBaru->tanggal = getTanggalSekarang();
        transaksiBaru->waktu = getWaktuSekarang();
        
        // Inisialisasi item transaksi
        transaksiBaru->itemHead = NULL;
        transaksiBaru->itemTail = NULL;
        transaksiBaru->jumlahItem = 0;
        transaksiBaru->totalBiaya = 0.0;
        
        // Tambahkan item-item transaksi
        char tambahLagi = 'y';
        do {
            tambahItemKeTransaksi(transaksiBaru);
            
            cout << "\n----------------------------------------------------\n";
            cout << "TOTAL SEMENTARA: Rp " << fixed << setprecision(0) << transaksiBaru->totalBiaya << endl;
            cout << "----------------------------------------------------\n";
            
            cout << "\nTambah item lain? (y/n): ";
            cin >> tambahLagi;
            cin.ignore();
            
        } while (tambahLagi == 'y' || tambahLagi == 'Y');
        
        // Proses pembayaran
        prosesPembayaran(transaksiBaru);
        
        // Tambahkan ke linked list transaksi
        transaksiBaru->next = NULL;
        transaksiBaru->prev = NULL;
        
        if (headTransaksi == NULL) {
            headTransaksi = transaksiBaru;
            tailTransaksi = transaksiBaru;
        } else {
            tailTransaksi->next = transaksiBaru;
            transaksiBaru->prev = tailTransaksi;
            tailTransaksi = transaksiBaru;
        }
        
        totalTransaksi++;
        
        // Cetak struk
        cetakStrukPembayaran(transaksiBaru);
        
        cout << "\n====================================================\n";
        cout << "      TRANSAKSI BERHASIL DIBUAT DAN DISIMPAN!\n";
        cout << "      Total transaksi: " << totalTransaksi << endl;
        cout << "====================================================\n";
    }
    
    // Fungsi untuk menambahkan item ke transaksi
    void tambahItemKeTransaksi(Transaksi* transaksi) {
        ItemTransaksi* itemBaru = new ItemTransaksi;
        
        cout << "\nTAMBAH ITEM TRANSAKSI:\n";
        
        // Pilih jenis layanan/produk
        cout << "PILIH JENIS LAYANAN/PRODUK:\n";
        cout << "  1. Pemeriksaan Umum (Rp 150.000)\n";
        cout << "  2. Pemeriksaan Spesialis (Rp 300.000)\n";
        cout << "  3. Vaksinasi Dasar (Rp 200.000)\n";
        cout << "  4. Vaksinasi Premium (Rp 350.000)\n";
        cout << "  5. Grooming Basic (Rp 100.000)\n";
        cout << "  6. Grooming Premium (Rp 250.000)\n";
        cout << "  7. Obat Antibiotik (Rp 75.000)\n";
        cout << "  8. Obat Vitamin (Rp 50.000)\n";
        cout << "  9. Obat Anti Nyeri (Rp 65.000)\n";
        cout << "  10. Rawat Inap (Rp 500.000/hari)\n";
        cout << "  11. Operasi (Rp 2.500.000)\n";
        cout << "  12. Lainnya (Input manual)\n";
        cout << "  Pilihan (1-12): ";
        
        int pilihan;
        cin >> pilihan;
        
        if (cin.fail() || pilihan < 1 || pilihan > 12) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = 1;
        }
        
        cin.ignore(); // membersihkan buffer
        
        double harga = 0;
        string namaItem;
        
        switch(pilihan) {
            case 1: 
                namaItem = "Pemeriksaan Umum";
                harga = 150000;
                break;
            case 2: 
                namaItem = "Pemeriksaan Spesialis";
                harga = 300000;
                break;
            case 3: 
                namaItem = "Vaksinasi Dasar";
                harga = 200000;
                break;
            case 4: 
                namaItem = "Vaksinasi Premium";
                harga = 350000;
                break;
            case 5: 
                namaItem = "Grooming Basic";
                harga = 100000;
                break;
            case 6: 
                namaItem = "Grooming Premium";
                harga = 250000;
                break;
            case 7: 
                namaItem = "Obat Antibiotik";
                harga = 75000;
                break;
            case 8: 
                namaItem = "Obat Vitamin";
                harga = 50000;
                break;
            case 9: 
                namaItem = "Obat Anti Nyeri";
                harga = 65000;
                break;
            case 10: 
                namaItem = "Rawat Inap (per hari)";
                harga = 500000;
                break;
            case 11: 
                namaItem = "Operasi";
                harga = 2500000;
                break;
            case 12: 
                cout << "Nama Item: ";
                getline(cin, namaItem);
                cout << "Harga: Rp ";
                cin >> harga;
                cin.ignore();
                break;
        }
        
        itemBaru->namaItem = namaItem;
        itemBaru->harga = harga;
        
        // Input jumlah
        cout << "Jumlah: ";
        cin >> itemBaru->jumlah;
        
        if (cin.fail() || itemBaru->jumlah <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            itemBaru->jumlah = 1;
        }
        
        cin.ignore(); // membersihkan buffer
        
        // Hitung subtotal
        itemBaru->subtotal = itemBaru->harga * itemBaru->jumlah;
        
        // Update total transaksi
        transaksi->totalBiaya += itemBaru->subtotal;
        
        // Tambahkan ke linked list item transaksi
        itemBaru->next = NULL;
        itemBaru->prev = NULL;
        
        if (transaksi->itemHead == NULL) {
            transaksi->itemHead = itemBaru;
            transaksi->itemTail = itemBaru;
        } else {
            transaksi->itemTail->next = itemBaru;
            itemBaru->prev = transaksi->itemTail;
            transaksi->itemTail = itemBaru;
        }
        
        transaksi->jumlahItem++;
        
        cout << "Item berhasil ditambahkan!\n";
    }
    
    // Fungsi untuk proses pembayaran
    void prosesPembayaran(Transaksi* transaksi) {
        cout << "\n====================================================\n";
        cout << "               PROSES PEMBAYARAN\n";
        cout << "====================================================\n";
        cout << "TOTAL YANG HARUS DIBAYAR: Rp " << fixed << setprecision(0) << transaksi->totalBiaya << endl;
        
        // Pilih metode pembayaran
        cout << "\nPILIH METODE PEMBAYARAN:\n";
        cout << "  1. Tunai\n";
        cout << "  2. Transfer Bank\n";
        cout << "  3. E-Wallet (GoPay/OVO/Dana)\n";
        cout << "  Pilihan (1-3): ";
        
        int pilihan;
        cin >> pilihan;
        
        if (cin.fail() || pilihan < 1 || pilihan > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = 1;
        }
        
        switch(pilihan) {
            case 1: 
                transaksi->metodePembayaran = "Tunai";
                break;
            case 2: 
                transaksi->metodePembayaran = "Transfer Bank";
                break;
            case 3: 
                transaksi->metodePembayaran = "E-Wallet";
                break;
        }
        
        // Input pembayaran
        if (transaksi->metodePembayaran == "Tunai") {
            do {
                cout << "\nMasukkan jumlah uang yang dibayarkan: Rp ";
                cin >> transaksi->pembayaranDiterima;
                
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    transaksi->pembayaranDiterima = 0;
                }
                
                if (transaksi->pembayaranDiterima < transaksi->totalBiaya) {
                    cout << "Pembayaran kurang! Kurang Rp " 
                         << fixed << setprecision(0) 
                         << (transaksi->totalBiaya - transaksi->pembayaranDiterima) << endl;
                    cout << "Silakan masukkan jumlah yang cukup.\n";
                }
            } while (transaksi->pembayaranDiterima < transaksi->totalBiaya);
            
            transaksi->kembalian = transaksi->pembayaranDiterima - transaksi->totalBiaya;
            transaksi->statusPembayaran = "Lunas";
            
            if (transaksi->kembalian > 0) {
                cout << "Kembalian: Rp " << fixed << setprecision(0) << transaksi->kembalian << endl;
            }
        } else {
            transaksi->pembayaranDiterima = transaksi->totalBiaya;
            transaksi->kembalian = 0;
            transaksi->statusPembayaran = "Lunas";
            cout << "\nPembayaran dengan " << transaksi->metodePembayaran << " berhasil!\n";
        }
        
        cout << "\nStatus Pembayaran: " << transaksi->statusPembayaran << endl;
        cin.ignore(); // membersihkan buffer
    }
    
    // Fungsi untuk mencetak struk pembayaran
    void cetakStrukPembayaran(Transaksi* transaksi) {
        cout << "\n\n";
        cout << "====================================================\n";
        cout << "              PET COMPANY - STRUK PEMBAYARAN\n";
        cout << "              Jl. Kesehatan Hewan No. 123\n";
        cout << "              Telp: (021) 1234-5678\n";
        cout << "====================================================\n";
        cout << "ID Transaksi   : " << transaksi->idTransaksi << endl;
        cout << "Tanggal        : " << transaksi->tanggal << endl;
        cout << "Waktu          : " << transaksi->waktu << endl;
        cout << "ID Hewan       : " << transaksi->idHewan << endl;
        cout << "Nama Hewan     : " << transaksi->namaHewan << endl;
        cout << "Nama Pemilik   : " << transaksi->pemilik << endl;
        cout << "----------------------------------------------------\n";
        cout << left << setw(30) << "ITEM" 
             << setw(8) << "QTY" 
             << setw(12) << "HARGA" 
             << setw(12) << "SUBTOTAL" << endl;
        cout << "----------------------------------------------------\n";
        
        // Tampilkan semua item
        ItemTransaksi* currentItem = transaksi->itemHead;
        while (currentItem != NULL) {
            cout << left << setw(30) << currentItem->namaItem 
                 << setw(8) << currentItem->jumlah 
                 << "Rp " << setw(9) << fixed << setprecision(0) << currentItem->harga
                 << "Rp " << setw(9) << fixed << setprecision(0) << currentItem->subtotal << endl;
            currentItem = currentItem->next;
        }
        
        cout << "----------------------------------------------------\n";
        cout << right << setw(52) << "TOTAL: Rp " 
             << fixed << setprecision(0) << transaksi->totalBiaya << endl;
        cout << "Metode Bayar   : " << transaksi->metodePembayaran << endl;
        cout << "Dibayar        : Rp " << fixed << setprecision(0) << transaksi->pembayaranDiterima << endl;
        
        if (transaksi->kembalian > 0) {
            cout << "Kembalian      : Rp " << fixed << setprecision(0) << transaksi->kembalian << endl;
        }
        
        cout << "Status         : " << transaksi->statusPembayaran << endl;
        cout << "====================================================\n";
        cout << "        TERIMA KASIH TELAH BERKUNJUNG\n";
        cout << "      Kesehatan Hewan Anda Prioritas Kami\n";
        cout << "====================================================\n\n";
    }
    
    // Fungsi untuk mencari transaksi berdasarkan ID
    Transaksi* cariTransaksiByID(string idTransaksi) {
        Transaksi* current = headTransaksi;
        while (current != NULL) {
            if (current->idTransaksi == idTransaksi) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }
    
    // Fungsi untuk menampilkan semua transaksi
    void tampilkanSemuaTransaksi() {
        if (headTransaksi == NULL) {
            cout << "\nTidak ada transaksi yang tersimpan!\n";
            return;
        }
        
        Transaksi* current = headTransaksi;
        int nomor = 1;
        
        cout << "\n====================================================\n";
        cout << "           DAFTAR SEMUA TRANSAKSI\n";
        cout << "====================================================\n";
        
        while (current != NULL) {
            cout << "\nTRANSAKSI #" << nomor << ":\n";
            cout << left << setw(20) << "  ID Transaksi" << ": " << current->idTransaksi << endl;
            cout << left << setw(20) << "  Tanggal" << ": " << current->tanggal << endl;
            cout << left << setw(20) << "  Nama Hewan" << ": " << current->namaHewan << endl;
            cout << left << setw(20) << "  Pemilik" << ": " << current->pemilik << endl;
            cout << left << setw(20) << "  Total Biaya" << ": Rp " << fixed << setprecision(0) << current->totalBiaya << endl;
            cout << left << setw(20) << "  Metode Bayar" << ": " << current->metodePembayaran << endl;
            cout << left << setw(20) << "  Status" << ": " << current->statusPembayaran << endl;
            cout << "  ---------------------------------------------\n";
            
            current = current->next;
            nomor++;
        }
        
        cout << "\nTOTAL TRANSAKSI: " << totalTransaksi << endl;
        cout << "====================================================\n";
    }
    
    // Fungsi untuk menampilkan transaksi dari belakang (terbaru)
    void tampilkanTransaksiTerbalik() {
        if (tailTransaksi == NULL) {
            cout << "\nTidak ada transaksi yang tersimpan!\n";
            return;
        }
        
        Transaksi* current = tailTransaksi;
        int nomor = totalTransaksi;
        
        cout << "\n====================================================\n";
        cout << "     DAFTAR TRANSAKSI (TERBARU KE TERLAMA)\n";
        cout << "====================================================\n";
        
        while (current != NULL) {
            cout << "\nTRANSAKSI #" << nomor << ":\n";
            cout << left << setw(20) << "  ID Transaksi" << ": " << current->idTransaksi << endl;
            cout << left << setw(20) << "  Tanggal" << ": " << current->tanggal << endl;
            cout << left << setw(20) << "  Nama Hewan" << ": " << current->namaHewan << endl;
            cout << left << setw(20) << "  Pemilik" << ": " << current->pemilik << endl;
            cout << left << setw(20) << "  Total Biaya" << ": Rp " << fixed << setprecision(0) << current->totalBiaya << endl;
            cout << left << setw(20) << "  Metode Bayar" << ": " << current->metodePembayaran << endl;
            cout << left << setw(20) << "  Status" << ": " << current->statusPembayaran << endl;
            cout << "  ---------------------------------------------\n";
            
            current = current->prev;
            nomor--;
        }
        
        cout << "\nTOTAL TRANSAKSI: " << totalTransaksi << endl;
        cout << "====================================================\n";
    }
    
    // Fungsi untuk melihat detail transaksi
    void lihatDetailTransaksi() {
        if (headTransaksi == NULL) {
            cout << "\nTidak ada transaksi yang tersimpan!\n";
            return;
        }
        
        string idTransaksi;
        cout << "\nMasukkan ID Transaksi: ";
        cin.ignore();
        getline(cin, idTransaksi);
        
        Transaksi* transaksi = cariTransaksiByID(idTransaksi);
        
        if (transaksi == NULL) {
            cout << "\nTransaksi dengan ID " << idTransaksi << " tidak ditemukan!\n";
            return;
        }
        
        cetakStrukPembayaran(transaksi);
    }
    
    // Fungsi untuk menghapus transaksi
    void hapusTransaksi() {
        if (headTransaksi == NULL) {
            cout << "\nTidak ada transaksi yang tersimpan!\n";
            return;
        }
        
        string idTransaksi;
        cout << "\nMasukkan ID Transaksi yang akan dihapus: ";
        cin.ignore();
        getline(cin, idTransaksi);
        
        Transaksi* transaksi = cariTransaksiByID(idTransaksi);
        
        if (transaksi == NULL) {
            cout << "\nTransaksi dengan ID " << idTransaksi << " tidak ditemukan!\n";
            return;
        }
        
        cout << "\nDATA TRANSAKSI YANG AKAN DIHAPUS:\n";
        cout << "ID Transaksi : " << transaksi->idTransaksi << endl;
        cout << "Tanggal      : " << transaksi->tanggal << endl;
        cout << "Nama Hewan   : " << transaksi->namaHewan << endl;
        cout << "Total Biaya  : Rp " << fixed << setprecision(0) << transaksi->totalBiaya << endl;
        
        cout << "\nAPAKAH ANDA YAKIN INGIN MENGHAPUS? (y/n): ";
        char konfirmasi;
        cin >> konfirmasi;
        cin.ignore();
        
        if (konfirmasi != 'y' && konfirmasi != 'Y') {
            cout << "\nPenghapusan dibatalkan.\n";
            return;
        }
        
        // Hapus item transaksi terlebih dahulu
        hapusItemTransaksi(transaksi->itemHead);
        
        // Hapus dari linked list transaksi
        if (transaksi->prev != NULL) {
            transaksi->prev->next = transaksi->next;
        } else {
            headTransaksi = transaksi->next;
        }
        
        if (transaksi->next != NULL) {
            transaksi->next->prev = transaksi->prev;
        } else {
            tailTransaksi = transaksi->prev;
        }
        
        delete transaksi;
        totalTransaksi--;
        
        cout << "\nTransaksi berhasil dihapus!\n";
        cout << "Total transaksi saat ini: " << totalTransaksi << endl;
    }
    
    // Fungsi untuk laporan keuangan harian
    void laporanKeuanganHarian() {
        if (headTransaksi == NULL) {
            cout << "\nTidak ada transaksi yang tersimpan!\n";
            return;
        }
        
        string tanggal;
        cout << "\nMasukkan tanggal (DD-MM-YYYY) atau ketik 'hari' untuk hari ini: ";
        cin.ignore();
        getline(cin, tanggal);
        
        if (tanggal == "hari") {
            tanggal = getTanggalSekarang();
        }
        
        Transaksi* current = headTransaksi;
        int jumlahTransaksi = 0;
        double totalPendapatan = 0.0;
        double tunai = 0, transfer = 0, ewallet = 0;
        
        cout << "\n====================================================\n";
        cout << "        LAPORAN KEUANGAN HARIAN\n";
        cout << "        Tanggal: " << tanggal << "\n";
        cout << "====================================================\n";
        
        cout << left << setw(15) << "ID Transaksi" 
             << setw(15) << "Nama Hewan"
             << setw(15) << "Metode Bayar"
             << setw(15) << "Total" << endl;
        cout << "----------------------------------------------------\n";
        
        while (current != NULL) {
            if (current->tanggal == tanggal && current->statusPembayaran == "Lunas") {
                jumlahTransaksi++;
                totalPendapatan += current->totalBiaya;
                
                // Hitung berdasarkan metode pembayaran
                if (current->metodePembayaran == "Tunai") tunai += current->totalBiaya;
                else if (current->metodePembayaran == "Transfer Bank") transfer += current->totalBiaya;
                else if (current->metodePembayaran == "E-Wallet") ewallet += current->totalBiaya;
                
                cout << left << setw(15) << current->idTransaksi.substr(0, 12)
                     << setw(15) << (current->namaHewan.length() > 12 ? current->namaHewan.substr(0, 12) + "..." : current->namaHewan)
                     << setw(15) << current->metodePembayaran
                     << "Rp " << fixed << setprecision(0) << setw(12) << current->totalBiaya << endl;
            }
            current = current->next;
        }
        
        cout << "----------------------------------------------------\n";
        cout << "\nRINGKASAN:\n";
        cout << "Jumlah Transaksi  : " << jumlahTransaksi << endl;
        cout << "Total Pendapatan  : Rp " << fixed << setprecision(0) << totalPendapatan << endl;
        
        if (jumlahTransaksi > 0) {
            double rataRata = totalPendapatan / jumlahTransaksi;
            cout << "Rata-rata         : Rp " << fixed << setprecision(0) << rataRata << endl;
        }
        
        cout << "\nBREAKDOWN METODE PEMBAYARAN:\n";
        cout << "  Tunai           : Rp " << fixed << setprecision(0) << tunai 
             << " (" << (totalPendapatan > 0 ? (tunai / totalPendapatan * 100) : 0) << "%)" << endl;
        cout << "  Transfer Bank   : Rp " << fixed << setprecision(0) << transfer 
             << " (" << (totalPendapatan > 0 ? (transfer / totalPendapatan * 100) : 0) << "%)" << endl;
        cout << "  E-Wallet        : Rp " << fixed << setprecision(0) << ewallet 
             << " (" << (totalPendapatan > 0 ? (ewallet / totalPendapatan * 100) : 0) << "%)" << endl;
        
        cout << "====================================================\n";
    }
    
    // Fungsi untuk laporan keuangan bulanan
    void laporanKeuanganBulanan() {
        if (headTransaksi == NULL) {
            cout << "\nTidak ada transaksi yang tersimpan!\n";
            return;
        }
        
        string bulanTahun;
        cout << "\nMasukkan bulan dan tahun (MM-YYYY) atau ketik 'bulan' untuk bulan ini: ";
        cin.ignore();
        getline(cin, bulanTahun);
        
        // Jika input "bulan", ambil bulan ini
        if (bulanTahun == "bulan") {
            time_t sekarang = time(0);
            tm* waktuLokal = localtime(&sekarang);
            char buffer[8];
            strftime(buffer, sizeof(buffer), "%m-%Y", waktuLokal);
            bulanTahun = buffer;
        }
        
        Transaksi* current = headTransaksi;
        int jumlahTransaksi = 0;
        double totalPendapatan = 0.0;
        
        cout << "\n====================================================\n";
        cout << "        LAPORAN KEUANGAN BULANAN\n";
        cout << "        Periode: " << bulanTahun << "\n";
        cout << "====================================================\n";
        
        // Array untuk pendapatan harian
        double pendapatanHarian[31] = {0};
        int transaksiHarian[31] = {0};
        
        while (current != NULL) {
            if (current->statusPembayaran == "Lunas") {
                // Cek apakah transaksi di bulan yang diminta
                size_t pos = current->tanggal.find('-');
                if (pos != string::npos) {
                    string tanggal = current->tanggal;
                    string bulanTransaksi = tanggal.substr(pos + 1, 7); // MM-YYYY
                    
                    if (bulanTransaksi == bulanTahun) {
                        jumlahTransaksi++;
                        totalPendapatan += current->totalBiaya;
                        
                        // Ekstrak hari
                        int hari = atoi(tanggal.substr(0, 2).c_str());
                        if (hari >= 1 && hari <= 31) {
                            pendapatanHarian[hari-1] += current->totalBiaya;
                            transaksiHarian[hari-1]++;
                        }
                    }
                }
            }
            current = current->next;
        }
        
        // Tampilkan ringkasan
        cout << "Jumlah Transaksi : " << jumlahTransaksi << endl;
        cout << "Total Pendapatan : Rp " << fixed << setprecision(0) << totalPendapatan << endl;
        
        if (jumlahTransaksi > 0) {
            double rataRata = totalPendapatan / jumlahTransaksi;
            cout << "Rata-rata        : Rp " << fixed << setprecision(0) << rataRata << endl;
        }
        
        // Tampilkan pendapatan per hari
        cout << "\nPENDAPATAN PER HARI:\n";
        cout << "Hari   Transaksi   Pendapatan\n";
        cout << "--------------------------------\n";
        
        for (int i = 0; i < 31; i++) {
            if (transaksiHarian[i] > 0) {
                cout << setw(2) << (i+1) << "     "
                     << setw(5) << transaksiHarian[i] << "     Rp "
                     << setw(10) << fixed << setprecision(0) << pendapatanHarian[i] << endl;
            }
        }
        
        cout << "====================================================\n";
    }
    
    // Fungsi untuk statistik layanan terlaris
    void statistikLayananTerlaris() {
        if (headTransaksi == NULL) {
            cout << "\nTidak ada transaksi yang tersimpan!\n";
            return;
        }
        
        cout << "\n====================================================\n";
        cout << "        STATISTIK LAYANAN TERLARIS\n";
        cout << "====================================================\n";
        
        // Simple statistik - hanya hitung total per kategori
        double pemeriksaan = 0, vaksinasi = 0, grooming = 0, obat = 0, lainnya = 0;
        int countPemeriksaan = 0, countVaksinasi = 0, countGrooming = 0, countObat = 0, countLainnya = 0;
        
        Transaksi* current = headTransaksi;
        
        while (current != NULL) {
            ItemTransaksi* item = current->itemHead;
            while (item != NULL) {
                string nama = item->namaItem;
                if (nama.find("Pemeriksaan") != string::npos) {
                    pemeriksaan += item->subtotal;
                    countPemeriksaan += item->jumlah;
                } else if (nama.find("Vaksinasi") != string::npos) {
                    vaksinasi += item->subtotal;
                    countVaksinasi += item->jumlah;
                } else if (nama.find("Grooming") != string::npos || nama.find("grooming") != string::npos) {
                    grooming += item->subtotal;
                    countGrooming += item->jumlah;
                } else if (nama.find("Obat") != string::npos || nama.find("obat") != string::npos) {
                    obat += item->subtotal;
                    countObat += item->jumlah;
                } else {
                    lainnya += item->subtotal;
                    countLainnya += item->jumlah;
                }
                item = item->next;
            }
            current = current->next;
        }
        
        cout << left << setw(20) << "KATEGORI" 
             << setw(15) << "JUMLAH"
             << setw(20) << "TOTAL PENDAPATAN" << endl;
        cout << "----------------------------------------------------\n";
        
        cout << left << setw(20) << "Pemeriksaan"
             << setw(15) << countPemeriksaan
             << "Rp " << fixed << setprecision(0) << setw(17) << pemeriksaan << endl;
        
        cout << left << setw(20) << "Vaksinasi"
             << setw(15) << countVaksinasi
             << "Rp " << fixed << setprecision(0) << setw(17) << vaksinasi << endl;
        
        cout << left << setw(20) << "Grooming"
             << setw(15) << countGrooming
             << "Rp " << fixed << setprecision(0) << setw(17) << grooming << endl;
        
        cout << left << setw(20) << "Obat"
             << setw(15) << countObat
             << "Rp " << fixed << setprecision(0) << setw(17) << obat << endl;
        
        cout << left << setw(20) << "Lainnya"
             << setw(15) << countLainnya
             << "Rp " << fixed << setprecision(0) << setw(17) << lainnya << endl;
        
        cout << "====================================================\n";
        
        // Tampilkan layanan paling populer
        double total = pemeriksaan + vaksinasi + grooming + obat + lainnya;
        if (total > 0) {
            cout << "\nPERSENTASE PENDAPATAN:\n";
            cout << "Pemeriksaan: " << fixed << setprecision(1) << (pemeriksaan/total*100) << "%\n";
            cout << "Vaksinasi  : " << fixed << setprecision(1) << (vaksinasi/total*100) << "%\n";
            cout << "Grooming   : " << fixed << setprecision(1) << (grooming/total*100) << "%\n";
            cout << "Obat       : " << fixed << setprecision(1) << (obat/total*100) << "%\n";
            cout << "Lainnya    : " << fixed << setprecision(1) << (lainnya/total*100) << "%\n";
        }
        
        cout << "====================================================\n";
    }
    
    // Fungsi untuk cetak ulang struk
    void cetakUlangStruk() {
        if (headTransaksi == NULL) {
            cout << "\nTidak ada transaksi yang tersimpan!\n";
            return;
        }
        
        string idTransaksi;
        cout << "\nMasukkan ID Transaksi untuk cetak ulang struk: ";
        cin.ignore();
        getline(cin, idTransaksi);
        
        Transaksi* transaksi = cariTransaksiByID(idTransaksi);
        if (transaksi != NULL) {
            cetakStrukPembayaran(transaksi);
        } else {
            cout << "\nTransaksi tidak ditemukan!\n";
        }
    }
    
    // Fungsi untuk membersihkan semua transaksi
    void bersihkanSemuaTransaksi() {
        Transaksi* current = headTransaksi;
        while (current != NULL) {
            Transaksi* next = current->next;
            hapusItemTransaksi(current->itemHead);
            delete current;
            current = next;
        }
        headTransaksi = NULL;
        tailTransaksi = NULL;
        totalTransaksi = 0;
        counterID = 1;
    }
    
    // Getter untuk total transaksi
    int getTotalTransaksi() {
        return totalTransaksi;
    }
};

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    cout << "\n=======================================================\n";
    cout << "        SISTEM TRANSAKSI & PEMBAYARAN\n";
    cout << "               PET COMPANY\n";
    cout << "=======================================================\n";
    cout << "  1. Buat Transaksi Baru\n";
    cout << "  2. Tampilkan Semua Transaksi\n";
    cout << "  3. Tampilkan Transaksi (Terbaru ke Terlama)\n";
    cout << "  4. Lihat Detail Transaksi\n";
    cout << "  5. Hapus Transaksi\n";
    cout << "  6. Laporan Keuangan Harian\n";
    cout << "  7. Laporan Keuangan Bulanan\n";
    cout << "  8. Statistik Layanan Terlaris\n";
    cout << "  9. Cetak Ulang Struk\n";
    cout << "  10. Keluar\n";
    cout << "=======================================================\n";
    cout << "  Pilihan Anda (1-10): ";
}

// Fungsi utama
int main() {
    TransaksiManager sistemTransaksi;
    int pilihan;
    
    cout << "=========================================================\n";
    cout << "     SISTEM TRANSAKSI & PEMBAYARAN PET COMPANY\n";
    cout << "           (Menggunakan Doubly Linked List)\n";
    cout << "=========================================================\n";
    
    do {
        tampilkanMenu();
        cin >> pilihan;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInput tidak valid! Masukkan angka 1-10.\n";
            continue;
        }
        
        switch(pilihan) {
            case 1:
                sistemTransaksi.buatTransaksiBaru();
                break;
                
            case 2:
                sistemTransaksi.tampilkanSemuaTransaksi();
                break;
                
            case 3:
                sistemTransaksi.tampilkanTransaksiTerbalik();
                break;
                
            case 4:
                sistemTransaksi.lihatDetailTransaksi();
                break;
                
            case 5:
                sistemTransaksi.hapusTransaksi();
                break;
                
            case 6:
                sistemTransaksi.laporanKeuanganHarian();
                break;
                
            case 7:
                sistemTransaksi.laporanKeuanganBulanan();
                break;
                
            case 8:
                sistemTransaksi.statistikLayananTerlaris();
                break;
                
            case 9:
                sistemTransaksi.cetakUlangStruk();
                break;
                
            case 10:
                cout << "\n====================================================\n";
                cout << "  Terima kasih telah menggunakan sistem transaksi!\n";
                cout << "====================================================\n";
                break;
                
            default:
                cout << "\nPilihan tidak valid! Masukkan angka 1-10.\n";
        }
        
        if (pilihan != 10) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        
    } while (pilihan != 10);
    
    return 0;
}
