#include <iostream>
using namespace std;

void bubbleSort(int data[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (data[j] > data[j + 1])
                swap(data[j], data[j + 1]);
}

int binarySearch(int data[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (data[mid] == target)
            return mid;
        else if (data[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {
    int data[] = {30, 10, 50, 20, 40};
    int n = 5;

    cout << "Data sebelum diurutkan: ";
    for (int i = 0; i < n; i++) cout << data[i] << " ";

    bubbleSort(data, n);

    cout << "\nData setelah diurutkan: ";
    for (int i = 0; i < n; i++) cout << data[i] << " ";

    int cari;
    cout << "\n\nMasukkan angka yang ingin dicari: ";
    cin >> cari;

    int posisi = binarySearch(data, n, cari);
    if (posisi != -1)
        cout << "Data ditemukan di indeks ke-" << posisi << endl;
    else
        cout << "Data tidak ditemukan.\n";

    return 0;
}

