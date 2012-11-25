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
    /*Primo que define el campo y variable auxiliar*/
    static Fp primo,auxiliar;
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
    static Fp &getP();

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

    /*Operadores aritmeticos*/
    static void suma(Fp &a, Fp &b, Fp &resultado);
    static void suma(Fp &a, uInt64 b, Fp &resultado);

    static void resta(Fp &a, Fp &b, Fp &resultado,bool permitirResultadosNegativos = false);
    static void resta(Fp &a, uInt64 b, Fp &resultado,bool permitirResultadosNegativos = false);

    static void multiplicacionBinariaIzquierdaADerecha(Fp &a, Fp &b, Fp &resultado);
    /*TODO*/
    static void multiplicacionClasica(Fp &a, Fp &b, Fp &resultado);
    static void multiplicacionMontgomery(Fp &a, Fp &b, Fp &resultado);

    static void exponenciacionBinariaIzquierdaADerecha(Fp &b, Fp &e, Fp &resultado);
    static void exponenciacionBinariaDerechaAIzquierda(Fp &b, Fp &e, Fp &resultado);
    static void exponenciacionBinariaSideChannels(Fp &b, Fp &e, Fp &resultado);
    static void exponenciacionVentanasFijas(Fp &b, Fp &e, Fp &resultado);
    static void exponenciacionVentanasDeslizantes(Fp &b, Fp &e, Fp &resultado);

    void reduccionBarret();
    void reduccionConRestauracion();
    void reduccionSinRestauracion();
    /*TODO end*/

    /*Operadores a nivel bits*/
    void operadorTilde();
    void corrimientoUnBitDerecha();
    void corrimientoUnBitIzquierda();

    /*Operadores logicos*/
    bool operator <(Fp &b);
    bool operator >(Fp &b);
    bool operator <(uInt64 b);
    bool operator >(uInt64 b);
    bool operator ==(Fp &b);
    bool operator ==(uInt64 n);

    /*Operadores de posicionamiento*/
    uInt64 &operator [](int i);
    int bitEnPosicion(int i);

    void imprime();
};

#endif // FP_H
