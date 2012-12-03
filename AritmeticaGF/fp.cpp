#include "fp.h"

Fp Fp::auxiliar;
Fp Fp::primo;
Fp Fp::mu;
Fp Fp::b;
Fp Fp::q;
Fp Fp::residuo1;
Fp Fp::residuo2;
Fp Fp::r;
Fp Fp::pInv;
Fp Fp::aBarra;
Fp Fp::bBarra;
Fp Fp::cBarra;
Fp Fp::unoBarra;
Fp Fp::R0;
Fp Fp::R1;
int Fp::d = 0;
uInt64 Fp::montgFlag = 0;
int Fp::k = 0;
int Fp::kLim = 0;

Fp::Fp(){
    misPalabras = (uInt64*) malloc(sizeof(uInt64) * kLim );

    for(int i = 0; i < kLim ;i++)
        misPalabras[i] = 0;

    this->esNeg = false;
}

Fp::Fp(std::string numeroEnHex){    
    misPalabras = (uInt64*) malloc(sizeof(uInt64) * kLim );

    this->parseNumber(numeroEnHex);

    this->esNeg = false;
}

void Fp::aleatorizaNumero(){    
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

    for(int i = 0 ; i < kLim;i++)
        (*this)[i] = otroNumero[i];

    this->setNegativo(otroNumero.esNegativo());
}

void Fp::creaYCopia(uInt64 *unVector,int longitud){
    misPalabras = NULL;
    misPalabras = (uInt64*) malloc(sizeof(uInt64) *  longitud * 4  );

    for(int i = 0 ; i < longitud;i++){
        (*this)[i] = unVector[i];
        (*this)[i+longitud] = (*this)[i+2*longitud] = (*this)[i+3*longitud] = 0;
    }
}

void Fp::mapeoMontgomery(Fp &a, Fp &aBarra){
    Fp::multiplicacionClasica(a,Fp::r,aBarra,true);
}

void Fp::productoMontgomery(Fp &aBarra, Fp &bBarra, Fp &cBarra){
    Fp t,m,u;

    Fp::multiplicacionBinariaIzquierdaADerecha(aBarra,bBarra,t,false);
    Fp::multiplicacionClasica(t,Fp::pInv,m,false);

    //Modulo r
    m[r.longitudEnPalabras()-1] = m[r.longitudEnPalabras()-1]&montgFlag;
    for(int i = r.longitudEnPalabras(); i <= kLim;i++)
        m[i] = 0;

    Fp::multiplicacionClasica(m,Fp::primo,u,false);
    Fp::suma(u,t,u,false);

    for(int i = 0 ; i < r.longitudEnBits()-1;i++)
        u.corrimientoUnBitDerecha();

    if(u > primo){
        Fp::resta(u,primo,auxiliar,false);
        u.copia(auxiliar);
    }else if(u == primo){
        u.limpia();
    }

    cBarra.copia(u);
}

std::vector<Fp> &Fp::EuclidesExtendido(Fp a, Fp b){
    std::vector<Fp> *result = new std::vector<Fp>();
    Fp x,y,q;

    if(b == 0){
        x[0] = 1;

        result->push_back(x);
        result->push_back(y);

        return *(result);
    }

    //(X,Y,D)
    *result = EuclidesExtendido(b,a%b);
    q = (a/b).at(0);
    //X' = Y
    x.copia(result->at(1));
    //Y' = X - (a/b)*Y
    Fp::multiplicacionBinariaIzquierdaADerecha(q,result->at(1),R1);

    if(result->at(0).esPositivo() && result->at(1).esNegativo()){
        Fp::suma(result->at(0),R1,y,false);
        y.setNegativo(false);
    }else if(result->at(0).esPositivo() && result->at(1).esPositivo()){
        Fp::resta(result->at(0),R1,y,true);
    }else if(result->at(0).esNegativo() && result->at(1).esPositivo()){
        Fp::suma(result->at(0),R1,y,false);
        y.setNegativo(true);
    }else if(result->at(0).esNegativo() && result->at(1).esNegativo()){
        Fp::resta(R1,result->at(0),y,true);
    }

    result->clear();
    result->push_back(x);
    result->push_back(y);

    return *(result);
}

