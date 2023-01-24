#pragma once
#include "Entidade.h"

class Item: public Entidade//todos os itens são Entidades colecionaveis
{
private:
    int obj_existe;
public:

    Item(int _x = SCREEN_W/2, int _y = SCREEN_H/2, float e = 1, int a = 44, int l = 44, int _linhas = 0, int _colunas = 0);

    ~Item();

    void imprime();

    void set_obj_existe(int obj_e);

};
