#include "../includes/Fase2.h"

Fase2::~Fase2()///DETONA RALPH
{
    //cuidado com o que você destrói!
    al_destroy_font(font);
    al_destroy_bitmap(fundo);
    //al_destroy_audio_stream(musica1);

    for(i = 0; i < 22; i++)
        delete(plataformas[i]);

    delete item1;
    delete item2;
    delete item3;

    delete peixe1;
    delete peixe2;

    delete passaro;
    delete passaro2;

    teclado = NULL;
    menu = NULL;
    fundo = NULL;
    heart = NULL;
    gore = NULL;
    font = NULL;

}

Fase2::Fase2( Teclado* tec, Jogador* _jogador1, Jogador* _jogador2 ): mapa1( 800, 600 )
{
    gores = 1;
    teclado = tec;
	pausado = 0;

	///SETANDO AS VIDAS DOS MEUS INIMIGOS
	for( int w = 0 ; w < N_PERSONAGENS_2 ; w++ )
        inimigos[w].vivo = 1;

	///ATRIBUINDO OS JOGADORES
    jogador1 = _jogador1;
    jogador2 = _jogador2;

	chama_jogador2 = 0;//iinicialmente o jogador não aparece, apenas se apertarmos F9
    jogador2->zera_vidas();

	item1 = new Item(30, 30, 1, 44, 44, 0, 0); //Vidas
    item2 = new Item(470, 60, 0.4, 40, 40, 0, 0);
    item3 = new Item(100, 30, 1.1, 40, 40, 0, 0); //Gores


	peixe1 = new Peixinho(390, SCREEN_H);
    peixe2 = new Peixinho(510, SCREEN_H);

	passaro = new Passaro(330, 100, 100);
    passaro2 = new Passaro(50, 150, 100);


	///O comprimento de um bloco é 35!!!!!!!
    plataformas[0] = new PlataformaGelo(15, 540);
    plataformas[1] = new PlataformaGelo(50, 540);
    plataformas[2] = new PlataformaGelo(85, 540);
    plataformas[3] = new PlataformaGelo(120, 500);
    plataformas[4] = new PlataformaGelo(180, 400);
    plataformas[5] = new PlataformaGelo(100, 300);
    plataformas[6] = new PlataformaGelo(180, 200);
    plataformas[7] = new PlataformaGelo(290, 140);
    plataformas[8] = new PlataformaGelo(330, 450);
    plataformas[9] = new PlataformaGelo(450, 450);
    plataformas[10] = new PlataformaGelo(570, 450);
    plataformas[11] = new PlataformaGelo(650, 360);
    plataformas[12] = new PlataformaGelo(650, 260);
    plataformas[13] = new PlataformaGelo(650, 160);
    plataformas[14] = new PlataformaGelo(650, 500);
    plataformas[15] = new PlataformaGelo(470, 100);
    plataformas[16] = new PlataformaGelo(505, 100);
    plataformas[17] = new PlataformaGelo(540, 100);
    plataformas[18] = new PlataformaGelo(725, 540);
    plataformas[19] = new PlataformaGelo(750, 540);
    plataformas[20] = new PlataformaGelo(785, 540);

    ///carregando as fontes
    font = al_load_ttf_font("fonte.ttf", 30, 0 );//TEMOS A VARIÁVEL FONTE E ESTAMOS CARREGANDO A FONTE NESSE PONTEIRO

    ///carregando minhas musicas
    //musica1 = al_load_audio_stream("fase1_convertida.ogg", 4, 1024);
    //if ( !musica1 )
        //cout << "erro ao carregar a musica" << endl;
    //liga o stream no mixer
   // al_attach_audio_stream_to_mixer(musica1, al_get_default_mixer());
    //define que o stream vai tocar no modo repeat
    //al_set_audio_stream_playmode(musica1, ALLEGRO_PLAYMODE_LOOP);

    ///setando as imagens
    fundo = al_load_bitmap("imagens/fundo_mar2.png");
    if( !fundo )
        cout << "As imagens do fundo da fase2 não estao sendo carregadas corretamente" << endl;

    heart = al_load_bitmap("imagens/heart.png");
    gore = al_load_bitmap("imagens/gore.png");

    ///colocando as imagens nos personagems
    mapa1.setFundo(fundo);

    item1->set_sprite(heart);
    item2->set_sprite(gore);
    item3->set_sprite(gore);//o gore que queremos pegar

    ///incluindo os objetos na lista de colisões
	p = static_cast<Personagem*>(passaro);
	p2 = static_cast<Personagem*>(passaro2);
	p3 = static_cast<Personagem*>(peixe1);
	p4 = static_cast<Personagem*>(peixe2);

    obj_colisoes.adicionaJogador(jogador1);
    obj_colisoes.adicionaJogador(jogador2);

    obj_colisoes.adicionaPersonagem(p);
    obj_colisoes.adicionaPersonagem(p2);
    obj_colisoes.adicionaPersonagem(p3);
    obj_colisoes.adicionaPersonagem(p4);

    //obj_colisoes.adicionaItem(item1);
    obj_colisoes.adicionaItem(item2);
    //obj_colisoes.adicionaItem(item3);

    for(i = 0; i < 21; i++)
        obj_colisoes.adicionaPlataforma(plataformas[i]);

    jogador1->set_y(300);
	jogador2->set_y(300);

}

