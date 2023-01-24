
#include "../includes/GerenciadorColisao.h"

enum F
{
    D, E
};

GerenciadorColisao::GerenciadorColisao() {}
GerenciadorColisao::~GerenciadorColisao() {}

void GerenciadorColisao::adicionaJogador(Jogador* j)
{
    if(j)
        listaJogadores.incluir(j);
}

void GerenciadorColisao::adicionaPersonagem(Personagem *p)
{
    if( p )
        listaPersonagens.incluir(p);
}

void GerenciadorColisao::adicionaItem(Item* it)
{
    if(it)
        listaItens.incluir(it);
}

void GerenciadorColisao::adicionaPlataforma(Plataforma* plat)
{
    if(plat)
        listaPlataformas.incluir(plat);
}

void GerenciadorColisao::adicionaChefao(ChefaoPrimario* c)
{
    chefao = c;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GerenciadorColisao::verificaColisaoChefao()
{
    for( unsigned int w = 0 ; w < 2 ; w++ ) //Loop pros jogadores
    {
        if( !chefao )
        {
            listaJogadores.getLista()[w]->set_pode_mover(D, 1);//meu jogador pode voltar a andar normalmente para a direita
            listaJogadores.getLista()[w]->set_pode_mover(E, 1);//meu jogador pode voltar a andar normalmente para a esquerda
        }

        if(!chefao->get_morreu())
        {
            x1 = (listaJogadores.getLista()[w])->get_x();
            x3 = chefao->get_x();

            y1 = (listaJogadores.getLista()[w])->get_y();
            y3 = chefao->get_y();

            distancia1 = ((listaJogadores.getLista()[w]->get_frameWidth())*(listaJogadores.getLista()[w]->get_escala()))/2 + ((chefao->get_frameWidth())*(chefao->get_escala()))/2;
            distancia2 = ((listaJogadores.getLista()[w]->get_frameHeight())*(listaJogadores.getLista()[w]->get_escala()))/2 + ((chefao->get_frameHeight())*(chefao->get_escala()))/2;

            if( x1 > x3 )///pinguim indo para a esquerda
            {
                listaJogadores.getLista()[w]->set_pode_mover(D, 1);//pode mover
                chefao->set_pode_mover(E, 1);//pode mover

                if( x1-x3 < distancia1 )//conferindo se também não estão na mesma altura
                {
                    if( y3-y1 < 0 )//O pinguim está abaixo do personagem
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(E, 1);
                        chefao->set_pode_mover(D, 1);
                    }
                    else if( y3-y1 <= distancia2+30 && y3-y1 >= distancia2 )//se está caindp
                    {
                        (*chefao)--;

                        if(chefao->get_vidas() == 0)
                        {
                            chefao->morrer();
                            chefao->set_xm(chefao->get_x());
                        }

                        listaJogadores.getLista()[w]->set_dy(-20);
                        listaJogadores.getLista()[w]->set_dx(40);
                    }
                    else if( y3 - y1 >= distancia2 )//se está pulando por cima
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(E, 1);
                        chefao->set_pode_mover(D, 1);
                    }
                    else//se bate de lado
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(E, 0);
                        chefao->set_pode_mover(D, 0);
                        listaJogadores.getLista()[w]->vai_pra_direita();
                        listaJogadores.getLista()[w]->perde_uma_vida();
                        break;
                    }
                }
                else
                {
                    listaJogadores.getLista()[w]->set_pode_mover(E, 1);
                    chefao->set_pode_mover(D, 1);
                }


            }

            if( x1 < x3 )///pinguim indo para a direita
            {
                listaJogadores.getLista()[w]->set_pode_mover(E, 1);
                chefao->set_pode_mover(D, 1);

                if( x3-x1 < distancia1 )//diferenças de distancias
                {
                    if( y3-y1 < 0 )//O pinguim está abaixo do personagem
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(E, 1);
                        chefao->set_pode_mover(D, 1);
                    }
                    else if( y3-y1 <= distancia2+30 && y3-y1 >= distancia2 )//se está caindp
                    {
                        (*chefao)--;

                        if(chefao->get_vidas() == 0)
                        {
                            chefao->morrer();
                            chefao->set_xm(chefao->get_x());
                        }

                        listaJogadores.getLista()[w]->set_dy(-20);
                        listaJogadores.getLista()[w]->set_dx(-40);
                    }
                    else if( y3 - y1 >= distancia2 )//se está pulando por cima
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(D, 1);
                        chefao->set_pode_mover(E, 1);
                    }
                    else//se bate de lado
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(D, 0);
                        chefao->set_pode_mover(E, 0);
                        listaJogadores.getLista()[w]->vai_pra_esquerda();
                        listaJogadores.getLista()[w]->perde_uma_vida();
                        break;
                    }
                }
                else
                {
                    listaJogadores.getLista()[w]->set_pode_mover(D, 1);
                    chefao->set_pode_mover(E, 1);
                }
            }
        }


    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///100 pontos para matar um bichinho
