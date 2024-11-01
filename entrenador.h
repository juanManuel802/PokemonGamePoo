#ifndef ENTRENADOR_H
#define ENTRENADOR_H
#include <iostream>
#include <vector>
#include "pokemon.h"
#include "epersonalizado.h"
using namespace std;

class Entrenador {
private:
    vector<Pokemon> misPokemones; // aunque debe ser 3, eso se maneja en la excepción
    string nombre;
    int nivel;

public:
    Entrenador();
    string getNombre() const;
    int getNivel() const;
    void setNombre(string nombre);
    void setNivel(int nivel);
    Pokemon &getPokemon(int i);
    void agregarpokemon(Pokemon &poke);
    void entrenar(Pokemon &miPok, const Pokemon &oponente);
    void aumentarNivel();
    bool operator==(const Entrenador &ec) const;
    friend ostream &operator<<(ostream &o, Entrenador c);
};

#endif 
