#ifndef FP12_H
#define FP12_H

#include "fp6.h"

class Fp12{
    Fp6 coeficientes[2];
public:
    Fp12();
    static void creaCampo(std::string &primo);

    void estableceCoeficiente(std::string numero, int i);
    void limpia();
    void imprime();

    Fp6 &operator [](int i);
};

#endif // FP12_H
