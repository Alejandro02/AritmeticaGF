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

    //Algoritmo 5 - Suma de dos elementos en Fp2
    static void suma(Fp2 &a,Fp2 &b,Fp2 &c);
    //Algoritmo 6 - Resta de dos elementos en Fp2
    static void resta(Fp2 &a,Fp2 &b,Fp2 &c);
    //Algoritmo 7 - Multiplicacion de un elemento en Fp por un elemento en Fp2
    static void multiplicacion(Fp2 &a,Fp &b,Fp2 &c);
    //Algoritmo 8 - Inverso de un elemento en Fp2
    static void inverso(Fp2 &a,Fp2 &inverso);

    //Multiplicacion de dos elementos en Fp2
    static void multiplicacion(Fp2 &a,Fp2 &b,Fp2 &c);
    //Cuadrado de un elemento en Fp2
    static void cuadrado(Fp2 &a,Fp2 &c);
    //Conjugado de un elemento en Fp2
    static void conjugado(Fp2 &a,Fp2 &b);
    //Multiplicacion por u
    static void multiplicaPorXi(Fp2 &a,Fp2 &c);

    static void multiplicacionPorMenosUno(Fp2 &a,Fp2 &c);

    void estableceCoeficiente(std::string numero, int i);
    void limpia();
    void copia(Fp2 &b);
    void imprime(bool saltosDeLinea = true);

    Fp &operator [](int i);
};

#endif // FP2_H
