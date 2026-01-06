#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ==============================================
// STRUCT DASAR HEWAN
// ==============================================
struct Hewan {
    int id;
    string nama;
    string jenis;
    string ras;
    int umur;
    string jenis_kelamin;
};

// ==============================================
// STRUCT NODE UNTUK DOUBLY LINKED LIST
// ==============================================
struct NodeHewan {
    Hewan data;
    NodeHewan* next;
    NodeHewan* prev;
    
    NodeHewan(Hewan h) : data(h), next(NULL), prev(NULL) {}
};

// ==============================================
// CLASS DOUBLY LINKED LIST UNTUK DATA HEWAN
// ==============================================
class DoublyLinkedListHewan {
private:
    NodeHewan* head;
    NodeHewan* tail;
    int size;
    int idCounter;

public:
    DoublyLinkedListHewan() : head(NULL), tail(NULL), size(0), idCounter(1) {}

    ~DoublyLinkedListHewan() {
        clear();
    }

    // Fungsi untuk membersihkan input buffer
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Menambahkan data hewan baru
    void tambahHewan(Hewan hewanBaru) {
        hewanBaru.id = idCounter++;
        NodeHewan* newNode = new NodeHewan(hewanBaru);
        
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    // Mencari hewan berdasarkan ID (linear search)
    NodeHewan* cariByID(int id) {
        NodeHewan* current = head;
        while (current) {
            if (current->data.id == id) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    // Mencari hewan berdasarkan Nama (linear search)
    NodeHewan* cariByNama(string nama) {
        NodeHewan* current = head;
        while (current) {
            if (current->data.nama == nama) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    // Mencari hewan berdasarkan Jenis (sequential search)
    void cariByJenis(string jenis) {
        NodeHewan* current = head;
        bool ditemukan = false;
        
        cout << "\n=== HASIL PENCARIAN UNTUK JENIS '" << jenis << "' ===\n";
        cout << string(80, '=') << "\n";
        cout << setw(5) << "ID" << setw(15) << "Nama" << setw(15) << "Jenis" 
             << setw(15) << "Ras" << setw(10) << "Umur" << setw(15) << "Jenis Kelamin\n";
        cout << string(80, '=') << "\n";
        
        while (current) {
            if (current->data.jenis == jenis) {
                cout << setw(5) << current->data.id 
                     << setw(15) << current->data.nama 
                     << setw(15) << current->data.jenis 
                     << setw(15) << current->data.ras 
                     << setw(10) << current->data.umur 
                     << setw(15) << current->data.jenis_kelamin << "\n";
                ditemukan = true;
            }
            current = current->next;
        }
        
        if (!ditemukan) {
            cout << "Tidak ada data hewan dengan jenis '" << jenis << "'\n";
        }
        cout << string(80, '=') << "\n";
    }

    // Menghapus hewan berdasarkan ID
    bool hapusByID(int id) {
        NodeHewan* node = cariByID(id);
        if (!node) return false;
        
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }
        
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
        
        delete node;
        size--;
        return true;
    }

    // Menampilkan semua data hewan
    void tampilkanSemua() {
        if (size == 0) {
            cout << "Tidak ada data hewan.\n";
            return;
        }
        
        cout << "\n" << string(80, '=') << "\n";
        cout << "                       DATA HEWAN KLINIK\n";
        cout << string(80, '=') << "\n";
        cout << setw(5) << "ID" << setw(15) << "Nama" << setw(15) << "Jenis" 
             << setw(15) << "Ras" << setw(10) << "Umur" << setw(15) << "Jenis Kelamin\n";
        cout << string(80, '=') << "\n";
        
        NodeHewan* current = head;
        while (current) {
            cout << setw(5) << current->data.id 
                 << setw(15) << current->data.nama 
                 << setw(15) << current->data.jenis 
                 << setw(15) << current->data.ras 
                 << setw(10) << current->data.umur 
                 << setw(15) << current->data.jenis_kelamin << "\n";
            current = current->next;
        }
        cout << string(80, '=') << "\n";
        cout << "Total data: " << size << " hewan\n";
    }

    // Sorting berdasarkan ID (Insertion Sort pada linked list)
    void sortByID() {
        if (!head || !head->next) return;
        
        NodeHewan* sorted = NULL;
        NodeHewan* current = head;
        
        while (current) {
            NodeHewan* next = current->next;
            current->prev = current->next = NULL;
            
            // Insert current node into sorted list
            if (!sorted) {
                sorted = current;
            } else if (sorted->data.id >= current->data.id) {
                current->next = sorted;
                sorted->prev = current;
                sorted = current;
            } else {
                NodeHewan* temp = sorted;
                while (temp->next && temp->next->data.id < current->data.id) {
                    temp = temp->next;
                }
                current->next = temp->next;
                if (temp->next) {
                    temp->next->prev = current;
                }
                temp->next = current;
                current->prev = temp;
            }
            current = next;
        }
        head = sorted;
        
        // Update tail
        tail = head;
        while (tail && tail->next) {
            tail = tail->next;
        }
    }

    // Sorting berdasarkan Nama (Bubble Sort pada linked list)
    void sortByNama() {
        if (!head || !head->next) return;
        
        bool swapped;
        do {
            swapped = false;
            NodeHewan* current = head;
            
            while (current->next) {
                if (current->data.nama > current->next->data.nama) {
                    // Swap data
                    Hewan temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    // Sorting berdasarkan Umur (Selection Sort pada linked list)
    void sortByUmur() {
        if (!head || !head->next) return;
        
        NodeHewan* current = head;
        
        while (current) {
            NodeHewan* minNode = current;
            NodeHewan* temp = current->next;
            
            while (temp) {
                if (temp->data.umur < minNode->data.umur) {
                    minNode = temp;
                }
                temp = temp->next;
            }
            
            // Swap data
            if (minNode != current) {
                Hewan tempData = current->data;
                current->data = minNode->data;
                minNode->data = tempData;
            }
            
            current = current->next;
        }
    }

    // Mendapatkan node pada posisi tertentu
    NodeHewan* getAt(int index) {
        if (index < 0 || index >= size) return NULL;
        
        NodeHewan* current = head;
        for (int i = 0; i < index && current; i++) {
            current = current->next;
        }
        return current;
    }

    // Mendapatkan jumlah data
    int getSize() { return size; }

    // Mendapatkan ID counter
    int getIDCounter() { return idCounter; }

    // Set ID counter
    void setIDCounter(int counter) { idCounter = counter; }

    // Membersihkan semua data
    void clear() {
        NodeHewan* current = head;
        while (current) {
            NodeHewan* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = NULL;
        size = 0;
        idCounter = 1;
    }

    // Mendapatkan head
    NodeHewan* getHead() { return head; }
};

// ==============================================
// OBJEK LINKED LIST GLOBAL
// ==============================================
DoublyLinkedListHewan listHewan;

// ==============================================
// PROTOTYPE FUNGSI
// ==============================================
void tambahDataHewan();
void tampilkanDataHewan();
void editDataHewan();
void hapusDataHewan();
void cariHewan();
void menuSorting();
void menuUtama();

// ==============================================
// FUNGSI UTAMA
// ==============================================
int main() {
    cout << "========================================\n";
    cout << "   SISTEM MANAJEMEN DATA HEWAN KLINIK\n";
    cout << "       (Doubly Linked List Version)\n";
    cout << "========================================\n";
    
    // Data sample untuk testing
    Hewan hewan1 = {1, "Budi", "Kucing", "Persia", 2, "Jantan"};
    Hewan hewan2 = {2, "Molly", "Anjing", "Golden Retriever", 3, "Betina"};
    Hewan hewan3 = {3, "Snowy", "Kelinci", "Holland Lop", 1, "Betina"};
    
    listHewan.tambahHewan(hewan1);
    listHewan.tambahHewan(hewan2);
    listHewan.tambahHewan(hewan3);
    listHewan.setIDCounter(4);
    
    // Sort data awal berdasarkan ID
    listHewan.sortByID();
    
    menuUtama();
    
    return 0;
}

// ==============================================
// IMPLEMENTASI FUNGSI-FUNGSI
// ==============================================
void tambahDataHewan() {
    if (listHewan.getSize() >= 1000) {
        cout << "Kapasitas data hewan penuh! Tidak bisa menambah data baru.\n";
        return;
    }
    
    Hewan hewanBaru;
    cout << "\n=== TAMBAH DATA HEWAN BARU ===\n";
    
    hewanBaru.id = listHewan.getIDCounter();
    cout << "ID Hewan: " << hewanBaru.id << " (otomatis)\n";
    
    cout << "Nama Hewan: ";
    listHewan.clearInputBuffer();
    getline(cin, hewanBaru.nama);
    
    cout << "Jenis (kucing/anjing/kelinci/dll): ";
    getline(cin, hewanBaru.jenis);
    
    cout << "Ras: ";
    getline(cin, hewanBaru.ras);
    
    cout << "Umur (tahun): ";
    while (!(cin >> hewanBaru.umur) || hewanBaru.umur < 0) {
        cout << "Umur harus angka positif: ";
        listHewan.clearInputBuffer();
    }
    
    listHewan.clearInputBuffer();
    cout << "Jenis Kelamin (jantan/betina): ";
    getline(cin, hewanBaru.jenis_kelamin);
    
    listHewan.tambahHewan(hewanBaru);
    listHewan.sortByID();
    cout << "\nData hewan berhasil ditambahkan!\n";
}

void tampilkanDataHewan() {
    listHewan.tampilkanSemua();
}

void editDataHewan() {
    if (listHewan.getSize() == 0) {
        cout << "Tidak ada data hewan untuk diedit.\n";
        return;
    }
    
    int id;
    cout << "\n=== EDIT DATA HEWAN ===\n";
    cout << "Masukkan ID hewan yang akan diedit: ";
    cin >> id;
    
    NodeHewan* node = listHewan.cariByID(id);
    if (!node) {
        cout << "Data hewan dengan ID " << id << " tidak ditemukan!\n";
        return;
    }
    
    cout << "\nData saat ini:\n";
    cout << "Nama: " << node->data.nama << "\n";
    cout << "Jenis: " << node->data.jenis << "\n";
    cout << "Ras: " << node->data.ras << "\n";
    cout << "Umur: " << node->data.umur << "\n";
    cout << "Jenis Kelamin: " << node->data.jenis_kelamin << "\n";
    
    cout << "\nMasukkan data baru:\n";
    listHewan.clearInputBuffer();
    
    cout << "Nama Hewan: ";
    getline(cin, node->data.nama);
    
    cout << "Jenis: ";
    getline(cin, node->data.jenis);
    
    cout << "Ras: ";
    getline(cin, node->data.ras);
    
    cout << "Umur: ";
    while (!(cin >> node->data.umur) || node->data.umur < 0) {
        cout << "Umur harus angka positif: ";
        listHewan.clearInputBuffer();
    }
    
    listHewan.clearInputBuffer();
    cout << "Jenis Kelamin: ";
    getline(cin, node->data.jenis_kelamin);
    
    // Sort ulang setelah edit
    listHewan.sortByID();
    cout << "\nData hewan berhasil diupdate!\n";
}

void hapusDataHewan() {
    if (listHewan.getSize() == 0) {
        cout << "Tidak ada data hewan untuk dihapus.\n";
        return;
    }
    
    int id;
    cout << "\n=== HAPUS DATA HEWAN ===\n";
    cout << "Masukkan ID hewan yang akan dihapus: ";
    cin >> id;
    
    NodeHewan* node = listHewan.cariByID(id);
    if (!node) {
        cout << "Data hewan dengan ID " << id << " tidak ditemukan!\n";
        return;
    }
    
    cout << "\nData hewan yang akan dihapus:\n";
    cout << "ID: " << node->data.id << "\n";
    cout << "Nama: " << node->data.nama << "\n";
    cout << "Jenis: " << node->data.jenis << "\n";
    cout << "Ras: " << node->data.ras << "\n";
    
    cout << "\nApakah Anda yakin ingin menghapus data ini? (y/n): ";
    char konfirmasi;
    cin >> konfirmasi;
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        if (listHewan.hapusByID(id)) {
            cout << "Data hewan berhasil dihapus!\n";
        } else {
            cout << "Gagal menghapus data hewan!\n";
        }
    } else {
        cout << "Penghapusan dibatalkan.\n";
    }
}

void cariHewan() {
    if (listHewan.getSize() == 0) {
        cout << "Tidak ada data hewan untuk dicari.\n";
        return;
    }
    
    int pilihan;
    cout << "\n=== PENCARIAN HEWAN ===\n";
    cout << "1. Cari berdasarkan ID\n";
    cout << "2. Cari berdasarkan Nama\n";
    cout << "3. Cari berdasarkan Jenis\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    
    if (pilihan == 1) {
        int id;
        cout << "Masukkan ID hewan: ";
        cin >> id;
        NodeHewan* node = listHewan.cariByID(id);
        if (node) {
            cout << "\nData ditemukan:\n";
            cout << string(40, '-') << "\n";
            cout << "ID: " << node->data.id << "\n";
            cout << "Nama: " << node->data.nama << "\n";
            cout << "Jenis: " << node->data.jenis << "\n";
            cout << "Ras: " << node->data.ras << "\n";
            cout << "Umur: " << node->data.umur << " tahun\n";
            cout << "Jenis Kelamin: " << node->data.jenis_kelamin << "\n";
            cout << string(40, '-') << "\n";
        } else {
            cout << "Data tidak ditemukan!\n";
        }
    }
    else if (pilihan == 2) {
        string nama;
        cout << "Masukkan nama hewan: ";
        listHewan.clearInputBuffer();
        getline(cin, nama);
        
        // Sort dulu berdasarkan nama
        listHewan.sortByNama();
        NodeHewan* node = listHewan.cariByNama(nama);
        if (node) {
            cout << "\nData ditemukan:\n";
            cout << string(40, '-') << "\n";
            cout << "ID: " << node->data.id << "\n";
            cout << "Nama: " << node->data.nama << "\n";
            cout << "Jenis: " << node->data.jenis << "\n";
            cout << "Ras: " << node->data.ras << "\n";
            cout << "Umur: " << node->data.umur << " tahun\n";
            cout << "Jenis Kelamin: " << node->data.jenis_kelamin << "\n";
            cout << string(40, '-') << "\n";
        } else {
            cout << "Data tidak ditemukan!\n";
        }
        // Kembalikan ke sort by ID
        listHewan.sortByID();
    }
    else if (pilihan == 3) {
        string jenis;
        cout << "Masukkan jenis hewan: ";
        listHewan.clearInputBuffer();
        getline(cin, jenis);
        listHewan.cariByJenis(jenis);
    }
    else {
        cout << "Pilihan tidak valid!\n";
    }
}

void menuSorting() {
    if (listHewan.getSize() == 0) {
        cout << "Tidak ada data hewan untuk di-sort.\n";
        return;
    }
    
    int pilihan;
    cout << "\n=== SORTING DATA HEWAN ===\n";
    cout << "1. Sort by ID\n";
    cout << "2. Sort by Nama\n";
    cout << "3. Sort by Umur\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    
    if (pilihan == 1) {
        listHewan.sortByID();
        cout << "Data berhasil diurutkan berdasarkan ID!\n";
    } else if (pilihan == 2) {
        listHewan.sortByNama();
        cout << "Data berhasil diurutkan berdasarkan Nama!\n";
    } else if (pilihan == 3) {
        listHewan.sortByUmur();
        cout << "Data berhasil diurutkan berdasarkan Umur!\n";
    } else {
        cout << "Pilihan tidak valid!\n";
        return;
    }
    
    listHewan.tampilkanSemua();
}

void menuUtama() {
    while (true) {
        cout << "\n=== SISTEM MANAJEMEN DATA HEWAN KLINIK ===\n";
        cout << "1. Tambah Data Hewan\n";
        cout << "2. Tampilkan Semua Data Hewan\n";
        cout << "3. Edit Data Hewan\n";
        cout << "4. Hapus Data Hewan\n";
        cout << "5. Cari Hewan\n";
        cout << "6. Sorting Data Hewan\n";
        cout << "7. Keluar\n";
        cout << "Pilihan: ";
        
        int pilihan;
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tambahDataHewan();
                break;
            case 2:
                tampilkanDataHewan();
                break;
            case 3:
                editDataHewan();
                break;
            case 4:
                hapusDataHewan();
                break;
            case 5:
                cariHewan();
                break;
            case 6:
                menuSorting();
                break;
            case 7:
                cout << "Terima kasih telah menggunakan sistem manajemen data hewan!\n";
                return;
            default:
                cout << "Pilihan tidak valid! Silakan pilih 1-7.\n";
                listHewan.clearInputBuffer();
        }
    }
}
