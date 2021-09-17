#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h> 

#define VERT 0x01; // Configuration pour la couleur verte
#define ROUGE 0x02; // Configuration pour la couleur rouge
#define ETEINT 0x00; //Configuration pour lumiere eteinte

void Delay_us(int n) {
    while (n--) {
        _delay_us(5);
    }
}

int main()
{
    const int toutSortie = 0xff;
    DDRA = toutSortie; // Tout les ports de A sont en Sortie

    int a = 1000;
    int b = 1000;
    int dec = 10;

    while (a >= 0)
    {   
        for (int i=0; i<5;i++){  
            PORTA = ROUGE;
            Delay_us(a);
            PORTA = ETEINT;
            Delay_us(b-a);
        }
            a -= dec;
    }
    return 0; 
}