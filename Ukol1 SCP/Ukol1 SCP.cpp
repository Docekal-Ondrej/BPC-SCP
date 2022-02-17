#include <iostream>
#include "func.h"

int main()
{
    while (1) {
        int cislo;
        std::cout << "Zadejte cislo:\n";
        cin >> cislo;
        sude(cislo);
        liche(cislo);
        prvoc(cislo);
        fact(cislo);
    }
    return 0;
}
