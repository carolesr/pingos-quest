#include "../includes/Peixinho.h"

Peixinho::Peixinho( int _x , int _y ):
Saltador(3, _x, _y, 32, 32, 3, 0, 1, 40, 0, 1 )
//Saltador(0, _x, _y, 100, 100, 1, 0, 0.5, 40, 0, 1 ) --> barreto
//Saltador(0, _x, _y, 110, 110, 1, 0, 0.3, 40, 0, 1 ) --> pokebola
{
    sprite = al_load_bitmap("imagens/peixe.png");
    gravidade = 2;
}
Peixinho::~Peixinho()
{
}

