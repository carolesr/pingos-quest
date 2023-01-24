#include "../includes/Inimigo.h"

Inimigo::Inimigo( int _linha, int _x, int _y, int _frameWidth, int _frameHeight, int _maxFrame, int _passos, float _escala ):
Personagem(_frameWidth, _frameHeight, _x,_y, _maxFrame, _linha, _escala )
{
    //passos = _passos;

}

Inimigo::~Inimigo() {}

void Inimigo::mover()
{

}

