#pragma once
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Teclado.h"

#define SCREEN_W 800
#define SCREEN_H 600

//Precisamos fazer o menu conseguir pegar os comandos do teclado, e baseado nisso, mover a seta

class MenuPausa
{
private:
    ALLEGRO_FONT *fonte;
    ALLEGRO_FONT *fonteT;
    ALLEGRO_FONT *fonteC;
public:
    MenuPausa();
    ~MenuPausa();

    int imprimeMenuPausa( Teclado* tec, int* opcoes_pausa );

};

