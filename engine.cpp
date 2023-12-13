#include "engine.h"
#include "dice.h"

int triang(int n){
    return (n*n + n) / 2;
}

void Engine::game(int player_num, int turn1_time, int turn2_time){
    for (int i = 0; i < player_num; i++){
        character_creator_screen();
    }
    Action::instantiateActions();
    instantiatePlaces();
    roleSelector();
    for (int i = 0; i < players.size(); i++){
        pass_screen(players[i]);
        role_screen(players[i]);
    }
    for (game_time = 0; game_time < MAX_TIME; game_time++){
        for (int i = 0; i < players.size(); i++){
            pass_screen(players[i]);
            playerTurn1(players[i], turn1_time);
        }
        for (int i = 0; i < players.size(); i++){
            players[i]->resultsText = "";
            pass_screen(players[i]);
            playerTurn2(players[i], turn2_time);
        }
        results();
        for (int i = 0; i < players.size(); i++){
            pass_screen(players[i]);
            result_screen(players[i]);
        }
        for (int i = 0; i < players.size(); i++){
            if (!players[i]->isAlive()){
                deletePlayer(players[i]->get_id());
                i--;
            }
        }
        if (check_for_ending()){
            break;
        }
    }
    for (int i = 0; i < PLACE_NUM; i++){
        delete places[i];
    }
}
void Engine::game_settings(){

    tgui::Theme theme{"./Black.txt"};
    bool stay = true;

    int player_num = 3;
    int turn1_time = 10;
    int turn2_time = 15;

    //Imagem de fundo
    auto picture = tgui::Picture::create("./criacaopersn.png");
    picture->setSize({"100%", "100%"});
    gui.add(picture);
    
    //Titulo
    auto title = tgui::TextArea::create();
    title->setRenderer(theme.getRenderer("TextArea"));
    title->setPosition(230, 20);
    title->setMaximumCharacters(0);
    title->setSize(340, 40);
    title->setText("Configurações de jogo");
    title->setTextSize(23);
    title->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(title);
    
    //Quantidade de jogadores
    auto playersButton = tgui::SpinButton::create();
    playersButton->setRenderer(theme.getRenderer("SpinButton"));
    playersButton->setMaximum(8);
    playersButton->setMinimum(3);
    playersButton->setStep(1);
    playersButton->setPosition(210, 250);
    playersButton->setSize(30, 50);
    playersButton->setTextSize(13);
    playersButton->setValue(player_num);
    gui.add(playersButton);

    auto playersArea = tgui::TextArea::create();
    playersArea->setRenderer(theme.getRenderer("TextArea"));
    playersArea->setPosition(50, 250);
    playersArea->setMaximumCharacters(0);
    playersArea->setSize(160, 50);
    playersArea->setText(std::to_string(player_num) + " jogadores");
    playersArea->setTextSize(16);
    playersArea->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(playersArea);

    auto turn1Button = tgui::SpinButton::create();
    turn1Button->setRenderer(theme.getRenderer("SpinButton"));
    turn1Button->setMaximum(30);
    turn1Button->setMinimum(5);
    turn1Button->setStep(1);
    turn1Button->setPosition(210, 350);
    turn1Button->setSize(30, 50);
    turn1Button->setTextSize(13);
    turn1Button->setValue(turn1_time);
    gui.add(turn1Button);
    
    auto turn1Area = tgui::TextArea::create();
    turn1Area->setRenderer(theme.getRenderer("TextArea"));
    turn1Area->setPosition(50, 350);
    turn1Area->setMaximumCharacters(0);
    turn1Area->setSize(160, 50);
    turn1Area->setText("Turno 1: " + std::to_string(turn1_time) + " segundos");
    turn1Area->setTextSize(16);
    turn1Area->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(turn1Area);

    auto turn2Button = tgui::SpinButton::create();
    turn2Button->setRenderer(theme.getRenderer("SpinButton"));
    turn2Button->setMaximum(30);
    turn2Button->setMinimum(5);
    turn2Button->setStep(1);
    turn2Button->setPosition(210, 450);
    turn2Button->setSize(30, 50);
    turn2Button->setTextSize(13);
    turn2Button->setValue(turn2_time);
    gui.add(turn2Button);

    auto turn2Area = tgui::TextArea::create();
    turn2Area->setRenderer(theme.getRenderer("TextArea"));
    turn2Area->setPosition(50, 450);
    turn2Area->setMaximumCharacters(0);
    turn2Area->setSize(160, 50);
    turn2Area->setText("Turno 2: " + std::to_string(turn2_time) + " segundos");
    turn2Area->setTextSize(16);
    turn2Area->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(turn2Area);

    //Botao de começar o jogo
    auto nextButton = tgui::Button::create();
    nextButton->setRenderer(theme.getRenderer("Button"));
    nextButton->setPosition(630, 540);
    nextButton->setSize(170, 60);;
    nextButton->setText("Começar");
    nextButton->setTextSize(20);
    nextButton->onClick([&]{
        game(playersButton->getValue(), turn1_time, turn2_time);
        stay = false;
    });
    gui.add(nextButton);

    //Botao de sair
    auto exitButton = tgui::Button::create();
    exitButton->setRenderer(theme.getRenderer("Button"));
    exitButton->setPosition(0, 540);
    exitButton->setSize(170, 60);
    exitButton->setText("SAIR");
    exitButton->setTextSize(20);
    exitButton->onClick([&]{
        stay = false;
    });
    gui.add(exitButton);

    while(stay) {
        sf::Event role_screen;
        while(window.pollEvent(role_screen)) {
            gui.handleEvent(role_screen);
            if(role_screen.type == sf::Event::Closed) {
                horrorgame.~Music();
                window.close();
                exit(0);
            }
        }
        player_num = playersButton->getValue();
        turn1_time = turn1Button->getValue();
        turn2_time = turn2Button->getValue();
        playersArea->setText(std::to_string(player_num) + " jogadores");
        turn1Area->setText("Turno 1: " + std::to_string(turn1_time) + " segundos");
        turn2Area->setText("Turno 2: " + std::to_string(turn2_time) + " segundos");
        window.clear();
        gui.draw();
        window.display();
    }
    gui.removeAllWidgets();

}

