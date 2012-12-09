#include "fp12.h"

Fp6 Fp12::t0;
Fp6 Fp12::t1;
Fp6 Fp12::auxiliar0;
Fp6 Fp12::auxiliar1;
Fp6 Fp12::auxiliar2;

Fp Fp12::pMenos1;
Fp Fp12::iterador;
Fp Fp12::seis;
Fp Fp12::aux;

Fp2 Fp12::Xi;

Fp2 Fp12::Gamma11;
Fp2 Fp12::Gamma12;
Fp2 Fp12::Gamma13;
Fp2 Fp12::Gamma14;
Fp2 Fp12::Gamma15;

Fp2 Fp12::Gamma21;
Fp2 Fp12::Gamma22;
Fp2 Fp12::Gamma23;
Fp2 Fp12::Gamma24;
Fp2 Fp12::Gamma25;

Fp2 Fp12::Gamma31;
Fp2 Fp12::Gamma32;
Fp2 Fp12::Gamma33;
Fp2 Fp12::Gamma34;
Fp2 Fp12::Gamma35;

Fp2 Fp12::conjugadoAux;

Fp2 Fp12::Frobenius_t1;
Fp2 Fp12::Frobenius_t2;
Fp2 Fp12::Frobenius_t3;
Fp2 Fp12::Frobenius_t4;
Fp2 Fp12::Frobenius_t5;
Fp2 Fp12::Frobenius_t6;

void Fp12::creaGamma1x(){
    pMenos1.crea(Fp::k);
    iterador.crea(Fp::k);
    seis.crea(Fp::k);
    aux.crea(Fp::k);

    seis[0] = 6;
    Fp::resta(Fp::getP(),1,pMenos1);

    Fp2::exponenciacionIzquierdaADerecha(Xi,(pMenos1/seis).at(0),Gamma11);

    aux.limpia();
    iterador.limpia();
    iterador[0] = 2;
    Fp::multiplicacionClasica(pMenos1,iterador,aux,false);
    Fp2::exponenciacionIzquierdaADerecha(Xi,(aux/seis).at(0),Gamma12);

    aux.limpia();
    iterador[0] = 3;
    Fp::multiplicacionClasica(pMenos1,iterador,aux,false);
    Fp2::exponenciacionIzquierdaADerecha(Xi,(aux/seis).at(0),Gamma13);

    aux.limpia();
    iterador[0] = 4;
    Fp::multiplicacionClasica(pMenos1,iterador,aux,false);
    Fp2::exponenciacionIzquierdaADerecha(Xi,(aux/seis).at(0),Gamma14);

    aux.limpia();
    iterador[0] = 5;
    Fp::multiplicacionClasica(pMenos1,iterador,aux,false);
    Fp2::exponenciacionIzquierdaADerecha(Xi,(aux/seis).at(0),Gamma15);
}

void Fp12::creaGamma2x(){
    Fp2::conjugado(Gamma11,conjugadoAux);
    Fp2::multiplicacion(Gamma11,conjugadoAux,Gamma21);

    Fp2::conjugado(Gamma12,conjugadoAux);
    Fp2::multiplicacion(Gamma12,conjugadoAux,Gamma22);

    Fp2::conjugado(Gamma13,conjugadoAux);
    Fp2::multiplicacion(Gamma13,conjugadoAux,Gamma23);

    Fp2::conjugado(Gamma14,conjugadoAux);
    Fp2::multiplicacion(Gamma14,conjugadoAux,Gamma24);

    Fp2::conjugado(Gamma15,conjugadoAux);
    Fp2::multiplicacion(Gamma15,conjugadoAux,Gamma25);

}

void Fp12::creaGamma3x(){
    Fp2::multiplicacion(Gamma11,Gamma21,Gamma31);
    Fp2::multiplicacion(Gamma12,Gamma22,Gamma32);
    Fp2::multiplicacion(Gamma13,Gamma23,Gamma33);
    Fp2::multiplicacion(Gamma14,Gamma24,Gamma34);
    Fp2::multiplicacion(Gamma15,Gamma25,Gamma35);
}

Fp12::Fp12(){
}

