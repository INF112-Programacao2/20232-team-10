#ifndef V_ENGINE
#define V_ENGINE

#include <iostream>
#include <vector>

#include "actions.h"
#include "actor.h"
#include "player.h"

class Engine {
 private:
  std::vector<Player*> _players;
  unsigned int _time = 0;

 public:
  void game();                        // A FUNCAO!!
  void render_scene();                // Interface - Desenha na tela
  Action player_turn(Player player);  // Turno do jogador
  void results();                     // Resultado dos turnos
};

#endif