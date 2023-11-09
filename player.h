#ifndef V_PLAYER
#define V_PLAYER

#include "actor.h"

class Player : public Actor {
    private:
        int id;
        unsigned int project_bar;
        unsigned int study_bar;

    public:
        Player(int id);
        virtual void workOnProject(int x) override;
        virtual void study(int x) override;
};

#endif