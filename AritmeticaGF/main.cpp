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

    Fp x("dd85d8fd73bdc4d53219d426d0eb997fe4564d1e18ba4094313b70a08e0bf28");
    Fp y("b7e17edd0a6d4befa64e8438d8ce3df47b9015c7fcda9606630f29a65bd6bff");
    Fp z;

    printf("p");
    Fp::getP().imprime();

    Fp::multiplicacionMontgomery(x,y,z);
    z.imprime();
    Fp::multiplicacionClasica(x,y,z,true);
    z.imprime();
    return 0;
}


/* Main para probar los metodos de multiplicacion y reduccion*/
/*int main(){
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

