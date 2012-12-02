#ifndef FP_H
#define FP_H

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>

/*Traduce una cadena a entero*/
template <class T>bool fromStringTo(T& t,const std::string& s,std::ios_base& (*f)(std::ios_base&)){
    std::istringstream iss(s);
    return !(iss >> f >> t).fail();
}

typedef unsigned long long int uInt64;
typedef unsigned int uint128_t __attribute__((mode(TI)));

#define MUL64(h,s,c,a,b,d,e)\
    h = ( (uint128_t) a*b + d + e);\
    s = h; c = h >> 64;\

class Fp{
private:    
    /*Otro auxiliar*/
    static Fp auxiliar;

    /*Primo que define el campo */
    static Fp primo;

    /*Para la reduccion Barret*/
    static Fp mu;
    static Fp b;
    static Fp q;
    static Fp residuo1;
    static Fp residuo2;

    /*Para la multiplicacion Montgomery*/
    static Fp r;

    /*Auxiliares en reducciones.R0 no debe usarse como resultado en la resta. En su lugar usar R1*/
    static Fp R0;
    static Fp R1;

    /*Longitud en palabras del primo*/
    static int k;
    /*Longitud de los */
    static int kLim;

    /*Numero maximo de digitos hexadecimales en una palabra*/
    static const short maxN = 16;

    /*Descriptivo por si mismo*/
    static const uInt64 maximoValorDePalabra = 0xffffffffffffffff;

    bool esNeg;
    uInt64* misPalabras;    

    /*Funciones necesarias para la reduccion de Barret y multiplicacion Montgomery*/
    /*Barret y Euclides extendido necesitan la division*/
    /*Euclides extendido necesita el modulo*/
    /*La division necesita el corrimiento con copia*/
    static void calculaMu();
    std::vector<Fp> &operator /(Fp &b);
    Fp &corrimientoUnBitDerechaConCopia();    
    std::vector<Fp> &EuclidesExtendido(Fp &a,Fp &b);
    Fp &operator %(Fp &b);

    /*Reserva memoria y le asigna el vector al objeto que lo llama*/
    void creaYCopia(uInt64 *unVector,int longitud);

public:
    static void setP(std::string &primo,bool usarBarret = false);
    static Fp &getP();

    Fp();
    Fp(std::string numeroEnHex);

    void aleatorizaNumero();
    void copia(Fp &otroNumero);

    void setNegativo(bool negativo);
    void parseNumber(std::string numeroEnHex);

    void insertaFinal(uInt64 palabra);
    void borraFinal();
    void limpia();

    int longitudEnBits();
    int longitudEnPalabras();

    bool esNegativo() const;
    bool esPositivo() const;
    bool esImpar() ;
    bool esPar() const;

    /*Operadores aritmeticos*/
    static void suma(Fp &a, Fp &b, Fp &resultado,bool reducirAlFinalizar = true);
    static void suma(Fp &a, uInt64 b, Fp &resultado,bool reducirAlFinalizar = true);

    static void resta(Fp &a, Fp &b, Fp &resultado,bool permitirResultadosNegativos = false);
    static void resta(Fp &a, uInt64 b, Fp &resultado,bool permitirResultadosNegativos = false);

    static void multiplicacionBinariaIzquierdaADerecha(Fp &a, Fp &b, Fp &resultado,bool reducirAlFinalizar = false);
    static void multiplicacionClasica(Fp &a, Fp &b, Fp &resultado,bool reducirAlFinalizar = false);
    /*TODO*/
    static void multiplicacionMontgomery(Fp &a, Fp &b, Fp &resultado);
    /*TODO end*/
    static void exponenciacionBinariaIzquierdaADerecha(Fp &b, Fp &e, Fp &resultado);
    static void exponenciacionBinariaDerechaAIzquierda(Fp &b, Fp &e, Fp &resultado);
    static void exponenciacionBinariaSideChannels(Fp &b, Fp &e, Fp &resultado);
    /*TODO*/
    static void exponenciacionVentanasFijas(Fp &b, Fp &e, Fp &resultado);
    static void exponenciacionVentanasDeslizantes(Fp &b, Fp &e, Fp &resultado);
    /*TODO end*/
    static void reduccionBarret(Fp &t);    
    static void reduccionConRestauracion(Fp &t);
    static void reduccionSinRestauracion(Fp &t);

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
