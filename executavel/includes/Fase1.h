#include "Fase.h"

#define N_PERSONAGENS_1 7

class Fase1:public Fase
{
private:
    int i, chama_jogador2, pontos, pausado;
    ALLEGRO_AUDIO_STREAM *musica1;
    ALLEGRO_BITMAP *fundo;//REPRESENTA AS IMAGENS
    Fundo mapa1;
    Pinguim* pinguins[10];
    PinguimRei* king;
    PlataformaPedras* plataformas[30];
    Item item1, item2, *item[3];//vamos fazer um vetor de ponteiros para os gores
    ALLEGRO_BITMAP *heart, *gore;
    Personagem* p[7];
    GerenciadorColisao obj_colisoes;
    ALLEGRO_FONT *font;//AQUELA FONTE QUE USAMO

public:
    Jogador* jogador1;
    Jogador* jogador2;

    Fase1( Teclado* tec = NULL, Jogador* jogador1 = NULL, Jogador* jogador2 = NULL );
    ~Fase1();

    ///executando a primeira fase do jogo
    void executa(int* fase, int* pontos, int* no_menu_da_pausa );

    ///retorna um ou zero dizendo se o personagem pode ir para a próxima fase
    void avanca(int* fase);

    ///CASO O JOGADOR TENTE VOLTAR PARA A FASE ANTERIOR
    void nao_pode_voltar();

    ///FAZENDO OS PERSONAGENS RECEBEREM AS POSIÇÕES DO JOGO SALVO
    void cada_um_no_seu_quadrado();

    int get_n_personagens();


};
