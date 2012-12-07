#include "fp6.h"

Fp2 Fp6::t0;
Fp2 Fp6::t1;
Fp2 Fp6::t2;
Fp2 Fp6::auxiliar0;
Fp2 Fp6::auxiliar1;
Fp2 Fp6::auxiliar2;
Fp2 Fp6::auxiliar3;
Fp2 Fp6::auxiliar4;
Fp2 Fp6::auxiliar5;
Fp2 Fp6::auxiliar6;
Fp2 Fp6::A;
Fp2 Fp6::B;
Fp2 Fp6::C;
Fp Fp6::dos;

void Fp6::creaCampo(std::string &primo){
    Fp2::creaCampo(primo);
    Fp2::crea(t0);
    Fp2::crea(t1);
    Fp2::crea(t2);
    Fp2::crea(auxiliar0);
    Fp2::crea(auxiliar1);
    Fp2::crea(auxiliar2);
    Fp2::crea(auxiliar3);
    Fp2::crea(auxiliar4);
    Fp2::crea(auxiliar5);
    Fp2::crea(auxiliar6);
    Fp2::crea(A);
    Fp2::crea(B);
    Fp2::crea(C);
    dos.crea(Fp::k);
    dos.limpia();
    dos[0] = 2;

}

void Fp6::crea(Fp6 &a){
    Fp2::crea(a[0]);
    Fp2::crea(a[1]);
    Fp2::crea(a[2]);
}

Fp6::Fp6(){

}

void Fp6::suma(Fp6 &a, Fp6 &b, Fp6 &c){
    Fp2::suma(a[0],b[0],c[0]);
    Fp2::suma(a[1],b[1],c[1]);
    Fp2::suma(a[2],b[2],c[2]);
}

void Fp6::resta(Fp6 &a, Fp6 &b, Fp6 &c){
    Fp2::resta(a[0],b[0],c[0]);
    Fp2::resta(a[1],b[1],c[1]);
    Fp2::resta(a[2],b[2],c[2]);
}

void Fp6::multiplicacion(Fp6 &a, Fp2 &b, Fp6 &c){
    Fp2::multiplicacion(a[0],b,c[0]);
    Fp2::multiplicacion(a[1],b,c[1]);
    Fp2::multiplicacion(a[2],b,c[2]);
}

void Fp6::multiplicacion(Fp6 &a, Fp2 &b0, Fp2 &b1, Fp6 &c){
    Fp2::multiplicacion(a[0],b0,t0);
    Fp2::multiplicacion(a[1],b1,t1);

    //Empieza ((a1+a2)(b1)-t1)Xi + t0
    Fp2::suma(a[1],a[2],auxiliar1);
    Fp2::multiplicacion(auxiliar1,b1,auxiliar2);
    Fp2::resta(auxiliar2,t1,auxiliar3);

    auxiliar1.limpia();
    auxiliar2.limpia();

    auxiliar1[1].copia(auxiliar3[0]);
    Fp::multiplicacionClasica(auxiliar3[1],Fp2::beta,auxiliar1[0],true);

    Fp2::suma(auxiliar1,t0,c[0]);

    //Termina ((a1+a2)(b1)-t1)Xi + t0

    auxiliar1.limpia();
    auxiliar2.limpia();
    auxiliar3.limpia();

    //Empieza (a0+a1)(b0+b1) - t0 - t1
    Fp2::suma(a[0],a[1],auxiliar1);
    Fp2::suma(b0,b1,auxiliar2);

    Fp2::multiplicacion(auxiliar1,auxiliar2,auxiliar3);

    auxiliar1.limpia();
    auxiliar2.limpia();

    Fp2::resta(auxiliar3,t0,auxiliar2);
    Fp2::resta(auxiliar2,t1,c[1]);
    //Termina (a0+a1)(b0+b1) - t0 - t1

    auxiliar1.limpia();
    auxiliar2.limpia();
    auxiliar3.limpia();

    //Empieza a2b0 +t1

    Fp2::multiplicacion(a[2],b0,auxiliar1);
    Fp2::suma(auxiliar1,t1,c[2]);


}

