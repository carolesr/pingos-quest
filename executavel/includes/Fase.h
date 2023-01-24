#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Jogador.h"
#include "Ursinho.h"
#include "Peixinho.h"
#include "Passaro.h"
#include "Pinguim.h"
#include "PinguimRei.h"
#include "GerenciadorColisao.h"
#include "Fundo.h"
#include "Teclado.h"
#include "PlataformaPedras.h"
#include "PlataformaGelo.h"
#include "Plataforma.h"
#include "PlataformaMadeira.h"
#include "ChefaoPrimario.h"
#include "ChefaoSecundario.h"


#define FPS 15//ERA 60, FPS = FRAMES POR SEGUNDO
#define SCREEN_W 800//LARGURA DA TELA, original = 640
#define SCREEN_H 600//ALTURA DA TELA, original - 480

class Fase
{
protected:
    Teclado* teclado;
    int *menu;
    int fases[3];
    int vidas;
    int gores;
public:
    Dados inimigos[7];
    Dados coisas_vermelhas[3];

    Fase();
    virtual ~Fase();
    int get_vidas();
    int get_gores();
};
