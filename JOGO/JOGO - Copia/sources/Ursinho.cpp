#include "../includes/Ursinho.h"

Ursinho::Ursinho( int _x, int _y, int _passos ):
Andador( 2, _x, _y, 32 , 32 , 3 , 20, 0.8 )
{
    sprite = al_load_bitmap("imagens/beer1_sheet_sprite.png");
}
Ursinho::~Ursinho(){}
