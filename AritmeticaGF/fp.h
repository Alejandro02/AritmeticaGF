#ifndef FP_H
#define FP_H

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

/*Traduce una cadena a entero*/
template <class T>bool fromStringTo(T& t,const std::string& s,std::ios_base& (*f)(std::ios_base&)){
    std::istringstream iss(s);
    return !(iss >> f >> t).fail();
}

typedef unsigned long long int uInt64;

class Fp{
private:
    /*Primo que define el campo*/
    static Fp primo;
    /*Longitud en palabras del primo*/
    static int k;
    /*Numero maximo de digitos hexadecimales en una palabra*/
    static const short maxN = 16;
    /*Descriptivo por si mismo*/
    static const uInt64 maximoValorDePalabra = 0xffffffffffffffff;

    bool esNeg;
    uInt64* misPalabras;

    void iniciarSemillaAleatoria();

public:
    static void setP(std::string &primo);
    static void imprimeP();

    Fp();
    Fp(std::string numeroEnHex);

    void aleatorizaNumero();

    void copia(Fp &otroNumero);
    void copia(uInt64 *unVector,int longitud);
    void setNegativo(bool negativo);
    void parseNumber(std::string numeroEnHex);

    void insertaFinal(uInt64 palabra);
    void borraFinal();
    void limpia();

    int longitudEnBits();
    int longitudEnPalabras();

    bool esNegativo() const;
    bool esPositivo() const;
    bool esImpar() const;
    bool esPar() const;

    /*Arithmetic operators*/
    Fp &operator +(Fp &b);
    Fp &operator +(uInt64 n);
    Fp &operator -(Fp &b);
    Fp &operator -(uInt64 n);
    Fp &operator *(Fp &b);
    Fp &operator *(uInt64 n);
    Fp &operator ^(Fp &e);
    Fp &operator ^(uInt64 n);

    /*Bitwise operators */
    Fp &operator >>(int n);
    Fp &operator <<(int n);
    bool operator <(Fp &b);
    bool operator >(Fp &b);
    bool operator <(uInt64 b);
    bool operator >(uInt64 b);
    bool operator ==(Fp &b);
    bool operator ==(uInt64 n);
    Fp &operator ~();

    uInt64 &operator [](int i);
    int bitAt(int i);

    void imprime();
};

#endif // FP_H
