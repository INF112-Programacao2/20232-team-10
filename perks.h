#ifndef PERKS_H
#define PERKS_H
#include <string>
#include <vector>
#include "actions.h"

//Classe destinada ao gerenciamento das perks
class Perk{
    private:
        tgui::String nome;
        tgui::String descricao;
        int id;
    public::
        tgui::String get_nome();
        tgui::String get_descricao();
        int get_id();
        Perk(tgui::String nome, tgui::String descricao, int id);
        virtual void onAdd();


};
#endif