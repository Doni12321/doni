#include <iostream>
using namespace std;

// Struktur untuk node linked list
struct Node {
    int data;       // Data yang disimpan dalam node
    Node* next;    // Pointer ke node berikutnya
};

// Fungsi untuk menghitung banyaknya elemen dalam linked list
int hitungElemen(Node* head) {
    int count = 0; // Inisialisasi count
    Node* current = head; // Pointer untuk traversing linked list

    // Traversing linked list
    while (current != NULL) {
        count++; // Tambah count untuk setiap node
        current = current->next; // Pindah ke node berikutnya
    }

    return count; // Kembalikan jumlah elemen
}

// Fungsi untuk menambahkan node baru di akhir linked list
void tambahNode(Node*& head, int data) {
    Node* newNode = new Node(); // Buat node baru
    newNode->data = data; // Set data
    newNode->next = NULL; // Set next ke nullptr

    if (head == NULL) {
        head = newNode; // Jika linked list kosong, node baru menjadi head
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next; // Pindah ke node terakhir
        }
        temp->next = newNode; // Tambahkan node baru di akhir
    }
}

// Fungsi untuk membersihkan memori linked list
void hapusLinkedList(Node*& head) {
    Node* current = head;
    while (current != NULL) {
        Node* nextNode = current->next;
        delete current; // Hapus node saat ini
        current = nextNode; // Pindah ke node berikutnya
    }
    head = NULL; // Set head ke nullptr setelah dihapus
}

int main() {
    Node* head = NULL; // Inisialisasi head linked list

    // Menambahkan beberapa elemen ke linked list
    tambahNode(head, 10);
    tambahNode(head, 20);
    tambahNode(head, 30);
    tambahNode(head, 40);

    // Menghitung dan menampilkan banyaknya elemen
    int jumlahElemen = hitungElemen(head);
    cout << "Banyaknya elemen dalam linked list: " << jumlahElemen << endl;

    // Membersihkan memori
    hapusLinkedList(head);

    return 0;
}

