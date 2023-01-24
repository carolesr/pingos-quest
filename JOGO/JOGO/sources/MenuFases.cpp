
#include "../includes/MenuFases.h"

MenuFases::MenuFases()
{
    fonteT = al_load_ttf_font("floquinho.ttf", 120, 0);
    fonte = al_load_ttf_font("floquinho.ttf", 50, 0);
    fonteC = al_load_ttf_font("fanny.ttf", 10, 0);
}
MenuFases::~MenuFases()
{
    al_destroy_font(fonteT);
    al_destroy_font(fonte);
    al_destroy_font(fonteC);
}

int MenuFases::imprimeMenuFases( Teclado* tec, int* fase  )
{

    ///SE TIVER UMA IMAGEM DE FUNDO COLOCAMOS ELA AQUI EM VEZ DE DAR CLEAR TO COLOR!!!!!!!!!!!!!!!!!!!!!!!!!!
    al_clear_to_color( al_map_rgb( 255, 255, 255 ));

    al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/2.2, ALLEGRO_ALIGN_CENTRE, " 1              2              3");
    al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/1.2, ALLEGRO_ALIGN_CENTRE, "Back");
    al_draw_text(fonteC, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/1.03, ALLEGRO_ALIGN_CENTRE, "by Bruna Pinheiro e Caroline Rosa");

    if( *fase == 1 )//FASE1
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 187, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "---");

        if( tec->teclas[tec->KEY_RIGHT] )
            (*fase)++;
        else if( tec->teclas[tec->KEY_LEFT] )
            (*fase)--;
    }

    else if( *fase == 2 )//FASE2
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 402, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "---");

        if( tec->teclas[tec->KEY_RIGHT] )
            (*fase)++;

        else if( tec->teclas[tec->KEY_LEFT] )
            (*fase)--;
    }

    else if( *fase == 3 )//FASE3
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 627, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "---");

        if( tec->teclas[tec->KEY_RIGHT] )
            (*fase)=0;///se for para a direita as fases volta a ser zero

        else if( tec->teclas[tec->KEY_LEFT] )
            (*fase)--;

    }

     else if( *fase == 0 )//FASE3
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, 525, ALLEGRO_ALIGN_CENTRE, "--------");

        if( tec->teclas[tec->KEY_RIGHT] )
            (*fase)=3;

        else if( tec->teclas[tec->KEY_LEFT] )
            (*fase)++;
    }

    if( tec->teclas[tec->KEY_ENTER] )
    {
        tec->teclas[tec->KEY_ENTER] = 0;///ZERANDO O VETOR DE TECLAS PRO CODE BLOCKS NÃO IMPLICAR
        if( *fase == 0 )
            return(0);///APERTOU BACK
        else
            return(1);
    }

    al_flip_display();
    return(2);//PODEMOS CONTINUAR NO MENU

}
