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
    static void crea(Fp6 &a);
    Fp6();

    //Algoritmo 9 - Cuadrado en Fp4 (Representado como dos elementos de Fp2
    static void cuadradoFp4(Fp2 &a0,Fp2 &a1,Fp2 &c0,Fp2 &c1);
    //Algoritmo 10 - Suma en Fp6
    static void suma(Fp6 &a,Fp6 &b,Fp6 &c);
    //Algoritmo 11 - Resta en Fp6
    static void resta(Fp6 &a,Fp6 &b,Fp6 &c);
    //Algoritmo 12 - Multiplicacion por Gamma
    static void multiplicacionGamma(Fp6 &a,Fp6 &c);
    //Algoritmo 13 - Multiplicacion de dos elementos en Fp6
    static void multiplicacion(Fp6 &a,Fp6 &b,Fp6 &c);
    //Algoritmo 14 - Multiplicacion de un elemento en Fp6 por un elemento en Fp2
    static void multiplicacion(Fp6 &a,Fp2 &b,Fp6 &c);
    //Algoritmo 15 - Multiplicacion de un elemento en Fp6 por uno de Fp4 representado como dos elementos de Fp2
    static void multiplicacion(Fp6 &a,Fp2 &b0,Fp2 &b1,Fp6 &c);
    //Algoritmo 16 - Cuadrado en Fp6
    static void cuadrado(Fp6 &a, Fp6&c);
    //Algoritmo 17 - Inverso en Fp6 Bien
    static void inverso(Fp6 &a,Fp6 &aInv);

    static void multiplicacionPorDos(Fp6 &a,Fp6 &c);
    static void multiplicacionPorMenosUno(Fp6 &a,Fp6 &c);

    void copia(Fp6 &a);
    void estableceCoeficiente(std::string numero, int i);
    void limpia();
    void imprime(bool saltosDeLinea = true);

    Fp2 &operator [](int i);
};

#endif // FP6_H
