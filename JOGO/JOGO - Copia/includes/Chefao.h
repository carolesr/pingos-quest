#pragma once
#include "Inimigo.h"

class Chefao: public Inimigo
{
protected:
    int n_passos;
    //int vidas;

public:
    Chefao(int _linha = 2, int _x = SCREEN_W/8, int _y = SCREEN_H - SCREEN_H/4.68, int _frameWidth = 32,
                     int _frameHeight = 32, int _maxFrame = 3, int _passos = 30, float _escala = 1, int _n_passos = 0/*, int _vidas = 5*/);
    ~Chefao();
    virtual void mover();

};
