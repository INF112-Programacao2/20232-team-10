#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>
#include "engine.h"


void Engine::game() {


}

void Engine::render_scene() {
  sf::RenderWindow window{{800, 600}, "CCPânico"}; //Cria tela de jogo
  tgui::Gui gui{window};
  gui.mainLoop();
}
Action Engine::player_turn(Player player) {
  Action *action;
  std::cout << "O que voce faz?\n";
  std::cout << "1- Trabalho no meu projeto\n";
  std::cout << "2- Tento assassinar meu coleguinha\n";
  int action_num;
  std::cin >> action_num;

  switch (action_num) {
    case 1:
      action = new WorkOnProjectAction(player) break;

    case 2:
      int coleguinha;
      std::cout << "Qual coleguinha?\n";
      cin >> coleguinha;
      action = DamageAction(player, coleguinha) break;
    default:
      break;
  }
}