void Engine::roleSelector() {
    int chosen = Dice::single_die(players.size()) - 1;
    players[chosen]->setKiller();
}

void Engine::role_screen(Player *player) {
    tgui::Theme theme{"./Black.txt"};
    bool stay = true;
    tgui::String text, description, screen;
    if (player->isKiller()){
        text = "Você é o assassino!";    
        description = "Seu objetivo é matar furtivamente todos os estudantes de computação!\n Complete seu objetivo antes do final da última semana do período sem ser pego.";
        screen = "./capyblood.jpeg";
    }
    else{
        text = "Você é um estudante!";
        description = "Seu objetivo é sobreviver à última semana do período!\n Estude para suas provas finais e conclua o trabalho final de Programação II, mas fique de olho no assassino que está solto!";
        screen = "./capystd.jpeg";    
    }

    // Imagem de fundo
    auto roleScreenBackground = tgui::Picture::create(screen);
    roleScreenBackground->setSize({"100%", "100%"});
    gui.add(roleScreenBackground);
    
    //Mensagem da carga
    auto roleText = tgui::TextArea::create();
    roleText->setRenderer(theme.getRenderer("TextArea"));
    roleText->setMaximumCharacters(0);
    roleText->setPosition(240,30);
    roleText->setSize(320, 40);
    roleText->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    roleText->setTextSize(25);
    roleText->setReadOnly(true);
    roleText->setText(text);
    gui.add(roleText);

    //Descricao da carga
    auto roleDescription = tgui::TextArea::create();
    roleDescription->setRenderer(theme.getRenderer("TextArea"));
    roleDescription->setMaximumCharacters(0);
    roleDescription->setPosition(255,400);
    roleDescription->setSize(290, 115);
    roleDescription->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    roleDescription->setText(description);
    roleDescription->setTextSize(15);
    roleDescription->setReadOnly(true);
    gui.add(roleDescription);

    //Botao de proximo
    auto nextButton = tgui::Button::create();
    nextButton->setRenderer(theme.getRenderer("Button"));
    nextButton->setPosition(630, 540);
    nextButton->setSize(170, 60);;
    nextButton->setText("Proximo");
    nextButton->setTextSize(20);
    nextButton->onClick([&]{
        stay = false;
    });
    gui.add(nextButton);

    while(stay) {
        sf::Event role_screen;
        while(window.pollEvent(role_screen)) {
            gui.handleEvent(role_screen);
            if(role_screen.type == sf::Event::Closed) {
                horrorgame.~Music();
                window.close();
                exit(0);
            }
        }
        window.clear();
        gui.draw();
        window.display();
    }
    gui.removeAllWidgets();

}

void Engine::pass_screen(Player *player) {
    tgui::Theme theme{"./Black.txt"};

    //Configura a imagem de fundo do menu de espera 
    auto picture = tgui::Picture::create("./capypass.png");
    picture->setSize(630,530);
    picture->setPosition(70,10);
    gui.add(picture);
    bool stay = true;

    //Botao de proximo turno
    auto nextTurnButton = tgui::Button::create();
    nextTurnButton->setRenderer(theme.getRenderer("Button"));
    nextTurnButton->setPosition(630, 540);
    nextTurnButton->setSize(170, 60);;
    nextTurnButton->setText("Vez de " + player->getName());
    nextTurnButton->setTextSize(20);
    nextTurnButton->onClick([&]{
        stay = false;
    });
    gui.add(nextTurnButton);

 //Geracao do window para o Pass Screen (tela intermediaria entre turnos)
    while(stay) {
        sf::Event pass_screen;
        while(window.pollEvent(pass_screen)) {
            gui.handleEvent(pass_screen);
            if(pass_screen.type == sf::Event::Closed) {
                horrorgame.~Music();
                window.close();
                exit(0);
            }
        }
        window.clear();
        gui.draw();
        window.display();
    }
    gui.removeAllWidgets();
}

