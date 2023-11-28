#ifndef PERKS_H
#define PERKS_H
#include <string>
#include <vector>
#include "actor.h"
#include "player.h"
#include "actions.h"

//Classe destinada ao gerenciamento das perks
class Perks{
    private:
        std::string nome;
        std::string descricao;
        int id;
    public::
        std::string get_nome();
        std::string get_descricao();
        int get_id();
        Perks(std::string nome, std::string descricao, int id);
        ~Perks();
        virtual void onAdd();


};
#endif