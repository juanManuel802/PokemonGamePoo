#include "entrenador.h"
#include "epersonalizado.h"
#include <iostream>
using namespace std;

Entrenador::Entrenador() : nombre(""), nivel(1) {}

string Entrenador::getNombre() const { return nombre; }
int Entrenador::getNivel() const { return nivel; }
void Entrenador::setNombre(string nombre) { this->nombre = nombre; }
void Entrenador::setNivel(int nivel) { this->nivel = nivel; }

Pokemon &Entrenador::getPokemon(int i) {
    return misPokemones[i];
}

void Entrenador::agregarpokemon(Pokemon &poke) {
    if (misPokemones.size() < 3) {
        misPokemones.push_back(poke);
    } else {
        throw Epersonalizado("Error al agregar el pokemon", "El limite son 3 pokemones");
    }
}

void Entrenador::entrenar(Pokemon &miPok, const Pokemon &oponente) {
    miPok.setXp(miPok.getXp() + oponente.getNivel() * nivel);
    cout << "El entrenador " << nombre << " ha entrenado a " << miPok.getNombre() << endl;
    if (miPok.verificarAumentoNivel()) {
        string nombre, color;
        // Cambiar mensajes
        cout << "¡Enhorabuena, has subido de nivel!!\nPuedes cambiar el nombre y color de tu Pokémon. Además, la potencia de ataque se aumentó un 20%\n";
        cout << "Nuevo nombre:\n";
        cin >> nombre;
        cout << "Nuevo color:\n";
        cin >> color;
        miPok.aumentarNivel();
        miPok.evolucionar(nombre, color);
        aumentarNivel();
    }
    cout << miPok;
}

void Entrenador::aumentarNivel() {
    setNivel(getNivel() + 1);
}
//const despues de parentesis
bool Entrenador::operator==(const Entrenador &ec) const{
    if (nombre != ec.nombre || nivel != ec.nivel)
        return false;
    if (misPokemones.size() != ec.misPokemones.size())
        return false;
    for (int i = 0; i < misPokemones.size(); ++i) {
        if (!(misPokemones[i] == ec.misPokemones[i]))
            return false;
    }
    return true;
}

ostream &operator<<(ostream &o, Entrenador c) {
    for (const auto &poke : c.misPokemones) {
        o << poke << " ";
    }
    return o;
}