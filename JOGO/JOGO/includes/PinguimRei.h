#pragma once
#include "Andador.h"
#include "Jogador.h"
#include "math.h"

class PinguimRei:public Andador
{
private:
    Jogador *jogador1, *jogador2;
    int distancia1, distancia2;
public:
    PinguimRei( int _x = SCREEN_W/2 , int _y = SCREEN_H/2, Jogador* j1 = NULL, Jogador* j2 = NULL );
    ~PinguimRei();

    void mover();
};
