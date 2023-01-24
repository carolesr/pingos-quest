#pragma once
#include "Andador.h"

class Passaro:public Andador
{
public:
    Passaro( int _x = SCREEN_W/2 , int _y = SCREEN_H/2, int _passos = 20 );
    ~Passaro();
};