void Fase2::executa( int* fases, int* pontos, int* no_menu_da_pausa )
{
	jogador1->set_chao(SCREEN_H);
    jogador2->set_chao(SCREEN_H);

	///MATANDO O JOGADOR SE ELE CAIR
    if( jogador1->get_y() == SCREEN_H || jogador2->get_y() == SCREEN_H )
    {
        jogador1->zera_vidas();
        jogador2->zera_vidas();
    }

	///CASO O/OS JOGADORES MORRAM
	if( jogador1->get_vidas() + jogador2->get_vidas() <= 0 )
    {
        al_clear_to_color( al_map_rgb( 255, 255, 255 ));
        al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "Oops! Seems like heaven got a new penguin :)");
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
		for(i = 0; i < 21; i++)
			plataformas[i]->imprime();

		item1->imprime();//coracao das vidas
		item2->imprime();//---------------------->gore que queremos dar um sumisso
		item3->imprime();//gore principal

		///MOVENDO OS PERSONAGENS
		jogador1->mover( teclado );

		if( chama_jogador2 )//se o jogador 1 existe
			jogador2->mover( teclado );///A PARTIR DE AGORA O JOGADOR 2 SEMPRE VAI EXIRTIR
		else if( chama_jogador2 == 0 && jogador1->get_vidas() >= 1 )//se temos apenas um jogador, zeramos as vidas dele
			jogador2->zera_vidas();

		peixe1->mover();
		peixe2->mover();

		passaro->mover();
		passaro2->mover();

		///AQUI ESTOU SALVANDO NO VETOR DE INIMIGOS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        ///UM JEITO DE SALVAR O X E O Y DOS PERSONAGENS DE UMA FOR ESTÁTICA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        inimigos[0].x = p->get_x();
        inimigos[0].y = p->get_y();
        inimigos[0].vivo = p->get_vivo();

        inimigos[1].x = p2->get_x();
        inimigos[1].y = p2->get_y();
        inimigos[1].vivo = p2->get_vivo();

        inimigos[2].x = peixe1->get_x();
        inimigos[2].y = peixe1->get_y();
        inimigos[2].vivo = peixe1->get_vivo();

        inimigos[3].x = peixe2->get_x();
        inimigos[3].y = peixe2->get_y();
        inimigos[3].vivo = peixe2->get_vivo();

        coisas_vermelhas[0].x = item2->get_x();//pegar as posições dos gores
        coisas_vermelhas[0].y = item2->get_y();
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
        teclado->teclas[8] = 0;//"desapertando" a tecla para que o jogador possa apertar ela movamente
    }

    /// TOCANDO A MUSICA
    //al_set_audio_stream_playing(musica1, false);


    ///ESCREVENDO COISAS
    al_draw_textf(font, al_map_rgb(255, 255, 255), 30, 12, ALLEGRO_ALIGN_CENTRE, "%d",  jogador1->get_vidas() + jogador2->get_vidas());
    al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 12, ALLEGRO_ALIGN_CENTRE, "%d", jogador1->get_bolas() + jogador2->get_bolas());
    al_draw_textf(font, al_map_rgb(255, 255, 255), 750, 12, ALLEGRO_ALIGN_CENTRE, "%d", *pontos);

    ///CONFERINDO AS FRONTEIRAS DA TELA
    avanca(fases);
    nao_pode_voltar();

    ///DESENHANDO COISAS
    al_flip_display();
}

void Fase2::avanca( int* fases  )//lembrando que funções retornam o que for apenas uma vez
{
    if( jogador1->get_x() >= SCREEN_W || jogador2->get_x() >= SCREEN_W )//consefirmos primeiro o jogaador e depois o jogador 2, se ele existir
    ///se entrou aqui é porque está no canto direito da tela
    {
        if( chama_jogador2 )//se o jogador 2 existe conferimos a posição dele
        {
            if( jogador1->get_x() >= SCREEN_W && jogador2->get_x() >= SCREEN_W && jogador1->get_bolas()+jogador2->get_bolas() == gores )//ambos os jogadores no canto, muda de fase e se tiverem pego todos os gore
                *fases = 3;
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
            {
                *fases = 3;
            }
            else
                jogador1->set_pode_mover(0, 0);
        }
    }
}

void Fase2::nao_pode_voltar()
{
    if( jogador1->get_x() <= 0 || jogador2->get_x() <= SCREEN_W )//se os os jogadores qeiserem voltar
    {
        if( jogador1->get_x() <= 0 )//se o jogador1 tenta voltar
            jogador1->set_pode_mover(1, 0);
        if( jogador2->get_x() <= 0 )//se o jogador2 tenta voltar
            jogador2->set_pode_mover(1, 0);
    }
}

void Fase2::cada_um_no_seu_quadrado()
{
        //colocando os personagens nos seus devidos lugares

        p->set_x(inimigos[0].x);
        p->set_y(inimigos[0].y);

        p2->set_x(inimigos[1].x);
        p2->set_y(inimigos[1].y);
        p2->set_vivo(inimigos[1].vivo);

        peixe1->set_x(inimigos[2].x);
        peixe1->set_y(inimigos[2].y);
        peixe1->set_vivo(inimigos[2].vivo);

        peixe2->set_x(inimigos[3].x);
        peixe2->set_y(inimigos[3].y);
        peixe2->set_vivo(inimigos[3].vivo);

        item2->set_x(coisas_vermelhas[0].x);
        item2->set_y(coisas_vermelhas[0].y);
}

int Fase2::get_n_personagens(){ return(N_PERSONAGENS_2); }
