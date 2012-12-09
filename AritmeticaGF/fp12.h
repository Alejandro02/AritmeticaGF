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

    static Fp pMenos1;
    static Fp iterador;
    static Fp seis;
    static Fp aux;

    static Fp2 Gamma11;
    static Fp2 Gamma12;
    static Fp2 Gamma13;
    static Fp2 Gamma14;
    static Fp2 Gamma15;

    static Fp2 Gamma21;
    static Fp2 Gamma22;
    static Fp2 Gamma23;
    static Fp2 Gamma24;
    static Fp2 Gamma25;

    static Fp2 Gamma31;
    static Fp2 Gamma32;
    static Fp2 Gamma33;
    static Fp2 Gamma34;
    static Fp2 Gamma35;

    static Fp2 conjugadoAux;

    static Fp2 Xi;

    static Fp2 Frobenius_t1;
    static Fp2 Frobenius_t2;
    static Fp2 Frobenius_t3;
    static Fp2 Frobenius_t4;
    static Fp2 Frobenius_t5;
    static Fp2 Frobenius_t6;

    static void creaGamma1x();
    static void creaGamma2x();
    static void creaGamma3x();

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
    //Algoritmo 23 - Inverso en Fp12
    static void inverso(Fp12 &a,Fp12 &c);
    //Algoritmo 24 - Es otro cuadrado en Fp12, no se si lo necesite
    //TODO:Algoritmo 25 - Exponenciacion de Fp12
    //Algoritmo 26 - No necesario
    //Algoritmo 27 - No necesario
    //Algoritmo 28 - Frobenius a la p
    static void frobeniusP(Fp12 &a,Fp12 &c);
    //Algoritmo 29 - Frobenius a la p^2
    static void frobeniusP2(Fp12 &a,Fp12 &c);
    //Algoritmo 30 - Frobenius a la p^3
    static void frobeniusP3(Fp12 &a,Fp12 &c);

    void estableceCoeficiente(std::string numero, int i);
    void limpia();
    void imprime();

    Fp6 &operator [](int i);
};

#endif // FP12_H