void GerenciadorColisao::verificaColisaoPersonagens(int* pontos, Dados* inimigos)//compara as fronteiras do personagem com as dos objetos
{
    for( unsigned int w = 0 ; w < 2 ; w++ )//verifica para o primeiro e o segundo jogador
    {
        listaJogadores.getLista()[w]->set_pode_mover(D, 1);//meu jogador pode voltar a andar normalmente para a direita
        listaJogadores.getLista()[w]->set_pode_mover(E, 1);//meu jogador pode voltar a andar normalmente para a esquerda

        for( unsigned int i = 0 ; i < listaPersonagens.getLista().size() ; i++ )
        {
            x1 = (listaJogadores.getLista()[w])->get_x();
            x3 = (listaPersonagens.getLista()[i])->get_x();

            y1 = (listaJogadores.getLista()[w])->get_y();
            y3 = (listaPersonagens.getLista()[i])->get_y();

            distancia1 = ((listaJogadores.getLista()[w]->get_frameWidth())*(listaJogadores.getLista()[w]->get_escala()))/2 + ((listaPersonagens.getLista()[i]->get_frameWidth())*(listaPersonagens.getLista()[i]->get_escala()))/2;
            distancia2 = ((listaJogadores.getLista()[w]->get_frameHeight())*(listaJogadores.getLista()[w]->get_escala()))/2 + ((listaPersonagens.getLista()[i]->get_frameHeight())*(listaPersonagens.getLista()[i]->get_escala()))/2;

            if( x1 > x3 )///pinguim indo para a esquerda
            {
                listaJogadores.getLista()[w]->set_pode_mover(D, 1);//pode mover
                listaPersonagens.getLista()[i]->set_pode_mover(E, 1);//pode mover

                if( x1-x3 < distancia1 )//conferindo se também não estão na mesma altura
                {
                    if( y3-y1 < 0 )//O pinguim está abaixo do personagem
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(E, 1);
                        listaPersonagens.getLista()[i]->set_pode_mover(D, 1);
                    }
                    else if( y3-y1 <= distancia2+30 && y3-y1 >= distancia2 )//se está caindp
                    {
                        listaPersonagens.getLista()[i]->cair();
                        listaPersonagens.getLista()[i]->morrer();
                        //lista.erase(lista.begin()+i);
                        inimigos[i].vivo = 0;
                        (*pontos)+=PRESENTES;
                        listaJogadores.getLista()[w]->set_dy(-20);
                    }
                    else if( y3 - y1 >= distancia2 )//se está pulando por cima
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(E, 1);
                        listaPersonagens.getLista()[i]->set_pode_mover(D, 1);
                    }
                    else//se bate de lado
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(E, 0);
                        listaPersonagens.getLista()[i]->set_pode_mover(D, 0);
                        listaJogadores.getLista()[w]->vai_pra_direita();
                        listaJogadores.getLista()[w]->perde_uma_vida();
                        break;
                    }
                }
                else
                {
                    listaJogadores.getLista()[w]->set_pode_mover(E, 1);
                    listaPersonagens.getLista()[i]->set_pode_mover(D, 1);
                }


            }
            if( x1 < x3 )///pinguim indo para a direita
            {
                listaJogadores.getLista()[w]->set_pode_mover(E, 1);
                listaPersonagens.getLista()[i]->set_pode_mover(D, 1);

                if( x3-x1 < distancia1 )//diferenças de distancias
                {
                    if( y3-y1 < 0 )//O pinguim está abaixo do personagem
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(E, 1);
                        listaPersonagens.getLista()[i]->set_pode_mover(D, 1);
                    }
                    else if( y3-y1 <= distancia2+30 && y3-y1 >= distancia2 )//se está caindp
                    {
                        listaPersonagens.getLista()[i]->cair();
                        //lista.erase(lista.begin()+i);
                        inimigos[i].vivo = 0;
                        (*pontos)+=PRESENTES;
                        listaJogadores.getLista()[w]->set_dy(-20);
                    }
                    else if( y3 - y1 >= distancia2 )//se está pulando por cima
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(D, 1);
                        listaPersonagens.getLista()[i]->set_pode_mover(E, 1);
                    }
                    else//se bate de lado
                    {
                        listaJogadores.getLista()[w]->set_pode_mover(D, 0);
                        listaPersonagens.getLista()[i]->set_pode_mover(E, 0);
                        listaJogadores.getLista()[w]->vai_pra_esquerda();
                        listaJogadores.getLista()[w]->perde_uma_vida();
                        break;
                    }
                }
                else
                {
                    listaJogadores.getLista()[w]->set_pode_mover(D, 1);
                    listaPersonagens.getLista()[i]->set_pode_mover(E, 1);
                }
            }


        }
    }
}

