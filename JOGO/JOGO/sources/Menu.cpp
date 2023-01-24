#include "../includes/Menu.h"

Menu::Menu()
{
    fonteT = al_load_ttf_font("floquinho.ttf", 120, 0);
    fonte = al_load_ttf_font("floquinho.ttf", 50, 0);
    fonteC = al_load_ttf_font("fanny.ttf", 10, 0);

    ///carregando minhas musicas
    //musica = al_load_audio_stream("fase1_convertida.ogg", 4, 1024);
    //if ( !musica )
        //cout << "erro ao carregar a musica" << endl;
    //liga o stream no mixer
    //al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    //define que o stream vai tocar no modo repeat
    //al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);

}
Menu::~Menu() {}

int Menu::imprimeMenu( Teclado *tec, int* opcoes  )
{
    ///SE TIVER UMA IMAGEM DE FUNDO COLOCAMOS ELA AQUI EM VEZ DE DAR CLEAR TO COLOR!!!!!!!!!!!!!!!!!!!!!!!!!!
    al_clear_to_color( al_map_rgb( 255, 255, 255 ));

    /// TOCANDO A MUSICA
    //al_set_audio_stream_playing(musica, false);

    al_draw_text(fonteT, al_map_rgb(0, 0, 0), SCREEN_W/2, 5, ALLEGRO_ALIGN_CENTRE, "Pingo's");
    al_draw_text(fonteT, al_map_rgb(0, 0, 0), SCREEN_W/2, 110, ALLEGRO_ALIGN_CENTRE, "Quest");
    al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "Choose Level");
    al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/1.67, ALLEGRO_ALIGN_CENTRE, "Continue Match");
    al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/1.45, ALLEGRO_ALIGN_CENTRE, "High Scores");
    al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/1.2, ALLEGRO_ALIGN_CENTRE, "Exit");
    al_draw_text(fonteC, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/1.03, ALLEGRO_ALIGN_CENTRE, "by Bruna Pinheiro and Caroline Rosa");

    if( *opcoes == 0 )//primeira vez que entrando no loop, SELECIONAR NÍVEL
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 240, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, ">");

        if( tec->teclas[tec->KEY_DOWN] )
            (*opcoes)++;
    }

    else if( *opcoes == 1 )//CONNTINUAR PARTIDA
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 220, SCREEN_H/1.67, ALLEGRO_ALIGN_CENTRE, ">");

        if( tec->teclas[tec->KEY_UP] )
            (*opcoes)--;
        else if( tec->teclas[tec->KEY_DOWN] )
            (*opcoes)++;

    }

    else if( *opcoes == 2)//high scores
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 255, SCREEN_H/1.45, ALLEGRO_ALIGN_CENTRE, ">");

        if( tec->teclas[tec->KEY_UP] )
            *opcoes-=1;
        else if( tec->teclas[tec->KEY_DOWN] )
            (*opcoes)++;
    }

    else if( *opcoes == 3 )//SAIR
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2.45, SCREEN_H/1.2, ALLEGRO_ALIGN_CENTRE, ">");//para sair 2.4

        if( tec->teclas[tec->KEY_UP] )
            (*opcoes)--;

    }

    al_flip_display();

    if( tec->teclas[tec->KEY_ENTER] )
    {
        tec->teclas[tec->KEY_ENTER] = 0;///ZERANDO O VETOR DE TECLAS PRO CODE BLOCKS NÃO IMPLICAR
        if( *opcoes == 3 )//o usuário apertou back
            return(0);
        else//o usuário escolheu um nível
            return(1);
    }

    return(2);//usuário ainda não apertou nada

}
