#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
using namespace std;


class Pokemon
{
private:
    string nombre;
    string color;
    int ataque;
    int vida;
    int xp;
    int nivel;
    string ataqueEspecial;

public:
    Pokemon();
    Pokemon(string nombre, string color, int ataque, int vida, int xp, int nivel, string ataqueEspecial);

    string getNombre() const;
    string getColor() const;
    string getAtaqueEspecial() const;
    int getAtaque() const; 
    int getVida() const;
    int getXp() const;
    int getNivel() const; 

    void setNombre(string nombre);
    void setColor(string color);
    void setAtaque(int ataque);
    void setVida(int vida);
    void setXp(int xp);
    void setNivel(int nivel);
    void setAtaqueEspecial(string ataqueEspecial);

    void saludar();

    void sanar();

    void evolucionar(string nombre, string color);
    bool verificarAumentoNivel();

    void aumentarNivel();

    void mostrarDatos();

    // sobrecarga del + para crear pokemon recargado
    Pokemon operator+(const Pokemon &c) const;
    bool operator==(const Pokemon &p) const;

    friend ostream &operator<<(ostream &o, Pokemon c);
};

#endif