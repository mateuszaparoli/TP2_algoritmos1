#include "grafo.hpp"
#include <iostream>

Grafo::Grafo(){
    capacidades = new int*[500];
    for(int i = 0; i < 500; i++){
        capacidades[i] = new int[500];
        for(int j = 0; j < 500; j++){
            capacidades[i][j] = -1;
        }
    }

    fluxos = new int*[500];
    for(int i = 0; i < 500; i++){
        fluxos[i] = new int[500];
        for(int j = 0; j < 500; j++){
            fluxos[i][j] = 0;
        }
    }

    this->origemGlobal.setIdentificador(0);
    this->origemGlobal.setTipo('g');
    this->origemGlobal.setDemanda(0);
    this->destinoGlobal.setIdentificador(499);
    this->destinoGlobal.setTipo('c');
    this->destinoGlobal.setDemanda(2000);

    capacidades[0][499] = -1;
    capacidades[499][0] = -1;
    fluxos[0][499] = 0;
    fluxos[499][0] = 0;

    for(int i = 1; i < 499; i++){
        ativos[i] = 0;
    }

    ativos[0] = 1;
    ativos[499] = 1;

    //vertices.push_back(origemGlobal);
    //vertices.push_back(destinoGlobal);

    //this->vertices = std::vector<Ponto>();
}

//arrumar os free
Grafo::~Grafo(){
    //for(int i = 0; i < 500; i++){
    //    delete[] capacidades[i];
    //}
    //delete[] capacidades;
    //for(int i = 0; i < 500; i++){
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
    for(int i = 0; i < 500; i++){
        for(int j = 0; j < 500; j++){
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

void Grafo::criarGrafoResidual(Grafo grafo,Grafo grafoResidual){
    for(int i = 0; i < 500; i++){
       for(int j = 0; j < 500; j++){
            if(grafo.capacidades[i][j] > (-1) && i < j ){
                std::cout << "aaaaaaa" << grafo.capacidades[i][j] << std::endl;

                ativos[i] = 1;
                ativos[j] = 1;

                int capacidade = grafo.capacidades[i][j] - grafo.fluxos[i][j];
                int fluxo = grafo.fluxos[i][j];
                
                grafoResidual.setConexao(i, j, capacidade);
                grafoResidual.setConexao(j, i, fluxo);

                grafoResidual.fluxos[i][j] = 0;
                grafoResidual.fluxos[j][i] = 0;
            }
        }
    }
}

