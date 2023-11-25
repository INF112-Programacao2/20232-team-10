#include"engine.h"

int main(){
    Engine engine;
    Action::instantiate_actions();
    int atributes[6] = {1, 1, 1, 7, 1, 1};
    engine.createPlayer("Pedro", atributes);
    atributes[0] = 12;
    atributes[1] = 12;
    atributes[2] = 12;
    atributes[3] = 12;
    atributes[4] = 12;
    atributes[5] = 12;
    engine.createPlayer("Marianna", atributes);
    engine.game();
}