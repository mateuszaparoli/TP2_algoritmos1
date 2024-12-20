#include <cstdio>
#include <iostream>
#include "algoritmo.hpp"

int main(){
    int numPontos;
    int numFios;

    Grafo redeEletrica; 
    Grafo grafoResidual;

    //redeEletrica.adicionarOrigemDestino();
    int** capacidades;
    capacidades = new int*[TAMANHO];
    for(int i = 0; i < TAMANHO; i++){
        capacidades[i] = new int[TAMANHO];
        for(int j = 0; j < TAMANHO; j++){
            capacidades[i][j] = -1;
        }
    }

    scanf("%d %d", &numPontos, &numFios);

    int demanda_total = 0;
    for(int i = 0; i < numPontos; i++){
        int identificador;
        char tipo;
        int demanda;

        scanf("%d %d", &identificador, &demanda);
        demanda_total += demanda;
        if(demanda == 0){
            tipo = 'g';
        }
        else{
            tipo = 'c';
        }
        Ponto ponto(identificador, tipo, demanda);

        redeEletrica.addPonto(ponto);
        grafoResidual.addPonto(ponto);
    }

    for(int i = 0; i < numFios; i++){
        int origem;
        int destino;
        int capacidade;

        scanf("%d %d %d", &origem, &destino, &capacidade);

        redeEletrica.setConexao(origem, destino, capacidade);
        grafoResidual.setConexao(origem, destino, capacidade);
        capacidades[origem][destino] = capacidade;
    }

    //redeEletrica.print();

    //std::cout << "Grafo Residual" << std::endl;
    
    int fluxoMax = fordFulkerson(&grafoResidual, redeEletrica.getOrigem(), redeEletrica.getDestino());

    std::cout << fluxoMax << std::endl;

    std::cout << (demanda_total - fluxoMax) << std::endl;

    std::cout << (grafoResidual.getGeracaoTotal() - fluxoMax) << std::endl;

    std::vector<std::pair<int, int>> saturadas = grafoResidual.getSaturadas();
    std::cout << saturadas.size() << std::endl;
    
    for(auto [i, j] : saturadas) {
        int capacidadeMaior = 0;
        int imaior = -1;
        int jmaior = -1;
        for(auto [i, j] : saturadas) {
            if(capacidades[i][j] > capacidadeMaior){
                capacidadeMaior = capacidades[i][j];
                imaior = i;
                jmaior = j;
            }
        }
        std::cout << imaior << " " << jmaior << " " << capacidades[i][j] << std::endl;
        saturadas.pop_back();
    }

    for(int i = 0; i < TAMANHO; i++){
        delete[] capacidades[i];
    }
    delete[] capacidades;

    return 0;
}