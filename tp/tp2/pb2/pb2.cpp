/*
INF1900 - TP2 - Probleme 2

Nom: Jeremie Cloutier-Vilhuber
Nom: Pablo Sepulveda Solis
Date de modification: 2021-09-15

Description: 
Programme qui allume la couleur rouge d'une DEL quand la carte 
mère démarre. Si le bouton-poussoir noir est pesé, la DEL affiche 
la couleur ambre. Quand le bouton-poussoir est relâché, la DEL 
devient verte. Si le bouton est de nouveau pesé, la DEL prend la 
couleur rouge encore. Quand il est relâché, la DEL s'éteint. Si 
le bouton est de nouveau pesé, la DEL affiche la couleur verte. 
Quand il est relâché, la DEL tourne au rouge ce qui fait que la 
carte mère est de retour à son état initial et tout peut recommencer.

Le + de la DEL libre est connecté au port A2.
Le - de la DEL libre est connecté au port A1.

Table des etats:

Etat present   B   Etat suivant   Sortie
    INIT       0       INIT       rouge
    INIT       1       AMBRE      ambre
    AMBRE      0       VERT_1     vert
    AMBRE      1       AMBRE      ambre
    VERT_1     0       VERT_1     vert
    VERT_1     1       ROUGE      rouge
    ROUGE      0       ETEINT       0
    ROUGE      1       ROUGE      rouge
    ETEINT     0       ETEINT       0
    ETEINT     1       VERT_2     vert
    VERT_2     0        INIT      rouge
    VERT_2     1       VERT_2     vert

*/

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h> 

#define VERT 0x01
#define ROUGE 0x02
#define ETEINT 0x00
#define ENTREE 0x00
#define SORTIE 0xff


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

int main(){
    enum class etatRobot { INIT, AMBRE, VERT_1, ROUGE_1, ETEINT_1, VERT_2 };

    etatRobot etatPresent = etatRobot::INIT;
    DDRA = SORTIE;
    DDRD = ENTREE;

    lumiere_rouge();

    for(;;){
        if (lire_bouton()){

            switch(etatPresent)
            {
                case etatRobot::INIT:
                    etatPresent = etatRobot::AMBRE;
                    lumiere_ambre();
                    break;

                case etatRobot::AMBRE:
                    etatPresent = etatRobot::AMBRE;
                    break;

                case etatRobot::VERT_1:
                    etatPresent = etatRobot::ROUGE_1;
                    lumiere_rouge();
                    break;
                
                case etatRobot::ROUGE_1:
                    etatPresent = etatRobot::ROUGE_1;
                    break;

                case etatRobot::ETEINT_1:
                    etatPresent = etatRobot::VERT_2;
                    lumiere_verte();
                    break;
                
                case etatRobot::VERT_2:
                    etatPresent = etatRobot::VERT_2;
                    break;
            }
        }

        if (!lire_bouton()){

            switch(etatPresent)
            {
                case etatRobot::INIT:
                    etatPresent = etatRobot::INIT;
                    break;

                case etatRobot::AMBRE:
                    etatPresent = etatRobot::VERT_1;
                    lumiere_verte();
                    break;

                case etatRobot::VERT_1:
                    etatPresent = etatRobot::VERT_1;
                    break;
                
                case etatRobot::ROUGE_1:
                    etatPresent = etatRobot::ETEINT_1;
                    lumiere_eteinte();
                    break;

                case etatRobot::ETEINT_1:
                    etatPresent = etatRobot::ETEINT_1;
                    break;
                
                case etatRobot::VERT_2:
                    etatPresent = etatRobot::INIT;
                    lumiere_rouge();
                    break;
            }
        }
    }
}