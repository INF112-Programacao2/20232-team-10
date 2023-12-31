#ifndef V_PLAYER
#define V_PLAYER

#include "actor.h"

class Player : public Actor {               //Classe para jogadores (ou seja, que participam dos turnos)
    private:
        int id;                             //Numero para identificar o jogador
        unsigned int project_bar;           //Barra de progresso para o projeto
        unsigned int study_bar;             //Barra de progresso para estudo

    public:
        static unsigned int player_count;   //Quantidade de jogadores
        Player(tgui::String name, int atributes[6]);     //Construtor
        virtual void workOnProject(int x) override;     //Funcao para trabalhar no projeto
        virtual void study(int x) override;             //Funcao para estudar
        int get_id();
        unsigned int getProjectBar();
        unsigned int getStudyBar();
};

#endif