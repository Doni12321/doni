#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// ==============================================
// STRUCT DASAR
// ==============================================
struct Hewan {
    string nama;
    string jenis;
    int umur;
    string riwayatPenyakit;
};

struct Pemilik {
    string username;
    string password;
    string email;
    string noTelepon;
    Hewan hewan;
    string riwayatKunjungan[10];
    int jumlahRiwayat;
    bool aktif;
    Pemilik* next;
    Pemilik* prev;
    
};

struct Dokter {
    string username;
    string password;
    string nama;
    string spesialisasi;
    bool aktif;
    Dokter* next;
    Dokter* prev;
};

struct JanjiTemu {
    string namaPemilik;
    string namaHewan;
    string tanggal;
    string jam;
    string keluhan;
    string status;
    JanjiTemu* next;
    JanjiTemu* prev;
};

// ==============================================
// CLASS DOUBLY LINKED LIST TEMPLATE
// ==============================================
template <typename T>
class DoublyLinkedList {
private:
    T* head;
    T* tail;
    int size;

public:
    DoublyLinkedList() : head(NULL), tail(NULL), size(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    void addToEnd(T* newNode) {
        if (!head) {
            head = tail = newNode;
            newNode->next = newNode->prev = NULL;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = NULL;
            tail = newNode;
        }
        size++;
    }

    void addToFront(T* newNode) {
        if (!head) {
            head = tail = newNode;
            newNode->next = newNode->prev = NULL;
        } else {
            newNode->next = head;
            head->prev = newNode;
            newNode->prev = NULL;
            head = newNode;
        }
        size++;
    }

    T* findPemilikByUsername(string username) {
        T* current = head;
        while (current) {
            if (current->username == username) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    T* findDokterByUsername(string username) {
        T* current = head;
        while (current) {
            if (current->username == username) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    JanjiTemu* findJanjiByPemilik(string username) {
        T* current = head;
        while (current) {
            if (current->namaPemilik == username) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    void removeByUsername(string username) {
        T* current = head;
        while (current) {
            if (current->username == username) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                delete current;
                size--;
                return;
            }
            current = current->next;
        }
    }

    void removeJanjiByIndex(int index) {
        if (index < 0 || index >= size) return;
        
        T* current = head;
        for (int i = 0; i < index && current; i++) {
            current = current->next;
        }
        
        if (current) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            delete current;
            size--;
        }
    }

    void displayAllPemilik() {
        T* current = head;
        int counter = 1;
        while (current) {
            cout << counter << ". " << current->username;
            cout << " - " << current->hewan.nama;
            cout << " (" << current->hewan.jenis << ")";
            cout << " - Status: " << (current->aktif ? "Aktif" : "Nonaktif") << "\n";
            current = current->next;
            counter++;
        }
    }

    void displayAllDokter() {
        T* current = head;
        int counter = 1;
        while (current) {
            cout << counter << ". " << current->username;
            cout << " - " << current->nama;
            cout << " (" << current->spesialisasi << ")";
            cout << " - Status: " << (current->aktif ? "Aktif" : "Nonaktif") << "\n";
            current = current->next;
            counter++;
        }
    }

    void displayAllJanji() {
        T* current = head;
        int counter = 1;
        while (current) {
            cout << counter << ". " << current->namaHewan;
            cout << " - Pemilik: " << current->namaPemilik;
            cout << " - Tanggal: " << current->tanggal;
            cout << " - Jam: " << current->jam;
            cout << " - Status: " << current->status << "\n";
            cout << "   Keluhan: " << current->keluhan << "\n\n";
            current = current->next;
            counter++;
        }
    }

    void clear() {
        T* current = head;
        while (current) {
            T* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = NULL;
        size = 0;
    }

    T* getHead() { return head; }
    T* getTail() { return tail; }
    int getSize() { return size; }

    T* getAt(int index) {
        if (index < 0 || index >= size) return NULL;
        
        T* current = head;
        for (int i = 0; i < index && current; i++) {
            current = current->next;
        }
        return current;
    }
};

// ==============================================
// DEKLARASI OBJEK LINKED LIST
// ==============================================
DoublyLinkedList<Pemilik> listPemilik;
DoublyLinkedList<Dokter> listDokter;
DoublyLinkedList<JanjiTemu> listJanji;

// ==============================================
// PROTOTYPE FUNGSI
// ==============================================
void tampilkanMenuLogin();
void registrasiPemilik();
void loginPemilik();
void loginDokter();
void menuPemilik(string username);
void menuDokter(string username);
void buatJanjiTemu(string username);
void lihatRiwayat(string username);
void kelolaDataPasien();
void kelolaJadwal();
void gantiPasswordPemilik(string username);
void lupaPassword();
bool cekUsernameTerdaftar(string username);
void tampilkanHeader();
void kelolaPengguna();
void kelolaPemilik();
void kelolaDokter();
void tambahDokter();
void nonaktifkanPengguna();
void resetPasswordPengguna();
void lihatSemuaPengguna();

// ==============================================
// FUNGSI UTAMA
// ==============================================
int main() {
    // Inisialisasi data dummy pemilik menggunakan linked list
    Pemilik* pemilik1 = new Pemilik{
        "user1", "pass1", "user1@email.com", "08123456789", 
        {"Buddy", "Anjing", 3, "Tidak ada"}, {"Kontrol rutin", "Vaksinasi"}, 2, true,
        NULL, NULL
    };
    listPemilik.addToEnd(pemilik1);

    Pemilik* pemilik2 = new Pemilik{
        "user2", "pass2", "user2@email.com", "08765432109", 
        {"Milo", "Kucing", 2, "Flu kucing"}, {"Pemeriksaan umum"}, 1, true,
        NULL, NULL
    };
    listPemilik.addToEnd(pemilik2);
    
    // Inisialisasi data dummy dokter
    Dokter* dokter1 = new Dokter{
        "dokter1", "doc1", "Dr. Ahmad Wijaya", "Hewan Peliharaan", true,
        NULL, NULL
    };
    listDokter.addToEnd(dokter1);

    Dokter* dokter2 = new Dokter{
        "dokter2", "doc2", "Dr. Sari Dewi", "Hewan Eksotis", true,
        NULL, NULL
    };
    listDokter.addToEnd(dokter2);

    Dokter* admin = new Dokter{
        "admin", "admin123", "Administrator", "Admin Sistem", true,
        NULL, NULL
    };
    listDokter.addToEnd(admin);
    
    tampilkanHeader();
    tampilkanMenuLogin();
    
    // Cleanup (sebenarnya dilakukan oleh destructor, tapi untuk amannya)
    listPemilik.clear();
    listDokter.clear();
    listJanji.clear();
    
    return 0;
}

void tampilkanHeader() {
    cout << "========================================\n";
    cout << "     APLIKASI KLINIK HEWAN SEHAT\n";
    cout << "     (Doubly Linked List Version)\n";
    cout << "========================================\n";
}

void tampilkanMenuLogin() {
    int pilihan;
    
    while(true) {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Registrasi Pemilik Baru\n";
        cout << "2. Login sebagai Pemilik Hewan\n";
        cout << "3. Login sebagai Dokter/Admin\n";
        cout << "4. Lupa Password\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        switch(pilihan) {
            case 1:
                registrasiPemilik();
                break;
            case 2:
                loginPemilik();
                break;
            case 3:
                loginDokter();
                break;
            case 4:
                lupaPassword();
                break;
            case 5:
                cout << "Terima kasih telah menggunakan aplikasi!\n";
                return;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }
}

void registrasiPemilik() {
    if(listPemilik.getSize() >= 50) {
        cout << "Maaf, kuota pendaftaran sudah penuh.\n";
        return;
    }
    
    cout << "\n=== REGISTRASI PEMILIK BARU ===\n";
    
    string username, password, email, noTelepon;
    string namaHewan, jenisHewan;
    int umurHewan;
    
    cout << "Data Pemilik:\n";
    cout << "Username: ";
    getline(cin, username);
    
    if(cekUsernameTerdaftar(username)) {
        cout << "Username sudah terdaftar. Silakan gunakan username lain.\n";
        return;
    }
    
    cout << "Password: ";
    getline(cin, password);
    cout << "Email: ";
    getline(cin, email);
    cout << "No. Telepon: ";
    getline(cin, noTelepon);
    
    cout << "\nData Hewan Peliharaan:\n";
    cout << "Nama Hewan: ";
    getline(cin, namaHewan);
    cout << "Jenis Hewan: ";
    getline(cin, jenisHewan);
    cout << "Umur Hewan (tahun): ";
    cin >> umurHewan;
    cin.ignore();
    
    Pemilik* newPemilik = new Pemilik{
        username, password, email, noTelepon,
        {namaHewan, jenisHewan, umurHewan, "Tidak ada"}, {}, 0, true,
        NULL, NULL
    };
    
    listPemilik.addToEnd(newPemilik);
    cout << "\nRegistrasi berhasil! Silakan login dengan username: " << username << "\n";
}

bool cekUsernameTerdaftar(string username) {
    // Cek di list pemilik
    Pemilik* foundPemilik = listPemilik.findPemilikByUsername(username);
    if (foundPemilik) return true;
    
    // Cek di list dokter
    Dokter* foundDokter = listDokter.findDokterByUsername(username);
    if (foundDokter) return true;
    
    return false;
}

void loginPemilik() {
    string username, password;
    
    cout << "\n=== LOGIN PEMILIK HEWAN ===\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);
    
    Pemilik* pemilik = listPemilik.findPemilikByUsername(username);
    if(pemilik && pemilik->password == password) {
        if(!pemilik->aktif) {
            cout << "Akun Anda dinonaktifkan. Hubungi administrator.\n";
            return;
        }
        cout << "Login berhasil! Selamat datang " << username << "!\n";
        menuPemilik(username);
        return;
    }
    
    cout << "Username atau password salah!\n";
}

void loginDokter() {
    string username, password;
    
    cout << "\n=== LOGIN DOKTER/ADMIN ===\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);
    
    Dokter* dokter = listDokter.findDokterByUsername(username);
    if(dokter && dokter->password == password) {
        if(!dokter->aktif) {
            cout << "Akun Anda dinonaktifkan. Hubungi administrator.\n";
            return;
        }
        cout << "Login berhasil! Selamat datang " << dokter->nama << "!\n";
        menuDokter(username);
        return;
    }
    
    cout << "Username atau password salah!\n";
}

void lupaPassword() {
    string username, email;
    
    cout << "\n=== LUPA PASSWORD ===\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Email: ";
    getline(cin, email);
    
    // Cari di data pemilik
    Pemilik* pemilik = listPemilik.findPemilikByUsername(username);
    if(pemilik && pemilik->email == email) {
        string passwordBaru;
        cout << "Verifikasi berhasil. Masukkan password baru: ";
        getline(cin, passwordBaru);
        pemilik->password = passwordBaru;
        cout << "Password berhasil direset! Silakan login dengan password baru.\n";
        return;
    }
    
    // Cari di data dokter
    Dokter* dokter = listDokter.findDokterByUsername(username);
    if(dokter) {
        cout << "Untuk reset password dokter, harap hubungi administrator.\n";
        return;
    }
    
    cout << "Data tidak ditemukan. Pastikan username dan email benar.\n";
}

void menuPemilik(string username) {
    int pilihan;
    Pemilik* pemilikAktif = listPemilik.findPemilikByUsername(username);
    
    if(!pemilikAktif) return;
    
    while(true) {
        cout << "\n=== MENU PEMILIK HEWAN ===\n";
        cout << "Hewan: " << pemilikAktif->hewan.nama << " (" << pemilikAktif->hewan.jenis << ")\n";
        cout << "1. Buat Janji Temu\n";
        cout << "2. Lihat Riwayat Pemeriksaan\n";
        cout << "3. Ganti Password\n";
        cout << "4. Logout\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        switch(pilihan) {
            case 1:
                buatJanjiTemu(username);
                break;
            case 2:
                lihatRiwayat(username);
                break;
            case 3:
                gantiPasswordPemilik(username);
                break;
            case 4:
                cout << "Logout berhasil!\n";
                return;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }
}

void menuDokter(string username) {
    int pilihan;
    
    while(true) {
        cout << "\n=== MENU DOKTER/ADMIN ===\n";
        cout << "1. Kelola Data Pasien\n";
        cout << "2. Kelola Jadwal Janji Temu\n";
        cout << "3. Kelola Pengguna\n";
        cout << "4. Lihat Data Pemilik Terdaftar\n";
        cout << "5. Logout\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        switch(pilihan) {
            case 1:
                kelolaDataPasien();
                break;
            case 2:
                kelolaJadwal();
                break;
            case 3:
                kelolaPengguna();
                break;
            case 4:
                // Fitur tambahan untuk admin
                cout << "\n=== DATA PEMILIK TERDAFTAR ===\n";
                listPemilik.displayAllPemilik();
                break;
            case 5:
                cout << "Logout berhasil!\n";
                return;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }
}

// ==============================================
// FUNGSI KELOLA PENGGUNA (DOUBLY LINKED LIST)
// ==============================================

void kelolaPengguna() {
    int pilihan;
    
    while(true) {
        cout << "\n=== KELOLA PENGGUNA ===\n";
        cout << "1. Kelola Data Pemilik\n";
        cout << "2. Kelola Data Dokter\n";
        cout << "3. Tambah Dokter Baru\n";
        cout << "4. Nonaktifkan/Aktifkan Pengguna\n";
        cout << "5. Reset Password Pengguna\n";
        cout << "6. Lihat Semua Pengguna\n";
        cout << "7. Kembali ke Menu Utama\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        switch(pilihan) {
            case 1:
                kelolaPemilik();
                break;
            case 2:
                kelolaDokter();
                break;
            case 3:
                tambahDokter();
                break;
            case 4:
                nonaktifkanPengguna();
                break;
            case 5:
                resetPasswordPengguna();
                break;
            case 6:
                lihatSemuaPengguna();
                break;
            case 7:
                return;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }
}

void kelolaPemilik() {
    cout << "\n=== KELOLA DATA PEMILIK ===\n";
    
    if(listPemilik.getSize() == 0) {
        cout << "Tidak ada pemilik terdaftar.\n";
        return;
    }
    
    listPemilik.displayAllPemilik();
    
    cout << "\nPilih pemilik untuk detail lebih lanjut (0 untuk kembali): ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    if(pilihan > 0 && pilihan <= listPemilik.getSize()) {
        Pemilik* pemilik = listPemilik.getAt(pilihan - 1);
        if(!pemilik) return;
        
        cout << "\n=== DETAIL PEMILIK ===\n";
        cout << "Username: " << pemilik->username << "\n";
        cout << "Email: " << pemilik->email << "\n";
        cout << "No. Telepon: " << pemilik->noTelepon << "\n";
        cout << "Nama Hewan: " << pemilik->hewan.nama << "\n";
        cout << "Jenis Hewan: " << pemilik->hewan.jenis << "\n";
        cout << "Umur Hewan: " << pemilik->hewan.umur << " tahun\n";
        cout << "Status: " << (pemilik->aktif ? "Aktif" : "Nonaktif") << "\n";
        
        cout << "\n1. " << (pemilik->aktif ? "Nonaktifkan" : "Aktifkan") << " akun\n";
        cout << "2. Reset password\n";
        cout << "3. Hapus akun\n";
        cout << "4. Kembali\n";
        cout << "Pilih aksi: ";
        
        int aksi;
        cin >> aksi;
        cin.ignore();
        
        if(aksi == 1) {
            pemilik->aktif = !pemilik->aktif;
            cout << "Akun " << pemilik->username << " berhasil ";
            cout << (pemilik->aktif ? "diaktifkan" : "dinonaktifkan") << "!\n";
        } else if(aksi == 2) {
            string passwordBaru;
            cout << "Masukkan password baru: ";
            getline(cin, passwordBaru);
            pemilik->password = passwordBaru;
            cout << "Password berhasil direset!\n";
        } else if(aksi == 3) {
            char konfirmasi;
            cout << "Apakah Anda yakin ingin menghapus akun " << pemilik->username << "? (y/n): ";
            cin >> konfirmasi;
            if(konfirmasi == 'y' || konfirmasi == 'Y') {
                listPemilik.removeByUsername(pemilik->username);
                cout << "Akun berhasil dihapus!\n";
            }
        }
    }
}

void kelolaDokter() {
    cout << "\n=== KELOLA DATA DOKTER ===\n";
    
    if(listDokter.getSize() == 0) {
        cout << "Tidak ada dokter terdaftar.\n";
        return;
    }
    
    listDokter.displayAllDokter();
    
    cout << "\nPilih dokter untuk detail lebih lanjut (0 untuk kembali): ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    if(pilihan > 0 && pilihan <= listDokter.getSize()) {
        Dokter* dokter = listDokter.getAt(pilihan - 1);
        if(!dokter) return;
        
        cout << "\n=== DETAIL DOKTER ===\n";
        cout << "Username: " << dokter->username << "\n";
        cout << "Nama: " << dokter->nama << "\n";
        cout << "Spesialisasi: " << dokter->spesialisasi << "\n";
        cout << "Status: " << (dokter->aktif ? "Aktif" : "Nonaktif") << "\n";
        
        cout << "\n1. " << (dokter->aktif ? "Nonaktifkan" : "Aktifkan") << " akun\n";
        cout << "2. Reset password\n";
        cout << "3. Hapus akun\n";
        cout << "4. Kembali\n";
        cout << "Pilih aksi: ";
        
        int aksi;
        cin >> aksi;
        cin.ignore();
        
        if(aksi == 1) {
            dokter->aktif = !dokter->aktif;
            cout << "Akun " << dokter->username << " berhasil ";
            cout << (dokter->aktif ? "diaktifkan" : "dinonaktifkan") << "!\n";
        } else if(aksi == 2) {
            string passwordBaru;
            cout << "Masukkan password baru: ";
            getline(cin, passwordBaru);
            dokter->password = passwordBaru;
            cout << "Password berhasil direset!\n";
        } else if(aksi == 3) {
            char konfirmasi;
            cout << "Apakah Anda yakin ingin menghapus akun " << dokter->username << "? (y/n): ";
            cin >> konfirmasi;
            if(konfirmasi == 'y' || konfirmasi == 'Y') {
                listDokter.removeByUsername(dokter->username);
                cout << "Akun berhasil dihapus!\n";
            }
        }
    }
}

void tambahDokter() {
    if(listDokter.getSize() >= 5) {
        cout << "Maaf, kuota dokter sudah penuh.\n";
        return;
    }
    
    cout << "\n=== TAMBAH DOKTER BARU ===\n";
    
    string username, password, nama, spesialisasi;
    
    cout << "Username: ";
    getline(cin, username);
    
    if(cekUsernameTerdaftar(username)) {
        cout << "Username sudah terdaftar.\n";
        return;
    }
    
    cout << "Password: ";
    getline(cin, password);
    cout << "Nama Lengkap: ";
    getline(cin, nama);
    cout << "Spesialisasi: ";
    getline(cin, spesialisasi);
    
    Dokter* newDokter = new Dokter{
        username, password, nama, spesialisasi, true,
        NULL, NULL
    };
    
    listDokter.addToEnd(newDokter);
    cout << "Dokter baru berhasil ditambahkan!\n";
}

void nonaktifkanPengguna() {
    cout << "\n=== NONAKTIFKAN/AKTIFKAN PENGGUNA ===\n";
    
    cout << "Pilih jenis pengguna:\n";
    cout << "1. Pemilik Hewan\n";
    cout << "2. Dokter\n";
    cout << "Pilihan: ";
    
    int jenis;
    cin >> jenis;
    cin.ignore();
    
    if(jenis == 1) {
        kelolaPemilik();
    } else if(jenis == 2) {
        kelolaDokter();
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

void resetPasswordPengguna() {
    cout << "\n=== RESET PASSWORD PENGGUNA ===\n";
    
    cout << "Pilih jenis pengguna:\n";
    cout << "1. Pemilik Hewan\n";
    cout << "2. Dokter\n";
    cout << "Pilihan: ";
    
    int jenis;
    cin >> jenis;
    cin.ignore();
    
    if(jenis == 1) {
        kelolaPemilik();
    } else if(jenis == 2) {
        kelolaDokter();
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

void lihatSemuaPengguna() {
    cout << "\n=== SEMUA PENGGUNA TERDAFTAR ===\n";
    
    cout << "\n--- PEMILIK HEWAN ---\n";
    listPemilik.displayAllPemilik();
    
    cout << "\n--- DOKTER & ADMIN ---\n";
    listDokter.displayAllDokter();
    
    cout << "\nTotal Pemilik: " << listPemilik.getSize() << "\n";
    cout << "Total Dokter/Admin: " << listDokter.getSize() << "\n";
}

// ==============================================
// FUNGSI-FUNGSI LAINNYA (DOUBLY LINKED LIST)
// ==============================================

void buatJanjiTemu(string username) {
    Pemilik* pemilikAktif = listPemilik.findPemilikByUsername(username);
    
    if(!pemilikAktif) return;
    
    cout << "\n=== BUAT JANJI TEMU ===\n";
    cout << "Hewan: " << pemilikAktif->hewan.nama << "\n";
    
    if(listJanji.getSize() < 50) {
        JanjiTemu* newJanji = new JanjiTemu;
        newJanji->namaPemilik = username;
        newJanji->namaHewan = pemilikAktif->hewan.nama;
        
        cout << "Tanggal (DD/MM/YYYY): ";
        getline(cin, newJanji->tanggal);
        cout << "Jam: ";
        getline(cin, newJanji->jam);
        cout << "Keluhan: ";
        getline(cin, newJanji->keluhan);
        
        newJanji->status = "Menunggu";
        newJanji->next = NULL;
        newJanji->prev = NULL;
        
        listJanji.addToEnd(newJanji);
        cout << "Janji temu berhasil dibuat! Status: Menunggu konfirmasi.\n";
    } else {
        cout << "Maaf, kuota janji temu sudah penuh.\n";
    }
}

void lihatRiwayat(string username) {
    Pemilik* pemilikAktif = listPemilik.findPemilikByUsername(username);
    
    if(!pemilikAktif) return;
    
    cout << "\n=== RIWAYAT PEMERIKSAAN ===\n";
    cout << "Hewan: " << pemilikAktif->hewan.nama << "\n";
    cout << "Jenis: " << pemilikAktif->hewan.jenis << "\n";
    cout << "Umur: " << pemilikAktif->hewan.umur << " tahun\n";
    cout << "Riwayat Penyakit: " << pemilikAktif->hewan.riwayatPenyakit << "\n";
    
    cout << "\nRiwayat Kunjungan:\n";
    if(pemilikAktif->jumlahRiwayat > 0) {
        for(int i = 0; i < pemilikAktif->jumlahRiwayat; i++) {
            cout << "- " << pemilikAktif->riwayatKunjungan[i] << "\n";
        }
    } else {
        cout << "Belum ada riwayat kunjungan.\n";
    }
    
    cout << "\nJanji Temu yang Dijadwalkan:\n";
    bool adaJanji = false;
    
    // Traverse linked list janji temu
    JanjiTemu* current = listJanji.getHead();
    while(current) {
        if(current->namaPemilik == username) {
            cout << "- Tanggal: " << current->tanggal;
            cout << " | Jam: " << current->jam;
            cout << " | Keluhan: " << current->keluhan;
            cout << " | Status: " << current->status << "\n";
            adaJanji = true;
        }
        current = current->next;
    }
    
    if(!adaJanji) {
        cout << "Tidak ada janji temu yang dijadwalkan.\n";
    }
}

void gantiPasswordPemilik(string username) {
    string passwordLama, passwordBaru;
    
    cout << "\n=== GANTI PASSWORD ===\n";
    cout << "Password lama: ";
    getline(cin, passwordLama);
    
    Pemilik* pemilik = listPemilik.findPemilikByUsername(username);
    if(pemilik) {
        if(pemilik->password == passwordLama) {
            cout << "Password baru: ";
            getline(cin, passwordBaru);
            pemilik->password = passwordBaru;
            cout << "Password berhasil diubah!\n";
        } else {
            cout << "Password lama salah!\n";
        }
    }
}

void kelolaDataPasien() {
    int pilihan;
    
    cout << "\n=== KELOLA DATA PASIEN ===\n";
    cout << "Daftar Pasien Terdaftar:\n";
    
    listPemilik.displayAllPemilik();
    
    cout << "\nPilih pasien untuk melihat detail (0 untuk kembali): ";
    cin >> pilihan;
    cin.ignore();
    
    if(pilihan > 0 && pilihan <= listPemilik.getSize()) {
        Pemilik* pemilik = listPemilik.getAt(pilihan - 1);
        if(!pemilik) return;
        
        cout << "\n=== DETAIL PASIEN ===\n";
        cout << "Nama Hewan: " << pemilik->hewan.nama << "\n";
        cout << "Jenis: " << pemilik->hewan.jenis << "\n";
        cout << "Umur: " << pemilik->hewan.umur << " tahun\n";
        cout << "Riwayat Penyakit: " << pemilik->hewan.riwayatPenyakit << "\n";
        cout << "Pemilik: " << pemilik->username << "\n";
        cout << "Email: " << pemilik->email << "\n";
        cout << "Telepon: " << pemilik->noTelepon << "\n";
        
        cout << "\n1. Update riwayat penyakit\n";
        cout << "2. Tambah riwayat kunjungan\n";
        cout << "3. Kembali\n";
        cout << "Pilih aksi: ";
        
        int aksi;
        cin >> aksi;
        cin.ignore();
        
        if(aksi == 1) {
            cout << "Masukkan riwayat penyakit baru: ";
            getline(cin, pemilik->hewan.riwayatPenyakit);
            cout << "Riwayat penyakit berhasil diperbarui!\n";
        } else if(aksi == 2) {
            if(pemilik->jumlahRiwayat < 10) {
                cout << "Masukkan riwayat kunjungan: ";
                getline(cin, pemilik->riwayatKunjungan[pemilik->jumlahRiwayat]);
                pemilik->jumlahRiwayat++;
                cout << "Riwayat kunjungan berhasil ditambahkan!\n";
            } else {
                cout << "Maaf, kuota riwayat sudah penuh.\n";
            }
        }
    }
}

void kelolaJadwal() {
    cout << "\n=== KELOLA JADWAL JANJI TEMU ===\n";
    
    if(listJanji.getSize() == 0) {
        cout << "Tidak ada janji temu yang menunggu.\n";
        return;
    }
    
    listJanji.displayAllJanji();
    
    cout << "Pilih janji untuk mengubah status (0 untuk kembali): ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    if(pilihan > 0 && pilihan <= listJanji.getSize()) {
        JanjiTemu* janji = listJanji.getAt(pilihan - 1);
        if(!janji) return;
        
        cout << "Ubah status menjadi (Menunggu/Dikonfirmasi/Selesai/Batal): ";
        getline(cin, janji->status);
        cout << "Status berhasil diubah menjadi: " << janji->status << "\n";
    }
}
