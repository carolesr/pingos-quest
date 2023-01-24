#pragma once
#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include "EntidadeOriginal.h"

#define SCREEN_W 800
#define SCREEN_H 600

class Entidade: public EntidadeOriginal
{
protected:
    float escala;
    int altura;
    int largura;
    int linhas;
    int colunas;
public:
    Entidade( int _x = SCREEN_W/2, int _y = SCREEN_H/2, float e = 1, int a = 44, int l = 44, int _linhas = 0, int _colunas = 0 );
    virtual ~Entidade();

    virtual void imprime();

    int get_altura();
    int get_largura();

    int get_escala();
};
