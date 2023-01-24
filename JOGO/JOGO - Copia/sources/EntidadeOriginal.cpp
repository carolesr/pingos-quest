#include "../includes/EntidadeOriginal.h"

EntidadeOriginal::EntidadeOriginal(int _x, int _y):
Ponto(_x, _y){}

EntidadeOriginal::~EntidadeOriginal(){ sprite = NULL; }

void EntidadeOriginal::set_sprite(ALLEGRO_BITMAP* s)
{
    sprite = s;
}
