#include "../includes/Fase3.h"

Fase3::~Fase3()///DETONA RALPH
{
    //cuidado com o que você destrói!
    al_destroy_font(font);
    al_destroy_bitmap(fundo);
    //al_destroy_audio_stream(musica1);

    for(i = 0; i < 15; i++)
        delete(plataformas[i]);

    delete urso1;
    delete urso2;

    delete noel;
    if(noel->get_morreu() && !chefaoCriado)
    {
        delete noel2;
        delete noel3;
    }

    teclado = NULL;
    menu = NULL;
    fundo = NULL;
    heart = NULL;
    gore = NULL;
    font = NULL;
}

Fase3::Fase3( Teclado* tec, Jogador* _jogador1, Jogador* _jogador2 ): mapa1( 800, 600 )
{
    teclado = tec;
	pausado = 0;
	gores = 1;//////////////////////////////////////////////////////////


	///SETANDO AS VIDAS DOS MEUS INIMIGOS
    for( int w = 0 ; w < N_PERSONAGENS_3 ; w++ )
        inimigos[w].vivo = 1;

	///ATRIBUINDO OS JOGADORES
    jogador1 = _jogador1;
    jogador2 = _jogador2;

	chama_jogador2 = 0;//iinicialmente o jogador não aparece, apenas se apertarmos F9
    jogador2->zera_vidas();

    //jogador1->set_x(100);

    urso1 = new Ursinho(170, 340, 5);
    urso2 = new Ursinho(620, 340, 5);


    item1 = new Item(30, 30, 1, 44, 44, 0, 0); //Vidas
    item2 = new Item(100, 30, 1.1, 40, 40, 0, 0); //Gores
    item3 = new Item(400, 60, 0.4, 40, 40, 0, 0);
    item4 = new Item(400, 240, 0.6, 40, 40, 0, 0);


    //O comprimento de um bloco é 35!!!!!!!
    plataformas[0] = new PlataformaMadeira(100, 460);
    plataformas[1] = new PlataformaMadeira(250, 460);
    plataformas[2] = new PlataformaMadeira(400, 460);
    plataformas[3] = new PlataformaMadeira(550, 460);
    plataformas[4] = new PlataformaMadeira(700, 460);
    plataformas[5] = new PlataformaMadeira(175, 370);
    plataformas[6] = new PlataformaMadeira(325, 370);
    plataformas[7] = new PlataformaMadeira(475, 370);
    plataformas[8] = new PlataformaMadeira(625, 370);
    plataformas[9] = new PlataformaMadeira(250, 290);
    plataformas[10] = new PlataformaMadeira(400, 290);
    plataformas[11] = new PlataformaMadeira(550, 290);
    plataformas[12] = new PlataformaMadeira(325, 200);
    plataformas[13] = new PlataformaMadeira(475, 200);
    plataformas[14] = new PlataformaMadeira(400, 110);

	 ///carregando as fontes
    font = al_load_ttf_font("fonte.ttf", 30, 0 );//TEMOS A VARIÁVEL FONTE E ESTAMOS CARREGANDO A FONTE NESSE PONTEIRO


	///carregando minhas musicas
    /*musica1 = al_load_audio_stream("fase1_convertida.ogg", 4, 1024);
    if ( !musica1 )
        cout << "erro ao carregar a musica" << endl;
    //liga o stream no mixer
    al_attach_audio_stream_to_mixer(musica1, al_get_default_mixer());
    //define que o stream vai tocar no modo repeat
    al_set_audio_stream_playmode(musica1, ALLEGRO_PLAYMODE_LOOP);*/

    noel = new ChefaoPrimario(600, 530, jogador1, jogador2);
    chefaoCriado = 0;
    podeMover = 0;


    ///setando as imagens
    fundo = al_load_bitmap("imagens/fundo_fabrica3.png");
    if( !fundo )
        cout << "As imagens do fundo da fase2 não estao sendo carregadas corretamente" << endl;

    heart = al_load_bitmap("imagens/heart.png");
    gore = al_load_bitmap("imagens/gore.png");

    ///colocando as imagens nos personagems/jogadores
    mapa1.setFundo(fundo);
    item1->set_sprite(heart);//precisa mesmo adicionar o coração na lista?
    item2->set_sprite(gore);
    item3->set_sprite(gore);
    item4->set_sprite(heart);

    ///incluindo os objetos na lista de colisões

    obj_colisoes.adicionaJogador(jogador1);
    obj_colisoes.adicionaJogador(jogador2);

    p3 = static_cast<Personagem*>(urso1);
    p4 = static_cast<Personagem*>(urso2);
    obj_colisoes.adicionaPersonagem(p3);
    obj_colisoes.adicionaPersonagem(p4);

    obj_colisoes.adicionaChefao(noel);

    obj_colisoes.adicionaItem(item1);
    obj_colisoes.adicionaItem(item2);
    obj_colisoes.adicionaItem(item3);
    obj_colisoes.adicionaItem(item4);

    for(i = 0; i < 15; i++)
        obj_colisoes.adicionaPlataforma(plataformas[i]);

}

