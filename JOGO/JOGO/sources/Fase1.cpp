#include "../includes/Fase1.h"

Fase1::~Fase1()
{
    //cuidado com o que você destrói!
    al_destroy_font(font);
    al_destroy_bitmap(fundo);
    al_destroy_audio_stream(musica1);

    for( int i = 0 ; i < 22 ; i++ )
        delete(plataformas[i]);

    for( int i = 0 ; i < 6 ; i++ )
        delete(pinguins[i]);

    delete king;

    for( int i = 0 ; i < 3 ; i++ )
        delete(item[i]);

    //menu = NULL;
    fundo = NULL;
    heart = NULL;
    gore = NULL;
    font = NULL;
}


Fase1::Fase1( Teclado* tec, Jogador* _jogador1, Jogador* _jogador2 ):
    mapa1( 800, 600 ),
    item1( 30, 30, 1, 44, 44, 0, 0),
    item2( 100, 30, 1.1, 40, 40, 0, 0 )
{
    teclado = tec;
    pausado = 0;
    gores = 3;

	///SETANDO AS VIDAS DOS MEUS INIMIGOS
    for( int w = 0 ; w < N_PERSONAGENS_1 ; w++ )
        inimigos[w].vivo = 1;

    ///ATRIBUINDO OS JOGADORES
    jogador1 = _jogador1;
    jogador2 = _jogador2;

    chama_jogador2 = 0;//inicialmente o jogador não aparece, apenas se apertarmos F9
    jogador2->zera_vidas();


    item[0] = new Item( 3*SCREEN_W/5, 4*SCREEN_H/7, 0.4, 40, 40, 0, 0 ),
    item[1] = new Item( 4*SCREEN_W/5, 4*SCREEN_H/7, 0.4, 40, 40, 0, 0 ),
    item[2] = new Item( 100, 180, 0.4, 40, 40, 0, 0 );

    pinguins[0] = new Pinguim( 400, 529.4, 10 );
    pinguins[1] = new Pinguim( 133, 529.4, 30 );
    pinguins[2] = new Pinguim( 133, 529.4, 60 );
    pinguins[3] = new Pinguim( 291, 245, 20 );
    pinguins[4] = new Pinguim( 550, 195, 10 );
    pinguins[5] = new Pinguim( 600, 529.4, 30 );
    king = new PinguimRei(300, 245, jogador1, jogador2);

    plataformas[0] = new PlataformaPedras(1*SCREEN_W/5, SCREEN_H-SCREEN_H/4.3);
    plataformas[1] = new PlataformaPedras(1.5*SCREEN_W/5, SCREEN_H-SCREEN_H/4.3);
    plataformas[2] = new PlataformaPedras(350, SCREEN_H-SCREEN_H/8);
    plataformas[3] = new PlataformaPedras(2*SCREEN_W/5, SCREEN_H-SCREEN_H/2.6);
    plataformas[4] = new PlataformaPedras(3*SCREEN_W/5, SCREEN_H-SCREEN_H/2.6);
    plataformas[5] = new PlataformaPedras(4*SCREEN_W/5, SCREEN_H-SCREEN_H/2.6);
    plataformas[6] = new PlataformaPedras(1*SCREEN_W/5, SCREEN_H-SCREEN_H/2.6);
    for( i = 7 ; i < 12 ; i++ )
        plataformas[i] = new PlataformaPedras( 15+32*(i-8), 220 );
    for( i = 12 ; i < 20 ; i++ )
        plataformas[i] = new PlataformaPedras( 95+32*(i-8), 270 );
    for( i = 20 ; i < 22 ; i++ )
        plataformas[i] = new PlataformaPedras( 550+32*(i-20), 220 );

    ///carregando as fontes
    font = al_load_ttf_font("fonte.ttf", 30, 0 );//TEMOS A VARIÁVEL FONTE E ESTAMOS CARREGANDO A FONTE NESSE PONTEIRO

    ///carregando minhas musicas
    musica1 = al_load_audio_stream("fase1_cortada.ogg", 4, 1024);
    if ( !musica1 )
        cout << "erro ao carregar a musica" << endl;
    //liga o stream no mixer
    al_attach_audio_stream_to_mixer(musica1, al_get_default_mixer());
    //define que o stream vai tocar no modo repeat
    al_set_audio_stream_playmode(musica1, ALLEGRO_PLAYMODE_LOOP);

    ///setando as imagens
    fundo = al_load_bitmap("imagens/fundo_1.png");
    if( !fundo )
        cout << "As imagens não esto sendo carregadas corretamente" << endl;

    heart = al_load_bitmap("imagens/heart.png");
    gore = al_load_bitmap("imagens/gore.png");

    ///colocando as imagens nos personagems
    mapa1.setFundo(fundo);
    item1.set_sprite(heart);
    item2.set_sprite(gore);
    item[0]->set_sprite(gore);
    item[1]->set_sprite(gore);
    item[2]->set_sprite(gore);

    ///incluindo os objetos na lista de colisões
    p[0] = static_cast<Personagem*>(pinguins[0]);
    p[1] = static_cast<Personagem*>(pinguins[1]);
    p[2] = static_cast<Personagem*>(pinguins[2]);
    p[3] = static_cast<Personagem*>(pinguins[3]);
    p[4] = static_cast<Personagem*>(pinguins[4]);
    p[5] = static_cast<Personagem*>(pinguins[5]);
    p[6] = static_cast<Personagem*>(king);


    obj_colisoes.adicionaJogador(jogador1);
    obj_colisoes.adicionaJogador(jogador2);

    obj_colisoes.adicionaPersonagem(p[0]);
    obj_colisoes.adicionaPersonagem(p[1]);
    obj_colisoes.adicionaPersonagem(p[2]);
    obj_colisoes.adicionaPersonagem(p[3]);
    obj_colisoes.adicionaPersonagem(p[4]);
    obj_colisoes.adicionaPersonagem(p[5]);
    obj_colisoes.adicionaPersonagem(p[6]);

    obj_colisoes.adicionaItem(&item1);
    obj_colisoes.adicionaItem(&item2);
    obj_colisoes.adicionaItem(item[0]);
    obj_colisoes.adicionaItem(item[1]);
    obj_colisoes.adicionaItem(item[2]);

    for( i = 0 ; i < 22 ; i++ )
        obj_colisoes.adicionaPlataforma(plataformas[i]);
}




