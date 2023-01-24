#include "../includes/PlataformaPedras.h"


PlataformaPedras::PlataformaPedras( int _x, int _y ):
Plataforma( _x , _y, 0.4, 80, 80, 1, 6 )
{
    sprite = al_load_bitmap("imagens/tiles.png");
}

PlataformaPedras::~PlataformaPedras(){}
