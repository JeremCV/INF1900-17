#include <avr/io.h> 
#include <stdio.h>
#define F_CPU 8000000
#include <util/delay.h>

const uint8_t ENTREE = 0x00;
const uint8_t SORTIE = 0xff;