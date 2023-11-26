#ifndef PLACE_H
#define PLACE_H
#include <string>
#include <vector>
#include "actor.h"
#include "player.h"

//Locais onde o usuário pode visitar;
class LocalActions {
    private:
        std::string place;

    public:
        static std::vector<LocalActions*> placeActions;   //Vector para armazenar os lugares
        LocalActions(std::string place);         //Construtor
};
#endif