void Fase1::executa( int* fases, int* pontos, int* no_menu_da_pausa )
{
    ///CASO O/OS JOGADORES MORRAM
    if( jogador1->get_vidas() + jogador2->get_vidas() <= 0 )
    {
        al_clear_to_color( al_map_rgb( 255, 255, 255 ));
        al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "Hmmm... At least you doesn't have to buy a suit :)");
        al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W/2, 550, ALLEGRO_ALIGN_CENTRE, "Press SPACE to continue");

        if( teclado->teclas[teclado->KEY_SPACE] )
        {
            teclado->teclas[teclado->KEY_SPACE] = 0;
            *fases = 9;
        }

    }
    else
    {
        ///VERIFICANDO AS COLISÔES
        obj_colisoes.verificaColisaoPersonagens(pontos, inimigos);
        obj_colisoes.verificaColisaoItem(pontos);
        obj_colisoes.verificaColisaoPlataformas();

        ///DESENHANDO O FUNDO
        mapa1.imprimeFundo();

        ///IMPRIMINDO OBJETOS
        for( i = 0 ; i < 22; i++ )
            plataformas[i]->imprime();

        item1.imprime();//coracao das vidas
        item2.imprime();//gore principal

        for( i = 0 ; i < 3 ; i++ )
            item[i]->imprime();

        ///AQUI ESTOU SALVANDO NO VETOR DE INIMIGOS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        ///UM JEITO DE SALVAR O X E O Y DOS PERSONAGENS DE UMA FOR ESTÁTICA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        for( int w = 0 ; w < N_PERSONAGENS_1 ; w++ )//aqui estava p[0] mudei para p[w]
        {
            inimigos[w].x = p[w]->get_x();
            inimigos[w].y = p[w]->get_y();
        }

        for( int w = 0 ; w < 3 ; w++ )//Temos 3 gores
        {
            coisas_vermelhas[w].x = item[w]->get_x();//pegar as posições dos gores
            coisas_vermelhas[w].y = item[w]->get_y();
        }


        ///MOVENDO OS PERSONAGENS
        jogador1->mover( teclado );

        if( chama_jogador2 )//se o jogador 1 existe
            jogador2->mover( teclado );///A PARTIR DE AGORA O JOGADOR 2 SEMPRE VAI EXIRTIR
        else if( chama_jogador2 == 0 && jogador1->get_vidas() >= 1 )//se temos apenas um jogador, zeramos as vidas dele
            jogador2->zera_vidas();

        for( int i = 0 ; i < 6 ; i++ )
            pinguins[i]->mover();

        king->mover();

        //krampus[0]->mover();

    }


    ///verificando se o jogador apertou F9
    if( teclado->teclas[teclado->KEY_F9] )//apertou F9
    {
        if( chama_jogador2 == 0 )//quero fazer o jogador 2 aparecer
        {
            chama_jogador2 = 1;
            jogador2->set_vidas( jogador1->get_vidas() );//ele vai sempre começar com 3 vidas

        }
        else if( chama_jogador2 == 1 )//quero fazer o jogador 2 sumir
        {
            if( jogador1->get_vidas() > 1 )
                jogador1->set_vidas( (jogador1->get_vidas() + jogador2->get_vidas())/2 );
            else
                jogador1->set_vidas(1);
            chama_jogador2 = 0;
            jogador2->set_x(5);
            jogador2->set_y( jogador2->get_chao() );
        }
        teclado->teclas[7] = 0;
    }

    ///verificando se o jogador apertou P para pausar o jogo
    if( teclado->teclas[teclado->KEY_P] )//apertou P
    {
        *no_menu_da_pausa = 1;
        teclado->teclas[8] = 0;//"desapertando" a tecla para que o jogador possa apertar ela movamente
    }

    /// TOCANDO A MUSICA
    //al_set_audio_stream_playing(musica1, true);


    ///ESCREVENDO COISAS
    al_draw_textf(font, al_map_rgb(255, 255, 255), 30, 12, ALLEGRO_ALIGN_CENTRE, "%d", jogador1->get_vidas() + jogador2->get_vidas());
    al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 12, ALLEGRO_ALIGN_CENTRE, "%d", jogador1->get_bolas() + jogador2->get_bolas());
    al_draw_textf(font, al_map_rgb(255, 255, 255), 750, 12, ALLEGRO_ALIGN_CENTRE, "%d", *pontos);

    ///VERIFICANDO AS FRONTEIRAS DA TELA
    avanca(fases);
    nao_pode_voltar();

    ///DESENHANDO COISAS
    al_flip_display();
}

