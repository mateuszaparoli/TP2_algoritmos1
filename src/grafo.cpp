#include "grafo.hpp"
#include <iostream>

Grafo::Grafo(){
    capacidades = new int*[TAMANHO];
    for(int i = 0; i < TAMANHO; i++){
        capacidades[i] = new int[TAMANHO];
        for(int j = 0; j < TAMANHO; j++){
            capacidades[i][j] = -1;
        }
    }

    fluxos = new int*[TAMANHO];
    for(int i = 0; i < TAMANHO; i++){
        fluxos[i] = new int[TAMANHO];
        for(int j = 0; j < TAMANHO; j++){
            fluxos[i][j] = 0;
        }
    }

    this->origemGlobal.setIdentificador(0);
    this->origemGlobal.setTipo('g');
    this->origemGlobal.setDemanda(0);
    this->destinoGlobal.setIdentificador(TAMANHO - 1);
    this->destinoGlobal.setTipo('c');
    this->destinoGlobal.setDemanda(2000);

    capacidades[0][TAMANHO - 1] = -1;
    capacidades[TAMANHO - 1][0] = -1;
    fluxos[0][TAMANHO - 1] = 0;
    fluxos[TAMANHO - 1][0] = 0;

    for(int i = 1; i < TAMANHO - 1; i++){
        ativos[i] = 0;
    }

    ativos[0] = 1;
    ativos[TAMANHO - 1] = 1;

    //vertices.push_back(origemGlobal);
    //vertices.push_back(destinoGlobal);

    //this->vertices = std::vector<Ponto>();
}

//arrumar os delete talvez colocar free
Grafo::~Grafo(){
    //for(int i = 0; i < TAMANHO; i++){
    //    delete[] capacidades[i];
    //}
    //delete[] capacidades;
    //for(int i = 0; i < TAMANHO; i++){
    //    delete[] fluxos[i];
    //}
    //delete[] fluxos;
}

void Grafo::setConexao(int origem, int destino, int capacidade){
    //if(capacidades[origem][destino] != -1){
    //    std::cout << "Conexao de " << origem << " para " << destino << " ja existe" << std::endl;
    //    return;
    //}
    capacidades[origem][destino] = capacidade;
    //std::cout << "Conexao de " << origem << " para " << destino << " de capacidade " << capacidade << " estabelecida" << std::endl;
    return;
}

void Grafo::addPonto(Ponto ponto){
    if(ponto.getTipo() == 'g'){
        setConexao(origemGlobal.getIdentificador(), ponto.getIdentificador(), 20000);
        //vertices.push_back(ponto);
        ativos[ponto.getIdentificador()] = 1;
        return;
    }
    else if(ponto.getTipo() == 'c'){
        setConexao(ponto.getIdentificador(), destinoGlobal.getIdentificador(), 20000);
        //vertices.push_back(ponto);
        ativos[ponto.getIdentificador()] = 1;
        return;
    }

    return;
}

void Grafo::print(){
    for(int i = 0; i < TAMANHO; i++){
        for(int j = 0; j < TAMANHO; j++){
            if(capacidades[i][j] > -1 && i != j && ativos[i] == 1 && ativos[j] == 1){
                std::cout << "Conexao de " << i << " para " << j << " de capacidade " << capacidades[i][j] << std::endl;
            }
            if(capacidades[i][j] == -1){
                continue;
            }
        }
    }
    return;
}

//achar um jeito de nao ter a aresta 0-2 no residual

void Grafo::criarGrafoResidual(Grafo* grafo,Grafo* grafoResidual){
    for(int i = 0; i < TAMANHO; i++){
       for(int j = 0; j < TAMANHO; j++){
            if(grafo->capacidades[i][j] > (-1) && i < j ){
                std::cout << "aaaaaaa" << grafo->capacidades[i][j] << std::endl;

                ativos[i] = 1;
                ativos[j] = 1;

                int capacidade = grafo->capacidades[i][j] - grafo->fluxos[i][j];
                int fluxo = grafo->fluxos[i][j];
                
                grafoResidual->setConexao(i, j, capacidade);
                grafoResidual->setConexao(j, i, fluxo);

                grafoResidual->fluxos[i][j] = 0;
                grafoResidual->fluxos[j][i] = 0;
            }
        }
    }
}

void Grafo::setFluxo(int origem, int destino, int fluxo){
    fluxos[origem][destino] = fluxo;
    return;
}

void Grafo::atualizarGrafo(Grafo* grafoResidual){
    for(int i = 0; i < TAMANHO; i++){
        for(int j = 0; j < TAMANHO; j++){
            if(grafoResidual->capacidades[i][j] > -1){
                if(grafoResidual->fluxos[i][j] < grafoResidual->capacidades[i][j]){
                    grafoResidual->capacidades[i][j] = grafoResidual->capacidades[i][j] - grafoResidual->fluxos[i][j];
                }
                if(grafoResidual->fluxos[i][j] > 0){
                    grafoResidual->capacidades[j][i] = grafoResidual->fluxos[i][j];
                }
            }
        }
    }
    return;
}

int Grafo::getCapacidade(int origem, int destino){
    return capacidades[origem][destino];
}

Ponto Grafo::getDestino(){
    return destinoGlobal;
}

Ponto Grafo::getOrigem(){
    //std::cout << "origem: " << origemGlobal.getIdentificador() << std::endl;
    return origemGlobal;
}

bool Grafo::getAtivo(int i){
    return ativos[i];
}