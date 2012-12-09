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

void Fp12::creaExponentes(){
    pMenos1.limpia();
    aux.limpia();
    seis.limpia();
    //Esto es t = 2^62-2^54+2^44
    pMenos1[0] = 0x3FC0100000000000;
    //Esto es t^2
    Fp::multiplicacionClasica(pMenos1,pMenos1,aux);
    //Esto es t^3
    Fp::multiplicacionClasica(aux,pMenos1,seis);

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
    Fp12::creaExponentes();
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

void Fp12::exponenciacion(Fp12 &a, Fp &e, Fp12 &c){
    Fp12 Q;
    Fp12 aux;

    Q[0].copia(a[0]);
    Q[1].copia(a[1]);

    for(int i = e.longitudEnBits()-2;i >= 0;i--){
        Fp12::cuadrado(Q,aux);
        Q[0].copia(aux[0]);
        Q[1].copia(aux[1]);
        if(e.bitEnPosicion(i) == 1){
            Fp12::multiplicacion(Q,a,aux);
            Q[0].copia(aux[0]);
            Q[1].copia(aux[1]);
        }
    }
    c[0].copia(Q[0]);
    c[1].copia(Q[1]);
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

void Fp12::exponenciacionFinal(Fp12 &f, Fp12 &fr){
    Fp12 aux1,aux2,aux3,aux4,faux;
    Fp12 f1,f2;
    Fp12 ft1,ft2,ft3;
    Fp12 ffrob,ffrob2,ffrob3;
    Fp12 y0,y1,y2,y3,y4,y5,y6;
    Fp12 tao0,tao1;

    //f1 = fBarra
    Fp12::conjugado(f,f1);
    //f2 = f^-1
    Fp12::inverso(f,f2);
    //f = f1·f2
    Fp12::multiplicacion(f1,f2,aux1);
    //f^p^2
    Fp12::frobeniusP2(aux1,ffrob2);
    //f = f^p^2·f
    Fp12::multiplicacion(ffrob2,aux1,faux);
    /*pMenos1 es t, aux es t^2 y seis es t^3, fueron pre calculados*/
    //ft1 = f^t
    Fp12::exponenciacion(faux,pMenos1,ft1);
    //ft2 = f^t^2
    Fp12::exponenciacion(faux,aux,ft2);
    //ft2 = f^t^3
    Fp12::exponenciacion(faux,seis,ft3);
    //fp1 = f^p
    Fp12::frobeniusP(faux,ffrob);
    //fp2 = f^p^2
    Fp12::frobeniusP2(faux,ffrob2);
    //fp3 = f^p^3
    Fp12::frobeniusP3(faux,ffrob3);
    //fp1·fp2
    Fp12::multiplicacion(ffrob,ffrob2,aux1);
    //y0 = fp1·fp2·fp3
    Fp12::multiplicacion(aux1,ffrob3,y0);
    //y1 = f1
    y1[0].copia(f1[0]);
    y1[1].copia(f1[1]);
    //y2 = ft2^p^2
    Fp12::frobeniusP2(ft2,y2);
    //y3 = ft1^p
    Fp12::frobeniusP(ft1,aux1);
    //y3 = y3 Barra
    Fp12::conjugado(aux1,y3);
    //ft2^p
    Fp12::frobeniusP(ft2,aux1);
    //y4 = (ft2^p)·ft1
    Fp12::multiplicacion(aux1,ft1,aux2);
    //y4 = y4 Barra
    Fp12::conjugado(aux2,y4);
    //y5 = ft2 Barra
    Fp12::conjugado(ft2,y5);
    //ft3^p
    Fp12::frobeniusP(ft3,aux1);
    //y6 = ft3^p·ft3
    Fp12::multiplicacion(aux1,ft3,aux2);
    //y6 = y6 Barra
    Fp12::conjugado(aux2,y6);
    //y6^2
    Fp12::cuadrado(y6,aux1);
    //y6^2·y4
    Fp12::multiplicacion(aux1,y4,aux2);
    //t0 = y6^2·y4·y5
    Fp12::multiplicacion(aux2,y5,aux1);
    //y3·y5
    Fp12::multiplicacion(y3,y5,aux3);
    //t1 = y3·y5·t0
    Fp12::multiplicacion(aux3,aux1,aux4);
    //t0 = y2·t0
    Fp12::multiplicacion(aux1,y2,tao0);
    //t1^2
    Fp12::cuadrado(aux4,aux1);
    //t1^2·t0
    Fp12::multiplicacion(aux1,tao0,aux2);
    //t1 = (t1^2·t0)^2
    Fp12::cuadrado(aux2,tao1);
    //t0 = t1·y1
    Fp12::multiplicacion(tao1,y1,tao0);
    //t1 = t1·y0
    Fp12::multiplicacion(tao1,y0,aux1);
    //t0 = t0^2
    Fp12::cuadrado(tao0,aux2);
    //  ^
    //  |
    //Este es el unico que no esta como lo dice en el articulo.
    //f = t1·t0
    Fp12::multiplicacion(aux1,aux2,fr);
}

void Fp12::conjugado(Fp12 &a,Fp12 &b){
    b[0][0].copia(a[0][0]);
    b[0][1].copia(a[0][1]);
    b[0][2].copia(a[0][2]);
    Fp2::multiplicacionPorMenosUno(a[1][0],b[1][0]);
    Fp2::multiplicacionPorMenosUno(a[1][1],b[1][1]);
    Fp2::multiplicacionPorMenosUno(a[1][2],b[1][2]);
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
