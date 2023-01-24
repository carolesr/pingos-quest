#pragma once
#include "Entidade.h"

class Plataforma: public Entidade
{
protected:
    int extremo_esq, extremo_dir, chao;
public:
    Plataforma( int _x = SCREEN_W/2, int _y = SCREEN_H/2, float e = 1, int a = 80, int l = 80, int _linhas = 0, int _colunas = 0 );
    ~Plataforma();

    int get_extremo_esq();
    int get_extremo_dir();
    int get_chao();
    int get_extremo_inferior();
};
