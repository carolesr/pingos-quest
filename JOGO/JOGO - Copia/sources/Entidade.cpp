#include "../includes/Entidade.h"

Entidade::Entidade( int _x, int _y, float e, int a, int l, int _linhas, int _colunas ):
EntidadeOriginal(_x, _y)
{
    escala = e;
    altura = a;
    largura = l;
    linhas = _linhas;
    colunas = _colunas;
}
Entidade:: ~Entidade()
{
    al_destroy_bitmap(sprite);
}

void Entidade::imprime()
{
    al_draw_tinted_scaled_rotated_bitmap_region( sprite, colunas*largura, linhas*altura, largura, altura, al_map_rgb(255, 255, 255), largura/2, altura/2, x, y, escala, escala, 0, 0);
}

int Entidade::get_altura()
{
    return(altura);
}
int Entidade::get_largura()
{
    return(largura);
}

int Entidade::get_escala()
{
    return(escala);
}
