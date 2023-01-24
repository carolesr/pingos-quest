#pragma once
#include "Inimigo.h"

class Saltador: public Inimigo
{
protected:
    int pulo;
    int dy;
    int imprime;

public:
    Saltador( int _linha = 2, int _x = SCREEN_W/8, int _y = SCREEN_H - SCREEN_H/4.68, int _frameWidth = 32, int _frameHeight = 32, int _maxFrame = 3, int _passos = 30, float _escala = 1, int _pulo = 40, int _dy = 0, int imprime = 1 );
    ~Saltador();

    void mover();
};