void Fp6::multiplicacion(Fp6 &a, Fp6 &b, Fp6 &c){
    Fp2::multiplicacion(a[0],b[0],t0);
    Fp2::multiplicacion(a[1],b[1],t1);
    Fp2::multiplicacion(a[2],b[2],t2);

    //Empieza [(a1+a2)(b1+b2)-t1-t2]Xi + t0
    Fp2::suma(a[1],a[2],auxiliar1);
    Fp2::suma(b[1],b[2],auxiliar2);

    Fp2::multiplicacion(auxiliar1,auxiliar2,auxiliar3);

    auxiliar1.limpia();
    auxiliar2.limpia();

    Fp2::resta(auxiliar3,t1,auxiliar2);
    Fp2::resta(auxiliar2,t2,auxiliar1);

    auxiliar3.limpia();

    auxiliar3[1].copia(auxiliar1[0]);
    Fp::multiplicacionClasica(auxiliar1[1],Fp2::beta,auxiliar3[0],true);

    Fp2::suma(auxiliar3,t0,c[0]);
    //Termina [(a1+a2)(b1+b2)-t1-t2]Xi + t0

    auxiliar1.limpia();
    auxiliar2.limpia();
    auxiliar3.limpia();

    //Empieza (a0+a1)(b0+b1) - t0 - t1 + Xit2;

    Fp2::suma(a[0],a[1],auxiliar1);
    Fp2::suma(b[0],b[1],auxiliar2);

    Fp2::multiplicacion(auxiliar1,auxiliar2,auxiliar3);

    auxiliar1.limpia();
    auxiliar2.limpia();

    Fp2::resta(auxiliar3,t0,auxiliar2);
    Fp2::resta(auxiliar2,t1,auxiliar1);

    auxiliar3.limpia();

    auxiliar3[1].copia(t2[0]);
    Fp::multiplicacionClasica(t2[1],Fp2::beta,auxiliar3[0],true);

    Fp2::suma(auxiliar1,auxiliar3,c[1]);

    //Termina (a0+a1)(b0+b1) - t0 - t1 + Xit2;

    auxiliar1.limpia();
    auxiliar2.limpia();
    auxiliar3.limpia();

    //Empieza (a0+a2)(b0+b2)-t0-t2+t1

    Fp2::suma(a[0],a[2],auxiliar1);
    Fp2::suma(b[0],b[2],auxiliar2);

    Fp2::multiplicacion(auxiliar1,auxiliar2,auxiliar3);

    auxiliar1.limpia();
    auxiliar2.limpia();

    Fp2::resta(auxiliar3,t0,auxiliar2);
    Fp2::resta(auxiliar2,t2,auxiliar1);

    Fp2::suma(auxiliar1,t1,c[2]);

    //Termina (a0+a2)(b0+b2)-t0-t2+t1

}

void Fp6::multiplicacionGamma(Fp6 &a, Fp6 &c){
    auxiliar1.limpia();
    auxiliar1[1].copia(a[2][0]);
    Fp::multiplicacionClasica(a[2][1],Fp2::beta,auxiliar1[0],true);

    c[0].copia(auxiliar1);
    c[1].copia(a[0]);
    c[2].copia(a[1]);
}

void Fp6::multiplicacionPorDos(Fp6 &a, Fp6 &c){
    Fp2::multiplicacion(a[0],dos,c[0]);
    Fp2::multiplicacion(a[1],dos,c[1]);
    Fp2::multiplicacion(a[2],dos,c[2]);
}

