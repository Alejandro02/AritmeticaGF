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
    coeficientes[0].limpia();
    coeficientes[1].limpia();
}
