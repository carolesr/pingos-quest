
#include "../includes/Personagem.h"

Personagem::Personagem( int _frameWidth, int _frameHeight, int _x, int _y, int _maxFrame, int _linha, float _escala ):
EntidadeOriginal(_x, _y)
{
    bolas = 0;
    vidas = 1;//padrão, apenas o jogador terá três vidas
    frameWidth = _frameWidth;
    frameHeight = _frameHeight;
    maxFrame = _maxFrame;
    linha = _linha;
    escala = _escala;
    pode_mover[0] = 1;
    pode_mover[1] = 1;
    gravidade = 0;
    vivo = 1;
	morreu = 0;
}
Personagem:: ~Personagem(){ al_destroy_bitmap(sprite); sprite = NULL; }

bool Personagem::get_vivo(){ return(vivo); }

void Personagem::set_vivo( bool _vivo ){ vivo = _vivo; }

int Personagem::get_pode_mover( int i ){ return(pode_mover[i]); }
void Personagem::set_pode_mover( int pos, int i ){ pode_mover[pos] = i; }

int Personagem::get_frameWidth(){ return(frameWidth); }
int Personagem::get_frameHeight(){ return(frameHeight); }

int Personagem::get_escala(){ return(escala); }

void Personagem::aumenta_bolas(){ bolas++; }
void Personagem::reduz_bolas(){ if(bolas)bolas--; }
int Personagem::get_bolas(){ return(bolas); }
void Personagem::set_bolas(int _bolas){ bolas = _bolas; }

void Personagem::cair(){ gravidade = 10; }

int Personagem::get_morreu() { return(morreu); }

void Personagem::set_gravidade(int g) { gravidade = g; }
void Personagem::morrer(){ morreu = 1; }


