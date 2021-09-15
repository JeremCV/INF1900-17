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
    const int toutSortie = 0xff;
    DDRA = toutSortie; // Tout les ports de A sont en Sortie
    #define VERT 0x01; // Configuration pour la couleur verte
    #define ROUGE 0x02; // Configuration pour la couleur rouge
    #define ETEINT 0x00; //Configuration pour lumiere eteinte

    int a = 1000;
    int b = 1000;
    int dec = 1;

    while (a >= 0)
    {   
        PORTA = VERT;
        Delay_us(a);
        PORTA = ETEINT;
        Delay_us(b-a);
    }
    return 0; 
}