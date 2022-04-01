#include <Windows.h>
#include <iostream>

using namespace std;

template<class T> class LIFO {
	T* p;
	int n, LAST;


public:
	LIFO(int n) {
		p = new T[this->n = n];
		LAST = -1;
	}

	T Pop() {
		if (LAST < 0) {
			throw("Zasobnik je prazdny!");
		}
		else {
			LAST = LAST - 1;
			return p[LAST + 1];
		}		
	}

	void Push(T x) {
		if (LAST >= (n - 1)) {
			throw("Zasobnik je plny!");
		}
		else {
			LAST++;
			p[LAST] = x;
		}
	}

	~LIFO() {
		delete[] p;
	}
};

int main() {
	LIFO<int> K(5);

	while (1) {
		if ((rand() % 2) == 1) {
			try {
				K.Push(rand() % 10);
			}

			catch (const char* error) {
				cout << error << endl;
			}
		}

		else {
			try {
				cout << K.Pop() << endl;
			}

			catch (const char* error) {
				cout << error << endl;
			}
		}
		Sleep(500);
	};
}