void Engine::main_menu() {

    tgui::Theme theme{"./Black.txt"};
    
    //Configura a imagem de fundo do menu principal
    auto picture = tgui::Picture::create("./4pilastrascc.jpg");
    picture->setSize({"100%", "100%"});
    gui.add(picture);
    
    //Botao de novo jogo
    auto newGameButton = tgui::Button::create();
    newGameButton->setRenderer(theme.getRenderer("Button"));
    newGameButton->setPosition(50, 30);
    newGameButton->setSize(200, 70);
    newGameButton->setText("JOGAR");
    newGameButton->setTextSize(19);
    newGameButton->onClick([&]{
        gui.removeAllWidgets();
        game_settings();
    });
    gui.add(newGameButton);

    //Botao de sair
    auto exitButton = tgui::Button::create();
    exitButton->setRenderer(theme.getRenderer("Button"));
    exitButton->setPosition(550, 30);
    exitButton->setSize(200, 70);
    exitButton->setText("SAIR");
    exitButton->setTextSize(19);
    exitButton->onClick([&]{
                horrorgame.~Music();
                window.close();
                exit(0);
    });
    gui.add(exitButton);

    //Geracao do window para o Main Menu
    if (!horrorgame.openFromFile("8bit-Syndrome-Horror-audio01-.ogg"))
        return ; // error
    horrorgame.play();
    while (true) {
        sf::Event main_menu;
        while(window.pollEvent(main_menu)) {
            gui.handleEvent(main_menu);
            if(main_menu.type == sf::Event::Closed) {
                horrorgame.~Music();
                window.close();
                exit(0);
            }
        }
        window.clear();
        gui.draw();
        window.display();
    }
    gui.removeAllWidgets();
}

void Engine::playerTurn1(Player *player, int turn_time) {

    sf::Clock clock;

    int time = 4 * turn_time;

    tgui::Theme theme{"./Black.txt"};

    //Area de dados do jogador
    auto statsArea = tgui::TextArea::create();
    statsArea->setRenderer(theme.getRenderer("TextArea"));
    statsArea->setPosition(30, 10);
    statsArea->setMaximumCharacters(0);
    statsArea->setSize(470, 100);
    statsArea->setText("");
    statsArea->setTextSize(16);
    statsArea->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    statsArea->setReadOnly(true);
    statsArea->setText(player->getName() + '\n' + "Saúde: " + player->getHealth());
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
    auto timeBar = tgui::ProgressBar::create();
    timeBar->setRenderer(theme.getRenderer("ProgressBar"));
    timeBar->setPosition(600, 570);
    timeBar->setSize(200, 30);
    timeBar->setValue(time);                 //Recebe o valor do clock do turno
    timeBar->setMaximum(time);
    timeBar->setMinimum(0);
    timeBar->setText("TEMPO");        
    timeBar->setTextSize(15);
    gui.add(timeBar);

    //Texto do lado da combobox1 
    auto comboText1 = tgui::TextArea::create();
    comboText1->setRenderer(theme.getRenderer("TextArea"));
    comboText1->setPosition(210, 430);
    comboText1->setMaximumCharacters(0);
    comboText1->setSize(130, 35);
    comboText1->setText("DESTINO:");
    comboText1->setTextSize(20);
    comboText1->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(comboText1);

    //ComboBox1
    auto comboBox1 = tgui::ComboBox::create();
    comboBox1->setChangeItemOnScroll(true);
    comboBox1->setItemsToDisplay(0);
    comboBox1->setMaximumItems(0);
    comboBox1->setPosition(340, 430);
    comboBox1->setSize(250, 35);
    comboBox1->setTextSize(15);
    for (int i = 0; i < PLACE_NUM; i++){
        comboBox1->addItem(places[i]->getName(), std::to_string(i));
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
    TextArea1->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    TextArea1->setReadOnly(true);
    gui.add(TextArea1);
    
    //Botao de saude
    auto needsButton = tgui::Button::create();
    needsButton->setRenderer(theme.getRenderer("Button"));
    needsButton->setPosition(200, 140);
    needsButton->setSize(120, 35);
    needsButton->setText("NECESSIDADES");
    needsButton->setTextSize(16);
    needsButton->onClick([&]{
        TextArea1->setText("Necessidades: \n");
        for (int i = 0; i < NEEDS_NUM; i++){
            TextArea1->addText(needs_names[i] + ": " + std::to_string(player->getNeed(i)) + '\n');
        }
    });
    gui.add(needsButton);

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
            TextArea1->addText(skill_names[i] + ": " + std::to_string(player->getSkill(i)) + '\n');
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

    //Geracao do window para o Game Menu
    while (true){
        sf::Event event;
        while (window.pollEvent(event)){
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed){
                horrorgame.~Music();
                window.close();
                exit(0);
            }
        }
        if (clock.getElapsedTime() > sf::seconds(0.25)){
            clock.restart();
            time--;
            timeBar->setValue(time);
        }

        window.clear();
        gui.draw();
        window.display();
        if (time <= 0){
            break;
        }
    }

    Place* destination = places[comboBox1->getSelectedItemId().toInt()];

    player->travelTo(destination);

    gui.removeAllWidgets();
    
}

