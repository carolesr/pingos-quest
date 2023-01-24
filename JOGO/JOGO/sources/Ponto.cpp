
#include "../includes/Ponto.h"

Ponto::Ponto(int _x, int _y)
{
    x = _x;
    y = _y;
}
Ponto::~Ponto(){}

void Ponto::set_x(const int _x){ x = _x; }
void Ponto::set_y(const int _y){ y = _y; }
const int Ponto::get_x() const { return(x); }
const int Ponto::get_y() const { return(y); }
