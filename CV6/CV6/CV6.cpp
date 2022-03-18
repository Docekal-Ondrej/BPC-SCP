#include <iostream>

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

    int getRow() const{
        return row;
    }
    
    int getCol() const{
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

    int* operator[](int i) const{
        return Mat[i];
    }


};

Matice operator+(const Matice &MatA, const Matice &MatB) {
    Matice MatC(MatA);
    for (int i = 0; i < MatC.getRow(); i++) {
        for (int j = 0; j < MatC.getCol(); j++) {
                MatC[i][j] += MatB[0][0];
        };
    };
    return MatC;
}

ostream& operator<<(ostream& out,const Matice& M) {
    for (int i = 0; i < M.getRow(); i++) {
        for (int j = 0; j < M.getCol(); j++) {
            out << M[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

int main()
{
    Matice A(3, 4), B(3, 4), C(3, 4);

    A.fill(20);
    B.fill(20);
    C.fill(20);

    C = -A + B + 3 + B[1][2];

    cout << A << endl << B << endl << C << endl;
}
