#include "../includes/FaseFinal.h"

int compara(const void* a, const void* b)
{
  return( ((HighScore*)a)->pontuacao - ((HighScore*)b)->pontuacao );
}

FaseFinal::~FaseFinal()
{
    delete(aux);
    al_destroy_font(fonte);
}

FaseFinal::FaseFinal()
{
    highscore->pontuacao = -1;//se imprimir isso � porque deu errado
    salvo = 0;
    fonte = al_load_ttf_font("floquinho.ttf", 50, 0);
    strcpy(str, "");
}

int FaseFinal::manipular_entrada(ALLEGRO_EVENT *ev, Teclado* teclado, int* pontos)
{
    highscore->pontuacao = *pontos;

    if (ev->type == ALLEGRO_EVENT_KEY_CHAR)
    {
        if (strlen(str) <= 5)//tamanho da minha astring sem a posi��o final
        {
            char temp[] = {ev->keyboard.unichar, '\0'};

            if (ev->keyboard.unichar == ' ')
            {
                strcat(str, temp);
            }
            else if (ev->keyboard.unichar >= '0' &&
                     ev->keyboard.unichar <= '9')
            {
                strcat(str, temp);
            }
            else if (ev->keyboard.unichar >= 'A' &&
                     ev->keyboard.unichar <= 'Z')
            {
                strcat(str, temp);
            }
            else if (ev->keyboard.unichar >= 'a' &&
                     ev->keyboard.unichar <= 'z')
            {
                strcat(str, temp);
            }
        }

        if (ev->keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0)
        {
            str[strlen(str) - 1] = '\0';
        }

        /** PRIMEIRO TEMOS QUE LER O ARQUIVO PARA SABER O TAMANHO DELE, EM SEGUIDA*/
        if(ev->keyboard.keycode == ALLEGRO_KEY_ENTER && strlen(str) > 0 )
        {
            ///agora que j� pegamos o nome do jogador, podemos sa�v�-lo
            strcpy( highscore->nome, str );
            coloca_em_ordem();
            if( salvo )
                return(2);
        }
    }

    if (strlen(str) >= 0)
    {
        al_clear_to_color( al_map_rgb( 255, 255, 255 ));
        al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W/2, 200, ALLEGRO_ALIGN_CENTRE, "Enter your name:");
        al_draw_text(fonte, al_map_rgb(0, 0, 0), SCREEN_W / 2, (SCREEN_H - al_get_font_ascent(fonte)) / 2, ALLEGRO_ALIGN_CENTRE, str);
        al_flip_display();
    }

    return(0);
}

//Come�o da fun��o para ordenar o highscore.
//Ass:Wag
void FaseFinal::coloca_em_ordem()
{
    ///limpando o arquivo para fazer os testes, ou quando entra lixo
    /*FILE *arq_novo = fopen("References/HighScore.bin", "w");
    fclose(arq_novo);*/



    FILE *arq_entrada = fopen("References/HighScore.bin", "r+b");//mudei para r+b
    if( arq_entrada == NULL)
        cout << "Falha ao abrir o arquivo HighScore na FaseFinal" << endl;

    ///primeiro vamos percorrer o arquivo para contar quantos dados tem nele
    for( tam = 0 ; fread(&seta, sizeof(HighScore), 1, arq_entrada)!=0 ; tam++ ){}//o 1 mostra quantas classes e quero ver

    ///Como eu j� fui no final do vetor, posso escrever a pontua��o no final do vetor sem sobrescrever o que estava antes
    fwrite( &highscore, sizeof(HighScore), 1, arq_entrada );
    tam++;//como acabei de escrever no arquivo posso aumentar o tamanho dele

    ///voltando para o come�o do arquivo
    rewind(arq_entrada);

    aux = new HighScore[tam];

    ///Passando as informa��es do meu arquivo para o meu vetor para poder compar�-las
    ///percorre at� zero, porque quando a fun��o fread chega no fim ela retorna zero
    for( i = 0 ; fread(&aux[i], sizeof(HighScore), 1, arq_entrada) != 0 ; i++ ){}

    ///Mandando meu vetor para ser ordenado por uma fun��o da Qsort
    qsort( aux , tam , sizeof(HighScore) , compara );

    ///Agora que j� fizemos as altera��es necess�rias, podemos fechar o arquivo
    fclose(arq_entrada);

    ///Abrindo o arquivo, mas agora criando ele do zero para que possamos recolocar os dados do vetor na ordem certa
    arq_entrada = fopen("References/HighScore.bin", "w");

    ///Agora precisamos gravar as coisas no arquivo em prdem decrescente, e somente at� o numero de jogadores-1
    for( i = tam-1 ; i >= 0 ; i-- )
    {
        fwrite( &aux[i] , sizeof(HighScore) , 1 , arq_entrada);
        //cout << aux[i].nome << "-------"<< aux[i].pontuacao << endl;//Apenas para imprimir e podermos visualizar os valores nos testes
        if( i == (tam-10) )///para n�o salvar mais de 10 pontua��es
            break;
    }

    //cout << "==============================================================" << endl;//apenas para separar os highscores

    ///agora que j� sobreescrevemos o arquivo, podemos fech�-lo
    fclose(arq_entrada);
    salvo = 1;
}
