#include <vector>
#include "Item.h"

using namespace std;

class ListaItem
{
private:
    vector<Item*> lista;

public:
    ListaItem();
    ~ListaItem();
    void incluir(Item* p);
    void excluir(int pos);
    vector<Item*> getLista();
};
