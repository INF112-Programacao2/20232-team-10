#ifndef V_ACTOR
#define V_ACTOR
#include <string>
#include <map>

class Actor {
    protected:
        std::string name;
        int hp;
        int hp_max;
        std::map <std::string, int> skill;

    public:
        Actor(std::string name, int hp_max);
        void heal(int x);
        void damage(int x);
        void die();
        int getSkill(std::string s);
        virtual void workOnProject(int x) = 0;
        virtual void study(int x) = 0;
};

#endif