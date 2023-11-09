#include "engine.h"

void Engine::playerTurn(Player *player) {
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
            int target;
            std::cout << "Qual coleguinha?\n";
            std::cin >> target;

            action = new DamageAction(player, this->players[target]);
            break;
        case 3:
            action = new StudyAction(player);
        case 4:
            int target;
            std::cin >> target;

            action = new HealAction(player, this->players[target]);
        default:
            break;
    }
    this->turn_actions.push_back(action);
}

void Engine::results() {
    for(int i=0; i<turn_actions.size(); i++) {
        turn_actions[i]->execute();
        delete turn_actions[i];
    }
}