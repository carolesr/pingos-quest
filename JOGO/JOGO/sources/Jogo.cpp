#include "../includes/Jogo.h"


Jogo::~Jogo()///temos que destruir mais coisas
{
    teclado = NULL;

    delete(jogador1);
    delete(jogador2);

    delete(fonte);
    delete(fonteT);
    delete(fonteH);

}

//aqui inicializamos as funções do jogo

Jogo::Jogo() {}
Jogo::Jogo( Teclado* tec )
{
    no_menu_da_pausa = 0;
    escreveu = 0;
    teclado = tec;
    opcao = 0;
    opcao_da_pausa = 0;
    no_menu_da_pausa = 0;
    fase = 0;
    pontos = 0;

    no_menu_principal = 1;

    fonte = al_load_ttf_font("fonte.ttf", 25, 0 );
    fonteT = al_load_ttf_font("floquinho.ttf", 40, 0);
    fonteH = al_load_ttf_font("floquinho.ttf", 55, 0 );

    ///CRIANDO OS JOGADORES
    jogador1 = new Jogador(1);
    jogador2 = new Jogador(0);

    fasefinal = new FaseFinal();
}

void Jogo::reseta()
{
    ///DELETANDO A FASE
    if( fase == 1 )
        delete(fase1);
    if( fase == 2 )
        delete(fase2);
    if( fase == 3 )
        delete(fase3);

    no_menu_da_pausa = 0;
    teclado->teclas[teclado->KEY_ENTER] = 0;
    teclado->teclas[teclado->KEY_SPACE] = 0;
    escreveu = 0;
    opcao = 0;
    fase = 0;
    no_menu_principal = 2;
    pontos = 0;

    ///DELETANDO OS JOGADORES
    delete(jogador1);
    delete(jogador2);

    ///RECRIANDO OS JOGADORES
    jogador1 = new Jogador(1);
    jogador2 = new Jogador(0);
}

///Posso usar os personagens que já tenho em todas as fases
void Jogo::cuida_do_menu_principal( ALLEGRO_EVENT *ev )//estou passando um avento para ela
{
    teclado->verificaTeclado(ev);//fazendo o programa verificar os eventos do meu teclado
    no_menu_principal = menu_principal.imprimeMenu( teclado, &opcao );
}


void Jogo::seleciona_opcao_correta_do_menu_principal( ALLEGRO_EVENT *ev )
{
    int entrou_no_catch = 0;

    if( opcao == 0 )///ESCOLHER NIVEL
        cuida_do_menu_das_fases( ev );

    if( opcao == 1 )///CONTINUAR PARTIDA
    {
        try
        {
            carrega();
        }
        catch(invalid_argument& e)
        {
            cerr << e.what() << endl;
            entrou_no_catch = 1;
        }

        if( !entrou_no_catch )
        {
            no_menu_da_pausa = 0;
            no_menu_das_fases = 1;
            no_menu_principal = -1;
            ///AQUI EU CHAMO A FUNÇÃO QUE FAZ OS PERSONAGENS FICAREM NO SEUS DEVIDOS LUGARES
            ///CADA UM NO SEU QUADRADO
            if( fase == 1 )
                fase1->cada_um_no_seu_quadrado();
            if( fase == 2 )
                fase2->cada_um_no_seu_quadrado();
        }
        else if( entrou_no_catch )//precisamos fazer ele continuar no menu
        {
            reseta();
        }

    }

    if( opcao == 2 )///HIGH SCORES
        apresenta_high_scores( ev );

}


void Jogo::cuida_do_menu_das_fases( ALLEGRO_EVENT *ev )
{
    teclado->verificaTeclado(ev);

    no_menu_das_fases = menu_das_fases.imprimeMenuFases( teclado, &fase );
    if( no_menu_das_fases == 0 )//apertou back, tenho que deletar a fase em que ele estava quando ele sai
        no_menu_principal = 2;//manda voltar para o menu principal
    else if( no_menu_das_fases == 1 )//tenho que inicializar a fase aqui se não ele vai alocar memória para ela várias vezes, e assim aloco memória uma vez e já chamo a função efeito dominó de fases naquela outra parte da main
    {
        inicializa_a_fase_escolhida();
        no_menu_principal = -1;//só pra sair daqueles if da main, agora não corremos perido dele inicializar a fase mais de uma vez
    }

}

