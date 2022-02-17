#pragma once
#include <iostream>
using namespace std;


void sude(int x) {
	cout << "Sude: ";
	int i = 2;
	while (i <= x) {
		cout << i <<" ";
		i = i + 2;
	}
	cout << "\n";
}

void liche(int x) {
	cout << "Liche: ";
	int i = 1;
	while (i <= x) {
		cout << i << " ";
		i = i + 2;
	}
	cout << "\n";
}


void prvoc(int x) {
	cout << "Prvocisla: ";
	int z = 2;
	bool prime = true;
	for (z; z < x; z++) {
		for (int i = 2; i <= z / 2; i++) {
			if (z % i == 0) {
				prime = false;
				break;
			}
		}
		if (prime) {
			cout << z << " ";
		}
		else {
			prime = true;
		}
	}
	cout << "\n";
}

void fact(float x) {
	cout << "Faktorial: ";
	float i = 1;
	float result = 0;
	while (i <= x) {
		if (result == 0) {
			result = 1;
		}
		result = i * result;
		i++;
	}
	cout << result;
	cout << "\n";
}
