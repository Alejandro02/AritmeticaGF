#ifndef FP6_H
#define FP6_H
#include "fp2.h"

class Fp6{
    Fp2 coeficientes[3];
public:
    static void creaCampo(std::string &primo);
    Fp6();

    void estableceCoeficiente(std::string numero, int i);
    void limpia();
    void imprime();

    Fp2 &operator [](int i);
};

#endif // FP6_H
