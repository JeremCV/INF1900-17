/*
INF1900 - TP2 - Probleme 1

Nom: Jeremie Cloutier-Vilhuber
Nom: Pablo Sepulveda Solis
Date de modification: 2021-09-15

Description: 
Programme qui allume la couleur rouge d'une DEL pendant 1 seconde
après avoir appuyé et relâché 5 fois le bouton-poussoir. Par la suite, 
on revient au départ pour pouvoir recommencer.

Le + de la DEL libre est connecté au port A2.
Le - de la DEL libre est connecté au port A1.

Table des états:

État present   B   État suivant   Sortie
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
    _delay_ms(1000);
    PORTA = ETEINT;
}

int main(){
    enum etatRobot{ INIT, APPUI_1, APPUI_2, APPUI_3, APPUI_4 };

    etatRobot etatPresent = INIT;
    DDRA = SORTIE;
    DDRD = ENTREE;

    bool appui = 0;     //Variable aidant à vérifier qu'on vérifie seulement 1 fois l'appui

    for(;;){
        while (lire_bouton()){
            if(!appui){
                switch(etatPresent){
                    case INIT:
                        etatPresent = APPUI_1;
                        break;

                    case APPUI_1:
                        etatPresent = APPUI_2;
                        break;

                    case APPUI_2:
                        etatPresent = APPUI_3;
                        break;

                    case APPUI_3:
                        etatPresent = APPUI_4;
                        break;

                    case APPUI_4:
                        lumiere_rouge();
                        etatPresent = INIT;
                        break;
                }
                appui = 1;
            }
            if (!lire_bouton)
                break;
        }
        appui = 0;
    }
}