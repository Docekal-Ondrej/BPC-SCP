#define _USE_MATH_DEFINES

#include <iostream>
#include <complex>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

class Vyjimka {
	int n_error;

public:
	Vyjimka(int error) {
		n_error = error;
	}

	string message(void) {
		switch (n_error)
		{
		case 0: return string("Uzly jsou stejne!");
			break;
		case 1: return string("Uzel neexistuje!");
			break;
		case 2: return string("Pocet uzlu musi byt vetsi nez 1!");
			break;
		case 4: return string("Neplatna hodnota!");
			break;
		case 5: return string("Oba konce prvku nelze pripojit ke stejnemu uzlu!");
			break;
		case 6: return string("Tento typ prvku neexistuje!");
			break;
		default: return string("Jina chyba!");
			break;
		}
	}
};

typedef complex<double> cpxd;

cpxd one = 1, zero = 0;

template<class T> class Matice {
	int row, col;
	T** Mat;

public:

	Matice(int row, int col) {
		Mat = new T * [this->row = row];
		for (int i = 0; i < row; i++) {
			Mat[i] = new T[this->col = col];
		}
	}

	Matice(int i) {
		Mat = new T * [1];
		Mat[0] = i;
	}

	Matice(const Matice& x) {
		Mat = new T * [row = x.row];
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

	T determinant() {
		T det;
		if (row == 1) {
			det = Mat[0][0];
		}
		else if (row == 2) {
			det = (Mat[0][0] * Mat[1][1] - Mat[0][1] * Mat[1][0]);
		}
		else if (row == 3) {
			det = Mat[0][0] * (Mat[1][1] * Mat[2][2] - Mat[1][2] * Mat[2][1])
				- Mat[0][1] * (Mat[1][0] * Mat[2][2] - Mat[1][2] * Mat[2][0])
				+ Mat[0][2] * (Mat[1][0] * Mat[2][1] - Mat[1][1] * Mat[2][0]);

		}
		return det;
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

	~Matice() {
		for (int i = 0; i < row; i++) {
			delete Mat[i];
		}
		delete[] Mat;
	}
};

typedef complex<double> cpxd;
typedef Matice<cpxd> mcpxd;

template<class P>ostream& operator<<(ostream& out, const Matice<P>& M) {
	for (int i = 0; i < M.getRow(); i++) {
		for (int j = 0; j < M.getCol(); j++) {
			out << M[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

double mod(cpxd x) {
	return sqrt(x.real() * x.real() + x.imag() * x.imag());
}

double arc(cpxd x) {
	return atan2(x.imag(), x.real()) * 180 / M_PI;
}

string aplusB(cpxd x) {
	string res;
	res.append(to_string(mod(x)));
	res.append(" uhel:");
	res.append(to_string(arc(x)));
	return res; 
}

class Prvek {
protected:
	double f;
public:
	Prvek(double f) {
		this->f = f;
	}

	virtual string getName(void) = 0;
	virtual cpxd getVal(void) = 0;
	virtual void setName(string s) = 0;
	virtual void setVal(double x) = 0;
	virtual cpxd Z(void) = 0;
	virtual cpxd Y(void) = 0;
	virtual string getJednotky(void) = 0;

	virtual ~Prvek() {}
};

class Resistor : public Prvek {
	cpxd R;
	string name;
public:
	Resistor(string name, cpxd R, double f) : Prvek(f) {
		this->R = R;
		this->name = name;
	}

	virtual cpxd Z() {
		return R;
	}

	virtual cpxd Y() {
		return one / R;
	}

	virtual string getName() { return name; }
	virtual void setName(string s) { name = s; }

	virtual cpxd getVal() { return R; }
	virtual void setVal(double x) { R = x; }

	virtual string getJednotky() { return "ohm"; }
};

class Kapacitor : public Prvek {
	cpxd C;
	string name;
public:
	Kapacitor(string name, cpxd C, double f) : Prvek(f) {
		this->C = C;
		this->name = name;
	}

	virtual cpxd Z(void) {
		cpxd Z;
		Z.real(0);
		Z.imag(-1 / (2 * M_PI * f * C.real()));
		return Z;
	}

	virtual cpxd Y(void) {
		cpxd Y;
		Y.real(0);
		Y.imag(2 * M_PI * f * C.real());
		return Y;
	}

	virtual string getName() { return name; }
	virtual void setName(string s) { name = s; }

	virtual cpxd getVal() { return C; }
	virtual void setVal(double x) { C = x; }

	virtual string getJednotky() { return "F"; }
};

class Induktor : public Prvek {
	string name;
	cpxd L;
public:
	Induktor(string name, cpxd L, double f) : Prvek(f) {
		this->L = L;
		this->name = name;
	}

	virtual cpxd Z(void) {
		cpxd Z;
		Z.real(0);
		Z.imag(2 * M_PI * f * L.real());
		return Z;
	}

	virtual cpxd Y(void) {
		cpxd Y;
		Y.real(0);
		Y.imag(- 1 / (2 * M_PI * f * L.real()));
		return Y;
	}

	virtual string getName() { return name; }
	virtual void setName(string s) { name = s; }

	virtual cpxd getVal() { return L; }
	virtual void setVal(double x) { L = x; }

	virtual string getJednotky() { return "H"; }
};

class Uzel {
	double f = 0;
public:
	vector<Prvek*> prvky;
	vector<Prvek*> ::iterator it;
	cpxd I = 0;
	cpxd U = 0;

	Uzel(double f) {
		this->f = f;
	}

	Uzel(const Uzel& u) {
		f = u.f;
		prvky = u.prvky;
		I = u.I;
		U = u.U;
	}

	void Add(char c, string name, cpxd x) {
		if (c != 'R' && c != 'C' && c != 'L' && c != 'I') {
			throw(Vyjimka(6));
		}
		else if (x.real() <= 0)
		{
			throw(Vyjimka(4));
		}

		switch (c)
		{
		case 'R':
			prvky.push_back(new Resistor(name, x, f));
			break;
		case 'L':
			prvky.push_back(new Induktor(name, x, f));
			break;
		case 'C':
			prvky.push_back(new Kapacitor(name, x, f));
			break;
		case 'I':
			I = x;
			break;
		default:
			break;
		};
	}

	cpxd getY(void) {
		cpxd res = 0;
		for (it = prvky.begin(); it != prvky.end(); it++) {
			res = res + (*it)->Y();
		}
		return res;
	}

	cpxd getZ(void) {
		cpxd res = 0;
		res = one / getY();
		return res;
	}
	
	Prvek* find(string x) {
		for (it = prvky.begin(); it != prvky.end(); it++) {
			if ((*it)->getName()._Equal(x)) {
				return *it;
			}
		}
		throw(Vyjimka(4));
	}

	bool contains(string s) {
		for (it = prvky.begin(); it != prvky.end(); it++) {
			if ((*it)->getName()._Equal(s)) {
				return true;
				break;
			}
		}
		return false;
	}

	//~Uzel() {
	//	for (auto p : prvky)
	//	{
	//		delete p;
	//	}
	//	prvky.clear();
	//}
};

ostream& operator<<(ostream& out, Uzel& U) {
	vector<Prvek*> ::iterator it;
	if (U.I != zero) {
		out << "I: " << U.I << " A" << endl;
	}
	for (it = (U.prvky).begin() ; it != (U.prvky).end(); it++) {
		out << (*it)->getName() << ": " << (*it)->getVal() << " " << (*it)->getJednotky() << endl;
	}
	//out << "Celkove Y: " << U.getY() << endl;
	return out;
}

cpxd spojeneUzlyY(const Uzel u1, Uzel u2) {
	cpxd res;
	for (int i = 0; i != u1.prvky.size(); i++) {
		for (int j = 0; j != u2.prvky.size(); j++) {
			if (u1.prvky[i]->getName() == u2.prvky[j]->getName()) {
				res += u2.prvky[j]->Y();
				//cout << u2.prvky[j]->getName() << endl;
			};
		}
	}
	return res;
}

class Obvod {
protected:
	double f;
public:
	vector<Uzel> uzly;
	vector<Uzel> ::iterator it;

	Obvod(const Obvod& o) {
		f = o.f;
		uzly = o.uzly;
	}

	Obvod(double f) {
		if (f < 0) {
			throw(Vyjimka(4));
		}
		this->f = f;
	}

	
	double getf() { return f; }
	void setf(double f) { 
		if (f < 0) {
			throw(Vyjimka(4));
		}
		this->f = f;
	}
 
	void pridejUzel(int x) { 
		if (x < 1) {
			throw(Vyjimka(4));
		}
		for (int i = 0; i < x; i++) { uzly.push_back(Uzel(f)); } 
	};

	void pridejPrvek(char c, string name, cpxd val, int u1, int u2) {
		try
		{
			add(c, name, val, u1, u2);
		}
		catch (Vyjimka& V)
		{
			cout << V.message() << endl;
		}
	}

	void add(char c, string name, cpxd val, int u1, int u2) {
		if (uzly.size() < 2) {
			throw(Vyjimka(2));
		}
		else if (u1 > uzly.size() || u1 < 0 || u2 > uzly.size() || u2 < 0) {
			throw(Vyjimka(1));
		}
		else if (u1 == u2) {
			throw(Vyjimka(5));
		}

		try
		{
			uzly[u1].Add(c, name, val);
			uzly[u2].Add(c, name, val);
		}
		catch (Vyjimka& V)
		{
			cout << V.message() << endl;
		}
	}
	
	void vypocetU() {
		int size = uzly.size() - 1, i = 0;
		vector<cpxd> det;
		vector<cpxd> :: iterator itd;
		Matice<cpxd> mY = MaticeY();
		det.push_back(mY.determinant());

		cout << "Vypocet:" << endl;
		
		cout << mY << endl;

		for (int i = 0; i < size; i++)
		{
		Matice<cpxd> M = MaticeY();
			for (int j = 0; j < size; j++) {
				M[j][i] = uzly[j + 1].I;
			}
		det.push_back(M.determinant());
		cout << M << endl;
		}

		for (itd = det.begin(); itd != det.end(); itd++) {
			cout << "D" << i << ": " << (*itd) << "; " << mod(*itd) << ", " << arc(*itd) << endl;
			if (i != 0) {
				uzly[i].U = (*itd) / det[0];
			}
			i++;
		}
	}

	Matice<cpxd> MaticeY() {
		int size = uzly.size() - 1;
		Matice<cpxd> M(size, size);
		
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (j != i) {
					M[i][j] = spojeneUzlyY(uzly[i + 1], uzly[j + 1]);
					M[i][j].real(-M[i][j].real());
					M[i][j].imag(-M[i][j].imag());
				}
			}
		M[i][i] = uzly[i + 1].getY();
		}
		return M;
	}

	Prvek* find(string x) {
		try
		{
			for (it = uzly.begin(); it != uzly.end(); it++) {
				return (*it).find(x);
			}
		}
		catch (Vyjimka& V)
		{
			cout << V.message() << endl;
		}
	}


	cpxd napetiUzly(int a, int b) {
		if (a > uzly.size() || a < 0 || b > uzly.size() || b < 0) {
			throw(Vyjimka(1));
		}
		return (uzly[a].U) - (uzly[b].U);
	}

	cpxd hodnotaSoucastky(string s) {
		try
		{
			return find(s)->getVal();
		}
		catch (Vyjimka& V)
		{
			cout << V.message() << endl;
		}
	}

	cpxd napetiSoucastka(string s) {
		vector<Uzel> V;
		for (it = uzly.begin(); it != uzly.end(); it++) {
			if ((*it).contains(s)) {
				V.push_back(*it);
			}
		}
		if (V.size() < 2) {
			throw(Vyjimka(2));
		}
		cpxd res = V[1].U - V[0].U;
		return res;
	}

	//Ne vzdy lze pouzit tento vzorec ¯\_(ツ)_/¯
	cpxd proudSoucastka(string s) {
		cpxd res;
		try
		{
			res = napetiSoucastka(s) / find(s)->Z();
		}
		catch (Vyjimka& V)
		{
			cout << V.message() << endl;
		}
		return	res;
	}

	void setValSoucastky(string s, double x) {
		if (f < 0) {
			throw(Vyjimka(4));
		}
		try
		{
			find(s)->setVal(x);
		}
		catch (Vyjimka& V)
		{
			cout << V.message() << endl;
		}
	}

	void setNameSoucastky(string s, string x) {
		for (it = uzly.begin(); it != uzly.end(); it++) {
			if ((*it).contains(s)) {
				throw("Prvek s timto nazvem jiz existuje!");
			}
		}
		try
		{
			find(s)->setName(x);
		}
		catch (Vyjimka& V)
		{
			cout << V.message() << endl;
		}
	}
};

ostream& operator<<(ostream& out, Obvod& O) {
	vector<Uzel> ::iterator it;
	int i = 0;
	out << endl << "f: " << O.getf() << "Hz" << endl << endl;
	for (it = (O.uzly).begin(); it != (O.uzly).end(); it++) {
		out << "Uzel " << i << ": " << endl << "U: " << (*it).U << "; " << mod((*it).U) << ", " << arc((*it).U) << " V" << endl << (*it) << endl;
		i++;
	}
	return out;
}

int main() {
	cpxd I, I1, R;
	/* ---------- Priklad 3.5 ---------- */
	cout << endl << endl << "----------Priklad 3.5----------" << endl;

	Obvod B(400);

	B.pridejUzel(3);

	//pridejPrvek(typ, nazev, hodnota, uzel1, uzel2)
	B.pridejPrvek('L', "L", 0.2, 1, 2);
	B.pridejPrvek('R', "R1", 20, 1, 0);
	B.pridejPrvek('R', "R2", 100, 1, 0);
	B.pridejPrvek('R', "R3", 200, 2, 0);
	B.pridejPrvek('C', "C", 0.000005, 1, 0);
	B.pridejPrvek('I', "I", 0.5, 1, 0);

	B.vypocetU();

	Obvod X(B);

	cout << X;

	cout << "I1: " << X.proudSoucastka("R1") << " A" << ", " << aplusB(X.proudSoucastka("R1")) << endl;
	cout << "Napeti mezi uzly 2 a 0: " << B.napetiUzly(2, 0) << ", " << aplusB(B.napetiUzly(2, 0)) << " V" << endl;
	cout << "Napeti na soucastce R3: " << B.napetiSoucastka("R3") << ", " << aplusB(B.napetiSoucastka("R3")) << " V" << endl;


	/* ---------- Priklad 3.6 ---------- */
	cout << endl << endl << "----------Priklad 3.6----------" << endl;

	Obvod C(100);

	C.pridejUzel(4);

	//Je treba vypocitat proudovy zdroj
	R.real(50);
	I.real(91.92533);
	I.imag(77.13451);
	I = I / R;

	//pridejPrvek(typ, nazev, hodnota, uzel1, uzel2)
	C.pridejPrvek('R', "R1", 50, 1, 0);
	C.pridejPrvek('C', "C1", 0.000005, 1, 2);
	C.pridejPrvek('C', "C2", 0.00001, 2, 0);
	C.pridejPrvek('R', "R2", 100, 2, 3);
	C.pridejPrvek('L', "L", 0.2, 3, 0);
	C.pridejPrvek('I', "I", I, 1, 0);

	C.vypocetU();

	cout << C;

	cout << "Napeti mezi uzly 3 a 0 je: " << C.napetiSoucastka("L") << ", " << aplusB(C.napetiSoucastka("L")) << " V" << endl;

	/* ---------- Priklad 3.8 ---------- */
	cout << endl << endl << "----------Priklad 3.8----------" << endl;

	Obvod D(50);

	D.pridejUzel(4);

	R.real(10);
	I.real(40.7839);
	I.imag(19.0178);

	I = I / R;

	R.real(20);
	I1.real(30);
	I1.imag(-10);

	I1 = I1 / R;

	//pridejPrvek(typ, nazev, hodnota, uzel1, uzel2)
	D.pridejPrvek('R', "R1", 10, 1, 0);
	D.pridejPrvek('R', "R2", 20, 3, 0);
	D.pridejPrvek('C', "C1", 0.000005, 1, 2);
	D.pridejPrvek('C', "C2", 0.000003, 2, 0);
	D.pridejPrvek('L', "L", 1.5, 2, 3);
	D.pridejPrvek('I', "I1", I, 1, 0);
	D.pridejPrvek('I', "I2", I1, 3, 0);

	D.vypocetU();

	cout << D;

	//Jedina uzitecna hodnota kvuli chybe ve vypoctu I
	cout << "I3: " << D.proudSoucastka("C2") << " A" << endl;

	/* ---------- TEST ---------- */
	cout << endl << endl << "----------TEST----------" << endl;

	Obvod A(400);

	A.pridejUzel(3);
	
	try
	{
		A.pridejUzel(0);
	}
	catch (Vyjimka& V)
	{
		cout << V.message() << endl;
	}

	//pridejPrvek(typ, nazev, hodnota, uzel1, uzel2)
	A.pridejPrvek('V', "L", 0.2, 1, 2);
	A.pridejPrvek('R', "R1", 20, 1, 0);
	A.pridejPrvek('R', "R2", -6, 1, 0);
	A.pridejPrvek('R', "R3", 200, 2, 2);
	A.pridejPrvek('C', "C", 0.000005, 1, 0);
	A.pridejPrvek('I', "I", 0.5, 4, 0);

	A.vypocetU();

	cout << A;

	try
	{
		cout << "I1: " << A.proudSoucastka("R1") << " A" << ", " << aplusB(A.proudSoucastka("R1")) << endl;
	}
	catch (Vyjimka& V)
	{
		cout << V.message() << endl;
	}

	try
	{
		cout << "Napeti mezi uzly 2 a 0: " << A.napetiUzly(2, 0) << ", " << aplusB(A.napetiUzly(2, 0)) << " V" << endl;
	}
	catch (Vyjimka& V)
	{
		cout << V.message() << endl;
	}

	try
	{
		cout << "Napeti na soucastce R3: " << A.napetiSoucastka("R3") << ", " << aplusB(A.napetiSoucastka("R3")) << " V" << endl;
	}
	catch (Vyjimka& V)
	{
		cout <<V.message() << endl;
	}

}