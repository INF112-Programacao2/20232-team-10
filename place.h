#ifndef PLACE_H
#define PLACE_H
#include <string>
#include <vector>
#include "actor.h"
#include "player.h"
#include "actions.h"

//Locais onde o usuário pode visitar;
class Place {
    private:
        tgui::String place;

    public:
         std::vector<int> placeActions;   //Vector para armazenar os lugares
         Place(tgui::String place);         //Construtor
};
#endif