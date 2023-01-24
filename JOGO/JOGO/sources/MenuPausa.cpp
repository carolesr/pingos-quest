#include "../includes/MenuPausa.h"

MenuPausa::MenuPausa()
{
    fonteT = al_load_ttf_font("floquinho.ttf", 120, 0);
    fonte = al_load_ttf_font("floquinho.ttf", 50, 0);
    fonteC = al_load_ttf_font("fanny.ttf", 10, 0);
}
MenuPausa::~MenuPausa(){}

int MenuPausa::imprimeMenuPausa( Teclado *tec, int* opcoes_pausa )
{
    ///SE TIVER UMA IMAGEM DE FUNDO COLOCAMOS ELA AQUI EM VEZ DE DAR CLEAR TO COLOR!!!!!!!!!!!!!!!!!!!!!!!!!!
    al_clear_to_color( al_map_rgb( 255, 255, 255 ));

    al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, 150, ALLEGRO_ALIGN_CENTRE, "Continue");
    al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, 250, ALLEGRO_ALIGN_CENTRE, "Save");
    al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, 350, ALLEGRO_ALIGN_CENTRE, "Exit");

    if( *opcoes_pausa == 0 )//CONTINUE
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 260, 150, ALLEGRO_ALIGN_CENTRE, ">");

        if( tec->teclas[tec->KEY_DOWN] )
            (*opcoes_pausa)++;
    }

    else if( *opcoes_pausa == 1 )//SAVE
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 260, 250, ALLEGRO_ALIGN_CENTRE, ">");

        if( tec->teclas[tec->KEY_UP] )
            (*opcoes_pausa)--;
        else if( tec->teclas[tec->KEY_DOWN] )
            (*opcoes_pausa)++;

    }

    else if( *opcoes_pausa == 2 )//EXIT
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 260, 350, ALLEGRO_ALIGN_CENTRE, ">");

        if( tec->teclas[tec->KEY_UP] )
            (*opcoes_pausa)--;
    }

    al_flip_display();

    if( tec->teclas[tec->KEY_ENTER] )
    {
        tec->teclas[tec->KEY_ENTER] = 0;///ZERANDO O VETOR DE TECLAS PRO CODE BLOCKS NÃO IMPLICAR
        return(2);
    }

    if( tec->teclas[tec->KEY_P] )
    {
        tec->teclas[tec->KEY_P] = 0;
        return(0);
    }

    return(1);
}