void Jogo::cuida_do_menu_da_pausa( ALLEGRO_EVENT *ev )
{
    teclado->teclas[teclado->KEY_ENTER] = 0;///ZERANDO O ENTER PARA O CODE BLOCKS NÃO IMPLCIAR
    teclado->teclas[teclado->KEY_P] = 0;
    teclado->verificaTeclado(ev);


    no_menu_da_pausa = menu_da_pausa.imprimeMenuPausa( teclado, &opcao_da_pausa );
    if( no_menu_da_pausa == 2 )//se o menu da pausa valer 2, precisamos conferir as opções
    {
        if( opcao_da_pausa == 0 )//continuar
            no_menu_da_pausa = 0;
        else if( opcao_da_pausa == 1 && fase != 3 )
        {
            salva();
            reseta();
        }
        else if( opcao_da_pausa == 1 && fase == 3 )
        {
            feliz_natal.imprimeFelizNatal(teclado);
            no_menu_da_pausa = 1;
        }

        else if( opcao_da_pausa == 2 && fase != 3 )//apertou exit
            reseta();
        else if( opcao_da_pausa == 2 && fase == 3 )
        {
            sem_saida.imprimeSemSaida(teclado);
            no_menu_da_pausa = 1;
        }
    }


}


void Jogo::apresenta_high_scores(ALLEGRO_EVENT *ev)
{
    teclado->verificaTeclado(ev);

    ///"LIMPANDO" A MINHA TELA
    al_clear_to_color( al_map_rgb( 255, 255, 255 ) );

    ///MOSTRANDO O TÍTULO
    al_draw_textf(fonteH, al_map_rgb(0, 0, 0), SCREEN_W/2, 5, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");

    ///ABRINDO MEU ARQUIVO E ESCREVENDO TUDO O QUE TEM NO ARQUIVO NA TELA
    FILE *arq_entrada = fopen("References/HighScore.bin", "r");//r permite apenas que consigamos ler o arquivo
    if( arq_entrada == NULL)
        cout << "Falha ao abrir o arquivo HighScore para apresentar o HighScore" << endl;

    ///primeiro vamos percorrer o arquivo para contar quantos dados tem nele
    for( int tam = 0 ; fread(&seta, sizeof(HighScore), 1, arq_entrada)!=0 ; tam++ )//o 1 mostra quantas classes e quero ver
        al_draw_textf(fonteT, al_map_rgb(0, 0, 0), SCREEN_W/2, 70+45*tam, ALLEGRO_ALIGN_CENTRE, "%s  ......... %d", seta.nome, seta.pontuacao);

    ///Agora que já fizemos as alterações necessárias, podemos fechar o arquivo
    fclose(arq_entrada);

    al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, 550, ALLEGRO_ALIGN_CENTRE, "Press ENTER to continue");

    ///MUDANDO A TELA PARA APRESENTAR OS HIGH SCORES
    al_flip_display();
    if( teclado->teclas[teclado->KEY_ENTER] )//já leu os high scores e quer voltar para o menu
    {
        teclado->teclas[teclado->KEY_ENTER] = 0;
        opcao = 0;
        fase = 0;
        no_menu_principal = 2;
    }
}

void Jogo::inicializa_a_fase_escolhida()
{
    if( fase == 1 )
        fase1 = new Fase1( teclado, jogador1, jogador2);
    else if( fase == 2 )
        fase2 = new Fase2( teclado, jogador1, jogador2);
    else if( fase == 3 )
        fase3 = new Fase3( teclado, jogador1, jogador2);
}