void Fase3::executa(int* fase, int* pontos, int* no_menu_da_pausa)
{
	///CASO O/OS JOGADORES MORRAM
	if( jogador1->get_vidas() + jogador2->get_vidas() <= 0 )
    {
        al_clear_to_color( al_map_rgb( 255, 255, 255 ));
        al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "Oops! Seems like heaven got a new penguin :)");
		al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W/2, 550, ALLEGRO_ALIGN_CENTRE, "Press SPACE to continue");
        if( teclado->teclas[teclado->KEY_SPACE] )
        {
            teclado->teclas[teclado->KEY_SPACE] = 0;
            *fase = 9;
        }

    }
    else
    {
        ///VERIFICANDO AS COLISÔES
        obj_colisoes.verificaColisaoPersonagens(pontos, inimigos);
        obj_colisoes.verificaColisaoItem(pontos);
        obj_colisoes.verificaColisaoPlataformas();
        obj_colisoes.verificaColisaoChefao();

		///DESENHANDO O FUNDO
		mapa1.imprimeFundo();

		///IMPRIMINDO OBJETOS
		for(i = 0; i < 15; i++)
			plataformas[i]->imprime();

		item1->imprime();//coracao das vidas
		item2->imprime();
		item3->imprime();
		item4->imprime();

		///MOVENDO O PERSONAGEM
		jogador1->mover( teclado );

		if( chama_jogador2 )//se o jogador 1 existe
			jogador2->mover( teclado );///A PARTIR DE AGORA O JOGADOR 2 SEMPRE VAI EXIRTIR
		else if( chama_jogador2 == 0 && jogador1->get_vidas() >= 1 )//se temos apenas um jogador, zeramos as vidas dele
			jogador2->zera_vidas();

		jogador1->set_chao(SCREEN_H - SCREEN_H/8.2);
		jogador2->set_chao(SCREEN_H - SCREEN_H/8.2);

		urso1->mover();
		urso2->mover();

		noel->mover();

		///SÓ VAMOS CRIAR O CHEFAO2 QUANDO O CHEFAO1 MORRER
		if(noel->get_morreu() && !chefaoCriado)
		{
			noel2 = new ChefaoSecundario(noel->get_xm() +20, 530, 30);
			noel3 = new ChefaoSecundario(noel->get_xm() -20, 530, 30);

			p1 = static_cast<Personagem*>(noel2);
			obj_colisoes.adicionaPersonagem(p1);
			p2 = static_cast<Personagem*>(noel3);
			obj_colisoes.adicionaPersonagem(p2);

			chefaoCriado = 1;
			podeMover = 1;
		}

		if(podeMover)
		{
			noel2->mover();
			noel3->mover();
		}

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
            chama_jogador2 = 0;
            jogador2->set_x(5);
            jogador2->set_y( 200 );
        }
        teclado->teclas[7] = 0;
    }

	///verificando se o jogador apertou P para pausar o jogo
    if( teclado->teclas[teclado->KEY_P] )//apertou P
    {
        *no_menu_da_pausa = 1;
        teclado->teclas[teclado->KEY_P] = 0;//"desapertando" a tecla para que o jogador possa apertar ela movamente
    }

    /// TOCANDO A MUSICA
    //al_set_audio_stream_playing(musica1, false);


    ///ESCREVENDO COISAS
    vidas = jogador1->get_vidas() + jogador2->get_vidas();
    gores = jogador1->get_bolas() + jogador2->get_bolas();
    al_draw_textf(font, al_map_rgb(255, 255, 255), 30, 12, ALLEGRO_ALIGN_CENTRE, "%d", vidas);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 12, ALLEGRO_ALIGN_CENTRE, "%d", gores);


    ///CONFERINDO AS FRONTEIRAS DA TELA
    avanca(fases);
    nao_pode_voltar();

    ///DESENHANDO COISAS
    al_flip_display();
}

void Fase3::avanca(int* fases  )//lembrando que funções retornam o que for apenas uma vez
{
    if( jogador1->get_x() >= SCREEN_W || jogador2->get_x() >= SCREEN_W )//consefirmos primeiro o jogaador e depois o jogador 2, se ele existir
    ///se entrou aqui é porque está no canto direito da tela
    {
        if( chama_jogador2 )//se o jogador 2 existe conferimos a posição dele
        {
            if( jogador1->get_x() >= SCREEN_W && jogador2->get_x() >= SCREEN_W && jogador1->get_bolas()+jogador2->get_bolas() == gores )//ambos os jogadores no canto, muda de fase e se tiverem pego todos os gore
                *fases = 9;
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
                *fases = 9;
            else
                jogador1->set_pode_mover(0, 0);
        }
    }
}

void Fase3::nao_pode_voltar()
{
    if( jogador1->get_x() <= 0 || jogador2->get_x() <= SCREEN_W )//se os os jogadores qeiserem voltar
    {
        if( jogador1->get_x() <= 0 )//se o jogador1 tenta voltar
            jogador1->set_pode_mover(1, 0);
        if( jogador2->get_x() <= 0 )//se o jogador2 tenta voltar
            jogador2->set_pode_mover(1, 0);
    }
}


/*void Fase1::cada_um_no_seu_quadrado()
{
    for( int w = 0 ; w < N_PERSONAGENS ; w++ )//colocando os personagens nos seus devidos lugares
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

int Fase1::get_n_personagens(){ return(N_PERSONAGENS); }*/

