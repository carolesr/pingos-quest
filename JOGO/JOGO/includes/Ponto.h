#pragma once

class Ponto
{
protected:
    int x;
    int y;
public:
    Ponto(int _x, int _y);
    ~Ponto();

    void set_x(const int _x);
    void set_y(const int _y);
    const int get_x()const ;
    const int get_y()const ;
};
