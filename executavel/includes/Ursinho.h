#pragma once
#include "Andador.h"

//A construtora vai recever como parâmetro apenas as coordenadas iniciais e o quanto ele vai andar

class Ursinho: public Andador
{
public:
    Ursinho( int _x = SCREEN_W/2 , int _y = SCREEN_H/2, int _passos = 20 );
    ~Ursinho();
};
