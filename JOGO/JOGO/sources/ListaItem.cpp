#include "../includes/ListaItem.h"

ListaItem::ListaItem(){}

ListaItem::~ListaItem(){}

void ListaItem::incluir(Item* p)
{
    lista.push_back(p);
}

void ListaItem::excluir(int pos)
{
    lista.erase(lista.begin() + pos);
}

vector<Item*> ListaItem::getLista()
{
    return lista;
}
