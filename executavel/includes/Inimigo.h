#pragma once
#include "Personagem.h"

class Inimigo: public Personagem
{
protected:
    int linha;
    int passos;

public:
    Inimigo( int _linha = 2, int _x = SCREEN_W/8, int _y = SCREEN_H - SCREEN_H/4.68, int _frameWidth = 32,
                     int _frameHeight = 32, int _maxFrame = 3, int _passos = 30, float _escala = 1 );
    virtual ~Inimigo();

    virtual void mover() = 0;
};
