#include <cmath>
#include <iostream>

using namespace std;

class Complex
{
	double re, im;
public:
	Complex(void) { re = 0; im = 0; };

	void set_re(int re) { this->re = re; };
	void set_im(int im) { this->im = im; };

	double get_re(void) { return re; };
	double get_im(void) { return im; };

	double modul(void) { return sqrt(re * re + im * im); };
	double faze(void) { return tan(im / re); }

	void tisk(void) { cout << re << "+" << im << "i" << ", Modul: " << modul() << ", Faze: " << faze(); };
};