void Jogo::efeito_domino_das_fases(ALLEGRO_EVENT *ev)
{
    if( fase == 1 )
    {
        fase1->executa( &fase, &pontos, &no_menu_da_pausa );
        if( fase != 1 )//tem que ficar valendo pelo menos uma vez
        {
            delete(fase1);
            ///FAZENDO OS JOGADORES VOLTAREM PARA O COMEÇO DA TELA--->FAZER ISSO SEMPRE!
            jogador1->set_x(10);
            jogador2->set_x(10);

            fase2 = new Fase2( teclado, jogador1, jogador2 );
        }

    }

    if( fase == 2 )
    {
        fase2->executa( &fase, &pontos, &no_menu_da_pausa );
        if( fase != 2 )
        {
            delete(fase2);

            ///FAZENDO OS JOGADORES VOLTAREM PARA O COMEÇO DA TELA--->FAZER ISSO SEMPRE!
            jogador1->set_x(10);
            jogador1->set_y(300);
            jogador2->set_x(10);
            jogador2->set_y(300);

            fase3 = new Fase3( teclado, jogador1, jogador2 );
        }
    }
    if( fase == 3 )
    {
		fase3->executa( &fase, &pontos, &no_menu_da_pausa );
		if( fase != 3 )
        {
			al_clear_to_color( al_map_rgb( 255, 255, 255 ) );
			///Mensagem de finalização
			al_draw_textf(fonteH, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "Congratulations! You've saved Christmas!");
			al_flip_display();
        }

    }
    if( fase == 9 )
    {
        no_menu_das_fases = 9;
        escreveu = fasefinal->manipular_entrada(ev, teclado, &pontos);
        if( escreveu == 2 )
            reseta();
    }
}

void Jogo::salva()//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    salvacao.fase = fase;
    salvacao.pontos = pontos;
    salvacao.n_gores = jogador1->get_bolas() + jogador2->get_bolas();

    salvacao.x_jogador1 = jogador1->get_x();
    salvacao.x_jogador2 = jogador2->get_x();

    salvacao.y_jogador1 = jogador1->get_y();
    salvacao.y_jogador2 = jogador2->get_y();

    salvacao.vidas_jogador1 = jogador1->get_vidas();
    salvacao.vidas_jogador2 = jogador2->get_vidas();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if( salvacao.fase == 1 )
    {
        for( int w = 0 ; w < fase1->get_n_personagens() ; w++ )
        {
            salvacao.inimigos[w].x = fase1->inimigos[w].x;
            salvacao.inimigos[w].y = fase1->inimigos[w].y;
            salvacao.inimigos[w].vivo = fase1->inimigos[w].vivo;
        }

        for( int w = 0 ; w < 3 ; w++ )//colocando os itens nos seus devidos lugares
        {
            salvacao.gores[w].x = fase1->coisas_vermelhas[w].x;
            salvacao.gores[w].y = fase1->coisas_vermelhas[w].y;
        }
    }
    else if( salvacao.fase == 2 )
    {
        for( int w = 0 ; w < fase2->get_n_personagens() ; w++ )
        {
            salvacao.inimigos[w].x = fase2->inimigos[w].x;
            salvacao.inimigos[w].y = fase2->inimigos[w].y;
            salvacao.inimigos[w].vivo = fase2->inimigos[w].vivo;
        }

        salvacao.gores[0].x = fase2->coisas_vermelhas[0].x;
        salvacao.gores[0].y = fase2->coisas_vermelhas[0].y;
    }

    FILE *arq = fopen("References/Salva.bin", "w+b");//mudei para w+b pata conseguir escrever e salvar
    if( arq == NULL)
        cout << "Falha ao abrir o arquivo Salva.bin na FaseFinal" << endl;

    rewind(arq);

    ///Como eu já fui no final do vetor, posso escrever a pontuação no final do vetor sem sobrescrever o que estava antes
    fwrite( &salvacao, sizeof(Salvacao), 1, arq );
    /*cout << "fase1 " << salvacao.fase << endl;
    cout << "fase1 " << salvacao.x_jogador1 << endl;*/

    ///Agora que já fizemos as alterações necessárias, podemos fechar o arquivo
    fclose(arq);


    ///POR ALGUM MOTIVO MISTERIOSO ISSO DA CERTO, SÓ DEIXA ELE AÍ!!!!!
    /*Salvacao teste;
    arq = fopen("References/Salva.bin", "r");
    int f = fread(&teste, sizeof(Salvacao), 1, arq);
    cout << "fread bugado" << f << endl;
    fclose(arq);*/
}

