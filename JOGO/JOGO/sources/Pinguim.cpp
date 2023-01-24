#include "../includes/Pinguim.h"

Pinguim::Pinguim( int _x , int _y, int _passos ):
Andador( 0, _x, _y, 61, 63, 3, _passos, 0.32 )
{
    sprite = al_load_bitmap("imagens/Sprites_Pinguin.png");
}
Pinguim::~Pinguim()
{

}
