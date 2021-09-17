#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h> 

#define TOUTSORTIE 0xff;
#define SWITCH_COURANT 0x01; //Configuration pour changer le courant du moteur
#define DIRECTION 0x02; 

int main()
{
    DDRC = TOUTSORTIE; // Tout les ports de C sont en Sortie
    PORTC = SWITCH_COURANT;
    
    return 0; 
}