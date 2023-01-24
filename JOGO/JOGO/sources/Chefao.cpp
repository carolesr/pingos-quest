#include "../includes/Chefao.h"

enum f
{
    d, e
};

Chefao::Chefao( int _linha, int _x, int _y, int _frameWidth,
int _frameHeight, int _maxFrame, int _passos, float _escala, int _n_passos/*, int _vidas*/ ):
Inimigo(linha, _x, _y, _frameWidth, _frameHeight, _maxFrame, _passos, _escala)
{
    linha = _linha;
    frameWidth = _frameWidth;
    frameHeight = _frameHeight;
    escala = _escala;
    passos = _passos;

    curFrame = 0;
    frameCount = 0;
    frameDelay = 2;
    esquerda = 0;
    n_passos = _n_passos;

}

Chefao::~Chefao(){}

void Chefao::mover()
{

    if(++frameCount >= frameDelay)
    {
        if(++curFrame >= maxFrame)
        {
            curFrame = 0;
        }
        frameCount = 0;
    }

    if( n_passos <= 0 )
        esquerda = 0;

    if( n_passos >= passos )
        esquerda = 1;

    if( (!esquerda) && (pode_mover[d]) )
    {
        x += 5;
        n_passos++;
    }

    if( (esquerda) && (pode_mover[e]) )
    {
        x -= 5;
        n_passos--;
    }

    if(x <= 0 - frameWidth)
    {
        x = SCREEN_W;
    }

    y += gravidade;

    al_draw_tinted_scaled_rotated_bitmap_region( sprite, curFrame*frameWidth, linha*frameHeight, frameWidth, frameHeight, al_map_rgb(255, 255, 255), frameWidth/2, frameHeight/2, x, y, escala, escala, 0, esquerda);

}
