#include <iostream>
#include "fp12.h"

using namespace std;

int main(){
    string stringPrimo("2370FB049D410FBE4E761A9886E502417D023F40180000017E80600000000001");
    Fp12::creaCampo(stringPrimo);

    Fp12 h,hInv,uno,fp1,fp2,fp3,fp1L,fp2L,fp3L;

    h.estableceCoeficiente("5D89B696AB6E223DCB0AFF620FBA8887ECF370EE67D2827693E36DA5BF1FC8B",0);
    h.estableceCoeficiente("9D2C521C15B2BD702D6C064BE4F017E15DE1EA0329BE7E331F9545C3F9413D4",1);
    h.estableceCoeficiente("2B619C7546DCDE0C25371C6C9A9B592676A54B200A6ED8F8BAB401025EE4074",2);
    h.estableceCoeficiente("FD6924C2808EB45D0A702E24FBDD40AEE8E92BF38F7442CA6A3E07F0F4666C6",3);
    h.estableceCoeficiente("1EE9E40E5ADEEC0473B9001768F15E82C73F6314A390391CF15406933679CAC",4);
    h.estableceCoeficiente("DA6D75D7E85627A1B9C518110127AFAF36448745C4418A8BB06DC3C0A472C33",5);
    h.estableceCoeficiente("8B562018417A38B68988440FA95C16721F98594766345E4F87A8D741137F20F",6);
    h.estableceCoeficiente("1049BAA84BD63508CFE923994F993091351DB04D7F229DB64E88E6969B02CF97",7);
    h.estableceCoeficiente("D8AF06D113090A59F34E508BD2C5130FD997B669C9EEFBD846D96AAB473DA2F",8);
    h.estableceCoeficiente("B68EAB7D692A4443E2B475919F66810E3751D55716AF29D0017387BAB999B05",9);
    h.estableceCoeficiente("13DDC540CE36332709213549673F57F5B5DB05044351D61EEB54CED8AFF97060",10);
    h.estableceCoeficiente("47F7DE84D7C17A7A26BEBA084B2D72369BA61DDBB54D5129207FC7A5090DD52",11);

    Fp12::inverso(h,hInv);
    Fp12::multiplicacion(h,hInv,uno);
    Fp12::exponenciacion(h,Fp::getP(),fp1);
    Fp12::exponenciacion(fp1,Fp::getP(),fp2);
    Fp12::exponenciacion(fp2,Fp::getP(),fp3);
    Fp12::frobeniusP(h,fp1L);
    Fp12::frobeniusP2(h,fp2L);
    Fp12::frobeniusP3(h,fp3L);

    printf("\nUn elemento en Fp12:");
    h.imprime();
    printf("\nSu inverso:");
    hInv.imprime();
    printf("\nMultiplicados deben dar 1:");
    uno.imprime();

    printf("\nEl elemento de Fp12 elevado a la p mediante la funcion Frobenius");
    fp1L.imprime();
    printf("\nEl elemento de Fp12 elevado a la p mediante el algoritmo de exponenciacion");
    fp1.imprime();

    printf("\nEl elemento de Fp12 elevado a la p^2 mediante la funcion Frobenius");
    fp2L.imprime();
    printf("\nEl elemento de Fp12 elevado a la p^2 mediante el algoritmo de exponenciacion");
    fp2.imprime();

    printf("\nEl elemento de Fp12 elevado a la p^3 mediante la funcion Frobenius");
    fp3L.imprime();
    printf("\nEl elemento de Fp12 elevado a la p^3 mediante el algoritmo de exponenciacion");
    fp3.imprime();


}


