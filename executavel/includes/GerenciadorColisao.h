#pragma once
#include "Fundo.h"
#include "Plataforma.h"
#include "Lista.h"
#include "ListaJogador.h"
#include "ListaPersonagem.h"
#include "ListaItem.h"
#include "Pinguim.h"
#include "PinguimRei.h"
#include "Peixinho.h"
#include "Passaro.h"
#include "Ursinho.h"
#include "ChefaoPrimario.h"
using namespace std;

#define PRESENTES 100
#define GORES 150


class Dados
{
public:
    int x;
    int y;
    int vivo;
};

class GerenciadorColisao
{
private:
    ListaJogador listaJogadores;
    ListaItem listaItens;
    ListaPersonagem listaPersonagens;
    Lista <Plataforma*> listaPlataformas;
    ChefaoPrimario* chefao;
    int distancia1, distancia2, diferenca1, diferenca2, diferenca3, diferenca4;
    int x1, x2, x3, y1, y2, y3;
    Fundo *fundo;

public:

    GerenciadorColisao();
    ~GerenciadorColisao();

    void adicionaJogador(Jogador* j);
    void adicionaPersonagem(Personagem *p);
    void adicionaItem(Item* it);
    void adicionaPlataforma(Plataforma* plat);
    void adicionaChefao(ChefaoPrimario* c);

    void verificaColisaoPersonagens(int* pontos, Dados* inimigos);//compara as fronteiras do personagem com as dos objetos
    void verificaColisaoItem(int* pontos);
    void verificaColisaoPlataformas();
	void verificaColisaoChefao();

};

