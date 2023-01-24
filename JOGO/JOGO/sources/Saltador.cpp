#include "../includes/Saltador.h"
#include <iostream>
using namespace std;

enum f
{
    d, e
};

Saltador::Saltador( int _linha, int _x, int _y, int _frameWidth, int _frameHeight, int _maxFrame, int _passos, float _escala, int _pulo, int _dy, int _imprime ):
Inimigo( linha, _x, _y, _frameWidth, _frameHeight, _maxFrame, _passos, _escala )
{
    imprime = 1;
    pulo = 40;
    gravidade = 2;
    dy = 0 ;

    linha = _linha;
    curFrame = 0;
    frameCount = 0;
    frameDelay = 2;
    //velocidade = 5;
}

Saltador::~Saltador(){}

void Saltador::mover()
{
    if(++frameCount >= frameDelay)
    {
        if(++curFrame >= maxFrame)
            curFrame = 0;
        frameCount = 0;
    }

    if( vivo )
    {
        if( y >= SCREEN_H + 30 )//como aumentamos a gravidade quando ele cai, ele sempre vai chegar nessa posição
        {
            vivo = 0;
            x = 1000;
            y = 1000;
        }

        if(y >= SCREEN_H && gravidade!= 10)//pra quando ele estiver morrendo não volte a pular
            dy = - pulo;

        if( y < SCREEN_H )//criando e aumentando nossa gravidade, tirei o !pode pular
            dy += gravidade;

        y += dy;

        if( y >= SCREEN_H )//colidindo com o chão, antes dy == pulo - gravidade
            dy = 0;

        al_draw_tinted_scaled_rotated_bitmap_region( sprite, curFrame*frameWidth, linha*frameHeight, frameWidth, frameHeight, al_map_rgb(255, 255, 255), frameWidth/2, frameHeight/2, x, y, escala, escala, 0, 0);

    }
}
