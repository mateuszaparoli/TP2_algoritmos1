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

    fluxos = new int*[500];
    for(int i = 0; i < 500; i++){
        fluxos[i] = new int[500];
        for(int j = 0; j < 500; j++){
            fluxos[i][j] = 0;
        }
    }

    this->vertices = std::vector<Ponto>();
}

Grafo::~Grafo(){
    for(int i = 0; i < 500; i++){
        delete[] capacidades[i];
    }
    delete[] capacidades;
    for(int i = 0; i < 500; i++){
        delete[] fluxos[i];
    }
    delete[] fluxos;
}

void Grafo::adicionarOrigemDestino(){
    this->origemGlobal.setIdentificador(0);
    this->origemGlobal.setTipo('g');
    this->origemGlobal.setDemanda(0);
    this->destinoGlobal.setIdentificador(499);
    this->destinoGlobal.setTipo('c');
    this->destinoGlobal.setDemanda(2000);

    vertices.push_back(origemGlobal);
    vertices.push_back(destinoGlobal);
}

void Grafo::setConexao(int origem, int destino, int capacidade){
    if(capacidades[origem][destino] != 0){
        std::cout << "Conexao de " << origem << " para " << destino << " ja existe" << std::endl;
        return;
    }
    capacidades[origem][destino] = capacidade;
    //std::cout << "Conexao de " << origem << " para " << destino << " de capacidade " << capacidade << " estabelecida" << std::endl;
    return;
}

void Grafo::addPonto(Ponto ponto){
    if(ponto.getTipo() == 'g'){
        setConexao(origemGlobal.getIdentificador(), ponto.getIdentificador(), 20000000);
        vertices.push_back(ponto);
    }
    else if(ponto.getTipo() == 'c'){
        setConexao(ponto.getIdentificador(), destinoGlobal.getIdentificador(), 20000000);
        vertices.push_back(ponto);
    }

    return;
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

void Grafo::criarGrafoResidual(Grafo grafoResidual){
    for(int i = 0; i < 500; i++){
       for(int j = 0; j < 500; j++){
            grafoResidual.capacidades[i][j] = this->capacidades[i][j] - this->fluxos[i][j];
            grafoResidual.capacidades[j][i] = this->fluxos[i][j];
        }
    }
}