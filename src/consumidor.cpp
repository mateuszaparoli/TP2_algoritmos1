#include "consumidor.hpp"

Consumidor::Consumidor(int identificador,int demanda):Ponto(identificador, 'c', demanda){
    this->demanda = demanda;
}