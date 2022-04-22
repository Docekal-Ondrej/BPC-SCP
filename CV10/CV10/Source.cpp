#include <iostream>
#include <fstream>
#include "Source.h"

using namespace std;

class Matice {




public:
    int row, col;
    int** Mat;

    Matice(int row, int col) {
        Mat = new int* [this->row = row];
        for (int i = 0; i < row; i++) {
            Mat[i] = new int[this->col = col];
        }
    }

    Matice(const Matice& x) {
        Mat = new int* [row = x.row];
        for (int i = 0; i < x.row; i++) {
            Mat[i] = new int[col = x.col];
            for (int j = 0; j < x.col; j++) {
                Mat[i][j] = x[i][j];
            };
        }
    }

    Matice(int x) {
        row = 1; col = 1;
        Mat = new int* [row];
        Mat[0] = new int[col];
        Mat[0][0] = x;
    }

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

    void fill(int max) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                Mat[i][j] = rand() % max;
            };
        };
    }

    Matice operator -() {
        Matice M(*this);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                M[i][j] = -M[i][j];
            };
        };
        return M;
    }

    int* operator[](int i) const {
        return Mat[i];
    }

};

Matice operator+(const Matice& MatA, const Matice& MatB) {
    Matice MatC(MatA);
    for (int i = 0; i < MatC.getRow(); i++) {
        for (int j = 0; j < MatC.getCol(); j++) {
            MatC[i][j] += MatB[0][0];
        };
    };
    return MatC;
}

ostream& operator<<(ostream& out, Matice& M) {
    for (int i = 0; i < M.getRow(); i++) {
        for (int j = 0; j < M.getCol(); j++) {
            out << M[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

istream& operator>>(istream& in,const Matice& M) {
       in >> M[0][0] >> M[0][1] >> M[0][2] >> M[1][0] >> M[1][1] >> M[1][2] 
           >> M[2][0] >> M[2][1] >> M[2][2];
       return in;
}

int main()
{
    int i = 0;
    Matice A(3, 3), B(3, 3), C(3, 3);
    ifstream file;
    ofstream fileout;
    string soubor;

    //cin >> soubor;

    file.open("1mat.txt");
    file >> A;
    file.close();
    
    cout << A;
    i = 0;
    //cin >> soubor;
    
    file.open("2mat.txt");
    file >> B;
    file.close();
    
    cout << B;
    C = A + B;

    //cin >> soubor;

    fileout.open("3mat.txt");
    fileout << C;
    fileout.close();

    cout << C;
}