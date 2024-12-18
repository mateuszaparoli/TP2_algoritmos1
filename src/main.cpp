#include <cstdio>

#include "grafo.hpp"

int main(){
    int numPontos;
    int numFios;

    Grafo redeEletrica; 

    scanf("%d %d", &numPontos, &numFios);

    for(int i = 0; i < numPontos; i++){
        int identificador;
        char tipo;
        int demanda;

        scanf("%d %d", &identificador, &demanda);

        if(demanda == 0){
            tipo = 'g';
        }
        else{
            tipo = 'c';
        }
        Ponto ponto(identificador, tipo, demanda);

        redeEletrica.addPonto(ponto);
    }

    for(int i = 0; i < numFios; i++){
        int origem;
        int destino;
        int capacidade;

        scanf("%d %d %d", &origem, &destino, &capacidade);

        redeEletrica.setConexao(origem, destino, capacidade);
    }

    redeEletrica.print();
}