#include <string>
#include <vector>
#include "perks.h"
#include "actor.h"
#include "player.h"
#include "actions.h"

//Construtor

Perk::Perk(tgui::String nome, tgui::String descricao, int id):
nome(nome),descricao(descricao),id(id);

//Funções getter's
tgui::String Perk:: get_nome(){
    return  this->nome;
}
 tgui::String  Perk::get_descricao(){
    return this->descricao;
 }
int Perk:: get_id(){
    return this->id;
}
void Perk:: onAdd(){
    //A atualizar
 }