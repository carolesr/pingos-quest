#pragma once
#include <iostream>
#include <stdio.h>
#include <allegro5/allegro5.h>

using namespace std;

class Teclado
{
private:
    int i, j;
public:
    int teclas[12];

    enum TECLAS//PARA FACILITAR O USO DO VETOR TECLAS
    {
        KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_SPACE, KEY_ESCAPE, KEY_ENTER, KEY_F9, KEY_P, KEY_W, KEY_D, KEY_A
    };

    enum FRONTEIRAS
    {
        DIREITA, ESQUERDA
    };

Teclado();
~Teclado(){}

void verificaTeclado(ALLEGRO_EVENT *ev);//EVENTO: UMA TECLA APERTADA PARA O USUÁRIO

};