void Engine::playerTurn2(Player *player, int turn_time) {
    //***// Interface Game Menu //***//

    sf::Clock clock;

    int time = 4 * turn_time;

    bool valid_target = false;

    tgui::Theme theme{"./Black.txt"};

    auto picture = tgui::Picture::create(player->getPlace()->getPicture());
    picture->setSize({"100%", "100%"});
    gui.add(picture);

    //Area de dados do jogador
    auto statsArea = tgui::TextArea::create();
    statsArea->setRenderer(theme.getRenderer("TextArea"));
    statsArea->setPosition(30, 10);
    statsArea->setMaximumCharacters(0);
    statsArea->setSize(470, 100);
    statsArea->setText("");
    statsArea->setTextSize(16);
    statsArea->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    statsArea->setReadOnly(true);
    statsArea->setText(player->getName() + '\n' + "Saúde: " + player->getHealth());
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
    auto timeBar = tgui::ProgressBar::create();
    timeBar->setRenderer(theme.getRenderer("ProgressBar"));
    timeBar->setPosition(600, 570);
    timeBar->setSize(200, 30);
    timeBar->setValue(time);                 //Recebe o valor do clock do turno
    timeBar->setMaximum(time);
    timeBar->setMinimum(0);
    timeBar->setText("TEMPO");        
    timeBar->setTextSize(15);
    gui.add(timeBar);

    //Texto do lado da comboBox1 
    auto comboText1 = tgui::TextArea::create();
    comboText1->setRenderer(theme.getRenderer("TextArea"));
    comboText1->setPosition(230, 430);
    comboText1->setMaximumCharacters(0);
    comboText1->setSize(90, 35);
    comboText1->setText("AÇÃO:");
    comboText1->setTextSize(20);
    comboText1->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(comboText1);

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
        if (players[i] != player && player->getPlace() == players[i]->getPlace()){
            comboBox2->addItem(players[i]->getName(), std::to_string(i));
            valid_target = true;
        }
    }
    gui.add(comboBox2);

    //ComboBox1
    auto comboBox1 = tgui::ComboBox::create();
    comboBox1->setChangeItemOnScroll(true);
    comboBox1->setItemsToDisplay(0);
    comboBox1->setMaximumItems(0);
    comboBox1->setPosition(320, 430);
    comboBox1->setSize(250, 35);
    comboBox1->setTextSize(15);
    for (int i = 0; i < Action::game_actions.size(); i++){
        Action* hypotetic_action = Action::ActionByID(i, player);
        if ((valid_target || !hypotetic_action->isTargeted()) && hypotetic_action->possible()){
            comboBox1->addItem(Action::game_actions[i]->getDescription(), std::to_string(i));
        }
        delete hypotetic_action;
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
    TextArea1->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    TextArea1->setReadOnly(true);
    gui.add(TextArea1);
    
    //Botao de saude
    auto needsButton = tgui::Button::create();
    needsButton->setRenderer(theme.getRenderer("Button"));
    needsButton->setPosition(200, 140);
    needsButton->setSize(120, 35);
    needsButton->setText("NECESSIDADES");
    needsButton->setTextSize(16);
    needsButton->onClick([&]{
        TextArea1->setText("Necessidades: \n");
        for (int i = 0; i < NEEDS_NUM; i++){
            TextArea1->addText(needs_names[i] + ": " + std::to_string(player->getNeed(i)) + '\n');
        }
    });
    gui.add(needsButton);

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
            TextArea1->addText(skill_names[i] + ": " + std::to_string(player->getSkill(i)) + '\n');
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
            TextArea1->addText(players[i]->getName(false) + " (" + players[i]->getPlace()->getName() + ")\n");
        }
    });
    gui.add(playersButton);

    //TextArea2
    auto TextArea2 = tgui::TextArea::create();
    TextArea2->setRenderer(theme.getRenderer("TextArea"));
    TextArea2->setPosition(230, 500);
    TextArea2->setMaximumCharacters(0);
    TextArea2->setSize(90, 30);
    TextArea2->setText("ALVO: ");
    TextArea2->setTextSize(18);
    TextArea2->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(TextArea2);

    //Geracao do window para o Game Menu
    while (true){
        sf::Event event;
        while (window.pollEvent(event)){
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed){
                horrorgame.~Music();
                window.close();
                exit(0);
            }
        }
        if (clock.getElapsedTime() > sf::seconds(0.25)){
            clock.restart();
            time--;
            timeBar->setValue(time);
        }
        TextArea2->setVisible(Action::game_actions[comboBox1->getSelectedItemId().toInt()]->isTargeted() && valid_target);
        comboBox2->setVisible(Action::game_actions[comboBox1->getSelectedItemId().toInt()]->isTargeted() && valid_target);

        window.clear();
        gui.draw();
        window.display();
        if (time <= 0){
            break;
        }
    }

    int action_num = comboBox1->getSelectedItemId().toInt();

    Action* action = Action::ActionByID(action_num, player, players[comboBox2->getSelectedItemId().toInt()]);

    if (!action){
        action = new StudyAction(player);
    }

    this->turn_actions.push(action);

    gui.removeAllWidgets();

}

