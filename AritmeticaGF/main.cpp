#include <iostream>
#include "fp.h"

using namespace std;

/*
Primo de 254 bits
2370FB049D410FBE
4E761A9886E50241
7D023F4018000001
7E80600000000001
Numero en GF
1EE9E40E5ADEEC0473B9001768F15E82C73F6314A390391CF15406933679CAC
*/

int main(){
    string stringPrimo("2370FB049D410FBE4E761A9886E502417D023F40180000017E80600000000001");
    Fp::setP(stringPrimo);

    Fp x("1EE9E40E5ADEEC0473B9001768F15E82C73F6314A390391CF15406933679CAC");
    Fp y("00B562018417A38B68988440FA95C16721F98594766345E4F87A8D741137F20F");
    Fp z;

    Fp::getP().imprime();
    printf("x");
    x.imprime();
    printf("y");
    y.imprime();

    Fp::multiplicacionBinariaIzquierdaADerecha(x,y,z);
    z.imprime();

    printf("\n");
    Fp::multiplicacionClasica(x,y,z);
    z.imprime();

    return 0;
}

