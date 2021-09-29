#include <avr/io.h> 
#include <stdio.h>
#define F_CPU 8000000
#include <util/delay.h> 
#include <avr/interrupt.h>

const uint8_t ROUGE  0x02
const uint8_t VERT   0x01
const uint8_t ETEINT 0x00
const uint8_t ENTREE 0x00
const uint8_t SORTIE 0xff


//65,536 cycles before overflow

//7812.5 cycles/s with 1024 prescaler

//15625 cycles/s with 512 prescaler

//31250 cycles/s with 256 prescaler

//1 000 000 cycles/s with 8 prescaler


void ajustementPwm ( uint8_t a ) {
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    OCR1A = a;
    OCR1B = a;
    // division d'horloge par 8 - implique une fréquence de PWM fixe
    TCCR1A = (1 << COM1A1) | (1 << COM1A0);
    TCCR1A |= (1 << COM1B1) | (1 << COM1B0);
    TCCR1A |= (0 << WGM11) | (1 << WGM10);
    TCCR1B = (0 << WGM13) | (0 << WGM12);
    TCCR1C = 0;
}

void initialisation( void ){
    cli();

    DDRD = 0X3A;   //Pins 2,3,4,5 en Sortie, 0,1,6,7 en Entrée
    DDRA = SORTIE;

    EIMSK = (1 << INT0);
    EICRA = (1 << ISC00) | (1 << ISC01);

    sei();
}

int main(){
    initialisation();
    ajustementPwm(1*255);
    _delay_ms(2000);
    ajustementPwm(0.75*255);
    _delay_ms(2000);
    ajustementPwm(0.50*255);
    _delay_ms(2000);
    ajustementPwm(0.25*255);
    _delay_ms(2000);
    ajustementPwm(0*255);
}
