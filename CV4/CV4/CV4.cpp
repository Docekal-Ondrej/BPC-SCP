#include <iostream>

using namespace std;

class pole {
	int* p, s;

public:
	pole(int s) {
		p = new int[this->s = s];
	}

	pole(int s, int a) {
		p = new int[this->s = s];
		for (int i = 0; i < s; i++) {
			p[i] = a;
		};
	}

	pole(const char* a) {
		p = new int[this->s = strlen(a)];
		for (int i = 0; i < s; i++) {
			this->p[i] = a[i];
		};
	}

	pole(pole& x) {
		p = new int[s = x.s];
		for (int i = 0; i < s; i++) {
			p[i] = x.p[i];
		};
	}

	void napln() {
		for (int i = 0; i < s; i++) {
			p[i] = rand();
		};
	}

	void soucet(pole& x) {
		for (int i = 0; i < s; i++) {
			p[i] = p[i] + x.p[i];
		};
	}

	void tisk() {
		for (int i = 0; i < s; i++) {
			cout << p[i] << ", ";
		};
	}

	friend void soucetfriend(pole& a, pole& b, pole& c);

	~pole() {
		if (s > 0) { delete[] p; }
	}
};

void soucetfriend(pole& a, pole& b, pole& c) {
	for (int i = 0; i < c.s; i++) {
		c.p[i] = a.p[i] + b.p[i];
	};
}

int main()
{
	pole A(5), B(5, 1), C(5, 0);
	A.napln();
	A.tisk();
	cout << "\n";
	B.tisk();
	cout << "\n";
	C.tisk();
	cout << "\n";
	A.soucet(B);
	A.tisk();
	cout << "\n";
	soucetfriend(A, B, C);
	C.tisk();
	cout << "\n";
	pole s("Hello");
	s.tisk();
}