void Fp6::cuadrado(Fp6 &a, Fp6 &c){

    //c4 = 2(a0xa1)
    Fp2::multiplicacion(a[0],a[1],auxiliar5);
    Fp2::multiplicacion(auxiliar5,dos,auxiliar4);

    //c5 = (a2)^2
    Fp2::cuadrado(a[2],auxiliar5);

    //Xi(c5)
    auxiliar3[1].copia(auxiliar5[0]);
    Fp::multiplicacionClasica(auxiliar5[1],Fp2::beta,auxiliar3[0],true);
    //c1 = Xi(c5) + c4
    Fp2::suma(auxiliar3,auxiliar4,c[1]);

    auxiliar3.limpia();
    //c2 = c4 - c5
    Fp2::resta(auxiliar4,auxiliar5,auxiliar2);
    //c3 = a0^2
    Fp2::cuadrado(a[0],auxiliar3);
    //c4 = a0-a1+a2
    Fp2::resta(a[0],a[1],t0);
    Fp2::suma(t0,a[2],auxiliar4);

    //c5 = 2(a1xa2)
    Fp2::multiplicacion(a[0],a[1],auxiliar1);
    Fp2::multiplicacion(auxiliar1,dos,auxiliar5);
    //c4 = c4^2
    Fp2::cuadrado(auxiliar4,auxiliar4);

    //Xi(c5)
    auxiliar1.limpia();
    auxiliar1[1].copia(auxiliar5[0]);
    Fp::multiplicacionClasica(auxiliar5[1],Fp2::beta,auxiliar1[0],true);
    //c0 = Xi(c5) + c3
    Fp2::suma(auxiliar1,auxiliar3,c[0]);

    t0.limpia();
    //c2 = (c2 en realidad es auxiliar2 aqui) c2+c4+c5-c3
    Fp2::suma(auxiliar2,auxiliar4,auxiliar1);
    Fp2::suma(auxiliar1,auxiliar5,t0);
    Fp2::resta(t0,auxiliar3,c[2]);
}

void Fp6::inverso(Fp6 &a, Fp6 &aInv){
    auxiliar0.limpia();
    auxiliar1.limpia();
    auxiliar2.limpia();
    auxiliar3.limpia();
    auxiliar4.limpia();
    auxiliar5.limpia();
    auxiliar6.limpia();
    A.limpia();
    B.limpia();
    C.limpia();
    t0.limpia();
    t1.limpia();
    t2.limpia();

    Fp2::cuadrado(a[0],auxiliar0);
    Fp2::cuadrado(a[1],auxiliar1);
    Fp2::cuadrado(a[2],auxiliar2);
    Fp2::multiplicacion(a[0],a[1],auxiliar3);
    Fp2::multiplicacion(a[0],a[2],auxiliar4);
    Fp2::multiplicacion(a[1],a[2],auxiliar5);

    //Xi(c5) ya deberia hacer funcion para esto xD
    t0.limpia();
    t0[1].copia(auxiliar5[0]);
    Fp::multiplicacionClasica(auxiliar5[1],Fp2::beta,t0[0],true);

    Fp2::resta(auxiliar0,t0,A);

    //Xi(c2)
    t0.limpia();
    t0[1].copia(auxiliar2[0]);
    Fp::multiplicacionClasica(auxiliar2[1],Fp2::beta,t0[0],true);

    Fp2::resta(t0,auxiliar3,B);

    Fp2::resta(auxiliar1,auxiliar4,C);

    Fp2::multiplicacion(a[0],A,auxiliar6);

    //Xi(a2)
    t0.limpia();
    t0[1].copia(a[2][0]);
    Fp::multiplicacionClasica(a[2][1],Fp2::beta,t0[0],true);

    t1.limpia();
    Fp2::multiplicacion(t0,B,t1);
    Fp2::suma(t1,auxiliar6,auxiliar6);

    //Xi(a1)
    t0.limpia();
    t0[1].copia(a[1][0]);
    Fp::multiplicacionClasica(a[1][1],Fp2::beta,t0[0],true);

    t1.limpia();
    Fp2::multiplicacion(t0,C,t1);
    Fp2::suma(t1,auxiliar6,auxiliar6);

    Fp2::inverso(auxiliar6,t2);

    Fp2::multiplicacion(A,t2,aInv[0]);
    Fp2::multiplicacion(B,t2,aInv[1]);
    Fp2::multiplicacion(C,t2,aInv[2]);
}

void Fp6::imprime(bool saltosDeLinea){
    if(saltosDeLinea)
        printf("\n");

    printf("(");
    (*this)[2].imprime(false);
    printf(")v^2");

    printf(" + ");

    printf("(");
    (*this)[1].imprime(false);
    printf(")v");

    printf(" + ");

    printf("(");
    (*this)[0].imprime(false);
    printf(")");

    if(saltosDeLinea)
        printf("\n");
}

void Fp6::estableceCoeficiente(std::string numero, int i){
    (*this)[i/2][i%2].parseNumber(numero);
}

void Fp6::limpia(){
    (*this)[0].limpia();
    (*this)[1].limpia();
    (*this)[2].limpia();
}

Fp2 &Fp6::operator [](int i){
    return coeficientes[i];
}

