#include "fp.h"

Fp Fp::primo,Fp::auxiliar;
int Fp::k = 0;

Fp::Fp(){    
    misPalabras = (uInt64*) malloc(sizeof(uInt64) * 2 * k );

    for(int i = 0; i < 2*k ;i++)
        misPalabras[i] = 0;

    this->esNeg = false;
}

Fp::Fp(std::string numeroEnHex){
    misPalabras = (uInt64*) malloc(sizeof(uInt64) * 2 * k );

    this->parseNumber(numeroEnHex);

    this->esNeg = false;
}

void Fp::aleatorizaNumero(){
    this->iniciarSemillaAleatoria();
    short aux;

    for(int i = 0; i < k ;i++){
        aux = rand();
        (*this)[i] = aux;
        (*this)[i] <<= 16;

        aux = rand();
        (*this)[i] |= aux;
        (*this)[i] <<= 16;


        aux = rand();
        (*this)[i] |= aux;
        (*this)[i] <<= 16;

        aux = rand();
        (*this)[i] |= aux;
    }

    (*this)[k-1] = (*this)[k-1]%Fp::primo[k-1];
}

void Fp::copia(Fp &otroNumero){
    this->limpia();

    for(int i = 0 ; i < otroNumero.longitudEnPalabras();i++)
        (*this)[i] = otroNumero[i];
}

void Fp::copia(uInt64 *unVector,int longitud){
    misPalabras = NULL;
    misPalabras = (uInt64*) malloc(sizeof(uInt64) *  longitud * 2 );

    for(int i = 0 ; i < longitud;i++){
        (*this)[i] = unVector[i];
        (*this)[i+longitud] = 0;
    }
}

void Fp::setNegativo(bool negativo){
    this->esNeg = negativo;
}

int Fp::longitudEnPalabras(){
    int i;
    for(i = 0; (*this)[i] != 0 && i < 2*k ;i++);

    return i;
}

int Fp::longitudEnBits(){
    int i,palabrasLlenas,bitsEnUltimaPalabra;
    uInt64 aux;

    for(i = 0; (*this)[i] != 0 && i < 2*k ;i++);

    palabrasLlenas =  (i - 1)*sizeof(uInt64)*8;

    for(bitsEnUltimaPalabra = 0, aux = (*this)[i-1]; aux != 0 ;aux >>= 1, bitsEnUltimaPalabra++);

    return palabrasLlenas + bitsEnUltimaPalabra;
}

bool Fp::esNegativo() const{
    return this->esNeg;
}

bool Fp::esPositivo() const{
    return !this->esNeg;
}

void Fp::limpia(){
    for(int i = 0; i < 2*k ;i++)
        (*this)[i] = 0;
}

void Fp::parseNumber(std::string numeroEnHex){
    uInt64 aux;
    int i;

    this->limpia();

    for( i = numeroEnHex.size() - maxN ; i >= 0; i-= maxN){
        fromStringTo<uInt64>(aux,numeroEnHex.substr(i,maxN),std::hex);
        this->insertaFinal(aux);
    }
    i+=maxN;
    if(i > 0){
        fromStringTo<uInt64>(aux,numeroEnHex.substr(0,i),std::hex);
        this->insertaFinal(aux);
    }
}

void Fp::insertaFinal(uInt64 palabra){
    int final;
    final = this->longitudEnPalabras();
    if(final < 2*k)
        (*this)[final] = palabra;
}

void Fp::borraFinal(){
    int final;
    final = this->longitudEnPalabras();
    if(final > 0)
        (*this)[final-1] = 0;
}

void Fp::imprime(){
    printf("\n");
    int aux;

    if(this->longitudEnPalabras() == 0){
        printf("0");
        return;
    }

    if(this->esNegativo())
        printf("-");

    for(int i = this->longitudEnPalabras()-1;i >= 0;i--){

        aux = (*this)[i]>>32;
        printf("%.8x",aux);
        aux = (*this)[i];
        printf("%.8x ",aux);

    }
    printf("\n");
}

void Fp::iniciarSemillaAleatoria(){
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
}

void Fp::setP(std::string &primoCadena){
    uInt64 *palabras,aux;
    int i,j,primoLen = (primoCadena.size()*4)/64;

    primoLen = (primoCadena.size()*4)%64 != 0 ? primoLen + 1 : primoLen;

    palabras = (uInt64*) malloc(sizeof(uInt64) * primoLen );

    for( j = 0, i = primoCadena.size() - maxN ; i >= 0; i-= maxN,j++){
        fromStringTo<uInt64>(aux,primoCadena.substr(i,maxN),std::hex);
        palabras[j] = aux;
    }

    i+=maxN;

    if(i > 0){
        fromStringTo<uInt64>(aux,primoCadena.substr(0,i),std::hex);
        palabras[j] = aux;
    }
    Fp::primo.copia(palabras,primoLen);

    auxiliar.copia(palabras,primoLen);

    Fp::k = primoLen;
}

Fp &Fp::getP(){
    return Fp::primo;
}

void Fp::suma(Fp &a, Fp &b, Fp &resultado){
    int i,c;
    uInt64 s,aux;

    for(i = 0,c = 0; i < 2*k;i++){
        s = a[i] + b[i] + c;
        aux = maximoValorDePalabra - (b[i] + c);
        c = ( a[i] > aux) ? 1 : 0;
        resultado[i] = s;
    }

    if(resultado > Fp::primo){
        Fp::resta(resultado,Fp::primo,resultado);
    }else if(resultado == Fp::primo){
        resultado.limpia();
    }
}

