#ifndef FP2_H
#define FP2_H
#include "fp.h"


class Fp2{
    Fp coeficientes[2];

    static Fp beta;

    /*Auxiliares para multiplicacion Karatsuba*/
    static Fp t0;
    static Fp t1;
    static Fp t2;
    static Fp A;
    static Fp B;
public:
    Fp2();

    static void suma(Fp2 &a,Fp2 &b,Fp2 &c);
    static void resta(Fp2 &a,Fp2 &b,Fp2 &c);
    static void multiplicacion(Fp2 &a,Fp2 &b,Fp2 &c);
    static void exponenciacion(Fp2 &m,Fp &e,Fp2 &c);
    static void frobenius(Fp &a,Fp &c);

    void estableceCoeficiente(std::string numero, int i);
    void limpia();
    void imprime();

    Fp &operator [](int i);
};

#endif // FP2_H
