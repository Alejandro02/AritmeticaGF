#ifndef FP2_H
#define FP2_H
#include "fp.h"


class Fp2{
    Fp coeficientes[2];

    /*Auxiliares de proposito general*/
    static Fp A;
    static Fp B;

    /*Auxiliares para multiplicacion Karatsuba*/
    static Fp t0;
    static Fp t1;
    static Fp t2;
    static Fp t3;

    /*Auxiliares en el inverso*/
    static Fp pMenos2;
public:
    static Fp beta;
    static Fp betaNegativo;

    static void creaCampo(std::string &primo);
    static void crea(Fp2 &a);
    Fp2();

    static void suma(Fp2 &a,Fp2 &b,Fp2 &c);
    static void resta(Fp2 &a,Fp2 &b,Fp2 &c);
    static void multiplicacion(Fp2 &a,Fp2 &b,Fp2 &c);
    static void multiplicacion(Fp2 &a,Fp &b,Fp2 &c);
    static void cuadrado(Fp2 &a,Fp2 &c);
    static void inverso(Fp2 &a,Fp2 &inverso);

    void estableceCoeficiente(std::string numero, int i);
    void limpia();
    void copia(Fp2 &b);
    void imprime(bool saltosDeLinea = true);

    Fp &operator [](int i);
};

#endif // FP2_H
