#include "Fase.h"

#define N_PERSONAGENS_3 5

class Fase3: public Fase
{
private:
	int i, chama_jogador2, pontos, pausado;
    ALLEGRO_BITMAP *fundo;//REPRESENTA AS IMAGENS
    Fundo mapa1;
    PlataformaMadeira* plataformas[28];
    Item *item1, *item2, *item3, *item4;
    ALLEGRO_BITMAP *pingo, *pingo2, *heart, *gore;
    GerenciadorColisao obj_colisoes;
    ALLEGRO_FONT *font;//AQUELA FONTE QUE USAMOS
    Jogador* jogador1;
    Jogador* jogador2;
    Ursinho *urso1, *urso2;
    Personagem *p1, *p2, *p3, *p4;
    ChefaoPrimario *noel;
    ChefaoSecundario *noel2, *noel3;
    int chefaoCriado;
    int podeMover;

public:
    Fase3( Teclado* tec = NULL, Jogador* jogador1 = NULL, Jogador* jogador2 = NULL);
    ~Fase3();

    ///executando a terceira fase do jogo
    void executa(int* fase, int* pontos, int* no_menu_da_pausa);

    ///diz se o jogador pode ou não ir para a próxima fase
    void avanca(int* fases);

	///CASO O JOGADOR TENTE VOLTAR PARA A FASE ANTERIOR
    void nao_pode_voltar();

	///FAZENDO OS PERSONAGENS RECEBEREM AS POSIÇÕES DO JOGO SALVO
    void cada_um_no_seu_quadrado();

    int get_n_personagens();

};

