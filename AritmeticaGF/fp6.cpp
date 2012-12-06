#include "fp6.h"

void Fp6::creaCampo(std::string &primo){
    Fp::setP(primo);
}

Fp6::Fp6(){

}

void Fp6::imprime(){
    printf("\n");

    printf("(");
    coeficientes[2].imprime(false);
    printf(")w^2");

    printf(" + ");

    printf("(");
    coeficientes[1].imprime(false);
    printf(")w");

    printf(" + ");

    printf("(");
    coeficientes[0].imprime(false);
    printf(")");

    printf("\n");
}

void Fp6::estableceCoeficiente(std::string numero, int i){
    (*this)[i/2][i%2].parseNumber(numero);
}

void Fp6::limpia(){
    coeficientes[0].limpia();
    coeficientes[1].limpia();
    coeficientes[2].limpia();
}

Fp2 &Fp6::operator [](int i){
    return coeficientes[i];
}

