#ifndef BATALLA_H
#define BATALLA_H

#include <iostream>
#include <vector>
#include "pokemon.h"
#include "entrenador.h"
#include "epersonalizado.h"
using namespace std;

class Batalla {
private:
    int registroDaño;
    vector<string> ganadoresCombatesPok;
    string contrincantes[2];
    string ganador;
    vector<int> registroRondas;

public:
    Batalla();
    Batalla(string ent1, string ent2);
    int getRegistroDaño() const;
    string getGanador() const;
    string getContrincante(int i) const;
    string getGanadoresCombatesPok(int i);
    void setGanador(Entrenador &en);
    void setRegistroDaño(int registroDaño);
    void agregarPokGanador(Pokemon &pok);
    void agregarRondas(int rond);
    void luchar(Pokemon &miPok, Pokemon &oponente, bool &ganador);
    friend ostream &operator<<(ostream &o, Batalla b);
};

#endif 