void Engine::character_creator_screen() {
    tgui::Theme theme{"./Black.txt"};

    bool stay = true;
    int points = 36;
    int atributes[SKILL_NUM] = {1, 1, 1, 1, 1, 1};
    
    //Configura a imagem de fundo do menu de personagem
    auto picture = tgui::Picture::create("./criacaopersn.png");
    picture->setSize({"100%", "100%"});
    gui.add(picture);
    
    //Titulo
    auto title = tgui::TextArea::create();
    title->setRenderer(theme.getRenderer("TextArea"));
    title->setPosition(230, 20);
    title->setMaximumCharacters(0);
    title->setSize(340, 40);
    title->setText("CRIADOR DE PERSONAGEM");
    title->setTextSize(23);
    title->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(title);

    //Botao de atletismo
    auto FitnessButton = tgui::SpinButton::create();
    FitnessButton->setRenderer(theme.getRenderer("SpinButton"));
    FitnessButton->setPosition(230, 180);
    FitnessButton->setMaximum(5);
    FitnessButton->setMinimum(1);
    FitnessButton->setSize(20, 50);
    FitnessButton->setStep(1);
    FitnessButton->setValue(atributes[FITNESS]);
    gui.add(FitnessButton);

    //Botao de agilidade
    auto AgilityButton = tgui::SpinButton::create();
    AgilityButton->setRenderer(theme.getRenderer("SpinButton"));
    AgilityButton->setPosition(470, 180);
    AgilityButton->setMaximum(5);
    AgilityButton->setMinimum(1);
    AgilityButton->setSize(20, 50);
    AgilityButton->setStep(1);
    AgilityButton->setValue(atributes[AGILITY]);
    gui.add(AgilityButton);

    //Botao de resistencia
    auto EnduranceButton = tgui::SpinButton::create();
    EnduranceButton->setRenderer(theme.getRenderer("SpinButton"));
    EnduranceButton->setPosition(710, 180);
    EnduranceButton->setMaximum(5);
    EnduranceButton->setMinimum(1);
    EnduranceButton->setSize(20, 50);
    EnduranceButton->setStep(1);
    EnduranceButton->setValue(atributes[ENDURANCE]);
    gui.add(EnduranceButton);

    //Botao de pensamento
    auto ThinkingButton = tgui::SpinButton::create();
    ThinkingButton->setRenderer(theme.getRenderer("SpinButton"));
    ThinkingButton->setPosition(230, 280);
    ThinkingButton->setMaximum(5);
    ThinkingButton->setMinimum(1);
    ThinkingButton->setSize(20, 50);
    ThinkingButton->setStep(1);
    ThinkingButton->setValue(atributes[LOGIC]);
    gui.add(ThinkingButton);

    //Botao de primeiros socorros
    auto FirstAidButton = tgui::SpinButton::create();
    FirstAidButton->setRenderer(theme.getRenderer("SpinButton"));
    FirstAidButton->setPosition(470, 280);
    FirstAidButton->setMaximum(5);
    FirstAidButton->setMinimum(1);
    FirstAidButton->setSize(20, 50);
    FirstAidButton->setStep(1);
    FirstAidButton->setValue(atributes[FIRST_AID]);
    gui.add(FirstAidButton);

    //Botao de carisma
    auto CharismaButton = tgui::SpinButton::create();
    CharismaButton->setRenderer(theme.getRenderer("SpinButton"));
    CharismaButton->setPosition(710, 280);
    CharismaButton->setMaximum(5);
    CharismaButton->setMinimum(1);
    CharismaButton->setSize(20, 50);
    CharismaButton->setStep(1);
    CharismaButton->setValue(atributes[COMMUNICATION]);
    gui.add(CharismaButton);

    //Atletismo Area
    
    auto FitnessArea = tgui::TextArea::create();
    FitnessArea->setRenderer(theme.getRenderer("TextArea"));
    FitnessArea->setPosition(70, 180);
    FitnessArea->setMaximumCharacters(0);
    FitnessArea->setSize(160, 50);
    FitnessArea->setText("ATLETISMO: " + std::to_string(atributes[FITNESS]));
    FitnessArea->setTextSize(16);
    FitnessArea->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(FitnessArea);

    //Agilidade Area
    auto AgilityArea = tgui::TextArea::create();
    AgilityArea->setRenderer(theme.getRenderer("TextArea"));
    AgilityArea->setPosition(310, 180);
    AgilityArea->setMaximumCharacters(0);
    AgilityArea->setSize(160, 50);
    AgilityArea->setText("AGILIDADE: " + std::to_string(atributes[AGILITY]));
    AgilityArea->setTextSize(16);
    AgilityArea->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(AgilityArea);

    //Resistência Area
    auto EnduranceArea = tgui::TextArea::create();
    EnduranceArea->setRenderer(theme.getRenderer("TextArea"));
    EnduranceArea->setPosition(550, 180);
    EnduranceArea->setMaximumCharacters(0);
    EnduranceArea->setSize(160, 50);
    EnduranceArea->setText("RESISTÊNCIA: " + std::to_string(atributes[ENDURANCE]));
    EnduranceArea->setTextSize(16);
    EnduranceArea->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(EnduranceArea);

    //Lógica Area
    auto ThinkingArea = tgui::TextArea::create();
    ThinkingArea->setRenderer(theme.getRenderer("TextArea"));
    ThinkingArea->setPosition(70, 280);
    ThinkingArea->setMaximumCharacters(0);
    ThinkingArea->setSize(160, 50);
    ThinkingArea->setText("LÓGICA: " + std::to_string(atributes[LOGIC]));
    ThinkingArea->setTextSize(16);
    ThinkingArea->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(ThinkingArea);

    //Primeiros Socorros Area
    auto FirstAidArea = tgui::TextArea::create();
    FirstAidArea->setRenderer(theme.getRenderer("TextArea"));
    FirstAidArea->setPosition(310, 280);
    FirstAidArea->setMaximumCharacters(0);
    FirstAidArea->setSize(160, 50);
    FirstAidArea->setText("PRIMEIROS SOCORROS: " + std::to_string(atributes[FIRST_AID]));
    FirstAidArea->setTextSize(16);
    FirstAidArea->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(FirstAidArea);

    //Comunicação Area
    auto CharismaArea = tgui::TextArea::create();
    CharismaArea->setRenderer(theme.getRenderer("TextArea"));
    CharismaArea->setPosition(550, 280);
    CharismaArea->setMaximumCharacters(0);
    CharismaArea->setSize(160, 50);
    CharismaArea->setText("COMUNICAÇÃO: " + std::to_string(atributes[COMMUNICATION]));
    CharismaArea->setTextSize(16);
    CharismaArea->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(CharismaArea);

    //EditBox1
    auto EditBox1 = tgui::EditBox::create();
    EditBox1->setAlignment(tgui::EditBox::Alignment::Center);
    EditBox1->setPosition(320, 70);
    EditBox1->setSize(160, 50);
    EditBox1->setText("NOME");
    EditBox1->setTextSize(15);
    gui.add(EditBox1);

    auto ErrorArea = tgui::TextArea::create();
    ErrorArea->setRenderer(theme.getRenderer("TextArea"));
    ErrorArea->setPosition(300, 400);
    ErrorArea->setMaximumCharacters(0);
    ErrorArea->setSize(200, 100);
    ErrorArea->setText("");
    ErrorArea->setTextSize(16);
    ErrorArea->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(ErrorArea);
    ErrorArea->setVisible(false);

    //Botao de proximo
    auto NextButton = tgui::Button::create();
    NextButton->setPosition(630, 540);
    NextButton->setSize(170, 60);
    NextButton->setText("PRÓXIMO");
    NextButton->setTextSize(20);
    NextButton->onClick([&]{
        if (EditBox1->getText() == ""){
            ErrorArea->setVisible(true);
            ErrorArea->setText("Insira um nome de verdade");
        }
        else if (points < 0){
            ErrorArea->setVisible(true);
            ErrorArea->setText("Você está gastando " + std::to_string(points * -1) + " a mais do que permitido." );
        }
        else{
            createPlayer(EditBox1->getText(), atributes);
            stay = false;
        }
    });
    gui.add(NextButton);

    //Pontos restantes
    auto RemainingPoints = tgui::TextArea::create();
    RemainingPoints->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    RemainingPoints->setMaximumCharacters(0);
    RemainingPoints->setPosition(270, 130);
    RemainingPoints->setSize(260, 30);
    RemainingPoints->setText("PONTOS RESTANTES: " + std::to_string(points));
    RemainingPoints->setTextSize(18);
    gui.add(RemainingPoints);


    while (stay){
        sf::Event event;
        while (window.pollEvent(event)){
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed){
                horrorgame.~Music();
                window.close();
                exit(0);
            }
        }

        atributes[FITNESS] = FitnessButton->getValue();
        atributes[AGILITY] = AgilityButton->getValue();
        atributes[ENDURANCE] = EnduranceButton->getValue();
        atributes[LOGIC] = ThinkingButton->getValue();
        atributes[FIRST_AID] = FirstAidButton->getValue();
        atributes[COMMUNICATION] = CharismaButton->getValue();

        FitnessArea->setText("ATLETISMO: " + std::to_string(atributes[FITNESS]));
        AgilityArea->setText("AGILIDADE: " + std::to_string(atributes[AGILITY]));
        EnduranceArea->setText("RESISTÊNCIA: " + std::to_string(atributes[ENDURANCE]));
        ThinkingArea->setText("LÓGICA: " + std::to_string(atributes[LOGIC]));
        FirstAidArea->setText("PRIMEIROS SOCORROS: " + std::to_string(atributes[FIRST_AID]));
        CharismaArea->setText("COMUNICAÇÃO: " + std::to_string(atributes[COMMUNICATION]));

        points = 36;
        for (int i = 0; i < SKILL_NUM; i++){
            points -= triang(atributes[i]);
        }

        RemainingPoints->setText("PONTOS RESTANTES: " + std::to_string(points));

        window.clear();
        gui.draw();
        window.display();
    }

    gui.removeAllWidgets();

}

