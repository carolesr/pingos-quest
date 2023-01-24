#pragma once
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Teclado.h"

#define SCREEN_W 800
#define SCREEN_H 600

class FelizNatal
{
private:
    ALLEGRO_FONT *fonte;
    ALLEGRO_FONT *fonteT;
    ALLEGRO_FONT *fonteC;
    ALLEGRO_AUDIO_STREAM *musica;
public:
    FelizNatal();
    ~FelizNatal();

    int imprimeFelizNatal( Teclado* tec );

};
