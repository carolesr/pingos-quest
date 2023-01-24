#include "../includes/Passaro.h"

Passaro::Passaro( int _x , int _y, int _passos ):
Andador( 0, _x, _y, 48, 48, 3, _passos, 1 )
{
    sprite = al_load_bitmap("imagens/bird1.png");
}
Passaro::~Passaro()
{
}

