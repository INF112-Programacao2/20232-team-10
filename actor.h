#ifndef V_ACTOR
#define V_ACTOR

#include <TGUI/TGUI.hpp>

const unsigned int SKILL_NUM = 6;   // Número de skills no jogo

const tgui::String skill_name[SKILL_NUM] = {     // Nomes das skills
    "Atletismo",
    "Agilidade",
    "Resistencia",
    "Pensamento",
    "Primeiros Socorros",
    "Carisma"
};

enum skills{   // Enum para o nome das skills
    FITNESS,        // ATLETISMO
    AGILITY,        // AGILIDADE
    ENDURANCE,      // RESISTENCIA
    THINKING,       // PENSAMENTO
    FIRST_AID,      // PRIMEIROS SOCORROS
    CHARISMA,       // CARISMA
};

class Actor {                               //Classe geral para todos os atores do jogo (jogador, vilao, NPC, etc)
    protected:
        tgui::String name;                   //Nome
        int injuries;                       //Quantidade de dano acumulado
        int vitality;                       //Quantidade de dano que
        unsigned int skill[6];              //Array para os valores das skills, em ordem
        bool alive;                         //Bool para estado de vida

    public:
        Actor(tgui::String name);                    //Construtor
        Actor(tgui::String name, int atributes[6]);
        void heal(int x);                           //Funcao para curar
        void damage(int x);                         //Funcao para causar dano
        void die();                                 //Funcao para morte
        tgui::String getName();          
        int getSkill(unsigned int s);
        int getDamageLevel();
        tgui::String getHealth();
        virtual void workOnProject(int x) = 0;      //Funcao para trabalhar no projeto
        virtual void study(int x) = 0;              //Funcao para estudar
        //virtual void travelTo(Place *destination);
};

#endif
