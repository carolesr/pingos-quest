#include "../includes/ListaPersonagem.h"

ListaPersonagem::ListaPersonagem(){}

ListaPersonagem::~ListaPersonagem(){}

void ListaPersonagem::incluir(Personagem* p)
{
    lista.push_back(p);
}

void ListaPersonagem::excluir(int pos)
{
    lista.erase(lista.begin() + pos);
}


vector<Personagem*> ListaPersonagem::getLista()
{
    return lista;
}
