
#include "../includes/Plataforma.h"

Plataforma::Plataforma( int _x , int _y, float e, int a, int l, int _linhas, int _colunas ):
Entidade( _x , _y, e, a, l, _linhas, _colunas ){}

Plataforma::~Plataforma(){ sprite = NULL; }

int Plataforma::get_extremo_esq(){ return( x-(escala*largura/2)-5); }
int Plataforma::get_extremo_dir(){ return(x+(escala*largura/2)+5); }
int Plataforma::get_chao(){ return(y - (1.9*escala*altura/2)); }
int Plataforma::get_extremo_inferior(){ return(y+escala*altura/2); }
