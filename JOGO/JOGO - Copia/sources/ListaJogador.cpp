#include "../includes/ListaJogador.h"

ListaJogador::ListaJogador(){}

ListaJogador::~ListaJogador(){}

void ListaJogador::incluir(Jogador* p)
{
    lista.push_back(p);
}

void ListaJogador::excluir(int pos)
{
    lista.erase(lista.begin() + pos);
}

vector<Jogador*> ListaJogador::getLista()
{
    return lista;
}
