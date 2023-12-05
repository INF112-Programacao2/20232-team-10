#include <string>
#include <vector>
#include "perks.h"
#include "actor.h"
#include "player.h"
#include "actions.h"

//Construtor

Perk::Perk(Actor *actor):
    actor(actor), name("PERK_BASE"), description("NÃO DEVERIA APARECER"),id(-1){};

//Funções getter's
tgui::String Perk::getName(){
    return this->name;
}
tgui::String Perk::getDescription(){
    return this->description;
}
int Perk:: get_id(){
    return this->id;
}

ToughPerk::ToughPerk(Actor *actor) : Perk(actor){
    name = "Resistente";
    description = "Seja mais resistente a dano";
};

void ToughPerk::onAdd(){
    actor->study(10); // Placeholder
}