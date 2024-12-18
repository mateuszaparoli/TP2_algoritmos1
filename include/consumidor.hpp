#ifndef CONSUMIDOR
#define CONSUMIDOR

#include "ponto.hpp"

class Consumidor: public Ponto{
    private:
        int demanda;
    public:
        Consumidor(int identificador, int demanda);
        void setDemanda(int demanda);
        int getDemanda();
};


#endif