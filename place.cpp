 #include "place.h"
#include <iostream>

//Declaração do Vector LocalActions 
static std::vector< Action*> placeActions; 
//Inicialização do construtor
Place:: Place(std::string place):place(place){}

//Objetos "Place" disponíveis no jogo
Place Bbt;
Place Cce;
Place Rita;
Place Pvb;
Place Pva;