void Fp::suma(Fp &a, uInt64 b, Fp &resultado){
    int i,c;
    uInt64 s,aux;

    s = a[0] + b;
    aux = maximoValorDePalabra - b;
    c = ( a[0] > aux) ? 1 : 0;

    resultado[0] = s;

    for(i = 1; i < 2*k;i++){
        s = a[i]  + c;
        aux = maximoValorDePalabra - c;
        c = ( a[i] > aux) ? 1 : 0;

        resultado[i] = s;
    }

    if(resultado > Fp::primo){
        Fp::resta(resultado,Fp::primo,resultado);
    }else if(resultado == Fp::primo){
        resultado.limpia();
    }
}

void Fp::resta(Fp &a, Fp &b, Fp &resultado,bool permitirResultadosNegativos ){
    int i,c;
    uInt64 s;

    for(c = 0, i = 0; i < 2*k ;i++){
        s = a[i] - (b[i] + c);
        c = ( (b[i] + c ) > a[i] ) ? 1 : 0;
        resultado[i] = s;
    }

    if( a < b){ //Complemento a dos
        resultado.operadorTilde();
        Fp::suma(resultado,1,resultado);

        if(!permitirResultadosNegativos){
            Fp::resta(Fp::primo,resultado,resultado);
        }else{
            resultado.setNegativo(true);
        }
    }
}

void Fp::resta(Fp &a, uInt64 b, Fp &resultado,bool permitirResultadosNegativos){
    int i;
    uInt64 s,c;

    s = a[0] - b;
    c = ( b > a[0]) ? 1 : 0;

    resultado[0] = s;

    for(i = 1; i < 2*k ;i++){
        s = a[i] - c;
        c = ( c  > a[i] ) ? 1 : 0;
        resultado[i] = s;
    }

    if( a < b){ //Complemento a dos
        resultado.operadorTilde();
        Fp::suma(resultado,1,resultado);

        if(!permitirResultadosNegativos){
            Fp::resta(Fp::primo,resultado,resultado);
        }else{
            resultado.setNegativo(true);
        }
    }
}

void Fp::multiplicacionBinariaIzquierdaADerecha(Fp &a, Fp &b, Fp &resultado){
    if(b == 0){
        resultado.limpia();
        return;
    }

    resultado.copia(a);

    for(int i = b.longitudEnBits()-2 ; i >= 0;i--){
        resultado.corrimientoUnBitIzquierda();
        if(b.bitEnPosicion(i) == 1)
            Fp::suma(resultado,a,resultado);
    }

}

bool Fp::operator ==(Fp &b){
    for(int i = 0 ; i < 2*k;i++)
        if((*this)[i] != b[i])
            return false;

    return true;
}

bool Fp::operator ==(uInt64 n){
    if((*this)[0] != n)
        return false;

    for(int i = 1 ; i < 2*k;i++)
        if((*this)[i] != 0)
            return false;

    return true;
}

void Fp::operadorTilde(){
    for(int i = 0 ; i < 2*k;i++)
        (*this)[i] = ~(*this)[i];

}

void Fp::corrimientoUnBitDerecha(){
    int l,i;
    uInt64 acarreoActual,acarreoAnterior;

    l = this->longitudEnPalabras();

    for(i = l-1,acarreoAnterior = 0 ; i >= 0;i--){
        acarreoActual = (*this)[i]&0x1;
        (*this)[i] = ( (*this)[i]>>1) | acarreoAnterior;
        acarreoAnterior = acarreoActual<< 63;
    }
}

void Fp::corrimientoUnBitIzquierda(){
    int l,i;
    uInt64 acarreoActual,acarreoAnterior;

    l = this->longitudEnPalabras();

    for(i = 0,acarreoAnterior = 0 ; i < l ;i++){
        acarreoActual = (*this)[i] >> 63;
        (*this)[i] = ( (*this)[i]<<1) | acarreoAnterior;
        acarreoAnterior = acarreoActual;
    }
}

bool Fp::operator >(Fp &b){
    for(int i = 2*k-1; i>= 0;i--)
        if((*this)[i] < b[i])
            return false;
        else if((*this)[i] > b[i])
            return true;

    return false;
}

bool Fp::operator <(uInt64 b){
    for(int i = this->longitudEnPalabras()-1;i> 0;i--)
        if((*this)[i] != 0)
            return false;

    if((*this)[0] < b)
        return true;
    return false;
}

bool Fp::operator >(uInt64 b){
    if((*this)[0] > b)
        return true;

    for(int i = 1;i < this->longitudEnPalabras()-1;i++)
        if((*this)[i] != 0)
            return true;

    return false;
}

bool Fp::operator <(Fp &b){
    for(int i = 2*k-1; i>= 0;i--)
        if((*this)[i] < b[i])
            return true;
        else if((*this)[i] > b[i])
            return false;

    return false;
}

uInt64 &Fp::operator [](int i){
    return misPalabras[i];
}

int Fp::bitEnPosicion(int i){
    int bits;
    short estaEnPalabra,bitEnPalabra,bit;

    bits = this->longitudEnBits();

    if(i > bits || i < 0)
        return -1;

    estaEnPalabra = i/(sizeof(uInt64)*8);
    bitEnPalabra = i%(sizeof(uInt64)*8);

    bit = ((*this)[estaEnPalabra]>>bitEnPalabra)&0x1;

    return bit;
}
