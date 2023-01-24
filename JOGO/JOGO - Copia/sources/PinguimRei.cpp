#include "../includes/PinguimRei.h"
#include <iostream>
using namespace std;

PinguimRei::PinguimRei( int _x, int _y, Jogador* j1, Jogador* j2 ):
    Andador(  0, _x, _y, 61, 63, 3, 0, 0.32  )
{
    jogador1 = j1;
    jogador2 = j2;

    sprite = al_load_bitmap("imagens/chefao.png");

}
PinguimRei::~PinguimRei() {}

void PinguimRei::mover()
{
    if(++frameCount >= frameDelay)
    {
        if(++curFrame >= maxFrame)
        {
            curFrame = 0;
        }
        frameCount = 0;
    }
    distancia1 = abs( x - jogador1->get_x() );
    distancia2 = abs( x - jogador1->get_x() );

    if(!morreu)
    {

        if( distancia1 <= distancia2 )///FAZER O PINGUIM PERSEGUIR O JOGADOR1
        {
            if( jogador1->get_x() < x && x >= 230 )//pinguim vai para a esquerda
            {
                x-= 4;
                esquerda = 1;
            }
            else if( jogador1->get_x() > x && x <= 450 )//pinguim vai para a direita
            {
                x+= 4;
                esquerda = 0;
            }
        }

        else if( distancia2 < distancia1 )///PERSEGUINDO O JOGADOR2
        {
            if( jogador2->get_x() < x && x >= 240 )//pinguim vai para a esquerda
            {
                x-= 4;
                esquerda = 1;
            }
            else if( jogador2->get_x() > x && x <= 310 )//pinguim vai para a direita
            {
                x-= 4;
                esquerda = 0;
            }
        }
    }

    if(morreu)
        y += 9.5;


    al_draw_tinted_scaled_rotated_bitmap_region( sprite, curFrame*frameWidth, linha*frameHeight, frameWidth, frameHeight, al_map_rgb(255, 255, 255), frameWidth/2, frameHeight/2, x, y, escala, escala, 0, esquerda);

}
