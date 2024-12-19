#include "grafo.hpp"
#include <queue>
#include <climits>

int BFS(Grafo* residual, int* antecessores, bool* visitados, int origemID, int destinoID){
    std::queue<int> fila;
    fila.push(origemID);

    while(!fila.empty()){
        int atual = fila.front();
        fila.pop();
        visitados[atual] = true;

        for(int i = 0; i < 500; i++){
            int k = residual->getCapacidade(atual, i);

            if(k > 0 && !visitados[i]){
                fila.push(i);
                antecessores[i] = atual;
            } 
        }
    }
    return visitados[destinoID];
}

int fordFulkerson(Grafo* grafoResidual, Ponto origem, Ponto destino){
    bool visitados[500];
    int antecessores[500];

    for(int i = 0; i < 500; i++){
        visitados[i] = false;
    }
    for(auto i = 0; i < 500; i++){
        antecessores[i] = -1;
    }

    int fluxoMax = 0;

    while( BFS(grafoResidual, antecessores, visitados, origem.getIdentificador(), destino.getIdentificador())){
        int fluxoCaminho = INT_MAX;


        for(int i = destino.getIdentificador(); i != origem.getIdentificador(); i = antecessores[i]){
            int j = antecessores[i];
            fluxoCaminho = std::min(fluxoCaminho, grafoResidual->getCapacidade(j, i));
        }

        for(int i = destino.getIdentificador(); i != origem.getIdentificador(); i = antecessores[i]){
            int j = antecessores[i];
            grafoResidual->setConexao(j,i, grafoResidual->getCapacidade(j,i) - fluxoCaminho);
            grafoResidual->setConexao(i,j, grafoResidual->getCapacidade(i,j) + fluxoCaminho);
        }

        fluxoMax += fluxoCaminho;
    }


    return fluxoMax;
}