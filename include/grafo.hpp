#ifndef GRAFO
#define GRAFO

#include <map>
#include <vector>

//#include "gerador.hpp"
//#include "consumidor.hpp"
#include "ponto.hpp"

class Grafo{
    private:
        //std::map<int, std::vector<int>> conexoes;
        int** capacidades; //usada como capacidade do original e como fluxo pra frente no residual
        int** fluxos; //usada como fluxo de volta no residual

        Ponto origemGlobal;
        Ponto destinoGlobal;
        std::vector<Ponto> vertices;

    public:
        Grafo();
        ~Grafo();
        void adicionarOrigemDestino();
        void setConexao(int origem, int destino, int capacidade);
        void addPonto(Ponto ponto);
        void print();
        void criarGrafoResidual(Grafo grafo);
};



#endif