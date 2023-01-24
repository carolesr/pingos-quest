#pragma once
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Teclado.h"

#define SCREEN_W 800
#define SCREEN_H 600

//Precisamos fazer o menu conseguir pegar os comandos do teclado, e baseado nisso, mover a seta

class Menu
{
private:
    ALLEGRO_FONT *fonte;
    ALLEGRO_FONT *fonteT;
    ALLEGRO_FONT *fonteC;
    ALLEGRO_AUDIO_STREAM *musica;
public:
    Menu();
    ~Menu();

    int imprimeMenu( Teclado* tec, int* opcoes );

};
