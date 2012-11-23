#include "fp.h"

Fp Fp::primo;
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

uInt64 &Fp::operator [](int i){
    return misPalabras[i];
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
    (*this)[this->longitudEnPalabras()] = palabra;
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

void Fp::imprimeP(){
    int aux;

    printf("\n");

    for(int i = Fp::k-1;i >= 0;i--){

        aux = Fp::primo[i]>>32;
        printf("%.8x",aux);
        aux = Fp::primo[i];
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
    Fp::k = primoLen;
}

Fp &Fp::operator +(Fp &b){
    Fp* result = new Fp();
    int i,c;
    uInt64 s,aux;

    for(i = 0,c = 0; i < k+1;i++){
        s = (*this)[i] + b[i] + c;
        aux = maximoValorDePalabra - (b[i] + c);
        c = ( (*this)[i] > aux) ? 1 : 0;
        result->insertaFinal(s);
    }

    if(*result > Fp::primo){
        *result = (*result) - primo;
    }else if(*result == Fp::primo){
        result->limpia();
    }

    return *result;
}

Fp &Fp::operator +(uInt64 n){
    Fp* result = new Fp();
    int i,c;
    uInt64 s,aux;

    s = (*this)[0] + n;
    aux = maximoValorDePalabra - n;
    c = ( (*this)[0] > aux) ? 1 : 0;

    result->insertaFinal(s);

    for(i = 1; i < 2*k;i++){
        s = (*this)[i]  + c;
        aux = maximoValorDePalabra - c;
        c = ( (*this)[i] > aux) ? 1 : 0;

        result->insertaFinal(s);
    }

    if(*result > Fp::primo){
        *result = (*result) - Fp::primo;
    }else if(*result == Fp::primo){
        result->limpia();
    }

    return *result;
}

Fp &Fp::operator -(Fp &b){
    Fp* result = new Fp();
    int i,c;
    uInt64 s;

   for(c = 0, i = 0; i < 2*k ;i++){
        s = (*this)[i] - (b[i] + c);
        c = ( (b[i] + c ) > (*this)[i] ) ? 1 : 0;
        result->insertaFinal(s);
    }

    if( b > *this){
        *result = ~(*result)+1;
        *result = Fp::primo - *result;
    }

    return *(result);
}

bool Fp::operator ==(Fp &b){
    for(int i = 0 ; i < 2*k;i++)
        if((*this)[i] != b[i])
            return false;

    return true;
}

Fp &Fp::operator ~(){
    Fp* r = new Fp();
    for(int i = 0 ; i < 2*k;i++)
        (*r)[i] = ~(*this)[i];

    return *r;
}

bool Fp::operator >(Fp &b){
    for(int i = 2*k-1; i>= 0;i--)
        if((*this)[i] < b[i])
            return false;
        else if((*this)[i] > b[i])
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