//Tela para mostrar os resultados do jogo
void Engine::result_screen(Player *player){

    tgui::Theme theme{"./Black.txt"};
    bool stay=true;

    //Titulo
    auto title = tgui::TextArea::create();
    title->setRenderer(theme.getRenderer("TextArea"));
    title->setPosition(310, 20);
    title->setMaximumCharacters(0);
    title->setSize(180, 40);
    title->setText("RESULTADOS");
    title->setTextSize(23);
    title->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(title);

    //Botao de proximo
    auto NextButton = tgui::Button::create();
    NextButton->setRenderer(theme.getRenderer("Button"));
    NextButton->setPosition(630, 540);
    NextButton->setSize(170, 60);
    NextButton->setText(player->isAlive()? "PRÓXIMO" : "DESCANSE EM PAZ");
    NextButton->setTextSize(20);
    NextButton->onClick([&]{
        stay = false;
    });
    gui.add(NextButton);

    //Tabela de informações dos resultados
    auto info = tgui::TextArea::create();
    info->setRenderer(theme.getRenderer("TextArea"));
    info->setPosition(200, 170);
    info->setMaximumCharacters(0);
    info->setSize(400, 200);
    info->setText(player->resultsText);
    info->setTextSize(16);
    info->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Automatic);
    gui.add(info);

    while(stay) {
        sf::Event pass_screen;
        while(window.pollEvent(pass_screen)) {
            gui.handleEvent(pass_screen);
            if(pass_screen.type == sf::Event::Closed) {
                horrorgame.~Music();
                window.close();
                exit(0);
            }
        }
        window.clear();
        gui.draw();
        window.display();
    }
    gui.removeAllWidgets();
}

