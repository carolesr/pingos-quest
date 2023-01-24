#pragma once
#include "Inimigo.h"

class Andador: public Inimigo
{
protected:
    int linha;
    int passos;
    int n_passos;
    int x_min, x_max;
public:
    Andador( int _linha = 2, int _x = SCREEN_W/8, int _y = SCREEN_H - SCREEN_H/4.68, int _frameWidth = 32, int _frameHeight = 32, int _maxFrame = 3, int _passos = 30, float _escala = 1 );
    virtual ~Andador();

    virtual void mover();
};
