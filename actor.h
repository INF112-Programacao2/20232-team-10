#ifndef V_ACTOR
#define V_ACTOR
#include <string>

const unsigned int SKILL_NUM = 6;   // Número de skills no jogo

const std::string skill_name[SKILL_NUM] = {     // Nomes das skills
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
        std::string name;                   //Nome
        int hp;                             //Quantidade de vida
        int hp_max;                         //Quantidade de vida maxima
        unsigned int skill[6];              //Array para os valores das skills, em ordem
        bool alive;                         //Bool para estado de vida

    public:
        Actor(std::string name);                    //Construtor
        Actor(std::string name, int atributes[6]);
        void heal(int x);                           //Funcao para curar
        void damage(int x);                         //Funcao para causar dano
        void die();                                 //Funcao para morte
        std::string getName();          
        int getSkill(unsigned int s);
        int get_hp();
        virtual void workOnProject(int x) = 0;      //Funcao para trabalhar no projeto
        virtual void study(int x) = 0;              //Funcao para estudar
        //virtual void travelTo(Place *destination);
};

#endif
