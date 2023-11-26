#include "engine.h"

#include <iostream>

void Engine::game(){
    for (int i = 0; i < players.size(); i++){
        playerTurn2(players[i]);
    }
    results();
}

void Engine::pass_screen() {

    tgui::Theme theme{"../../themes/Black.txt"};

    //Botao de proximo turno
    auto nextTurnButton = tgui::Button::create();
    nextTurnButton->setRenderer(theme.getRenderer("Button"));
    nextTurnButton->setPosition(200, 230);
    nextTurnButton->setSize(400, 140);
    nextTurnButton->setText("TURN");
    nextTurnButton->setTextSize(25);
    gui.add(nextTurnButton);

 //Geracao do window para o Pass Screen (tela intermediaria entre turnos)
    while(true) {
        sf::Event pass_screen;
        while(window.pollEvent(pass_screen)) {
            gui.handleEvent(pass_screen);
            if(pass_screen.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        gui.draw();
        window.display();
    }
    gui.removeAllWidgets();
}

void Engine::main_menu() {
    tgui::Theme theme{"../../themes/Black.txt"};

    //Botao de novo jogo
    auto newGameButton = tgui::Button::create();
    newGameButton->setRenderer(theme.getRenderer("Button"));
    newGameButton->setPosition(540, 180);
    newGameButton->setSize(200, 70);
    newGameButton->setText("NOVO JOGO");
    newGameButton->setTextSize(19);
    gui.add(newGameButton);

    //Botao de carregar jogo
    auto loadGameButton = tgui::Button::create();
    loadGameButton->setRenderer(theme.getRenderer("Button"));
    loadGameButton->setPosition(540, 250);
    loadGameButton->setSize(200, 70);
    loadGameButton->setText("CARREGAR JOGO");
    loadGameButton->setTextSize(19);
    gui.add(loadGameButton);

    //Botao de criar personagem
    auto createCharacterButton = tgui::Button::create();
    createCharacterButton->setRenderer(theme.getRenderer("Button"));
    createCharacterButton->setPosition(540, 320);
    createCharacterButton->setSize(200, 70);
    createCharacterButton->setText("CRIAR PERSONAGEM");
    createCharacterButton->setTextSize(19);
    gui.add(createCharacterButton);

    //Botao de sair
    auto exitButton = tgui::Button::create();
    exitButton->setRenderer(theme.getRenderer("Button"));
    exitButton->setPosition(540, 390);
    exitButton->setSize(200, 70);
    exitButton->setText("SAIR");
    exitButton->setTextSize(19);
    gui.add(exitButton);

    //Geracao do window para o Main Menu
    while (true) {
        sf::Event main_menu;
        while(window.pollEvent(main_menu)) {
            gui.handleEvent(main_menu);
            if(main_menu.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        gui.draw();
        window.display();
    }
    gui.removeAllWidgets();
}

/*
void Engine::characterCreator(){
    int points = 12;
    std::string nome;
    int atributos[6];

    tgui::Theme theme{"../../themes/Black.txt"};
    tgui::Scrollbar::Policy Never;

    auto title = tgui::TextArea::create();
    title->setRenderer(theme.getRenderer("TextArea"));
    title->setPosition(30, 10);
    title->setMaximumCharacters(0);
    title->setSize(470, 100);
    title->setText("");
    title->setTextSize(16);
    title->setHorizontalScrollbarPolicy(Never);
    gui.add(title);

}
*/

void Engine::playerTurn1(Player *player) {
    /*
    int destination;

    std::cout << "Para onde voce quer ir?\n";
    
    std::cin >> destination;

    player->travelTo(this->places[destination]);

    */
}

void Engine::playerTurn2(Player *player) {

    //***// Interface Game Menu //***//

    tgui::Theme theme{"./Black.txt"};
    tgui::Scrollbar::Policy Never;

    //Area de dados do jogador
    auto statsArea = tgui::TextArea::create();
    statsArea->setRenderer(theme.getRenderer("TextArea"));
    statsArea->setPosition(30, 10);
    statsArea->setMaximumCharacters(0);
    statsArea->setSize(470, 100);
    statsArea->setText("");
    statsArea->setTextSize(16);
    statsArea->setHorizontalScrollbarPolicy(Never);
    statsArea->setReadOnly(true);
    gui.add(statsArea);

    //Barra de progresso para o trabalho
    auto projectBar = tgui::ProgressBar::create();
    projectBar->setRenderer(theme.getRenderer("ProgressBar"));
    projectBar->setPosition(520, 10);
    projectBar->setSize(200, 30);
    projectBar->setValue(player->getProjectBar());            //Recebe o valor do Player project_bar (unsigned int) 
    projectBar->setMaximum(100);
    projectBar->setMinimum(0);
    projectBar->setTextSize(15);
    projectBar->setText("TRABALHO");
    gui.add(projectBar);

    //Barra de progresso para estudo
    auto studyBar = tgui::ProgressBar::create();
    studyBar->setRenderer(theme.getRenderer("ProgressBar"));
    studyBar->setPosition(520, 50);
    studyBar->setSize(200, 30);
    studyBar->setValue(player->getStudyBar());              //Recebe o valor do Player study_bar (unsigned int)
    studyBar->setMaximum(100);
    studyBar->setMinimum(0);
    studyBar->setText("ESTUDO");
    studyBar->setTextSize(15);
    gui.add(studyBar);

    //Barra de tempo
    auto tempo = tgui::ProgressBar::create();
    tempo->setRenderer(theme.getRenderer("ProgressBar"));
    tempo->setPosition(600, 570);
    tempo->setSize(200, 30);
    tempo->setValue(0);                 //Recebe o valor do clock do turno
    tempo->setMaximum(100);
    tempo->setMinimum(0);
    tempo->setText("TEMPO");        
    tempo->setTextSize(15);
    gui.add(tempo);

    //Acao: 
    auto acao = tgui::TextArea::create();
    acao->setRenderer(theme.getRenderer("TextArea"));
    acao->setPosition(230, 430);
    acao->setMaximumCharacters(0);
    acao->setSize(90, 35);
    acao->setText("AÇÃO:");
    acao->setTextSize(20);
    acao->setHorizontalScrollbarPolicy(Never);
    gui.add(acao);

    //ComboBox1
    auto comboBox1 = tgui::ComboBox::create();
    comboBox1->setChangeItemOnScroll(true);
    comboBox1->setItemsToDisplay(0);
    comboBox1->setMaximumItems(0);
    comboBox1->setPosition(320, 430);
    comboBox1->setSize(250, 35);
    comboBox1->setTextSize(15);
    for (int i = 0; i < Action::game_actions.size(); i++){
        comboBox1->addItem(Action::game_actions[i]->getDescription(), Action::game_actions[i]->getDescription());
    }
    gui.add(comboBox1);

    //TextArea1
    auto TextArea1 = tgui::TextArea::create();
    TextArea1->setRenderer(theme.getRenderer("TextArea"));
    TextArea1->setPosition(200, 190);
    TextArea1->setMaximumCharacters(0);
    TextArea1->setSize(400, 200);
    TextArea1->setText("");
    TextArea1->setTextSize(15);
    TextArea1->setHorizontalScrollbarPolicy(Never);
    TextArea1->setReadOnly(true);
    gui.add(TextArea1);
    
    //Botao de saude
    auto healthButton = tgui::Button::create();
    healthButton->setRenderer(theme.getRenderer("Button"));
    healthButton->setPosition(200, 140);
    healthButton->setSize(120, 35);
    healthButton->setText("SAÚDE");
    healthButton->setTextSize(18);
    healthButton->onClick([&]{
        TextArea1->setText(std::to_string(player->get_hp()));
    });
    gui.add(healthButton);

    //Botao de habilidades
    auto skillButton = tgui::Button::create();
    skillButton->setRenderer(theme.getRenderer("Button"));
    skillButton->setPosition(480, 140);
    skillButton->setSize(120, 35);
    skillButton->setText("HABILIDADES");
    skillButton->setTextSize(18);
    skillButton->onClick([&]{ 
        TextArea1->setText("Skills: \n"); 
        for (int i = 0; i < SKILL_NUM; i++){
            TextArea1->addText(skill_name[i] + ": " + std::to_string(player->getSkill(i)) + '\n');
        }
    });
    gui.add(skillButton);

    //Botao de jogadores
    auto playersButton = tgui::Button::create();
    playersButton->setRenderer(theme.getRenderer("Button"));
    playersButton->setPosition(340, 140);
    playersButton->setSize(120, 35);
    playersButton->setText("JOGADORES");
    playersButton->setTextSize(18);
    playersButton->onClick([&]{ 
        TextArea1->setText("");
        for (int i = 0; i < players.size(); i++){
            if (players[i] == player){
                continue;
            }
            TextArea1->addText(players[i]->getName() + '\n');
        }
    });
    gui.add(playersButton);

    //ComboBox2
    auto comboBox2 = tgui::ComboBox::create();
    comboBox2->setRenderer(theme.getRenderer("ComboBox"));
    comboBox2->setChangeItemOnScroll(false);
    comboBox2->setItemsToDisplay(0);
    comboBox2->setMaximumItems(0);
    comboBox2->setPosition(320, 500);
    comboBox2->setSize(250, 30);
    comboBox2->setTextSize(13);
    for (int i = 0; i < players.size(); i++){
        comboBox2->addItem(players[i]->getName(), players[i]->getName());
    }
    gui.add(comboBox2);

    //TextArea2
    auto TextArea2 = tgui::TextArea::create();
    TextArea2->setRenderer(theme.getRenderer("TextArea"));
    TextArea2->setPosition(230, 500);
    TextArea2->setMaximumCharacters(0);
    TextArea2->setSize(90, 30);
    TextArea2->setText("ALVO: ");
    TextArea2->setTextSize(18);
    TextArea2->setHorizontalScrollbarPolicy(Never);
    gui.add(TextArea2);

    //Geracao do window para o Game Menu
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
    gui.removeAllWidgets();
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