#include "../includes/ChefaoPrimario.h"
#include <iostream>
using namespace std;

ChefaoPrimario::ChefaoPrimario( int _x, int _y, Jogador* j1, Jogador* j2 ):
    Chefao(  0, _x, _y, 29.6, 35, 3, 0, 1.2  )
{
    jogador1 = j1;
    jogador2 = j2;

    vidas = 5;

    xm = 0;

    sprite = al_load_bitmap("imagens/papai_noel.png");

}
ChefaoPrimario::~ChefaoPrimario()
{
    al_destroy_bitmap(sprite);
}

void ChefaoPrimario::mover()
{
    if(++frameCount >= frameDelay)
    {
        if(++curFrame >= maxFrame)
        {
            curFrame = 0;
        }
        frameCount = 0;
    }

    distancia1 = abs( x - jogador1->get_x() ); //pegando as distancias entre o inimigo e cada jogador
    distancia2 = abs( x - jogador2->get_x() );

    if(!morreu)
    {

        if( distancia1 <= distancia2 )///FAZER O PINGUIM PERSEGUIR O JOGADOR1
        {
            if( jogador1->get_x() < x && x <= SCREEN_W )//pinguim vai para a esquerda
            {
                x-= 7;
                esquerda = 1;
            }
            else if( jogador1->get_x() > x && x >= 0 )//pinguim vai para a direita
            {
                x+= 7;
                esquerda = 0;
            }
        }

        else if( distancia2 < distancia1 )///PERSEGUINDO O JOGADOR2
        {
            if( jogador2->get_x() < x && x >= SCREEN_W )//pinguim vai para a esquerda
            {
                x-= 10;
                esquerda = 1;
            }
            else if( jogador2->get_x() > x && x <= 0 )//pinguim vai para a direita
            {
                x-= 10;
                esquerda = 0;
            }
        }

        if(x <= 0)
        {
            esquerda = 0;
            x = 5;
        }
        if(x >= SCREEN_W)
        {
            esquerda = 1;
            x = SCREEN_W - 5;
        }

        al_draw_tinted_scaled_rotated_bitmap_region( sprite, curFrame*frameWidth, linha*frameHeight, frameWidth, frameHeight, al_map_rgb(255, 255, 255), frameWidth/2, frameHeight/2, x, y, escala, escala, 0, esquerda);

    }

    if(morreu)
    {
        set_gravidade(10);
    }

}

int ChefaoPrimario::get_vidas()
{
    return vidas;
}

ChefaoPrimario& ChefaoPrimario::operator--(int)
{
    vidas--;
    cout << "vidas:" << vidas << endl;
    return *this;
}

ChefaoPrimario& ChefaoPrimario::operator++(int)
{
    vidas++;
    cout << "vidas:" << vidas << endl;
    return *this;
}

void ChefaoPrimario::set_xm(int x)
{
    xm = x;
}

int ChefaoPrimario::get_xm()
{
    return xm;
}

