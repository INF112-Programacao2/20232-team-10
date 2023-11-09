#include "engine.h"

void Engine::player_turn(Player *player) {
    Action *action;
    std::cout << "O que voce faz?\n";
    std::cout << "1- Trabalho no meu projeto\n";
    std::cout << "2- Tento assassinar meu coleguinha\n";
    int action_num;
    std::cin >> action_num;

    switch (action_num) {
        case 1:
            action = new WorkOnProjectAction(player);
            break;

        case 2:
            int coleguinha;
            std::cout << "Qual coleguinha?\n";
            std::cin >> coleguinha;

            action = new DamageAction(player, _players[coleguinha]);
            break;
        default:
            break;
    }
}