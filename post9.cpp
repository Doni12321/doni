#include <iostream>
using namespace std;

class MatrixSorter {
private:
    int matrix[3][3];

public:
    
    friend istream& operator>>(istream& in, MatrixSorter& m) {
        cout << "Masukkan elemen matriks 3x3:\n";
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                cout << "Elemen [" << i << "][" << j << "]: ";
                in >> m.matrix[i][j];
            }
        return in;
    }

    
    friend ostream& operator<<(ostream& out, const MatrixSorter& m) {
        out << "Matriks:\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                out << m.matrix[i][j] << "\t";
            out << endl;
        }
        return out;
    }

   
    void sortMatrix() {
        int temp[9];
        int index = 0;

        
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                temp[index++] = matrix[i][j];

       
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8 - i; ++j)
                if (temp[j] > temp[j + 1])
                    swap(temp[j], temp[j + 1]);

        
        index = 0;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                matrix[i][j] = temp[index++];
    }
};

int main() {
    MatrixSorter m;

    cin >> m;
    cout << "\nMatriks sebelum diurutkan:\n" << m;

    m.sortMatrix();

    cout << "\nMatriks setelah diurutkan:\n" << m;

    return 0;
}

