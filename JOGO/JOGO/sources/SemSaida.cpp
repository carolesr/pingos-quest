
#include "../includes/SemSaida.h"

SemSaida::SemSaida()
{
    fonteT = al_load_ttf_font("floquinho.ttf", 90, 0);
    fonte = al_load_ttf_font("floquinho.ttf", 50, 0);
    fonteC = al_load_ttf_font("fanny.ttf", 15, 0);

    ///carregando minhas musicas
    //musica = al_load_audio_stream("fase1_convertida.ogg", 4, 1024);
    //if ( !musica )
        //cout << "erro ao carregar a musica" << endl;
    //liga o stream no mixer
    //al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    //define que o stream vai tocar no modo repeat
    //al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);

}
SemSaida::~SemSaida(){}

int SemSaida::imprimeSemSaida( Teclado *tec  )
{
    ///SE TIVER UMA IMAGEM DE FUNDO COLOCAMOS ELA AQUI EM VEZ DE DAR CLEAR TO COLOR!!!!!!!!!!!!!!!!!!!!!!!!!!
    al_clear_to_color( al_map_rgb( 255, 255, 255 ));

    /// TOCANDO A MUSICA
    //al_set_audio_stream_playing(musica, false);

    al_draw_text(fonteT, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/3, ALLEGRO_ALIGN_CENTRE, "Merry Crhistmas");
    al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "You can't go back :)");

    al_flip_display();

    if( tec->teclas[tec->KEY_SPACE] )
    {
        tec->teclas[tec->KEY_SPACE] = 0;///ZERANDO O VETOR DE TECLAS PRO CODE BLOCKS NÃO IMPLICAR
            return(0);
    }

    return(1);//usuário ainda não apertou nada

}
