#include <string>
#include <vector>
#include "perks.h"
#include "actor.h"
#include "player.h"
#include "actions.h"

//Construtor
Perks::Perks(std::string nome, std::string descricao, int id):
nome(nome),descricao(descricao),id(id);
//Destrutor
 ~Perks(){

 }
//Funções getter's
std::string Perks:: get_nome(){
    return  this->nome;
}
 std::string  Perks::get_descricao(){
    return this->descricao;
 }
int Perks:: get_id(){
    return this->id;
}
 virtual void Perks:: onAdd(){
    //A atualizar
 }