void Engine::results() {
    for (int i = 0; i < players.size(); i++){
        for (int j = 0; j < NEEDS_NUM; j++){
            players[i]->addNeed(j, -1);
            if (players[i]->getNeed(j) < 0){
                players[i]->randomSkillLoss();
                players[i]->resultsText += "Você perdeu pontos de habilidade por não cuidar de suas necessidades\n";
            }
        }
    }
    while (!turn_actions.empty()) {
        turn_actions.front()->execute();
        turn_actions.front()->updateResultsText();
        delete turn_actions.front();
        turn_actions.pop();
    }
}

void Engine::createPlayer(tgui::String name, int atributes[6]){
    players.push_back(new Player(name, atributes));
}

void Engine::deletePlayer(int id){
    for (int i = 0; i < players.size(); i++){
        if (players[i]->get_id() == id){
            delete players[i];
            players.erase(players.begin()+i);
        }
    }
}

bool Engine::check_for_ending(){
    bool killer_alive = false;
    bool someone_else_alive = false;
    for (int i = 0; i < players.size(); i++){
        if (players[i]->isKiller() && players[i]->isAlive()){
            killer_alive = true;
        }
        else if (!players[i]->isKiller() && players[i]->isAlive()){
            someone_else_alive = true;
        }
    }
    if (game_time >= MAX_TIME-1){
        ending_screen(END_OF_SEMESTER_ENDING);
    }
    else if (killer_alive && someone_else_alive){
        return false;
    }
    else if (someone_else_alive){
        ending_screen(KILL_THE_KILLER_ENDING);
    }
    else if (killer_alive){
        ending_screen(KILLER_WIN_ENDING);
    }
    else{
        ending_screen(EVERYONE_DEAD_ENDING);
    }
    return true;
}
       
