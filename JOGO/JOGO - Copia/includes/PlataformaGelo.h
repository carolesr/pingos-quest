#pragma once
#include "Plataforma.h"

class PlataformaGelo : public Plataforma
{
public:
    PlataformaGelo( int _x = SCREEN_H/2, int _y = SCREEN_H/2 );
    ~PlataformaGelo();
};

