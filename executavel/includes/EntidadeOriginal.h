#pragma once
#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include "Ponto.h"

class EntidadeOriginal: public Ponto
{
protected:
    ALLEGRO_BITMAP *sprite;

public:
    EntidadeOriginal(int _x, int _y);
    ~EntidadeOriginal();
    void set_sprite(ALLEGRO_BITMAP* s);
};
