#include "Complex.h"


int main()
{
    Complex C, *K;
    C.set_im(3);
    C.set_re(4);
    C.tisk();
    
    cout << "\n";

    K = new Complex[1];
    
    K[0].set_re(1);
    K[0].set_im(4);
    K->tisk();

    delete K;

    cout << "\n";

    return 0;
}
