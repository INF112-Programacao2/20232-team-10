#ifndef PLACE_H
#define PLACE_H
#include <string>
#include <vector>
#include "actor.h"
#include "player.h"


//Locais onde o usuário pode visitar;
class Place {
    private:
        std::string place;

    public:
         std::vector<Action*> placeActions;   //Vector para armazenar os lugares
         Place(std::string place);         //Construtor
};
#endif