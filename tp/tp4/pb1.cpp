#include <avr/io.h> 
#include <stdio.h>
#define F_CPU 8000000
#include <util/delay.h> 
#include <avr/interrupt.h>

#define VERT 0x01
#define ROUGE 0x02
#define ETEINT 0x00
#define ENTREE 0x00
#define SORTIE 0xff

volatile bool g_isOn;
enum class etatRobot { INIT, AMBRE, VERT_1, ROUGE_1, ETEINT_1, VERT_2 };
volatile etatRobot etatPresent = etatRobot::INIT;

bool lire_bouton(){
    if (PIND & 0x04){
        _delay_ms(10);
        if (PIND & 0x04)
            return 1;
    }
    else
        return 0;
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

void lumiere_ambre(){
    while(lire_bouton()){
        PORTA = VERT;
        _delay_ms(20);
        PORTA = ROUGE;
        _delay_ms(20);
    }
}

void initialisation ( void ) 
{
    cli ();
    
    DDRA = SORTIE;
    DDRD = ENTREE;
    etatPresent = etatRobot::INIT;

    EIMSK = (1 << INT1);

    EIMSK |= (1 << INT0) ;
    
    EICRA = (0 << ISC00) | (1 << ISC01);
    EICRA |= (1 << ISC10) | (1 << ISC11);
    
    sei ();
}

ISR (INT1_vect) 
{
    g_isOn = true;
    _delay_ms ( 10 );

    switch(etatPresent)
    {
        case etatRobot::INIT:
            etatPresent = etatRobot::AMBRE;
            break;

        case etatRobot::AMBRE:
            etatPresent = etatRobot::AMBRE;
            break;

        case etatRobot::VERT_1:
            etatPresent = etatRobot::ROUGE_1;
            break;
                
        case etatRobot::ROUGE_1:
            etatPresent = etatRobot::ROUGE_1;
            break;

        case etatRobot::ETEINT_1:
            etatPresent = etatRobot::VERT_2;
            break;
                
        case etatRobot::VERT_2:
            etatPresent = etatRobot::VERT_2;
            break;
    }
    EIFR |= (1 << INTF1) ;
}
ISR (INT0_vect) 
{
    g_isOn = false;
    _delay_ms ( 10 );

    switch(etatPresent)
    {
        case etatRobot::INIT:
            etatPresent = etatRobot::INIT;
            break;

        case etatRobot::AMBRE:
            etatPresent = etatRobot::VERT_1;
            break;

        case etatRobot::VERT_1:
            etatPresent = etatRobot::VERT_1;
            break;
                
        case etatRobot::ROUGE_1:
            etatPresent = etatRobot::ETEINT_1;
            break;

        case etatRobot::ETEINT_1:
            etatPresent = etatRobot::ETEINT_1;
            break;
                
        case etatRobot::VERT_2:
            etatPresent = etatRobot::INIT;
            break;
    }
    EIFR |= (1 << INTF0) ;
}

int main()
{
    initialisation();
    while(true)
    {
        switch(etatPresent)
        {
            case etatRobot::INIT:
                lumiere_rouge();
                break;

            case etatRobot::AMBRE:
                lumiere_ambre();
                break;

            case etatRobot::VERT_1:
                lumiere_verte();
                break;
                
            case etatRobot::ROUGE_1:
                lumiere_rouge();
                break;

            case etatRobot::ETEINT_1:
                lumiere_eteinte();
                break;
                
            case etatRobot::VERT_2:
                lumiere_verte();
                break;
        }  
    }
}