///50 PONTOS PARA PEGAR UM GORE
void GerenciadorColisao::verificaColisaoItem(int* pontos)
{
    for( unsigned int w = 0 ; w < 2 ; w++ )//verifica para o primeiro e o segundo jogador
    {
        x1 = listaJogadores.getLista()[w]->get_x();
        y1 = listaJogadores.getLista()[w]->get_y();

        for( unsigned int i = 0 ; i < listaItens.getLista().size() ; i++ )//cuidado! estamos mechendo com a lista de objetos
        {
            x3 = listaItens.getLista()[i]->get_x();
            y3 = listaItens.getLista()[i]->get_y();

            distancia1 = (listaJogadores.getLista()[w]->get_frameHeight())/4 + (listaItens.getLista()[i]->get_altura())/2;
            if( x1-x3 > 0 )
                diferenca1 = x1-x3;
            else
                diferenca1 = x3-x1;

            if( y1-y3 > 0 )
                diferenca2 = y1-y3;
            else
                diferenca2 = y3-y1;

            if( (diferenca1 <= distancia1) && (diferenca2 <= distancia1) )
            {
                listaItens.getLista()[i]->set_obj_existe(0);
                listaJogadores.getLista()[w]->aumenta_bolas();
                //listaItens.erase(listaItens.begin()+i);
                listaItens.getLista()[i]->set_x(1000);//pra ter certeza de que ele não será mais impresso
                listaItens.getLista()[i]->set_y(1000);
                (*pontos) += GORES;
            }
        }
    }
}

void GerenciadorColisao::verificaColisaoPlataformas()
{
    int possivel_chao, achou;
    for( unsigned int w = 0 ; w < 2 ; w++ )//verifica para o primeiro e o segundo jogador
    {
        possivel_chao = listaJogadores.getLista()[w]->get_chao_atual();
        achou = 0;

        Lista<Plataforma*>::Elemento<Plataforma*>* elaux = new Lista<Plataforma*>::Elemento<Plataforma*>;


        for(elaux = listaPlataformas.getInicio(); elaux != NULL; elaux = elaux->getProximo())
        {
            Plataforma* aux = elaux->getConteudo();

            y2 = listaJogadores.getLista()[w]->get_y() - listaJogadores.getLista()[w]->get_frameHeight()/2*listaJogadores.getLista()[w]->get_escala();

            //conferindo se o jogador está na zona da plataforma
            if( listaJogadores.getLista()[w]->get_x() >= aux->get_extremo_esq() && listaJogadores.getLista()[w]->get_x() <= aux->get_extremo_dir() )//na zona x da plataforma
            {
                distancia1 = listaJogadores.getLista()[w]->get_frameHeight()*listaJogadores.getLista()[w]->get_escala();

                if( listaJogadores.getLista()[w]->get_y() <= aux->get_chao() )//está acima da plataforma
                {
                    if( aux->get_chao() <= possivel_chao )
                    {
                        possivel_chao = aux->get_chao();
                        achou = 1;
                    }
                }

                if( y2 >= aux->get_extremo_inferior() -15 && y2 <= aux->get_extremo_inferior()+15 )//conferindo se está abaixo da plataforma
                    listaJogadores.getLista()[w]->set_dy(0);

            }
            if( listaJogadores.getLista()[w]->get_x() >= aux->get_extremo_esq() - 15 && listaJogadores.getLista()[w]->get_x()<= aux->get_extremo_dir() + 15 )//confere a posição em x
            {
                if( listaJogadores.getLista()[w]->get_y() <= aux->get_y()+20 && listaJogadores.getLista()[w]->get_y() >= aux->get_y()-20 )//confere a altura
                {
                    if( listaJogadores.getLista()[w]->get_x() > aux->get_x() )//pinguim batendo pela esquerda
                        listaJogadores.getLista()[w]->set_pode_mover( 1, 0 );

                    else if( listaJogadores.getLista()[w]->get_x() < aux->get_x() )//pinguim batendo pela direita
                        listaJogadores.getLista()[w]->set_pode_mover( 0, 0 );
                }
            }
        }
        if( !achou )
            possivel_chao = listaJogadores.getLista()[w]->get_chao();
        listaJogadores.getLista()[w]->set_chao_atual( possivel_chao );


    }
}

