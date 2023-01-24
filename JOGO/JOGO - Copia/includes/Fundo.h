#pragma once
#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>

#define SCREEN_W 800
#define SCREEN_H 600

using namespace std;

class Fundo
{
private:
    ALLEGRO_BITMAP* fundo;
    int largura;
    int altura;
    int x;
    int y;
    int chao;
public:
    Fundo( int a = 800, int l = 1200 );
    ~Fundo();

    void imprimeFundo();

    void setFundo(ALLEGRO_BITMAP* _fundo);

    void set_chao( int n_chao );
    int get_chao();

};
