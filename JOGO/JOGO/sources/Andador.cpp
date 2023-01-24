#include "../includes/Andador.h"

enum f
{
    d, e
};

Andador::Andador( int _linha, int _x, int _y, int _frameWidth, int _frameHeight, int _maxFrame, int _passos, float _escala ):
Inimigo(linha, _x, _y, _frameWidth, _frameHeight, _maxFrame, _passos, _escala)
{
    vivo = 1;
    linha = _linha;
    x_min = _x - _passos;
    x_max = _x + _passos;

    frameWidth = _frameWidth;
    frameHeight = _frameHeight;
    passos = _passos;
    escala = _escala;

    curFrame = 0;
    frameCount = 0;
    frameDelay = 2;
    velocidade = 5;
    esquerda = 0;
    n_passos = 0;
    //cair = 0;


}
Andador::~Andador() {}

void Andador::mover()
{
    if(++frameCount >= frameDelay)
    {
        if(++curFrame >= maxFrame)
        {
            curFrame = 0;
        }
        frameCount = 0;
    }

    if( vivo )
    {
        if( y == SCREEN_H )//se o personagem está lá em baixo da tela temos um problema
        {
            vivo = 0;
            x = 1000;//para ter certeza que o jogador não vai ficar batendo neles
            y = 1000;
        }
        else
        {
            if( x <= x_min )
                esquerda = 0;

            if( x >= x_max )
                esquerda = 1;

            if( (!esquerda) && (pode_mover[d]) )
                x += 3;

            if( (esquerda) && (pode_mover[e])  )
                x -= 3;

            y += gravidade;
            //al_draw_bitmap_region(sprite, curFrame*frameWidth, linha*frameHeight, frameWidth, frameHeight, x, y, esquerda);
            al_draw_tinted_scaled_rotated_bitmap_region( sprite, curFrame*frameWidth, linha*frameHeight, frameWidth, frameHeight, al_map_rgb(255, 255, 255), frameWidth/2, frameHeight/2, x, y, escala, escala, 0, esquerda);

        }
    }

}

