#include <iostream>
#include "fp.h"

using namespace std;

/*
Primo de 254 bits
2370FB049D410FBE4E761A9886E502417D023F40180000017E80600000000001
*/

int main(){
    string stringPrimo("2370FB049D410FBE4E761A9886E502417D023F40180000017E80600000000001");
    Fp::setP(stringPrimo,true);

    Fp x;
    Fp y;
    Fp z;

    printf("p");
    Fp::getP().imprime();

}


/*
int main(){
    string stringPrimo("2370FB049D410FBE4E761A9886E502417D023F40180000017E80600000000001");
    Fp::setP(stringPrimo,true);

    Fp x;
    Fp y;
    Fp z;
    Fp rNoRestoring,rRestoring,rBarret;

    printf("p");
    Fp::getP().imprime();

    for(int i = 0 ; i < 50000; i++){
        x.aleatorizaNumero();
        y.aleatorizaNumero();

        Fp::multiplicacionClasica(x,y,rRestoring);
        rNoRestoring.copia(rRestoring);
        rBarret.copia(rRestoring);

        Fp::reduccionConRestauracion(rRestoring);
        Fp::reduccionSinRestauracion(rNoRestoring);
        Fp::reduccionBarret(rBarret);

        if( !(rRestoring == rNoRestoring) && !(rNoRestoring == rBarret) ){
            printf("Iteracion %d",(i+1));
            Fp::multiplicacionClasica(x,y,z);

            printf("Residuo con restauracion");
            rRestoring.imprime();
            printf("Residuo sin restauracion");
            rNoRestoring.imprime();
            printf("Restauracion Barret");
            rBarret.imprime();

            printf("X");
            x.imprime();
            printf("Y");
            y.imprime();
            printf("X*Y");
            z.imprime();
            printf("\n\n");
            exit(0);
        }

    }
    return 0;
}*/

