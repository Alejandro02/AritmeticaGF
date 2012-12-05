#include "fp2.h"

Fp Fp2::beta;
Fp Fp2::t0;
Fp Fp2::t1;
Fp Fp2::t2;
Fp Fp2::A;
Fp Fp2::B;

Fp2::Fp2(){
    beta[0] = 5;
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
    Fp::resta(t2,t1,c[0]);
}

void Fp2::exponenciacion(Fp2 &m, Fp &e, Fp2 &c){
}

void Fp2::estableceCoeficiente(std::string numero, int i){
    (*this)[i].parseNumber(numero);
}

void Fp2::limpia(){
    coeficientes[0].limpia();
    coeficientes[1].limpia();
}

void Fp2::imprime(){
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

    if((*this)[0].longitudEnPalabras() != 0 && (*this)[1].longitudEnPalabras() != 0)
        printf("0");

    printf("\n");
}

Fp &Fp2::operator [](int i){
    return coeficientes[i];
}



