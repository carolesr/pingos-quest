#include <vector>
#include "Jogador.h"

using namespace std;

class ListaJogador
{
private:
    vector<Jogador*> lista;

public:
    ListaJogador();
    ~ListaJogador();
    void incluir(Jogador* p);
    void excluir(int pos);
    vector<Jogador*> getLista();
};