void Fase1::avanca( int* fases  )//lembrando que funções retornam o que for apenas uma vez
{
    if( jogador1->get_x() >= SCREEN_W || jogador2->get_x() >= SCREEN_W )//consefirmos primeiro o jogaador e depois o jogador 2, se ele existir
        ///se entrou aqui é porque está no canto direito da tela
    {
        if( chama_jogador2 )//se o jogador 2 existe conferimos a posição dele
        {
            if( jogador1->get_bolas()+jogador2->get_bolas() == gores && jogador1->get_x() >= SCREEN_W && jogador2->get_x() >= SCREEN_W )//ambos os jogadores no canto, muda de fase e se tiverem pego todos os gore
                *fases = 2;
            else//se apenas um dos jogadores foi para o canto
            {
                if( jogador1->get_x() >= SCREEN_W )//travando o jogador 1
                    jogador1->set_pode_mover(0, 0);//não pode ir para a direita
                if( jogador2->get_x() >= SCREEN_W )
                    jogador2->set_pode_mover(0, 0);
            }
        }
        else
        {
            if( jogador1->get_bolas() == gores )//se o único pinguim pegou todos os gores
                *fases = 2;
            else
                jogador1->set_pode_mover(0, 0);
        }
    }
}

void Fase1::nao_pode_voltar()
{
    if( jogador1->get_x() <= 0 || jogador2->get_x() <= SCREEN_W )//se os os jogadores qeiserem voltar
    {
        if( jogador1->get_x() <= 0 )//se o jogador1 tenta voltar
            jogador1->set_pode_mover(1, 0);
        if( jogador2->get_x() <= 0 )//se o jogador2 tenta voltar
            jogador2->set_pode_mover(1, 0);
    }
}


void Fase1::cada_um_no_seu_quadrado()
{
    for( int w = 0 ; w < N_PERSONAGENS_1 ; w++ )//colocando os personagens nos seus devidos lugares
    {
        p[w]->set_x(inimigos[w].x);
        p[w]->set_y(inimigos[w].y);
        p[w]->set_vivo(inimigos[w].vivo);
    }

    for( int w = 0 ; w < 3 ; w++ )//colocando os itens nos seus devidos lugares
    {
        item[w]->set_x( coisas_vermelhas[w].x );
        item[w]->set_y( coisas_vermelhas[w].y );
    }
}

int Fase1::get_n_personagens(){ return(N_PERSONAGENS_1); }
