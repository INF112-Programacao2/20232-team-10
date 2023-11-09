#ifndef V_PLAYER
#define V_PLAYER

#include "actor.h"

class Player : public Actor {
    private:
        static unsigned int player_count;
        int id;
        unsigned int project_bar;
        unsigned int study_bar;

    public:
        Player(std::string name, int atributes[6]);
        virtual void workOnProject(int x) override;
        virtual void study(int x) override;
};

#endif