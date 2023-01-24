#pragma once
#include "Plataforma.h"

class PlataformaPedras : public Plataforma
{
public:
    PlataformaPedras( int _x = SCREEN_H/2, int _y = SCREEN_H/2 );
    ~PlataformaPedras();
};
