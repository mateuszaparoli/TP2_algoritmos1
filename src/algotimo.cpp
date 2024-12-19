#include "grafo.hpp"

void fordFulkerson(Grafo& grafoResidual, Ponto origem, Ponto destino){
    for(int i = 0; i < 500; i++){
        for(int j = 0; j < 500; j++){
            grafoResidual.setFluxo(i, j, 0);
        }
    }
    origem.setDemanda(0);
    destino.setDemanda(2000);
}