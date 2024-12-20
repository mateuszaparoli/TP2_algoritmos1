#ifndef GRAFO
#define GRAFO

#include <map>
#include <vector>

#include "ponto.hpp"
#define TAMANHO 100


class Grafo{
    private:
        int** capacidades; //usada como capacidade do original e como fluxo pra frente no residual
        int** fluxos; //usada como reversas

        Ponto origemGlobal;
        Ponto destinoGlobal;
        std::vector<Ponto> vertices;
        int geracaoTotal = 0;

        int ativos[TAMANHO];

    public:
        Grafo();
        ~Grafo();
        //void adicionarOrigemDestino();
        void setConexao(int origem, int destino, int capacidade);
        void setConexaoReversa(int origem, int destino, int capacidade);
        void addPonto(Ponto ponto);
        void print();
        void criarGrafoResidual(Grafo* grafo, Grafo* GrafoResidual);
        int getCapacidade(int origem, int destino);
        int getCapacidadeReversa(int origem, int destino);
        Ponto getDestino();
        Ponto getOrigem();
        bool getAtivo(int i);
        void printMatriz();
        std::vector<std::pair<int, int>> getSaturadas();
        Ponto getPonto(int i);
        int getGeracaoTotal();
};



#endif