#include <vector>
#include "Personagem.h"
#include "Pinguim.h"
#include "PinguimRei.h"
#include "Peixinho.h"
#include "Passaro.h"
#include "Ursinho.h"

using namespace std;

class ListaPersonagem
{
private:
    vector<Personagem*> lista;

public:
    ListaPersonagem();
    ~ListaPersonagem();
    void incluir(Personagem* p);
    void excluir(int pos);
    vector<Personagem*> getLista();
};
