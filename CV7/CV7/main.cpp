#include <iostream>

using namespace std;

template<class T> class pole {
	T* p;
	int s;

public:
	pole(int n) {
		p = new T[s = n];
	}

	T& operator[](int i) {
		return p[i];
	}

	~pole() {
		delete[] p;
	}

	template<class P> friend ostream& operator <<(ostream& out, pole<P>& k);
};

template<class P> ostream& operator <<(ostream& out, pole<P>& p) {
	for (int i = 0; i < p.s; i++) out << p.p[i] << ' ';
	return out;
}

class Osoba {
protected:
	string jmeno, prijmeni;
	int ID, telefon;

public:
	Osoba() {

	}

	void setJmeno(string jmeno) { this->jmeno = jmeno; }

	void setPrijmeni(string prijmeni) { this->prijmeni = prijmeni; }

	void setID(int ID) { this->ID = ID; }

	void setTelefon(int telefon) { this->telefon = telefon; }

	string getJmeno() const {return jmeno; }

	string getPrijmeni() const { return prijmeni; }

	int getID() const{ return ID; }

	int getTelefon() const { return  telefon; }
	
	friend ostream& operator<<(ostream& out, const Osoba& O);
};

ostream& operator<<(ostream& out,const Osoba& O) {
	out << O.getID() << ' ' << O.getJmeno() << ' ' << O.getPrijmeni() << ' ' << O.getTelefon();
	return out;
}

int main() {
	pole<int> A(10);
	pole<Osoba> B(10);

	string jmena[10] = {"Jan", "Michal", "Pavel", "Jakub", "Martin", "Tomas", "Ota", "Radek", "Zdenek", "Radim"};
	string prijmeni[10] = {"Mikulka", "Fiala", "Roubal", "Dohnal", "Friedl", "Kriz", "Korinek", "Sedlacek", "Drexler", "Dedek",};
	
	for (int i = 0; i < 10; i++) {
		A[i] = i+1;
		B[i].setID(i + 1);
		B[i].setJmeno(jmena[rand() % 10]);
		B[i].setPrijmeni(prijmeni[rand() % 10]);
		B[i].setTelefon(1000 + rand() % 9000);
	}

	cout << A << endl << B << endl << endl;

	system("pause");
	return 0;
}	