#pragma once
#include "Chefao.h"
#include "Jogador.h"
#include "math.h"

class ChefaoPrimario: public Chefao
{
private:
    Jogador *jogador1, *jogador2;
    int distancia1, distancia2;
    int xm;

public:
    ChefaoPrimario( int _x = SCREEN_W/2 , int _y = SCREEN_H/2, Jogador* j1 = NULL, Jogador* j2 = NULL );
    ~ChefaoPrimario();

    void mover();
    int get_vidas();
    ChefaoPrimario &operator--(int);
    ChefaoPrimario &operator++(int);
    void set_xm(int x);
    int get_xm();
};
