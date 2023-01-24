#include "../includes/ChefaoSecundario.h"

ChefaoSecundario::ChefaoSecundario( int _x , int _y, int _passos ):
Chefao( 0, _x, _y, 29.6, 35, 3, _passos, 0.8 )
{
    sprite = al_load_bitmap("imagens/papai_noel.png");

    criado = 0;
}
ChefaoSecundario::~ChefaoSecundario()
{
    al_destroy_bitmap(sprite);
}

void ChefaoSecundario::criar()
{
    criado = 1;
}

int ChefaoSecundario::get_criado()
{
    return criado;
}
