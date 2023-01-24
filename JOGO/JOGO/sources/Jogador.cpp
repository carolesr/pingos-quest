#include "../includes/Jogador.h"

Jogador::Jogador( int player )
{
    vidas = 5;// cada jogador começará o jogo com três vidas
    player1 = player;
    y = SCREEN_H - SCREEN_H/8;
    curFrame = 0;
    frameCount = 0;
    frameDelay = 2;
    frameWidth = 32;
    frameHeight = 30;
    x = frameWidth/2;
    esquerda = 0;
    maxFrame = 2;
    dy = 0;
    dx = 0;
    gravidade = 5;
    bolas = 0;
    pulo = 30;
    chao = SCREEN_H - SCREEN_H/7.8;
    chao_atual = chao;

    if(player1)
        sprite = al_load_bitmap("imagens/Sprites-Pinguin.png");
    else if(!player1)
        sprite = al_load_bitmap("imagens/Sprites-Pinguin-roxo.png");
    if( !sprite )
        cout << "problemas com a imagem do jogador!" << endl;
}

Jogador::~Jogador()
{
    //al_destroy_bitmap(sprite);
}

void Jogador::reseta()
{
    vidas = 3;
    y = chao;
    x = 30;
    bolas = 0;
}

void Jogador::mover( Teclado *teclado )
{
    tec = teclado->teclas;

    if( curFrame >= maxFrame )
        curFrame = 0;

    if(player1)
    {
        if( tec[teclado->KEY_UP] )
        {
            if(y >= chao_atual)//if( pode_pular )//só pode pular se não estiver caindo
                dy = - pulo;//vai pulando de 10 em 10
        }
        if( tec[teclado->KEY_RIGHT] )
        {
            if(pode_mover[teclado->DIREITA])
                x += 7;
            esquerda = 0;
            curFrame++;
        }

        else if( tec[teclado->KEY_LEFT] )
        {
            if(pode_mover[teclado->ESQUERDA])
                x += -7;
            esquerda = 1;
            curFrame++;
        }
    }

    else if(!player1)
    {
        if( tec[teclado->KEY_W] )
        {
            if(y >= chao_atual)//if( pode_pular )//só pode pular se não estiver caindo
                dy = - pulo;//vai pulando de 10 em 10
        }
        if( tec[teclado->KEY_D] )
        {
            if(pode_mover[teclado->DIREITA])
                x += 7;
            esquerda = 0;
            curFrame++;
        }

        else if( tec[teclado->KEY_A] )
        {
            if(pode_mover[teclado->ESQUERDA])
                x += -7;
            esquerda = 1;
            curFrame++;
        }
    }



    if( y < chao_atual )//criando e aumentando nossa gravidade, tirei p !pode pular
        dy += gravidade;

    y += dy;

    if( y >= chao_atual )//colidindo com o chão, antes dy == pulo - gravidade
    {
        dy = 0;
        y = chao_atual;//SCREEN_H - SCREEN_H/4.545
    }

    if( dx > 0 )//para qunado o dx zerar
        dx -= gravidade;
    else if( dx < 0 )
        dx += gravidade;

    x += dx;

	if(x <= 0)
        x = 0;

    /*if( player1 )
        sprite = al_load_bitmap("imagens/Sprites-Pinguin.png");
    else
        sprite = al_load_bitmap("imagens/Sprites-Pinguin-roxo.png");*/

    //al_draw_bitmap_region(sprite, curFrame * frameWidth, 0*frameHeight, frameWidth, frameHeight, x, y, esquerda);
    al_draw_tinted_scaled_rotated_bitmap_region( sprite, curFrame * frameWidth, 0*frameHeight, frameWidth, frameHeight, al_map_rgb(255, 255, 255), frameWidth/2, frameHeight/2, x, y, escala, escala, 0, esquerda);
}


void Jogador::set_player( int player ){ player1 = player; }

void Jogador::perde_uma_vida(){ vidas--; }
int Jogador::get_vidas(){ return(vidas); }
void Jogador::adiciona_uma_vida(){ vidas++; }

void Jogador::operator--(){ vidas--; }
void Jogador::zera_vidas(){ vidas = 0; }

void Jogador::set_chao(int n_chao){ chao = n_chao; }

void Jogador::set_chao_atual( int n_chao ){ chao_atual = n_chao; }

void Jogador::set_dy(int n_dy){ dy = n_dy; }

void Jogador::set_dx(int n_dx){ dx += n_dx; }

int Jogador::get_chao(){ return(chao); }
int Jogador::get_chao_atual(){ return(chao_atual); }

void Jogador::vai_pra_direita( int n_dx ){ dx += n_dx; }//só da certo porque é 30!!!
void Jogador::vai_pra_esquerda( int n_dx ){ dx -= n_dx; }

void Jogador::set_vidas( int n_vidas ){ vidas = n_vidas; }
