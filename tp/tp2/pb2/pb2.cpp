/*
INF1900 - TP2 - Probleme 2

Nom: Jeremie Cloutier-Vilhuber
Nom: Pablo Sepulveda Solis
Date de modification: 2021-09-10

Description: 
Programme qui allume la couleur rouge d'une DEL quand la carte 
mère démarre. Si le bouton-poussoir noir est pesé, la DEL affiche 
la couleur ambre. Quand le bouton-poussoir est relâché, la DEL 
devient verte. Si le bouton est de nouveau pesé, la DEL prend la 
couleur rouge encore. Quand il est relâché, la DEL s'éteint. Si 
le bouton est de nouveau pesé, la DEL affiche la couleur verte. 
Quand il est relâché, la DEL tourne au rouge ce qui fait que la 
carte mère est de retour à son état initial et tout peut recommencer.

Table des etats:

Etat present   B   Etat suivant   Sortie
    INIT       0       INIT       rouge
    INIT       1       AMBER      ambre
    AMBER      0      GREEN_1     vert
    AMBER      1       AMBER      ambre
   GREEN_1     0      GREEN_1     vert
   GREEN_1     1        RED       rouge
     RED       0        OFF         0
     RED       1        RED       rouge
     OFF       0        OFF         0
     OFF       1      GREEN_2     vert
   GREEN_2     0        INIT      rouge
   GREEN_2     1      GREEN_2     vert

*/

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h> 

#define VERT 0x01
#define ROUGE 0x02
#define ETEINT 0x00
#define ENTREE 0x00
#define SORTIE 0xff


bool read_button(){
    if (PIND & 0x04){
        _delay_ms(10);
        if (PIND & 0x04)
            return 1;
    }
    else
        return 0;
}

void red_light(){
    PORTA = ROUGE;
}

void green_light(){
    PORTA = VERT;
}

void lights_off(){
    PORTA = ETEINT;
}

void amber_light(){
    while(read_button()){
        PORTA = VERT;
        _delay_ms(20);
        PORTA = ROUGE;
        _delay_ms(20);
        }
}

int main(){
    enum class robotState { INIT, AMBER, GREEN_1, RED, OFF, GREEN_2 };

    robotState currentState = robotState::INIT;
    DDRA = SORTIE;
    DDRD = ENTREE;

    red_light();

    for(;;){
        if (read_button()){

            switch(currentState)
            {
                case robotState::INIT:
                    currentState = robotState::AMBER;
                    amber_light();
                    break;

                case robotState::AMBER:
                    currentState = robotState::AMBER;
                    break;

                case robotState::GREEN_1:
                    currentState = robotState::RED;
                    red_light();
                    break;
                
                case robotState::RED:
                    currentState = robotState::RED;
                    break;

                case robotState::OFF:
                    currentState = robotState::GREEN_2;
                    green_light();
                    break;
                
                case robotState::GREEN_2:
                    currentState = robotState::GREEN_2;
                    break;
            }
        }

        if (!read_button()){

            switch(currentState)
            {
                case robotState::INIT:
                    currentState = robotState::INIT;
                    break;

                case robotState::AMBER:
                    currentState = robotState::GREEN_1;
                    green_light();
                    break;

                case robotState::GREEN_1:
                    currentState = robotState::GREEN_1;
                    break;
                
                case robotState::RED:
                    currentState = robotState::OFF;
                    lights_off();
                    break;

                case robotState::OFF:
                    currentState = robotState::OFF;
                    break;
                
                case robotState::GREEN_2:
                    currentState = robotState::INIT;
                    red_light();
                    break;
            }
        }
    }
}