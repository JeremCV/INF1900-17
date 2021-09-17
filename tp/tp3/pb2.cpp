#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h> 

void Delay_us(int n) {
    while (n--) {
        _delay_us(1);
    }
}

int main()
{
    #define TOUTSORTIE 0xff;
    #define SWITCH_COURANT 0x01; //Configuration pour changer le courant du moteur
    #define DIRECTION 0x02; 
    DDRC = TOUTSORTIE; // Tout les ports de C sont en Sortie

    int a = 0;
    int b = 16667;
    int dec = 4167;
    PORTC = 0x01;

    while (a <= 16667)
    {
        for (int i=0; i<4;i++){  
            for (int j=0; j<120;j++){  
                PORTC ^= SWITCH_COURANT;
                Delay_us(a);
                PORTC ^= SWITCH_COURANT;
                Delay_us(b-a);
            }
        }
        a += dec;
    }
    return 0; 
}