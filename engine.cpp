#include "engine.h"

void Engine::game(){
    for (int i = 0; i < players.size(); i++){
        playerTurn2(players[i]);
    }
    results();
}

void Engine::PlayerTurn1(Player *player) {
    /*
    int destination;

    std::cout << "Para onde voce quer ir?\n";
    
    std::cin >> destination;

    player->travelTo(this->places[destination]);

    */
}

void Engine::playerTurn2(Player *player) {
    tgui::Theme theme{"../../themes/Black.txt"};
    auto projectBar = tgui::ProgressBar::create();
    projectBar->setRenderer(theme.getRenderer("ProgressBar"));
    projectBar->setPosition(520, 10);
    projectBar->setSize(200, 30);
    projectBar->setValue(50);
    projectBar->setMaximum(100);
    projectBar->setMinimum(0);
    projectBar->setText("TRABALHO");
    gui.add(projectBar);
    while (true){
        sf::Event event;
        while (window.pollEvent(event)){
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();

        gui.draw();

        window.display();
    }
}
/*    Action *action;
    
    int action_num;
    int target;
    std::cin >> action_num;

    switch (action_num) {
        case 1:
            action = new WorkOnProjectAction(player);
            break;

        case 2:
            std::cin >> target;

            action = new DamageAction(player, this->players[target]);
            break;
        case 3:
            action = new StudyAction(player);
        case 4:
            std::cin >> target;

            action = new HealAction(player, this->players[target]);
        default:
            break;
    }
    this->turn_actions.push_back(action);
*/

void Engine::results() {
    for(int i=0; i<turn_actions.size(); i++) {
        turn_actions[i]->execute();
        delete turn_actions[i];
    }
}

void Engine::createPlayer(std::string name, int atributes[6]){
    Player *player = new Player(name, atributes);
    players.push_back(player);
}

void Engine::characterCreator(){
    std::string name;
    int atributes[6];
    std::cout << "Nome: ";
    std::cin >> name;
    std::cout << "Skills:";
    for (int i = 0; i < 6; i++){
        std::cin >> atributes[i]; 
    }
    createPlayer(name, atributes);
}