Fp &Fp::operator %(Fp &b){
    Fp n;
    Fp *r = new Fp();
    int k,i;

    residuo1.copia(*this);
    residuo2.limpia();
    n.copia(b);

    k = 0;

    while(n < residuo1){
        n.corrimientoUnBitIzquierda();
        k++;
    }    

    for(i = 0; i < k+1;i++){
        Fp::resta(residuo1,n,residuo2,true);
        if(residuo2.esNegativo())
            residuo2.copia(residuo1);
        n.corrimientoUnBitDerecha();
        residuo1.copia(residuo2);
    }

    r->copia(residuo2);

    return *r;
}


void Fp::setNegativo(bool negativo){
    this->esNeg = negativo;
}

int Fp::longitudEnPalabras(){
    int i;

    for(i = kLim-1; i >= 0 ;i--)
        if((*this)[i] != 0)
            break;

    return i+1;
}

int Fp::longitudEnBits(){
    int i,palabrasLlenas,bitsEnUltimaPalabra;
    uInt64 aux;

    for(i = kLim-1; i >= 0 ;i--)
        if((*this)[i] != 0)
            break;
    i++;

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

bool Fp::esImpar(){
    return ((*this)[0]&0x1) == 1 ? true : false;
}

void Fp::limpia(){
    for(int i = 0; i < kLim ;i++)
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
    if(final < kLim)
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
        printf("\n");
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

void Fp::calculaMu(){
    Fp::b.limpia();
    Fp::mu.limpia();

    //b es 2 a la 64
    Fp::b[0] = 1;
    for(int j = 0 ; j < 2*k;j++){
        for(int i = kLim-1 ; i > 0;i--)
            Fp::b[i] = Fp::b[i-1];
        Fp::b[0] = 0;
    }

    R1.copia(Fp::primo);

    mu = (b/R1).at(0);

    Fp::b.limpia();
    Fp::b[0] = 1;
    for(int j = 0 ; j < k+1;j++){
        for(int i = kLim-1 ; i > 0;i--)
            Fp::b[i] = Fp::b[i-1];
        Fp::b[0] = 0;
    }
}

void Fp::inicializacionMontgomery(){
    Fp::r.limpia();

    Fp::r[0] = 1;

    while(r < primo)
        r.corrimientoUnBitIzquierda();

    pInv.copia(r.EuclidesExtendido(r,primo).at(1));

    if(pInv.esPositivo()){//-p^-1 mod r
        Fp::resta(r,pInv,auxiliar,false);
        pInv.copia(auxiliar);
    }

    pInv.setNegativo(false);

    montgFlag = r[r.longitudEnPalabras()-1];
    montgFlag = ~(~montgFlag+ 1);

}

std::vector<Fp> &Fp::operator /(Fp &b){
    std::vector<Fp> *QR= new std::vector<Fp>();
    Fp q,r;

    if(*this == 0){
        QR->push_back(q);
        QR->push_back(r);
        return *(QR);
    }
    *QR = this->corrimientoUnBitDerechaConCopia()/b;

    q = QR->at(0);
    r = QR->at(1);
    q.corrimientoUnBitIzquierda();
    r.corrimientoUnBitIzquierda();


    if(this->esImpar()){
        Fp::suma(r,1,r,false);
    }

    if( r > b || r == b){
        Fp::resta(r,b,auxiliar);
        r.copia(auxiliar);
        Fp::suma(q,1,q,false);
    }

    QR->clear();
    QR->push_back(q);
    QR->push_back(r);

    return *(QR);
}

void Fp::setP(std::string &primoCadena,int ventanaFijaTam){
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
    Fp::k = primoLen;
    Fp::kLim = 4*k;
    Fp::d = ventanaFijaTam;

    /*Inicializacion de los objetos*/
    Fp::primo.creaYCopia(palabras,k);
    Fp::R0.creaYCopia(palabras,k);
    Fp::R1.creaYCopia(palabras,k);
    Fp::auxiliar.creaYCopia(palabras,k);

    /*Inicializacion para Barret*/
    Fp::b.creaYCopia(palabras,k);
    Fp::q.creaYCopia(palabras,k);
    Fp::residuo1.creaYCopia(palabras,k);
    Fp::residuo2.creaYCopia(palabras,k);
    Fp::mu.creaYCopia(palabras,k);
    calculaMu();

    /*Inicializacion para Montgomery*/
    Fp::r.creaYCopia(palabras,k);
    Fp::aBarra.creaYCopia(palabras,k);
    Fp::bBarra.creaYCopia(palabras,k);
    Fp::cBarra.creaYCopia(palabras,k);
    Fp::unoBarra.creaYCopia(palabras,k);
    unoBarra[0] = 1;
    inicializacionMontgomery();

    /*Inicializacion de la semilla aleatoria*/
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
}

Fp &Fp::getP(){
    return Fp::primo;
}

void Fp::suma(Fp &a, Fp &b, Fp &resultado,bool reducirAlFinalizar ){
    int i,c;
    uInt64 s,aux;

    for(i = 0,c = 0; i < kLim;i++){
        s = a[i] + b[i] + c;
        aux = maximoValorDePalabra - (b[i] + c);
        c = ( a[i] > aux) ? 1 : 0;
        resultado[i] = s;
    }

    if(resultado > Fp::primo && reducirAlFinalizar){
        Fp::resta(resultado,Fp::primo,R0);
        resultado.copia(R0);
    }else if(resultado == Fp::primo && reducirAlFinalizar){
        resultado.limpia();
    }
}

void Fp::suma(Fp &a, uInt64 b, Fp &resultado,bool reducirAlFinalizar ){
    int i,c;
    uInt64 s,aux;

    s = a[0] + b;
    aux = maximoValorDePalabra - b;
    c = ( a[0] > aux) ? 1 : 0;

    resultado[0] = s;

    for(i = 1; i < kLim;i++){
        s = a[i]  + c;
        aux = maximoValorDePalabra - c;
        c = ( a[i] > aux) ? 1 : 0;

        resultado[i] = s;
    }

    if(resultado > Fp::primo && reducirAlFinalizar){
        Fp::resta(resultado,Fp::primo,R0);
        resultado.copia(R0);
    }else if(resultado == Fp::primo && reducirAlFinalizar){
        resultado.limpia();
    }
}

void Fp::resta(Fp &a, Fp &b, Fp &resultado,bool permitirResultadosNegativos ){
    int i,c;
    uInt64 s;

    for(c = 0, i = 0; i < kLim ;i++){
        s = a[i] - (b[i] + c);
        c = ( (b[i] + c ) > a[i] ) ? 1 : 0;
        resultado[i] = s;
    }

    if( a < b){ //Complemento a dos
        resultado.operadorTilde();
        Fp::suma(resultado,1,resultado);

        if(!permitirResultadosNegativos){
            Fp::resta(Fp::primo,resultado,R0);
            resultado.copia(R0);
        }else{
            resultado.setNegativo(true);
        }
    }else
        resultado.setNegativo(false);

}

void Fp::resta(Fp &a, uInt64 b, Fp &resultado,bool permitirResultadosNegativos){
    int i;
    uInt64 s,c;

    s = a[0] - b;
    c = ( b > a[0]) ? 1 : 0;

    resultado[0] = s;

    for(i = 1; i < kLim ;i++){
        s = a[i] - c;
        c = ( c  > a[i] ) ? 1 : 0;
        resultado[i] = s;
    }

    if( a < b){ //Complemento a dos
        resultado.operadorTilde();
        Fp::suma(resultado,1,resultado);

        if(!permitirResultadosNegativos){
            Fp::resta(Fp::primo,resultado,R0);
            resultado.copia(R0);
        }else{
            resultado.setNegativo(true);
        }
    }else
        resultado.setNegativo(false);
}

void Fp::multiplicacionBinariaIzquierdaADerecha(Fp &a, Fp &b, Fp &resultado, bool reducirAlFinalizar){
    if(b == 0 || a == 0){
        resultado.limpia();
        return;
    }

    resultado.copia(a);
    for(int i = b.longitudEnBits()-2 ; i >= 0;i--){
        resultado.corrimientoUnBitIzquierda();
        if(b.bitEnPosicion(i) == 1){
            Fp::suma(resultado,a,resultado,false);
        }
    }
    if(reducirAlFinalizar)
        Fp::reduccionBarret(resultado);
}

void Fp::multiplicacionClasica(Fp &a, Fp &b, Fp &resultado, bool reducirAlFinalizar){
    int i,j;
    uInt64 s,c;
    uint128_t h;

    resultado.limpia();

    for(i = 0 ; i < kLim/2;i++){
        for(c = 0,j = 0 ; j < kLim/2;j++){
            MUL64(h,s,c,a[j],b[i],resultado[i+j],c)
            resultado[i+j] = s;
        }
        resultado[i+j] = c;
    }

    if(reducirAlFinalizar)
        Fp::reduccionBarret(resultado);
}

void Fp::multiplicacionMontgomery(Fp &a, Fp &b, Fp &resultado){

    Fp::mapeoMontgomery(a,aBarra);
    Fp::mapeoMontgomery(b,bBarra);

    Fp::multiplicacionMontgomery(aBarra,bBarra,cBarra);

    Fp::multiplicacionMontgomery(cBarra,unoBarra,resultado);
}

void Fp::reduccionConRestauracion(Fp &t){
    int kPrima = 0;
    R0.copia(t);

    while(primo < R0){
        primo.corrimientoUnBitIzquierda();
        kPrima++;
    }

    for(int i = 0 ; i < kPrima +1;i++){
        Fp::resta(R0,primo,R1,true);
        if(R1.esNegativo())
            R1.copia(R0);
        if(i != kPrima-1)
            primo.corrimientoUnBitDerecha();
        R0.copia(R1);
    }

    t.copia(R0);
}

void Fp::reduccionSinRestauracion(Fp &t){
    int kPrima = 0;
    R0.copia(t);

    while(primo < R0){
        primo.corrimientoUnBitIzquierda();
        kPrima++;
    }    

    for(int i = 0 ; i < kPrima + 1;i++){
        if(R0.esNegativo())
            Fp::resta(primo,R0,R1,true);
        else
            Fp::resta(R0,primo,R1,true);

        if(i != kPrima-1)
            primo.corrimientoUnBitDerecha();
        R0.copia(R1);
    }

    if(R0.esNegativo()){
        Fp::resta(primo,R0,R1,true);
        R0.copia(R1);
    }

    t.copia(R0);
}

void Fp::reduccionBarret(Fp &t){
    R1.copia(t);
    /*x/b^(k-1)*/
    for(int i = 0 ; i < k-1;i++){
        for(int j = 1 ; j < kLim-1;j++)
            R1[j-1] = R1[j];
        R1[kLim-1] = 0;
    }

    /*(x/b^(k-1))*mu*/
    Fp::multiplicacionClasica(R1,mu,q);

    /*(x/b^(k-1))*mu*(1/b^(k+1))*/
    for(int i = 0 ; i < k+1;i++){
        for(int j = 1 ; j < kLim-1;j++)
            q[j-1] = q[j];
        q[kLim-1] = 0;
    }
    residuo1.copia(t);

    /*r1 = x mod b^(k+1)*/
    for(int i = k+1;i < kLim;i++)
        residuo1[i] = 0;

    residuo2.limpia();
    /*r2 = q*p mod b^(k+1)*/
    Fp::multiplicacionClasica(primo,q,residuo2);

    for(int i = k+1;i < kLim;i++)
        residuo2[i] = 0;

    Fp::resta(residuo1,residuo2,t,true);

    if(t.esNegativo()){
        /*Al finalizar el calculo de mu, deje a b como b^k+1*/
        Fp::suma(b,t,t,false);
    }

    while(t > primo){
        Fp::resta(t,primo,R1);
        t.copia(R1);
    }
}

bool Fp::operator ==(Fp &b){
    for(int i = 0 ; i < kLim;i++)
        if((*this)[i] != b[i])
            return false;

    return true;
}

bool Fp::operator ==(uInt64 n){
    if((*this)[0] != n)
        return false;

    for(int i = 1 ; i < kLim;i++)
        if((*this)[i] != 0)
            return false;

    return true;
}

Fp &Fp::corrimientoUnBitDerechaConCopia(){
    Fp* corrido = new Fp();
    int i;

    uInt64 acarreoActual,acarreoAnterior;
    for(i = kLim-1,acarreoAnterior = 0 ; i >= 0;i--){
        acarreoActual = (*this)[i]&0x1;
        (*corrido)[i] = ( (*this)[i]>>1) | acarreoAnterior;
        acarreoAnterior = acarreoActual<< 63;
    }

    return *corrido;
}

void Fp::operadorTilde(){
    for(int i = 0 ; i < kLim;i++)
        (*this)[i] = ~(*this)[i];

}

void Fp::corrimientoUnBitDerecha(){
    int i;
    uInt64 acarreoActual,acarreoAnterior;

    for(i = kLim-1,acarreoAnterior = 0 ; i >= 0;i--){
        acarreoActual = (*this)[i]&0x1;
        (*this)[i] = ( (*this)[i]>>1) | acarreoAnterior;
        acarreoAnterior = acarreoActual<< 63;
    }
}

void Fp::corrimientoUnBitIzquierda(){
    int i;
    uInt64 acarreoActual,acarreoAnterior;

    for(i = 0,acarreoAnterior = 0 ; i < kLim ;i++){
        acarreoActual = (*this)[i] >> 63;
        (*this)[i] = ( (*this)[i]<<1) | acarreoAnterior;
        acarreoAnterior = acarreoActual;
    }
}

bool Fp::operator >(Fp &b){
    for(int i = kLim-1; i>= 0;i--)
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
    for(int i = kLim-1; i>= 0;i--)
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

void Fp::exponenciacionBinariaIzquierdaADerecha(Fp &b, Fp &e, Fp &resultado){
    if(e == 0){
        resultado.limpia();
        resultado[1] = 1;
        return;
    }

    resultado.copia(b);

    for(int i = e.longitudEnBits()-2 ; i >= 0;i--){
        Fp::multiplicacionClasica(resultado,resultado,auxiliar,true);
        resultado.copia(auxiliar);
        if(e.bitEnPosicion(i) == 1){
            Fp::multiplicacionClasica(resultado,b,auxiliar,true);
            resultado.copia(auxiliar);
        }
    }
}

void Fp::exponenciacionBinariaDerechaAIzquierda(Fp &b, Fp &e, Fp &resultado){
    resultado.limpia();
    resultado[1] = 1;

    for(int i = 0 ; i < e.longitudEnBits() ;i++){
        if(e.bitEnPosicion(i) == 1){
            Fp::multiplicacionClasica(resultado,b,auxiliar,true);
            resultado.copia(auxiliar);
        }
        Fp::multiplicacionClasica(b,b,auxiliar,true);
        b.copia(auxiliar);
    }

}

void Fp::exponenciacionBinariaSideChannels(Fp &b, Fp &e, Fp &resultado){
    Fp c[2];

    c[0][0] = 1;

    for(int i = e.longitudEnBits()- 1 ; i >= 0;i--){
        Fp::multiplicacionClasica(c[0],c[0],auxiliar,true);
        c[0].copia(auxiliar);
        Fp::multiplicacionClasica(c[0],b,c[1],true);
        c[0].copia(c[e.bitEnPosicion(i)]);
    }

    resultado.copia(c[0]);
}



