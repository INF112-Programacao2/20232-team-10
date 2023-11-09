#ifndef V_PLAYER
#define V_PLAYER

#include "actor.h"

class Player : public Actor {
    private:
        int _num;
        unsigned int _project;
        unsigned int _study;

    public:
        Player(int num, );
        virtual void work_on_project(int x) override;
        virtual void study(int x) override;
};

#endif