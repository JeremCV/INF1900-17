#include <avr/io.h> 
#include <stdio.h>
#define F_CPU 8000000
#include <util/delay.h> 
#include <avr/interrupt.h>

#define ROUGE  0x02
#define VERT   0x01
#define ETEINT 0x00
#define ENTREE 0x00
#define SORTIE 0xff

volatile uint8_t gMinuterieExpiree;
volatile uint8_t gBoutonPoussoir;

//65,536 cycles before overflow

//7812.5 cycles/s with 1024 prescaler

//15625 cycles/s with 512 prescaler

//31250 cycles/s with 256 prescaler

ISR (TIMER1_COMPA_vect) {
    gMinuterieExpiree = 1;
}

ISR (INT0_vect) {
    gBoutonPoussoir = 1;
    _delay_ms(10);
}

void lumiere_rouge(){
    PORTA = ROUGE;
}

void lumiere_verte(){
    PORTA = VERT;
}

void lumiere_eteinte(){
    PORTA = ETEINT;
}

void partirMinuterie ( uint16_t duree ) {

    gMinuterieExpiree = 0;
    TCNT1 = 0 ;
    OCR1A = duree;
    TCCR1A = (1 << COM1A1) | (1 << COM1A0);
    TCCR1B = (1 << CS12) | (0 << CS11) | (0 << CS10); //prescaler à 256
    TCCR1C = 0;
    TIMSK1 = (1 << TOIE1) | (1 << OCIE1A) | (1 << OCIE1B) ;
}

void initialisation( void ){
    cli();

    DDRD = 0Xf0;
    DDRA = SORTIE;

    EIMSK = (1 << INT0) ;
    EICRA = (1 << ISC00) | (1 << ISC01);

    sei();
}

int main(){
    initialisation();

    _delay_ms(10000);
    lumiere_rouge();
    _delay_ms(100);
    lumiere_eteinte();
    partirMinuterie(31250);
    do {
        //nothing
    } while ( gMinuterieExpiree == 0 && gBoutonPoussoir == 0 );

    cli ();
 
    if(gMinuterieExpiree)
        lumiere_rouge();
    else if (!gMinuterieExpiree)
        lumiere_verte();
}
