
#include "../includes/Fundo.h"

Fundo::Fundo( int a, int l )
{
    altura = a;
    largura = l;
    chao = SCREEN_H - SCREEN_H/4.545;
}
Fundo::~Fundo() {}

void Fundo::imprimeFundo()
{
    //agora apenas imprimimos o fundo
    al_draw_scaled_bitmap(fundo, 0, 0, 800, 600, 0, 0, SCREEN_W, SCREEN_H, 0);//Os outros são onde vc qer desenhar a imagem, e o novo tamanho
}

void Fundo::setFundo(ALLEGRO_BITMAP* _fundo){ fundo = _fundo; }

void Fundo::set_chao( int n_chao ){ chao = n_chao; }
int Fundo::get_chao(){ return(chao); }
