 #include "place.h"
#include <iostream>

//Declaração do Vector LocalActions 
static std::vector<LocalActions*> placeActions; 
//Inicialização do construtor
LocalActions:: LocalActions(std::string place):place(place){}