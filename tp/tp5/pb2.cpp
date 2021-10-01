#include <stdio.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premiers registres pour vous éviter des complications.

UBRR0H = 0;

UBRR0L = 0xCF;

// permettre la réception et la transmission par le UART0

UCSR0A = 'modifier ici' ;

UCSR0B = 'modifier ici' ;

// Format des trames: 8 bits, 1 stop bits, sans parité

UCSR0C = 'modifier ici' ;

}

// Du USART vers le PC

void transmissionUART ( uint8_t donnee ) {

'modifier ici'

}

int main(){
    char mots[21] = "Le robot en INF1900\n";

uint8_t i, j;

for ( i = 0; i < 100; i++ ) {

for ( j=0; j < 20; j++ ) {

transmissionUART ( mots[j] );

}

}
}