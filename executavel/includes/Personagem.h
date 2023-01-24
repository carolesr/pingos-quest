#pragma once
#include "EntidadeOriginal.h"
using namespace std;

#define FPS 15//ERA 60, FPS = FRAMES POR SEGUNDO
#define SCREEN_W 800//LARGURA DA TELA, original = 640
#define SCREEN_H 600//ALTURA DA TELA, original - 480

class Personagem: public EntidadeOriginal
{
protected:
    bool vivo, morreu;
    int vidas;
    int bolas;
    int maxFrame;//númeto de frames por loop
    int curFrame;//usar depois
    int frameCount;//frame atual
    int frameDelay;
    int frameWidth;//tamanho de um ursinho
    int frameHeight;
    int velocidade;
    int esquerda;
    int linha;
    float escala;
    int pode_mover[2];
    int gravidade;
public:
    Personagem( int _frameWidth = 32, int _frameHeight = 32 , int _x = 10, int _y = SCREEN_H-SCREEN_H/4.525, int _maxFrame = 3, int _linha = 2, float _escala = 1.1 );
    virtual ~Personagem();

	bool get_vivo();
	void set_vivo( bool _vivo );

	int get_morreu();
    void morrer();

    int get_pode_mover( int i );
    void set_pode_mover( int pos, int i );

    int get_frameWidth();
    int get_frameHeight();

    int get_escala();

    void aumenta_bolas();
    void reduz_bolas();
    int get_bolas();
    void set_bolas(int _bolas);

    void cair();

    void set_gravidade(int g);

};
