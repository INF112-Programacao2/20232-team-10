# 20232-team-10
20232-team-10

Para instalação da biblioteca utilizada para a interface do jogo (SFML-TGUI), segue o link para uma guia de instalação:
https://tgui.eu/tutorials/latest-stable/

Na execucao do makefile (digitando "make" no terminal do diretorio da pasta), um executavel "main" vai ser gerado. Executando esse "main", o jogador poderá jogar CCPanico.

Para compilacao em terminals de Linux com SFML-TGUI ja instalado, a linha de comando é:
g++ main.cpp -ltgui -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio actions.cpp actor.cpp dice.cpp engine.cpp fight.cpp place.cpp player.cpp