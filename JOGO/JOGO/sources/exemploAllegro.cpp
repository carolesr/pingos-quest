#include "../includes/Jogo.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <allegro5/allegro.h> // Librería inicial de Allegro
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h> // Addon de primitivas (figuras)
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>

ALLEGRO_TIMER *timer = NULL;

int main(int argc, char **argv)
{

///INICIALIZANDO AS COISAS

    ALLEGRO_DISPLAY *display = NULL;//CRIOU UM PONTEIRO PARA UM DISPLAY
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;//PILHA DE FILA DE EVENTOS

///CONFERINDO SE ESTÁ TUDO CERTO

    if(!al_init()) //função que inicializa o allegro
    {
        cout << "failed to initialize allegro!\n";
        return -1;
    }

    if(!al_install_keyboard())//FUNÇÃO PARA CONFIGURAR O TECLADO
    {
        cout << "failed to initialize the keyboard!\n";
        return -1;
    }
//AQUI APENAS INFORMAMOS O ALLEGRO DE QUE PODEMOS QUERER FUTURAMENTE USAR ELAS
    al_init_font_addon(); // initialize the font addon => INICIALIZA A FONTE
    al_init_ttf_addon();// initialize the ttf (1 Type Font) addon => EH A FONTE DE TIPO TTF (EX PRA MUSICA MP3), QUE PODEMOS FUTURAMENTE USAR
//VER FUNÇÃO QUE PRINTA COISAS NA TELA COM ESSA FONTE

    if(!al_init_image_addon())//PERMITE USAR A IMAGEM
    {
        cout << "failed to initialize the al_init_image_addon!\n";
        return -1;
    }

    if(!al_install_audio())
    {
        cout << "failed to initialize audio!\n" ;
        return -1;
    }

    if(!al_init_acodec_addon())
    {
        cout << "failed to initialize audio codecs!\n";
        return -1;
    }

    //Reserves a number of sample instances, and creates a default mixer if one doesn't exist. This allows us to decide how many audio samples we will be creating for now we are only creating one.
if (!al_reserve_samples(3))//NUMERO DE SONS QUE PODEM SAIR AO MESMO TEMPO
{
    cout << "failed to reserve samples!\n";
    return -1;
}

    display = al_create_display(SCREEN_W, SCREEN_H);//CRIA O DISPLAY/TELA

    if(!display)//CONFERE SE O DISPLAY FOI CRIADO COM SUCESSO!
    {
        cout << "failed to create display!\n";
        al_destroy_timer(timer);
        return -1;
    }

    if (!al_install_mouse())
    {
        al_destroy_display(display);
        al_destroy_timer(timer);
        cout << "Falha ao inicializar o mouse.\n";
        return -1;
    }

//RECONHECE O MOUSE NO SISTEMA, SETA ELE!
    if (!al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        al_destroy_display(display);
        al_destroy_timer(timer);
        cout << "Falha ao atribuir ponteiro do mouse.\n";
        return -1;
    }


///MUITO IMPORTANTE!!!!!!!!!!!!!!!
    timer = al_create_timer(1.0 / FPS);//AJUDA A VERIFICAR SE O USUÁRI ODIGITOU ALGO

    if(!timer)
    {
        cout << "failed to create timer!\n";
        return -1;
    }

    al_set_target_bitmap(al_get_backbuffer(display));//<3 ACREDITA QUE SETAMOS ONDE COLOCAR A IMAGEM NO DISPLAY

    event_queue = al_create_event_queue();//CRIAMOS UM EVENTO QUEUE E FAZEMOS O NOSSO PONTEIRO APONTAR PARA ELE
    if(!event_queue)//CONFERE SE A FILA FOI CRIADA DIREITO
    {
        cout << "failed to create event_queue/FILA!\n";
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

//ESSAS FILAS REGISTRAM TODOS OS TIPOS DE EVENTO QUE PODEM OCORRER
    al_register_event_source(event_queue, al_get_display_event_source(display));//COISAS QUE ACONTECEM COM O DISPLAY
    al_register_event_source(event_queue, al_get_timer_event_source(timer));//'' '' TIMER
    al_register_event_source(event_queue, al_get_keyboard_event_source());//'' '' TECLADO
    al_register_event_source(event_queue, al_get_mouse_event_source());//'' '' MOUSE

    //al_clear_to_color(al_map_rgb(0,0,0));//LIMPA TUDO PARA A TELA PRETA
    al_flip_display();//MANDA O DISPLAY QUE MODIFICAMOS PARA O USUÁRIO
    al_start_timer(timer);//COMEÇA O TIMER


    ///CRIANDO AS COISAS DO MENU
    Teclado teclado;
    Jogo jogo( &teclado );//INSTANCIANDO MEU JOGO NO MENU
    ALLEGRO_EVENT ev;//CRIAMOS UM EVENTO
    jogo.cuida_do_menu_principal(&ev);
    //po menu conseguir imprimir
    while( 1 )//AQUI TODAS AS PARTES DO JOGO ACONTECERÃO
    {

        ALLEGRO_EVENT ev;//CRIAMOS UM EVENTO
        al_wait_for_event(event_queue, &ev);//ESPERA POR UM EVENTO

        if(ev.type == ALLEGRO_EVENT_TIMER)//SE O EVENTO FOR DO TIPO TIMER
        {
            ///confere o menu secundario e chama as funções responssáveis pelas fases
            if( !jogo.get_no_menu_da_pausa() && jogo.get_no_menu_das_fases() == 1 )//ele selecioou para escolher alguma fase e agora vamos jogar!
                jogo.efeito_domino_das_fases(&ev);///a "primeira" fase já foi escolheida, agora só falta chamarmos a função para jogarmos a fase
        }
        //se estiver na hora (x) de fechar a aplicação
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//SE O USUÁRIO FECHAR O DISPLAY
        {
            break;
        }
        //VERIFICA SE UMA TECLA FOI ABAIXADA OU LEVANTADA
        else if((ev.type == ALLEGRO_EVENT_KEY_DOWN) || (ev.type == ALLEGRO_EVENT_KEY_UP))
        {
            if( jogo.get_no_menu_principal() == 2 )///2 diz que o usuário ainda não apertou nenhuma tecla
                jogo.cuida_do_menu_principal(&ev);

            else if( jogo.get_no_menu_principal() == 0 )///apertou para sair
                break;

            else if( jogo.get_no_menu_principal() == 1 )///quer selecionar um nivel
                jogo.seleciona_opcao_correta_do_menu_principal( &ev );///AQUI CHAMO A FUNÇÃO QUE DEIXA O USUARIO ESCOLHER UM NIVEL OU IR PARA O TUTORIAL, ESSA FUNÇÃO JA SABE AS OPCOES QUE O USUARIO QUER

            if( jogo.get_no_menu_das_fases() == 1 )//ele selecioou para escolher alguma fase e agora vamos jogar!
                teclado.verificaTeclado(&ev);

            if( jogo.get_no_menu_da_pausa() == 1 )
                jogo.cuida_do_menu_da_pausa(&ev);
        }

        if( jogo.get_no_menu_das_fases() == 9 )
                jogo.efeito_domino_das_fases(&ev);


}

    //ENTENDE QUE SE VC SAIU E NÃO QUER MAIS JOGAR, DA UM FIM EM TUDO TUDO TUDO!!!
    ///DESTROI TUDO TUDO TUDO NA ORDEM CERTA////////////////////////////////////////////////////////
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    //al_destroy_sample(som);


    return 0;
}
