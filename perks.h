#ifndef PERKS_H
#define PERKS_H
#include <string>
#include <vector>
#include "actions.h"

//Classe destinada ao gerenciamento das perks
class Perk{
    protected:
        Actor *actor;
        tgui::String name;
        tgui::String description;
        int id;
    public:
        Perk(Actor *actor);
        tgui::String getName();
        tgui::String getDescription();
        int get_id();
        virtual void onAdd() = 0;
};

class ToughPerk : public Perk{
    ToughPerk(Actor *actor);
    virtual void onAdd() override;
};
#endif