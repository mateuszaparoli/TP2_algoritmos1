#include "grafo.hpp"
#include <iostream>

Grafo::Grafo(){
    capacidades = new int*[500];
    for(int i = 0; i < 500; i++){
        capacidades[i] = new int[500];
        for(int j = 0; j < 500; j++){
            capacidades[i][j] = 0;
        }
    }
    origemGlobal.setIdentificador(0);
    origemGlobal.setTipo('g');
    origemGlobal.setDemanda(0);
    destinoGlobal.setIdentificador(499);
    destinoGlobal.setTipo('c');
    destinoGlobal.setDemanda(2000);
}

Grafo::~Grafo(){
    for (int i = 0; i < 500; i++){
        delete[] capacidades[i];
    }
    delete[] capacidades;
}

void Grafo::setConexao(int origem, int destino, int capacidade){
    if(capacidades[origem][destino] != 0){
        std::cout << "Conexao de " << origem << " para " << destino << " ja existe" << std::endl;
        return;
    }
    capacidades[origem][destino] = capacidade;
    //std::cout << "Conexao de " << origem << " para " << destino << " de capacidade " << capacidade << " estabelecida" << std::endl;
}

void Grafo::addPonto(Ponto ponto){
    if(ponto.getTipo() == 'g'){
        setConexao(origemGlobal.getIdentificador(), ponto.getIdentificador(), 20000);
    }
    else if(ponto.getTipo() == 'c'){
        setConexao(ponto.getIdentificador(), destinoGlobal.getIdentificador(), 20000);
    }
}

void Grafo::print(){
    for(int i = 0; i < 500; i++){
        for(int j = 0; j < 500; j++){
            if(capacidades[i][j] != 0){
                std::cout << "Conexao de " << i << " para " << j << " de capacidade " << capacidades[i][j] << std::endl;
            }
        }
    }
    return;
}