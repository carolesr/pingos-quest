#pragma once
#include <iostream>
#include "Teclado.h"
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
using namespace std;

#define SCREEN_W 800
#define SCREEN_H 600
#define JOGADORES 11
///O VETOR PRECISA TER ONZE POSIÇÕES PARA PODERMOS INSERIR A PONTUAÇÃO A SER COMPARADA

class HighScore
{
public:
    char nome[6];//o nome tem 5 caracteres mais o caracter final
    int pontuacao;
};

///SE EU CHAMAR ESSA CLASSE SEI QUE DEVO SALVAR O NOME E A PONTUAÇÃO DO JOGADOR
class FaseFinal
{
public:
    int i, tam, salvo;
    HighScore seta;
    HighScore *aux;
    char str[6];

    FaseFinal();
    ~FaseFinal();
    ALLEGRO_FONT *fonte;
    HighScore highscore[JOGADORES];
    int manipular_entrada(ALLEGRO_EVENT *ev, Teclado* teclado, int* pontos);
    void coloca_em_ordem();
};
