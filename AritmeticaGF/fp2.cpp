#include "fp2.h"

Fp Fp2::beta;
Fp Fp2::betaNegativo;
Fp Fp2::t0;
Fp Fp2::t1;
Fp Fp2::t2;
Fp Fp2::t3;
Fp Fp2::A;
Fp Fp2::B;
Fp Fp2::pMenos2;

void Fp2::creaCampo(std::string &primo){
    Fp::setP(primo);
    Fp2::beta.crea(Fp::k);
    Fp2::betaNegativo.crea(Fp::k);
    Fp2::t0.crea(Fp::k);
    Fp2::t1.crea(Fp::k);
    Fp2::t2.crea(Fp::k);
    Fp2::t3.crea(Fp::k);
    Fp2::A.crea(Fp::k);
    Fp2::B.crea(Fp::k);
    Fp2::pMenos2.crea(Fp::k);
    beta.limpia();
    Fp::resta(Fp::getP(),5,beta,true);
    betaNegativo.limpia();
    betaNegativo[0] = 5;
    pMenos2.limpia();
    Fp::resta(Fp::getP(),2,pMenos2,true);
}

void Fp2::crea(Fp2 &a){
    a[0].crea(Fp::k);
    a[1].crea(Fp::k);
}

Fp2::Fp2(){

}

void Fp2::suma(Fp2 &a, Fp2 &b, Fp2 &c){
    Fp::suma(a[0],b[0],c[0]);
    Fp::suma(a[1],b[1],c[1]);
}

void Fp2::resta(Fp2 &a, Fp2 &b, Fp2 &c){
    c.limpia();
    Fp::resta(a[0],b[0],c[0]);
    Fp::resta(a[1],b[1],c[1]);
}

void Fp2::multiplicacion(Fp2 &a, Fp2 &b, Fp2 &c){

    Fp::multiplicacionClasica(a[0],b[0],t0,true);    
    Fp::multiplicacionClasica(a[1],b[1],t1,true);
    Fp::multiplicacionClasica(t1,beta,t2,true);
    Fp::suma(t0,t2,c[0]);

    Fp::suma(a[0],a[1],A);
    Fp::suma(b[0],b[1],B);

    Fp::multiplicacionClasica(A,B,t2,true);
    A.copia(t2);

    Fp::resta(A,t0,t2);
    Fp::resta(t2,t1,c[1]);
}

void Fp2::multiplicacion(Fp2 &a, Fp &b, Fp2 &c){
    Fp::multiplicacionClasica(a[0],b,c[0],true);
    Fp::multiplicacionClasica(a[1],b,c[1],true);
}

void Fp2::cuadrado(Fp2 &a, Fp2 &c){
    Fp::resta(a[0],a[1],t0);
    Fp::multiplicacionClasica(beta,a[1],A,true);
    Fp::resta(a[0],A,t3);
    Fp::multiplicacionClasica(a[0],a[1],t2,true);
    Fp::multiplicacionClasica(t0,t3,A,true);
    Fp::suma(A,t2,t0);
    Fp::suma(t2,t2,c[1]);
    Fp::multiplicacionClasica(beta,t2,B,true);
    Fp::suma(t0,B,c[0]);
}

void Fp2::inverso(Fp2 &a, Fp2 &inverso){
    Fp::multiplicacionClasica(a[0],a[0],t0,true);
    Fp::multiplicacionClasica(a[1],a[1],t1,true);

    Fp::multiplicacionClasica(beta,t1,A,true);
    Fp::resta(t0,A,B);
    t0.copia(B);

    Fp::exponenciacionVentanasDeslizantes(t0,pMenos2,t1);
    Fp::multiplicacionClasica(a[0],t1,inverso[0],true);
    Fp::multiplicacionClasica(a[1],t1,A,true);
    Fp::resta(Fp::getP(),A,inverso[1],true);
}

void Fp2::estableceCoeficiente(std::string numero, int i){
    (*this)[i].parseNumber(numero);
}

void Fp2::limpia(){
    (*this)[0].limpia();
    (*this)[1].limpia();
}

void Fp2::copia(Fp2 &b){
    (*this)[0].copia(b[0]);
    (*this)[1].copia(b[1]);
}

void Fp2::imprime(bool saltosDeLinea){
    if(saltosDeLinea)
        printf("\n");
    int aux;

    if((*this)[1].longitudEnPalabras() != 0){
        if((*this)[1].esNegativo())
            printf("-");

        for(int i = (*this)[1].longitudEnPalabras()-1;i >= 0;i--){
            aux = (*this)[1][i]>>32;
            printf("%.8x",aux);
            aux = (*this)[1][i];
            printf("%.8x",aux);
        }

        printf("u ");
    }

    if((*this)[0].longitudEnPalabras() != 0){
        if((*this)[1].longitudEnPalabras() != 0 && (*this)[0].esPositivo())
            printf("+ ");

        if((*this)[0].esNegativo())
            printf("-");

        for(int i = (*this)[0].longitudEnPalabras()-1;i >= 0;i--){
            aux = (*this)[0][i]>>32;
            printf("%.8x",aux);
            aux = (*this)[0][i];
            printf("%.8x",aux);
        }
    }

    if((*this)[0].longitudEnPalabras() == 0 && (*this)[1].longitudEnPalabras() == 0)
        printf("0");
    if(saltosDeLinea)
        printf("\n");
}

Fp &Fp2::operator [](int i){
    return coeficientes[i];
}



