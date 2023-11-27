#include"engine.h"

int main(){
    Engine engine;
    Action::instantiate_actions();
    for (int i = 0; i < 3; i++){
        engine.character_creator_screen();
    }
    engine.game();
}