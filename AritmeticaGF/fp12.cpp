#include "fp12.h"

Fp6 Fp12::t0;
Fp6 Fp12::t1;
Fp6 Fp12::auxiliar0;
Fp6 Fp12::auxiliar1;
Fp6 Fp12::auxiliar2;

Fp12::Fp12(){
}

void Fp12::creaCampo(std::string &primo){
    Fp6::creaCampo(primo);
    Fp6::crea(t0);
    Fp6::crea(t1);
    Fp6::crea(auxiliar0);
    Fp6::crea(auxiliar1);
    Fp6::crea(auxiliar2);
}

void Fp12::suma(Fp12 &a, Fp12 &b, Fp12 &c){
    Fp6::suma(a[0],b[0],c[0]);
    Fp6::suma(a[1],b[1],c[1]);
}

void Fp12::resta(Fp12 &a, Fp12 &b, Fp12 &c){
    Fp6::resta(a[0],b[0],c[0]);
    Fp6::resta(a[1],b[1],c[1]);
}

void Fp12::multiplicacion(Fp12 &a, Fp12 &b, Fp12 &c){
    Fp6::multiplicacion(a[0],b[0],t0);
    Fp6::multiplicacion(a[1],b[1],t1);

    Fp6::multiplicacionGamma(t1,auxiliar0);

    Fp6::suma(t0,auxiliar0,c[0]);

    Fp6::suma(a[0],a[1],auxiliar1);
    Fp6::suma(b[0],b[1],auxiliar2);

    auxiliar0.limpia();
    Fp6::multiplicacion(auxiliar1,auxiliar2,auxiliar0);

    auxiliar1.limpia();
    Fp6::resta(auxiliar0,t0,auxiliar1);

    Fp6::resta(auxiliar1,t1,c[1]);
}

void Fp12::cuadrado(Fp12 &a, Fp12 &c){
    //c0 = a0 - a1
    Fp6::resta(a[0],a[1],c[0]);

    //Gamma·a1
    Fp6::multiplicacionGamma(a[1],t0);
    //c3 = a0 - Gamma·a1
    Fp6::resta(a[0],t0,auxiliar0);

    //c2 = a·a1
    Fp6::multiplicacion(a[0],a[1],auxiliar1);

    //c0·c3
    Fp6::multiplicacion(c[0],auxiliar0,auxiliar2);

    //c0 = c2 + c0·c3
    Fp6::suma(auxiliar1,auxiliar2,c[0]);
    //c1 = 2c2
    Fp6::multiplicacionPorDos(auxiliar1,c[1]);
    //c2 = Gamma·c2
    Fp6::multiplicacionGamma(auxiliar1,t1);

    Fp6::suma(c[0],t1,c[0]);
}

void Fp12::inverso(Fp12 &a, Fp12 &c){

}

void Fp12::estableceCoeficiente(std::string numero, int i){
    coeficientes[i/6].estableceCoeficiente(numero,i%6);
}

void Fp12::limpia(){
    (*this)[0].limpia();
    (*this)[1].limpia();
}

void Fp12::imprime(){
    printf("\n");

    printf("(");
    (*this)[1].imprime(false);
    printf(")w");

    printf(" + ");

    (*this)[0].imprime(false);

    printf("\n");
}

Fp6 &Fp12::operator [](int i){
    return coeficientes[i];
}
