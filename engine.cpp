#include "engine.h"

int triang(int n){
    return (n*n + n) / 2;
}

void Engine::game(){
    for (int t = 0; t < 3; t++){
        for (int i = 0; i < players.size(); i++){
            pass_screen(players[i]);
            playerTurn2(players[i]);
        }
        results();
    }
}

void Engine::pass_screen(Player *player) {

    tgui::Theme theme{"./Black.txt"};

    //Configura a imagem de fundo do menu de espera 
    auto picture = tgui::Picture::create("./capypass.png");
    picture->setSize({"100%", "100%"});
    gui.add(picture);
    bool stay = true;

    //Botao de proximo turno
    auto nextTurnButton = tgui::Button::create();
    nextTurnButton->setRenderer(theme.getRenderer("Button"));
    nextTurnButton->setPosition(200, 230);
    nextTurnButton->setSize(400, 140);
    nextTurnButton->setText("Vez de " + player->getName());
    nextTurnButton->setTextSize(25);
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
    
    //Configura a imagem de fundo do menu principal
    auto picture = tgui::Picture::create("./4pilastrascc.png");
    picture->setSize({"100%", "100%"});
    gui.add(picture);
    bool stay = true;
    
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

    sf::Clock clock;

    int time = 60;

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
    statsArea->setText(player->getName());
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
    tempo->setValue(time);                 //Recebe o valor do clock do turno
    tempo->setMaximum(60);
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
    acao->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
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
        comboBox1->addItem(Action::game_actions[i]->getDescription(), std::to_string(i));
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
    auto healthButton = tgui::Button::create();
    healthButton->setRenderer(theme.getRenderer("Button"));
    healthButton->setPosition(200, 140);
    healthButton->setSize(120, 35);
    healthButton->setText("SAÚDE");
    healthButton->setTextSize(18);
    healthButton->onClick([&]{
        TextArea1->setText("Saúde: " + player->getHealth());
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
            TextArea1->addText(players[i]->getName(false) + '\n');
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
        if (i != player->get_id()){
            comboBox2->addItem(players[i]->getName(), std::to_string(i));
        }
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
    TextArea2->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
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
        if (clock.getElapsedTime() > sf::seconds(0.25)){
            clock.restart();
            time--;
            tempo->setValue(time);
        }
        TextArea2->setVisible(Action::game_actions[comboBox1->getSelectedItemId().toInt()]->isTargeted());
        comboBox2->setVisible(Action::game_actions[comboBox1->getSelectedItemId().toInt()]->isTargeted());

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
    auto picture = tgui::Picture::create("./criacaopersn.jpg");
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

    //Botao de proximo
    auto NextButton = tgui::Button::create();
    NextButton->setPosition(630, 540);
    NextButton->setSize(170, 60);
    NextButton->setText("PRÓXIMO");
    NextButton->setTextSize(20);
    NextButton->onClick([&]{
        if (points >= 0){
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
                window.close();
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
    title->setPosition(320, 20);
    title->setMaximumCharacters(0);
    title->setSize(160, 40);
    title->setText("RESULTADOS");
    title->setTextSize(23);
    title->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(title);

    //Botao de proximo
    auto NextButton = tgui::Button::create();
    NextButton->setPosition(630, 540);
    NextButton->setSize(170, 60);
    NextButton->setText("PRÓXIMO");
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
    info->setText("");
    info->setTextSize(16);
    info->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Automatic);
    gui.add(info);

}

void Engine::results() {
    while (!turn_actions.empty()) {
        turn_actions.front()->execute();
        delete turn_actions.front();
        turn_actions.pop();
    }
}

void Engine::createPlayer(tgui::String name, int atributes[6]){
    Player *player = new Player(name, atributes);
    players.push_back(player);
}
