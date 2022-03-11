#include <iostream>
#include <string>

using namespace std;

class Tvar {
protected:
	double* rozmery;
	int pocetrozmeru;

public:
	Tvar(int pocetrozmeru) {
		rozmery = new double[this->pocetrozmeru = pocetrozmeru];
	}

	virtual string vykresli(void) {
		return string("pocet stran: " + to_string(pocetrozmeru) + ", obvod: "
			+ to_string(obvod()) + ", obsah: " + to_string(obsah()) + "\n" + "\n");
	}

	void tisk() {
		cout << vykresli();
	}

	virtual long double obsah(void) = 0;

	virtual long double obvod(void) = 0;

	~Tvar() {
		if (pocetrozmeru > 0) { delete[] rozmery; }
	}
};

class Kruh : public Tvar {
public:
	Kruh(double polomer) : Tvar(1) {
		rozmery[0] = polomer;
	}
	virtual long double obsah() {
		return 3.14159 * rozmery[0] * rozmery[0];
	}
	virtual long double obvod() {
		return 3.14159 * 2 * rozmery[0];
	}
	virtual string vykresli(void) {
		return string("Kruh: pocet stran: " + to_string((long double)pocetrozmeru) + ", obvod: "
			+ to_string(obvod()) + ", obsah: " + to_string(obsah()) + "\n" + "\n");
	}
};

class Obdelnik : public Tvar {
public:
	Obdelnik(double a, double b) : Tvar(2) {
		rozmery[0] = a;
		rozmery[1] = b;
	}
	virtual long double obsah() {
		return rozmery[0] * rozmery[1];
	}
	virtual long double obvod() {
		return rozmery[0] * 2 + rozmery[1] * 2;
	}
	virtual string vykresli(void) {
		return string("Obdelnik: pocet stran: " + to_string((long double)pocetrozmeru) + ", obvod: "
			+ to_string(obvod()) + ", obsah: " + to_string(obsah()) + "\n" + "\n");
	}
};

class Barevny_Obdelnik : public Obdelnik {
protected:
	string barva;
public:
	Barevny_Obdelnik(double a, double b, string barva) : Obdelnik(a, b) {
		this->barva = barva;
	}

	virtual string vykresli(void) {
		return string("Obdelnik: pocet stran: " + to_string((long double)pocetrozmeru) + ", obvod: "
			+ to_string(obvod()) + "obsah: " + to_string(obsah()) + ", barva:" + barva + "\n" + "\n");
	}
};

class Trojuhelnik : public Tvar {
public:
	Trojuhelnik(double a, double b, double c) : Tvar(3) {
		rozmery[0] = a;
		rozmery[1] = b;
		rozmery[2] = c;
	}
	virtual long double obsah() {
		long double s = obvod() / 2;
		return sqrt((s - rozmery[0])*(s - rozmery[1])*(s - rozmery[2]));
	}
	virtual long double obvod() {
		return rozmery[0] + rozmery[1] + rozmery[2];
	}
	virtual string vykresli(void) {
		return string("Trojuhelnik: pocet stran: " + to_string((long double)pocetrozmeru) + ", obvod: "
			+ to_string(obvod()) + ", obsah: " + to_string(obsah()) + "\n" + "\n");
	}
};

int main() 
{
	Tvar* tvar[20];
	for (int i = 0; i < 20; i++) {
		int ran = rand() % 4 + 1;
		if (ran == 1) { tvar[i] = new Kruh(rand() % 100 + 1); };
		if (ran == 2) { tvar[i] = new Obdelnik(rand() % 100 + 1, rand() % 100 + 1); };
		if (ran == 3) { tvar[i] = new Barevny_Obdelnik(rand() % 100 + 1, rand() % 100 + 1, "cerveny"); };
		if (ran == 4) { tvar[i] = new Trojuhelnik(rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1); };
	}
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 19; j++) {
			if (tvar[j]->obsah() < tvar[j + 1]->obsah()) {
				swap(tvar[j], tvar[j + 1]);
			}
		}
	}
	for (int i = 0; i < 20; i++) {
		tvar[i]->tisk();
	}

}