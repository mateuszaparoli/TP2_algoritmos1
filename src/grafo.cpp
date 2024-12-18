#include "grafo.hpp"
#include <iostream>

Grafo::Grafo(){
    Ponto* a = new Ponto(0, 'g', 0);
    Ponto* b = new Ponto(2000, 'c', 2000);
    std::cout << "a: " << a->getIdentificador() << std::endl;
    std::cout << "b: " << b->getIdentificador() << std::endl;
}

Grafo::~Grafo(){}

void Grafo::setConexao(Ponto origem, Ponto destino, int capacidade){
    int idOrigem = origem.getIdentificador();
    int idDestino = destino.getIdentificador();
    conexoes[idOrigem].push_back(idDestino);
    std::cout << "Conexao de " << idOrigem << " para " << idDestino << " com capacidade " << capacidade << std::endl;
}

void Grafo::addPonto(Ponto ponto){
    if(ponto.getTipo() == 'g'){
        setConexao(origemGlobal, ponto, 20000);
    }
    else if(ponto.getTipo() == 'c'){
        setConexao(ponto, destinoGlobal, 20000);
    }
}
