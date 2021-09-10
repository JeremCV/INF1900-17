/*
INF1900 - TP2 - Probleme 1

Nom: Jeremie Cloutier-Vilhuber
Nom: Pablo Sepulveda Solis
Date de modification: 2021-09-08

Table des etats:

Etat present   B   Etat suivant   Sortie
    INIT       0       INIT         0
    INIT       1      APPUI 1       0
   APPUI 1     0      APPUI 1       0
   APPUI 1     1      APPUI 2       0
   APPUI 2     0      APPUI 2       0
   APPUI 2     1      APPUI 3       0
   APPUI 3     0      APPUI 3       0
   APPUI 3     1      APPUI 4       0
   APPUI 4     0      APPUI 4       0
   APPUI 4     1       INIT         2

*/

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h> 

#define ROUGE 0x02
#define ETEINT 0x00
#define SORTIE 0xff
#define ENTREE 0x00


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
    _delay_ms(1000);
    PORTA = ETEINT;
}

int main(){
    enum robotState{ INIT, APPUI_1, APPUI_2, APPUI_3, APPUI_4 };

    robotState currentState = INIT;
    DDRA = SORTIE;
    DDRD = ENTREE;

    bool appui = 0;     //Variable aidant à vérifier qu'on vérifie seulement 1 fois l'appui

    for(;;){
        while (read_button()){
            if(!appui){
                switch(currentState)
                {
                    case INIT:
                        currentState = APPUI_1;
                        break;

                    case APPUI_1:
                        currentState = APPUI_2;
                        break;

                    case APPUI_2:
                        currentState = APPUI_3;
                        break;

                    case APPUI_3:
                        currentState = APPUI_4;
                        break;

                    case APPUI_4:
                        red_light();
                        currentState = INIT;
                        break;
                }
                appui = 1;
            }
            if (!read_button)
                break;
        }
        appui = 0;
    }
}