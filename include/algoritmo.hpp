#include "../include/grafo.hpp"
#include <queue>
#include <climits>


//BFS para achar os caminhos simples
bool BFS(Grafo* residual, int* antecessores, bool* reversed, bool* visitados, int origemID, int destinoID){
    std::queue<int> fila;
    fila.push(origemID);

    while(!fila.empty()){
        int atual = fila.front();
        fila.pop();
        visitados[atual] = true;

        for(int i = 0; i < TAMANHO; i++){
            if(atual != i){
                int k = residual->getCapacidade(atual, i);
                if(k > 0 && !visitados[i]){
                    fila.push(i);
                    visitados[i] = true;
                    antecessores[i] = atual;
                    reversed[i] = false;
                    if(i == destinoID) {
                        visitados[destinoID] = true;
                        break;
                    } 
                } else {
                    k = residual->getCapacidadeReversa(atual, i);

                    if(k > 0 && !visitados[i]){
                        fila.push(i);
                        visitados[i] = true;
                        antecessores[i] = atual;
                        reversed[i] = true;
                        if(i == destinoID) {
                            visitados[destinoID] = true;
                            break;
                        }
                    }
                }

            }
        }
    }
    return visitados[destinoID];
}

//Ford Fulkerson algoritimo principal do programa
int fordFulkerson(Grafo* grafoResidual, Ponto origem, Ponto destino){
    bool visitados[TAMANHO];
    int antecessores[TAMANHO];
    bool reversed[TAMANHO];

    for(int i = 0; i < TAMANHO ; i++){
        visitados[i] = false;
    }
    for(auto i = 0; i < TAMANHO ; i++){
        antecessores[i] = -1;
    }

    int fluxoMax = 0;

    while( BFS(grafoResidual, antecessores, reversed, visitados, origem.getIdentificador(), destino.getIdentificador())){

        int fluxoCaminho = INT_MAX;

        //laço para encontrar o fluxo do caminho
        for(int i = destino.getIdentificador(); i != origem.getIdentificador(); i = antecessores[i]){
            int j = antecessores[i];
            if(reversed[i]) {
                if(grafoResidual->getCapacidadeReversa(j, i) < fluxoCaminho) {
                    fluxoCaminho = grafoResidual->getCapacidadeReversa(j, i);
                }
            } else {
                if(grafoResidual->getCapacidade(j, i) < fluxoCaminho) {
                    fluxoCaminho = grafoResidual->getCapacidade(j, i);
                }
            }
        }

        //laço para atualizar a capacidade das arestas do grafo residual
        for(int i = destino.getIdentificador(); i != origem.getIdentificador(); i = antecessores[i]){
            int j = antecessores[i];
            if(reversed[i]) {
                grafoResidual->setConexaoReversa(j,i, grafoResidual->getCapacidadeReversa(j,i) - fluxoCaminho);
                grafoResidual->setConexao(i,j, grafoResidual->getCapacidade(i,j) + fluxoCaminho);
            } else {
                grafoResidual->setConexao(j,i, grafoResidual->getCapacidade(j,i) - fluxoCaminho);
                grafoResidual->setConexaoReversa(i,j, grafoResidual->getCapacidadeReversa(i,j) + fluxoCaminho);
            }
        }
        
        fluxoMax += fluxoCaminho;
        //reinicializar os vetores
        for(int i = 0; i < TAMANHO ; i++){
            visitados[i] = false;
        }
        for(auto i = 0; i < TAMANHO ; i++){
            antecessores[i] = -1;
        }
    }
    
    return fluxoMax;
}