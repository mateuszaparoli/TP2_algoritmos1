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
    
    /*for(auto [i, j] : saturadas) {
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
        saturadas.pop(i,j);
    }*/ 

    /*while (!saturadas.empty()) {
        int capacidadeMaior = 0;
        int imaior = -1;
        int jmaior = -1;
        size_t indiceMaior = 0;

        // Encontrar a aresta com maior capacidade
        for (size_t idx = 0; idx < saturadas.size(); ++idx) {
            auto [i, j] = saturadas[idx];
            if (capacidades[i][j] > capacidadeMaior) {
                capacidadeMaior = capacidades[i][j];
                imaior = i;
                jmaior = j;
                indiceMaior = idx;
            }
        }

        // Imprimir a aresta com maior capacidade
        if (imaior != -1 && jmaior != -1) {
            std::cout << imaior << " " << jmaior << " " << capacidadeMaior << std::endl;
        }

        // Remover a aresta com maior capacidade da lista manualmente
        saturadas.erase(saturadas.begin() + indiceMaior);
    }*/

    while (!saturadas.empty()) {
        int capacidadeMaior = 0;
        int imaior = -1;
        int jmaior = -1;
        size_t indiceMaior = 0;

        // Encontrar a aresta com maior capacidade
        for (size_t idx = 0; idx < saturadas.size(); ++idx) {
            auto [i, j] = saturadas[idx];
            if (capacidades[i][j] > capacidadeMaior) {
                capacidadeMaior = capacidades[i][j];
                imaior = i;
                jmaior = j;
                indiceMaior = idx;
            }
        }

        // Imprimir a aresta com maior capacidade
        if (imaior != -1 && jmaior != -1) {
            std::cout << imaior << " " << jmaior << " " << capacidadeMaior << std::endl;
        }

        // Remover manualmente o elemento encontrado
        for (size_t idx = indiceMaior; idx < saturadas.size() - 1; ++idx) {
            saturadas[idx] = saturadas[idx + 1];
        }
        saturadas.pop_back();
    }



    for(int i = 0; i < TAMANHO; i++){
        delete[] capacidades[i];
    }
    delete[] capacidades;

    return 0;
}