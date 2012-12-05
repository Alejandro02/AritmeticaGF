#include <iostream>
#include "fp.h"

using namespace std;

/*
Primos de 256 bits
2370FB049D410FBE4E761A9886E502417D023F40180000017E80600000000001
357CC25F967F1C3EB5937C41A65808573C799B6C54074DE71E90C0A21C6FB3C3
9B78456A1FD05538733C3941F9527F4F756F08B18881BA01A975360DA98C82FB
C5316E71B5505F4859A7E3481198DA00A979761234B981396A895E816EF53FF9
*/

int main(){
    string stringPrimo("2370FB049D410FBE4E761A9886E502417D023F40180000017E80600000000001");
    Fp::setP(stringPrimo,4);

    Fp x,xInv,z,phi;

    Fp::resta(Fp::getP(),2,phi);

    printf("p");
    Fp::getP().imprime();        

    for(int i = 0 ; i < 10000; i++){
        //Numero aleatorio
        x.aleatorizaNumero();
        //Obteniendo su inverso
        Fp::exponenciacionVentanasDeslizantes(x,phi,xInv);
        //Multiplicando x por su inverso
        Fp::multiplicacionClasica(x,xInv,z,true);

        if( !(z == 1) ){
            printf("X");
            x.imprime();
            printf("X^-1");
            xInv.imprime();
            printf("X*X^-1");
            z.imprime();
            printf("\n\n");
            perror("Incongruencia");
            exit(0);
        }                
    }
    return 0;
}

