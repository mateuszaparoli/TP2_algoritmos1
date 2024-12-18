#include "grafo.hpp"

Grafo::Grafo(Ponto origemGlobal, Ponto destinoGlobal){
    Ponto origemGlobal = new Ponto(0, 'g', 0);
    Ponto destinoGlobal = new Ponto(2000, 'c', 2000);
}

Grafo::~Grafo(){
    delete origemGlobal;
    delete destinoGlobal;
}

Grafo::setConexao(Ponto origem.getIdentificador(), Ponto destino.getIdentificador){
    conexoes[origem].push_back(destino);
}

Grafo::addPonto(Ponto ponto){
    if(ponto.getTipo() == 'g'){
        setConexao(origemGlobal, ponto, 20000);
    }
    else if(ponto.getTipo == 'c'){
        setConexao(ponto, destinoGlobal, 20000);
    }
}