void Fp12::creaCampo(std::string &primo){
    Fp6::creaCampo(primo);
    Fp6::crea(t0);
    Fp6::crea(t1);
    Fp6::crea(auxiliar0);
    Fp6::crea(auxiliar1);
    Fp6::crea(auxiliar2);
    Fp2::crea(Gamma11);
    Fp2::crea(Gamma12);
    Fp2::crea(Gamma13);
    Fp2::crea(Gamma14);
    Fp2::crea(Gamma15);

    Fp2::crea(Gamma21);
    Fp2::crea(Gamma22);
    Fp2::crea(Gamma23);
    Fp2::crea(Gamma24);
    Fp2::crea(Gamma25);

    Fp2::crea(Gamma31);
    Fp2::crea(Gamma32);
    Fp2::crea(Gamma33);
    Fp2::crea(Gamma34);
    Fp2::crea(Gamma35);

    Fp2::crea(Frobenius_t1);
    Fp2::crea(Frobenius_t2);
    Fp2::crea(Frobenius_t3);
    Fp2::crea(Frobenius_t4);
    Fp2::crea(Frobenius_t5);
    Fp2::crea(Frobenius_t6);

    Fp2::crea(conjugadoAux);
    Fp2::crea(Xi);
    Xi[1][0] = 1;

    Fp12::creaGamma1x();
    Fp12::creaGamma2x();
    Fp12::creaGamma3x();
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
    //t0 = a0^2
    Fp6::cuadrado(a[0],t0);

    //t1 = a1^2
    Fp6::cuadrado(a[1],t1);

    //Gammat1
    Fp6::multiplicacionGamma(t1,auxiliar0);
    //t0 = t0 - Gammat1
    Fp6::resta(t0,auxiliar0,auxiliar1);
    //t1 = t0^-1
    Fp6::inverso(auxiliar1,t1);

    //c0 = a0t1
    Fp6::multiplicacion(a[0],t1,c[0]);
    //a1t1
    Fp6::multiplicacion(a[1],t1,auxiliar2);
    //c1 = -a1·t1
    Fp6::multiplicacionPorMenosUno(auxiliar2,c[1]);
}

void Fp12::frobeniusP(Fp12 &a, Fp12 &c){
    //a[0] = g ; a[1] = h
    Fp2::conjugado(a[0][0],Frobenius_t1);
    Fp2::conjugado(a[1][0],Frobenius_t2);
    Fp2::conjugado(a[0][1],Frobenius_t3);
    Fp2::conjugado(a[1][1],Frobenius_t4);
    Fp2::conjugado(a[0][2],Frobenius_t5);
    Fp2::conjugado(a[1][2],Frobenius_t6);

    c[0][0].copia(Frobenius_t1);
    Fp2::multiplicacion(Frobenius_t3,Gamma12,c[0][1]);
    Fp2::multiplicacion(Frobenius_t5,Gamma14,c[0][2]);
    Fp2::multiplicacion(Frobenius_t2,Gamma11,c[1][0]);
    Fp2::multiplicacion(Frobenius_t4,Gamma13,c[1][1]);
    Fp2::multiplicacion(Frobenius_t6,Gamma15,c[1][2]);
}

void Fp12::frobeniusP2(Fp12 &a, Fp12 &c){
    //a[0] = g ; a[1] = h
    c[0][0].copia(a[0][0]);
    Fp2::multiplicacion(a[1][0],Gamma21,c[1][0]);
    Fp2::multiplicacion(a[0][1],Gamma22,c[0][1]);
    Fp2::multiplicacion(a[1][1],Gamma23,c[1][1]);
    Fp2::multiplicacion(a[0][2],Gamma24,c[0][2]);
    Fp2::multiplicacion(a[1][2],Gamma25,c[1][2]);
}

void Fp12::frobeniusP3(Fp12 &a, Fp12 &c){
    //a[0] = g ; a[1] = h
    Fp2::conjugado(a[0][0],Frobenius_t1);
    Fp2::conjugado(a[1][0],Frobenius_t2);
    Fp2::conjugado(a[0][1],Frobenius_t3);
    Fp2::conjugado(a[1][1],Frobenius_t4);
    Fp2::conjugado(a[0][2],Frobenius_t5);
    Fp2::conjugado(a[1][2],Frobenius_t6);

    c[0][0].copia(Frobenius_t1);
    Fp2::multiplicacion(Frobenius_t3,Gamma32,c[0][1]);
    Fp2::multiplicacion(Frobenius_t5,Gamma34,c[0][2]);
    Fp2::multiplicacion(Frobenius_t2,Gamma31,c[1][0]);
    Fp2::multiplicacion(Frobenius_t4,Gamma33,c[1][1]);
    Fp2::multiplicacion(Frobenius_t6,Gamma35,c[1][2]);
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
