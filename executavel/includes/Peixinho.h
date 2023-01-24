#pragma once
#include "Saltador.h"

class Peixinho: public Saltador
{
public:
    Peixinho( int _x = SCREEN_W/2 , int _y = SCREEN_H/2 );
    ~Peixinho();
};

