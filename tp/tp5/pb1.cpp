#include <stdio.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "memoire_24.cpp"
#include <avr/io.h>

const uint8_t SORTIE     = 0xff;
const uint8_t VERT       = 0x01;
const uint8_t ROUGE      = 0x02;
const uint8_t ETEINTE    = 0x00;
uint8_t donnee[45] = {'*','P','*','O','*','L','*','Y','*','T','*','E','*','C','*','H','*','N','*','I','*','Q','*','U','*','E','*',' ','*','M','*','O','*','N','*','T','*','R','*','E','*','A','*','L','*'};
const double  delaiEcriture = 5.0;


void lumiere_rouge(){
    PORTA = ROUGE;
}

void lumiere_verte(){
    PORTA = VERT;
}

int main(void )
{   
    Memoire24CXXX memoireExt;
    uint16_t addrFin = 0x0000;

    for (int i = 0; i < donnee.size(); i++){
      memoireExt.ecriture(0x0000 + i*4, donnee[i])
      _delay_ms(delaiEcriture);
      addrFin += i*4;
    }
    //memoireExt.ecriture(0x0000, donnee, 45);
    memoireExt.ecriture(addrFin, 0x00);
    _delay_ms(5);
    DDRA = SORTIE;

    uint8_t resultatSortie[46];
    memoireExt.lecture(0x0000, resultatSortie, 46);

    bool pareil = 1;
    for (int i = 0; i < 45; i++){
        if (!(resultatSortie[i] == donnee[i]))
            pareil = 0;
    }

    if (!(resultatSortie[45] == 0x00))
        	pareil = 0;

    if (pareil)
        lumiere_verte();
    else
        lumiere_rouge();
    return 0;
}
