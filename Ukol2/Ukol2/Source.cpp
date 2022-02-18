#include <iostream>
using namespace std;

void sort(int pocetprvku, int *a, int *b) {
    for (int i = 0; i < pocetprvku - 1; i++) {
        for (int j = 0; j < pocetprvku - 1; j++) {
            if (a[j] < a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
            b[j] = a[j];
        }
    }
}

int main(int argc, char *argv[])
{
    int *vysledek;
    vysledek = new int[argc-1];
    
    int* pole;
    pole = new int[argc-1];

    for (int i = 0; i < argc - 1; i++) {
        pole[i] = atoi(argv[i+1]);
    }

    cout << "Zadane hodnoty:";
    for (int i = 0; i < argc - 1; i++) {
        cout << pole[i] << " ";
    }
    cout << "\n";

    sort(argc, pole, vysledek);
    
    for (int i = 0; i < argc - 1; i++) {
        cout << vysledek[i] << " ";
    }
    return 0;
}