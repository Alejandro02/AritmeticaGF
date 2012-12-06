#ifndef FP6_H
#define FP6_H
#include "fp2.h"

class Fp6{
    Fp2 coeficientes[3];

    static Fp2 t0;
    static Fp2 t1;
    static Fp2 t2;

    static Fp2 auxiliar0;
    static Fp2 auxiliar1;
    static Fp2 auxiliar2;
    static Fp2 auxiliar3;
    static Fp2 auxiliar4;
    static Fp2 auxiliar5;
    static Fp2 auxiliar6;

    static Fp2 A;
    static Fp2 B;
    static Fp2 C;

    static Fp dos;
public:
    static void creaCampo(std::string &primo);
    Fp6();

    static void suma(Fp6 &a,Fp6 &b,Fp6 &c);
    static void resta(Fp6 &a,Fp6 &b,Fp6 &c);
    static void multiplicacion(Fp6 &a,Fp2 &b,Fp6 &c);
    static void multiplicacion(Fp6 &a,Fp2 &b0,Fp2 &b1,Fp6 &c);
    static void multiplicacion(Fp6 &a,Fp6 &b,Fp6 &c);
    static void cuadrado(Fp6 &a, Fp6&c);
    static void inverso(Fp6 &a,Fp6 &aInv);

    void estableceCoeficiente(std::string numero, int i);
    void limpia();
    void imprime(bool saltosDeLinea = true);

    Fp2 &operator [](int i);
};

#endif // FP6_H
