#pragma once
#include "Andador.h"

class Pinguim:public Andador
{
public:
    Pinguim( int _x = SCREEN_W/2 , int _y = SCREEN_H/2, int _passos = 20 );
    ~Pinguim();
};
