#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h> 

#define TOUTSORTIE 0xff;
#define DIRECTION 0x02; 
#define COURANT_ALLUMER 0x01;
#define COURANT_ETEINT 0x00;

void Delay_us(int n) {
    while (n--) {
        _delay_us(1);
    }
}

void moteur_roule(int a, int b, int dec, int repetitions)
{
    while (a <= b)
    {
        for (int j=0; j<repetitions;j++){  
            PORTC = COURANT_ALLUMER;
            Delay_us(a);
            PORTC = COURANT_ETEINT;
            Delay_us(b-a);
        }
        a += dec;
    }
}
int main()
{
    DDRC = TOUTSORTIE; // Tout les ports de C sont en Sortie
    PORTC = 0x01;

    int a = 0;
    int b = 16667;
    int dec = 4166;
    moteur_roule(a, b, dec, 65);

    a = 0;
    b = 2500;
    dec = 500;
    moteur_roule(a, b, dec, 350);
    
    return 0; 
}