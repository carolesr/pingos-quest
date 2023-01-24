#pragma once
#include "Personagem.h"
#include "Teclado.h"

class Jogador: public Personagem
{
private:
    int dy;//velocidade do pulo, vertical
    int dx;
    int pulo;//altura máxima de pulo
    int player1;
    int chao;
    int chao_atual;
    int* tec;

public:
    Jogador( int player );

    ~Jogador();

    void reseta();

    void mover( Teclado *teclado );

    void set_player( int player );

    void perde_uma_vida();
    int get_vidas();
    void adiciona_uma_vida();
	void operator--(); ///*****************
    void zera_vidas();
    void set_vidas( int n_vidas );

    void set_chao(int n_chao);
    void set_chao_atual( int n_chao );
    void set_dy(int n_dy);
	void set_dx(int n_dx);

    int get_chao();
    int get_chao_atual();

    void vai_pra_direita(int n_dx = 20 );
    void vai_pra_esquerda(int n_dx = 20 );

};

