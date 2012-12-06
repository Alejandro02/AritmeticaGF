#include "fp12.h"

Fp12::Fp12(){
}

void Fp12::creaCampo(std::string &primo){
    Fp::setP(primo);
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
