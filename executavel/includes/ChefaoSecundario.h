#pragma once
#include "Chefao.h"

class ChefaoSecundario: public Chefao
{
    int criado;

public:
    ChefaoSecundario( int _x = SCREEN_W/2 , int _y = SCREEN_H/2, int _passos = 20 );
    ~ChefaoSecundario();

    void criar();
    int get_criado();
};
