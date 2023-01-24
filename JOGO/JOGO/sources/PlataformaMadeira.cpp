#include "../includes/PlataformaMadeira.h"


PlataformaMadeira::PlataformaMadeira( int _x, int _y ):
Plataforma( _x , _y, 1.1, 32, 32, 0, 0 )
{
    sprite = al_load_bitmap("imagens/bloco_madeira.png");
}

PlataformaMadeira::~PlataformaMadeira(){}
