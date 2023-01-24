#include "Fase.h"

#define N_PERSONAGENS_2 4

class Fase2: public Fase
{
private:
    int i, chama_jogador2, pontos, pausado;
    ALLEGRO_BITMAP *fundo;//REPRESENTA AS IMAGENS
    ALLEGRO_AUDIO_STREAM *musica1;
    Fundo mapa1;
    PlataformaGelo* plataformas[21];
    Item *item1, *item2, *item3;
    ALLEGRO_BITMAP *pingo, *pingo2, *heart, *gore;
    Peixinho *peixe1, *peixe2;
    Passaro *passaro, *passaro2;
    Personagem* p, *p2, *p3, *p4;
	GerenciadorColisao obj_colisoes;
    ALLEGRO_FONT *font;//AQUELA FONTE QUE USAMOS

public:
	Jogador* jogador1;
    Jogador* jogador2;

    Fase2( Teclado* tec = NULL, Jogador* jogador1 = NULL, Jogador* jogador2 = NULL);
    ~Fase2();

    ///executando a primeira fase do jogo
    void executa( int* fases, int* pontos, int* no_menu_da_pausa );

    ///diz se o jogador pode ou não ir para a próxima fase
    void avanca(int* fases);

	///CASO O JOGADOR TENTE VOLTAR PARA A FASE ANTERIOR
    void nao_pode_voltar();

	///FAZENDO OS PERSONAGENS RECEBEREM AS POSIÇÕES DO JOGO SALVO
    void cada_um_no_seu_quadrado();

	int get_n_personagens();

};
