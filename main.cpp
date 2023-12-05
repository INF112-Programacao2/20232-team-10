#include"engine.h"

int main(){
    Engine engine;
    for (int i = 0; i < 3; i++){
        engine.character_creator_screen();
    }
    engine.game();
}