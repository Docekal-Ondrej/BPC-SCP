#include <iostream>
#include <complex>
#include <vector>
#include <iterator>

using namespace std;

template<class T> class Matice {
    int row, col;
    T** Mat;

public:

    Matice(int row, int col) {
        Mat = new T* [this->row = row];
        for (int i = 0; i < row; i++) {
            Mat[i] = new T[this->col = col];
        }
    }

    Matice(const Matice& x) {
        Mat = new T* [row = x.row];
        for (int i = 0; i < x.row; i++) {
            Mat[i] = new T[col = x.col];
            for (int j = 0; j < x.col; j++) {
                Mat[i][j] = x[i][j];
            };
        }
    }

    Matice(T x) {
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

    Matice operator -() {
        Matice M(*this);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                M[i][j] = -M[i][j];
            };
        };
        return M;
    }

    T* operator[](int i) const {
        return Mat[i];
    }


};

typedef complex<double> cpxd;
typedef Matice<cpxd> mcpxd;

template<class P> Matice<P> operator+(const Matice<P>& MatA, const Matice<P>& MatB) {
    Matice<P> MatC(MatA);
    for (int i = 0; i < MatC.getRow(); i++) {
        for (int j = 0; j < MatC.getCol(); j++) {
            MatC[i][j] += MatB[i][j];
        };
    };
    return MatC;
}

template<class P>Matice<P> operator+(const Matice<P>& MatA, const P x) {
    Matice<P> MatC(MatA);
    for (int i = 0; i < MatC.getRow(); i++) {
        for (int j = 0; j < MatC.getCol(); j++) {
            MatC[i][j] += x;
        };
    };
    return MatC;
}


template<class P>ostream& operator<<(ostream& out, const Matice<P>& M) {
    for (int i = 0; i < M.getRow(); i++) {
        for (int j = 0; j < M.getCol(); j++) {
            out << M[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

void fill(Matice<cpxd>& A) {
    for (int i = 0; i < A.getRow(); i++) {
        for (int j = 0; j < A.getCol(); j++) {
            A[i][j].real((double)(rand() % 100));
            A[i][j].imag((double)(rand() % 100));
        };
    };
}

int main()
{
    vector<mcpxd> Vm;
    vector<mcpxd>::iterator it;

    Matice<cpxd> A(3, 3), B(3, 3), C(3, 3), D(3, 3);

    fill(A);
    fill(B);
    fill(C);

    D = A + B + C;

    Vm.push_back(A);
    Vm.push_back(B);
    Vm.push_back(C);
    Vm.push_back(D);

    for (it = Vm.begin(); it < Vm.end(); it++) {
        cout << *it << endl;
    }
}