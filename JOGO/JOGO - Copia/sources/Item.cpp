
#include "../includes/Item.h"

Item::Item( int _x, int _y, float e, int a, int l, int _linhas, int _colunas ):
Entidade( _x, _y, e, a, l, _linhas, _colunas )
{
    obj_existe = 1;
}

Item::~Item(){ sprite = NULL; }

void Item::imprime()
{
    if( obj_existe )
        al_draw_tinted_scaled_rotated_bitmap_region( sprite, colunas*largura, linhas*altura, largura, altura, al_map_rgb(255, 255, 255), largura/2, altura/2, x, y, escala, escala, 0, 0);
}

void Item::set_obj_existe(int obj_e)
{
    obj_existe = obj_e;
}
