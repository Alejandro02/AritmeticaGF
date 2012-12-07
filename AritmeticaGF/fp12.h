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

    static Fp2 Gamma11;
    static Fp2 Gamma12;
    static Fp2 Gamma13;
    static Fp2 Gamma14;
    static Fp2 Gamma15;

    static Fp2 Xi;

public:
    Fp12();
    static void creaCampo(std::string &primo);

    //Algoritmo 18 - Suma en Fp12
    static void suma(Fp12 &a,Fp12 &b,Fp12 &c);
    //Algoritmo 19 - Sustraccion en Fp12
    static void resta(Fp12 &a,Fp12 &b,Fp12 &c);
    //Algoritmo 20 - Multiplicacion de dos elementos en Fp12
    static void multiplicacion(Fp12 &a,Fp12 &b,Fp12 &c);
    //Algoritmo 22 - Cuadrado en Fp12
    static void cuadrado(Fp12 &a,Fp12 &c);
    //Algoritmo 23 - Inveso en Fp12
    static void inverso(Fp12 &a,Fp12 &c);

    void estableceCoeficiente(std::string numero, int i);
    void limpia();
    void imprime();

    Fp6 &operator [](int i);
};

#endif // FP12_H
