#ifndef GRAFO
#define GRAFO

#include <map>
#include <vector>

#include "gerador.hpp"
#include "consumidor.hpp"
#include "ponto.hpp"

class Grafo{
    private:
        std::map<int, std::vector<int>> conexoes;
        Ponto origemGlobal;
        Ponto destinoGlobal;

    public:
        Grafo();
        ~Grafo();
        void setConexao(Ponto origem, Ponto destino, int capacidade);
        void addPonto(Ponto ponto);
};



#endif