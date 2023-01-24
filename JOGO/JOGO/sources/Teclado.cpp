#include "../includes/Teclado.h"

Teclado::Teclado()
{
    for( i = 0 ; i < 12 ; i++)
        teclas[i] = 0;
}

void Teclado::verificaTeclado(ALLEGRO_EVENT *ev)//SEMPRE USAMOS PARA PEGAR AS TECLAS DO USUÁRIOL, COLOCAR SEMPRE A LETRA QUE QUEREMOS USAR AQUI
{
    if(ev->type == ALLEGRO_EVENT_KEY_DOWN)//CONFERE SE A TECLA FOI ABAIXADA
    {
        switch(ev->keyboard.keycode)
        {
        case ALLEGRO_KEY_UP:
            teclas[KEY_UP] = 1;
            break;

        case ALLEGRO_KEY_DOWN:
            teclas[KEY_DOWN] = 1;
            break;

        case ALLEGRO_KEY_RIGHT:
            teclas[KEY_RIGHT] = 1;
            break;

        case ALLEGRO_KEY_LEFT:
            teclas[KEY_LEFT] = 1;
            break;

        case ALLEGRO_KEY_SPACE:
            teclas[KEY_SPACE] = 1;
            break;

        case ALLEGRO_KEY_ESCAPE:
            teclas[KEY_ESCAPE] = 1;
            break;

        case ALLEGRO_KEY_ENTER:
            teclas[KEY_ENTER] = 1;
            break;

        case ALLEGRO_KEY_F9:
            teclas[KEY_F9] = 1;
            break;

        case ALLEGRO_KEY_P:
            teclas[KEY_P] = 1;
            break;

        case ALLEGRO_KEY_W:
            teclas[KEY_W] = 1;
            break;

        case ALLEGRO_KEY_D:
            teclas[KEY_D] = 1;
            break;

        case ALLEGRO_KEY_A:
            teclas[KEY_A] = 1;
            break;
        }
    }


    else if(ev->type == ALLEGRO_EVENT_KEY_UP)//CONFERE SE AS TECLAS ESTÃO LEVANTADAS, VOLTA PARA ZERO
    {
        switch(ev->keyboard.keycode)
        {
        case ALLEGRO_KEY_UP:
            teclas[KEY_UP] = 0;
            break;

        case ALLEGRO_KEY_DOWN:
            teclas[KEY_DOWN] = 0;
            break;

        case ALLEGRO_KEY_RIGHT:
            teclas[KEY_RIGHT] = 0;
            break;

        case ALLEGRO_KEY_LEFT:
            teclas[KEY_LEFT] = 0;
            break;

        case ALLEGRO_KEY_SPACE:
            teclas[KEY_SPACE] = 0;
            break;

        case ALLEGRO_KEY_ESCAPE:
            teclas[KEY_ESCAPE] = 0;
            break;

        case ALLEGRO_KEY_F9:
            teclas[KEY_F9] = 0;
            break;

        case ALLEGRO_KEY_P:
            teclas[KEY_P] = 0;
            break;

        case ALLEGRO_KEY_W:
            teclas[KEY_W] = 0;
            break;

        case ALLEGRO_KEY_D:
            teclas[KEY_D] = 0;
            break;

        case ALLEGRO_KEY_A:
            teclas[KEY_A] = 0;
            break;
        }
    }

}
