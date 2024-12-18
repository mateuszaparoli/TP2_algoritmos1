#ifndef GRAFO
#define GRAFO

#include <map>
#include <vector>

#include "gerador.hpp"
#include "consumidor.hpp"

class Grafo{
    private:
        std::map<int, std::vector<int>> conexoes;
        Ponto origemGlobal;
        Ponto destinoGlobal;

    public:
        Grafo(Ponto origemGlobal, Ponto destinoGlobal);
        ~Grafo();
        void setConexao(Ponto origem, Ponto destino);
        void addPonto(Ponto ponto);
};



#endif