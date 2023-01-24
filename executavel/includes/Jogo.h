#pragma once
#include "Fase1.h"
#include "Fase2.h"
#include "Fase3.h"
#include "FaseFinal.h"
#include "MenuFases.h"
#include "Menu.h"
#include "MenuPausa.h"
#include "FelizNatal.h"
#include "SemSaida.h"
#include <stdexcept>


class Salvacao
{
public:
    Dados inimigos[20];
    Dados gores[10];

    int x_jogador1;
    int x_jogador2;

    int y_jogador1;
    int y_jogador2;

    int vidas_jogador1;
    int vidas_jogador2;

    int n_gores;
    int pontos;
    int fase;

    int morreu;//para o chefão da terceira fase
};


class Jogo//criando a classe jogo que será instanciada na minha main
{
private:
    Salvacao salvacao;

    MenuFases menu_das_fases;
    Menu menu_principal;
    MenuPausa menu_da_pausa;
    FelizNatal feliz_natal;
    SemSaida sem_saida;
    int no_menu_principal;
    int no_menu_das_fases;
    int no_menu_da_pausa;
    int opcao, opcao_da_pausa, opcao_natal;

    ALLEGRO_FONT *fonte;
    ALLEGRO_FONT *fonteH;
    ALLEGRO_FONT *fonteT;
    HighScore seta;

    int i, gores, vidas, escreveu, pontos;
    Teclado* teclado;
    int fase;
    Fase1* fase1;
    Fase2* fase2;
    Fase3* fase3;
    FaseFinal* fasefinal;
    Jogador* jogador1;
    Jogador* jogador2;
public:
    Jogo();
    Jogo( Teclado* tec );
    ~Jogo();

    ///FUNÇÃO QUE IMPRIME OS HIGH SCORES
    void apresenta_high_scores(ALLEGRO_EVENT *ev);

    ///FUNÇÕES QUE GERENCIAM OS MENUS
    int get_no_menu_principal();
    int get_no_menu_das_fases();
    int get_no_menu_da_pausa();
    void cuida_do_menu_principal( ALLEGRO_EVENT *ev );
    void cuida_do_menu_das_fases( ALLEGRO_EVENT *ev );
    void cuida_do_menu_da_pausa( ALLEGRO_EVENT *ev );
    void seleciona_opcao_correta_do_menu_principal( ALLEGRO_EVENT *ev  );

    ///FUNÇÕES QUE GERENCIAM AS FASES
    void inicializa_a_fase_escolhida();
    void efeito_domino_das_fases(ALLEGRO_EVENT *ev);

    ///FUNÇÃO PARA RESETAR O JOGO
    void reseta();

    ///FUNÇÃO PARA SALVAR A FASE
    void salva();

    ///PARA JOGAR O JOGO SALVO
    void carrega();

    Jogo &operator=( const Jogo &joguinho )
    {

        gores = joguinho.gores;
        pontos = joguinho.pontos;
        fase = joguinho.fase;
        fase1 = joguinho.fase1;
        fase2 = joguinho.fase2;
        jogador1 = joguinho.jogador1;
        jogador2 = joguinho.jogador2;

        return *this;

    }

};
