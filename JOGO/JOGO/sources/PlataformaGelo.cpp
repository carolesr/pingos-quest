#include "../includes/PlataformaGelo.h"


PlataformaGelo::PlataformaGelo( int _x, int _y ):
Plataforma( _x , _y, 0.1, 350, 370, 0, 0 )
{
    sprite = al_load_bitmap("imagens/bloco3.png");
}

PlataformaGelo::~PlataformaGelo(){}