//Tela final do jogo
void Engine::ending_screen(int ending){
    
    tgui::Theme theme{"./Black.txt"};
    bool stay = true;
    tgui::String text, description, screen;

    if (ending == KILL_THE_KILLER_ENDING){
        text = "Parabens, você matou o assassino!";    
        description = "\n Com o projeto final entregue e nenhum assassino á solta,\n sinta-se livre para aproveitar suas férias da melhor forma possível.";
        screen = "beachcapy.jpeg";
    }
    else if (ending == KILLER_WIN_ENDING){
        text = "Parabens, você matou os alunos da Computação e ainda não foi pego!";    
        description = "\n Com o fim do semestre e sem nenhum aluno da computação para te infernizar,\n aproveite as suas férias livre de CCP's!";
        screen = "killercapyend.jpeg";
    }
    else if (ending == EVERYONE_DEAD_ENDING){
        text = "Infelizmente, todos os alunos da Computação foram mortos! :(";    
        description = "\n Mas junto com eles, o assassino também se foi! :) ";
        screen = "everyonedies.jpeg";
    }
    else if (ending == END_OF_SEMESTER_ENDING){
        text = " O semestre acabou, nenhum assassino foi descoberto, mas alguns alunos sobreviveram";    
        description = "\n Aproveite suas férias e volte bem para o próximo semestre,\n mas cuidado! \nNunca se sabe quando o CCPânico poderá ser reiniciado!!\n";
        for (int i = 0; i < players.size(); i++){
            if (Dice::single_die(200) < players[i]->getProjectBar() + players[i]->getStudyBar()){
                description += "\n" + players[i]->getName() + " passou de ano!";
            }
            else{
                description += "\n" + players[i]->getName() + " reprovou!";
            }
        }
        screen = "endofsemesterend.jpeg";
    }

    // Imagem de fundo
    auto endingScreenBackground = tgui::Picture::create(screen);
    endingScreenBackground->setSize({"100%", "100%"});
    gui.add(endingScreenBackground);

    //Mensagem do título
    auto endingText = tgui::TextArea::create();
    endingText->setRenderer(theme.getRenderer("TextArea"));
    endingText->setMaximumCharacters(0);
    endingText->setPosition(240,30);
    endingText->setSize(340, 40);
    endingText->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    endingText->setTextSize(15);
    endingText->setReadOnly(true);
    endingText->setText(text);
    gui.add(endingText);

    //Descricao da tela
    auto endingDescription = tgui::TextArea::create();
    endingDescription->setRenderer(theme.getRenderer("TextArea"));
    endingDescription->setMaximumCharacters(0);
    endingDescription->setPosition(255,400);
    endingDescription->setSize(290, 115);
    endingDescription->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    endingDescription->setText(description);
    endingDescription->setTextSize(15);
    endingDescription->setReadOnly(true);
    gui.add(endingDescription);

    while(stay) {
        sf::Event final_screen;
        while(window.pollEvent(final_screen)) {
            gui.handleEvent(final_screen);
            if(final_screen.type == sf::Event::Closed) {
                horrorgame.~Music();
                window.close();
                exit(0);
            }
        }
        window.clear();
        gui.draw();
        window.display();
    }
    gui.removeAllWidgets();
}

void Engine::instantiatePlaces(){
    places.push_back(new Place("CCE", "./cce.jpg"));
    places[0]->setBonus(ACTION_WORK_ON_PROJECT, 20);
    places[0]->setBonus(ACTION_STUDY, 15);
    places.push_back(new Place("DCE", "./dce.jpg"));
    places[1]->setBonus(ACTION_WORK_ON_PROJECT, -10);
    places[1]->setBonus(ACTION_STUDY, -15);
    places.push_back(new Place("PVA", "./pva.jpg"));
    places[2]->setBonus(ACTION_STUDY, 10);
    places.push_back(new Place("PVB", "./pvb.jpeg"));
    places[3]->setBonus(ACTION_STUDY, 10);
    places.push_back(new Place("Rita", "./rita.jpeg"));
    places[4]->setBonus(ACTION_WORK_ON_PROJECT, -20);
    places[4]->setBonus(ACTION_STUDY, -20);
    places.push_back(new Place("RU", "./RU.jpg"));
    places[5]->setBonus(ACTION_WORK_ON_PROJECT, -20);
    places[5]->setBonus(ACTION_STUDY, -15);
}

int Engine::getTime(){
    return game_time;
}
