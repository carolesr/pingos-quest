#pragma once
#include <iostream>

template<class TIPO>
class Lista
{
public:

    template <class T>
    class Elemento
    {
    private:
        Elemento<T>* proximo;
        T conteudo;
    public:
        Elemento() { proximo = NULL; conteudo = NULL; }
        ~Elemento(){}
        void setProximo(Elemento<T>* pp) { proximo = pp; }
        Elemento<T>* getProximo() { return proximo; }
        void setConteudo(T cont) { conteudo = cont; }
        T getConteudo() { return conteudo; }
    };

    private:

    Elemento<TIPO>* inicio;
    Elemento<TIPO>* atual;

    public:

    Lista();
    ~Lista();
    void incluir(TIPO pp);
    void excluir();
    Elemento<TIPO>* getInicio();
    Elemento<TIPO>* getAtual();
};

template<class TIPO>
Lista<TIPO>::Lista()
{
    inicio = NULL;
    atual = NULL;
}

template<class TIPO>
Lista<TIPO>::~Lista()
{
    excluir();
}

template<class TIPO>
void Lista<TIPO>::incluir(TIPO pp)
{
    if(pp)
    {
        Elemento<TIPO>* novo = new Elemento<TIPO>;
        novo->setConteudo(pp);

        if(inicio == NULL) //Se a lista estiver vazia
        {
            inicio = novo;
            atual = novo;
        }
        else //Se ja tiver coisa na lista
        {
            atual->setProximo(novo);
            atual = novo;
        }
    }
}

template<class TIPO>
void Lista<TIPO>::excluir()
{
    while(inicio->getProximo() != NULL)
    {
        Elemento<TIPO>* aux = inicio;
        aux = inicio->getProximo();
        inicio->setProximo(aux->getProximo());
        delete(aux);
    }
}

template<class TIPO>
Lista<TIPO>::Elemento<TIPO>* Lista<TIPO>::getInicio()
{
    return inicio;
}

template<class TIPO>
Lista<TIPO>::Elemento<TIPO>* Lista<TIPO>::getAtual()
{
    return atual;
}



