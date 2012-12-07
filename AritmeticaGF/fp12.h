#ifndef FP12_H
#define FP12_H

#include "fp6.h"

class Fp12{
    Fp6 coeficientes[2];

    static Fp6 t0;
    static Fp6 t1;

    static Fp6 auxiliar0;
    static Fp6 auxiliar1;
    static Fp6 auxiliar2;

public:
    Fp12();
    static void creaCampo(std::string &primo);

    static void suma(Fp12 &a,Fp12 &b,Fp12 &c);
    static void resta(Fp12 &a,Fp12 &b,Fp12 &c);
    static void multiplicacion(Fp12 &a,Fp12 &b,Fp12 &c);
    static void cuadrado(Fp12 &a,Fp12 &c);
    static void inverso(Fp12 &a,Fp12 &c);

    void estableceCoeficiente(std::string numero, int i);
    void limpia();
    void imprime();

    Fp6 &operator [](int i);
};

#endif // FP12_H
