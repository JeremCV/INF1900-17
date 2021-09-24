#include <avr/io.h> 
#include <stdio.h>
#define F_CPU 8000000
#include <util/delay.h> 
#include <avr/interrupt.h>

#define ROUGE 0x02
#define ETEINT 0x00
#define ENTREE 0x00
#define SORTIE 0xff


volatile uint8_t gMinuterieExpiree;
volatile uint8_t gBoutonPoussoir;

ISR () {
    gMinuterieExpiree = 1;
}

ISR () {
    gBoutonPoussoir = 1;
    _delay_ms(10);

}

void partirMinuterie ( uint16_t duree ) {

    gMinuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 'modifier ici' ;
    OCR1A = duree;
    TCCR1A = 'modifier ici' ;
    TCCR1B = 'modifier ici' ;
    TCCR1C = 0;
    TIMSK1 = 'modifier ici' ;
}

void initialisation( void ){
    cli()

    DDRD = ENTREE;
    DDRA = SORTIE;

    sei()
}

int main(){
    initialisation()
    do {
        //nothing
    } while ( gMinuterieExpiree == 0 && gBoutonPoussoir == 0 );


// Une interruption s'est produite. Arrêter toute

// forme d'interruption. Une seule réponse suffit.

cli ();

// Verifier la réponse

'modifier ici'
}