void Jogo::carrega()
{
    Salvacao* leitora;
    leitora = new Salvacao;
    FILE* arq = fopen("References/Salva.bin", "r");
    if( arq == NULL)
        cout << "Falha ao abrir o arquivo HighScore para apresentar o HighScore" << endl;

    rewind(arq);

    int f = fread(leitora, sizeof(Salvacao), 1, arq);

    fclose(arq);
    ///JÁ SALVAI TUDO NA SALVAÇÃO, AGORA É SÓ ATRIBUIR ISSO À MINHA FASE

    //tratando o erro da carrega caso f seja 0
    if(f == 0)
        throw invalid_argument("A fase nao pode ser carregada.");

    pontos = leitora->pontos;
    fase = leitora->fase;
    jogador1->set_bolas( leitora->n_gores );

    ///SALVANDO A FASE1/////
    if( leitora->fase == 1 )
    {
        fase1 = new Fase1( teclado, jogador1, jogador2 );

        for( int w = 0 ; w < fase1->get_n_personagens() ; w++ )
        {
            fase1->inimigos[w].vivo = leitora->inimigos[w].vivo;
            fase1->inimigos[w].x = leitora->inimigos[w].x;
            fase1->inimigos[w].y = leitora->inimigos[w].y;

        }

        for( int w = 0 ; w < 3 ; w++ )//colocando os itens nos seus devidos lugares
        {
            fase1->coisas_vermelhas[w].x = leitora->gores[w].x;
            fase1->coisas_vermelhas[w].y = leitora->gores[w].y;
        }

        fase1->jogador1->set_x(leitora->x_jogador1);
        fase1->jogador2->set_x(leitora->x_jogador2);

        fase1->jogador1->set_y(leitora->y_jogador1);
        fase1->jogador2->set_y(leitora->y_jogador2);

        fase1->jogador1->set_vidas(leitora->vidas_jogador1);
        fase1->jogador2->set_vidas(leitora->vidas_jogador2);
    }

    ///SALVANDO A FASE2/////
    if( leitora->fase == 2 )
    {
        fase2 = new Fase2( teclado, jogador1, jogador2 );

        for( int w = 0 ; w < fase1->get_n_personagens() ; w++ )
        {
            fase2->inimigos[w].x = leitora->inimigos[w].x;
            fase2->inimigos[w].y = leitora->inimigos[w].y;
            fase2->inimigos[w].vivo = leitora->inimigos[w].vivo;

        }

        fase2->coisas_vermelhas[0].x = leitora->gores[0].x;
        fase2->coisas_vermelhas[0].y = leitora->gores[0].y;

        fase2->jogador1->set_x(leitora->x_jogador1);
        fase2->jogador2->set_x(leitora->x_jogador2);

        fase2->jogador1->set_y(leitora->y_jogador1);
        fase2->jogador2->set_y(leitora->y_jogador2);

        fase2->jogador1->set_vidas(leitora->vidas_jogador1);
        fase2->jogador2->set_vidas(leitora->vidas_jogador2);
    }

    delete(leitora);

}

int Jogo::get_no_menu_principal()
{
    return(no_menu_principal);
}
int Jogo::get_no_menu_das_fases()
{
    return(no_menu_das_fases);
}
int Jogo::get_no_menu_da_pausa()
{
    return(no_menu_da_pausa);
}


