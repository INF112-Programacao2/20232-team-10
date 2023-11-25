#ifndef V_ACTOR
#define V_ACTOR
#include <string>
#include <map>

class Actor {                               //Classe geral para todos os atores do jogo (jogador, vilao, NPC, etc)
    protected:
        std::string name;                   //Nome
        int hp;                             //Quantidade de vida
        int hp_max;                         //Quantidade de vida maxima
        std::map <std::string, int> skill;  //Map para os nomes da skill e seu respectivo valor
        bool alive;                         //Bool para estado de vida

    public:
        Actor(std::string name);                    //Construtor
        Actor(std::string name, int atributes[6]);
        void heal(int x);                           //Funcao para curar
        void damage(int x);                         //Funcao para causar dano
        void die();                                 //Funcao para morte
        std::string getName();          
        int getSkill(std::string s);
        int get_hp();
        virtual void workOnProject(int x) = 0;      //Funcao para trabalhar no projeto
        virtual void study(int x) = 0;              //Funcao para estudar
        //virtual void travelTo(Place *destination);
};

#endif