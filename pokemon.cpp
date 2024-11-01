#include "pokemon.h"
#include <iostream>
using namespace std;


Pokemon::Pokemon(): nombre("Pokemon"), color("amarillo"), ataque(20), vida(100), xp(0), nivel(1), ataqueEspecial("") {}

Pokemon::Pokemon(string nombre, string color, int ataque, int vida, int xp, int nivel, string ataqueEspecial)
{
    this->nombre = nombre;
    this->color = color;
    this->ataque = ataque;
    this->vida = vida;
    this->xp = xp;
    this->nivel = nivel;
    this->ataqueEspecial = ataqueEspecial;
}

string Pokemon::getNombre() const { return nombre; }
string Pokemon::getColor() const { return color; }
string Pokemon::getAtaqueEspecial() const { return ataqueEspecial; }
int Pokemon::getAtaque() const { return ataque; }
int Pokemon::getVida() const { return vida; }
int Pokemon::getXp() const { return xp; }
int Pokemon::getNivel() const { return nivel; }

void Pokemon::setNombre(string nombre) { this->nombre = nombre; }
void Pokemon::setColor(string color) { this->color = color; }
void Pokemon::setAtaque(int ataque) { this->ataque = ataque; }
void Pokemon::setVida(int vida) { this->vida = vida; }
void Pokemon::setXp(int xp) { this->xp = xp; }
void Pokemon::setNivel(int nivel) { this->nivel = nivel; }
void Pokemon::setAtaqueEspecial(string ataqueEspecial) { this->ataqueEspecial = ataqueEspecial; }

void Pokemon::saludar()
{
    cout << "¡Hola!, soy " << nombre << ", estoy a tu disposición." << endl;
    mostrarDatos();
}

void Pokemon::sanar()
{
    if (vida < 100)
    {
        vida = 100;
    }
}

void Pokemon::evolucionar(string nombre, string color)
{
    if (nivel == 2)
    {
        this->nombre = nombre;
        this->color = color;
        ataque += ataque * 0.2;
    }
    else if (nivel == 3)
    {
        this->nombre = nombre;
        this->color = color;
        ataque += ataque * 0.2;
    }
    mostrarDatos();
}
bool Pokemon::verificarAumentoNivel()
{
    return xp > nivel * 100;
}

void Pokemon::aumentarNivel()
{
    nivel++;
}

void Pokemon::mostrarDatos()
{
    cout << nombre << " Color: " << color << " || Nivel de Vida: " << vida << " || Potencia de Ataque: " << ataque << " || Xp: " << xp << " || Nivel: " << nivel << endl;
}

// sobrecarga del + para crear pokemon recargado
Pokemon Pokemon::operator+(const Pokemon &c) const
{
    // creamos un objeto nuevo de la clase cargo llamado "pokemonrecargado" e instantaneamente en sus parametros
    // sumamos los atributos de otros objetos para agregarlos en los atributos de "pokemonrecargado"
    // y luego se retorna el objeto
    Pokemon pokemonrecargado(" SuperPokemon! ", " multicolor! ", ataque + c.ataque, vida + c.vida, xp + c.xp, nivel + c.nivel, "Vacio infinito!");

    return pokemonrecargado;
}
bool Pokemon::operator==(const Pokemon &p) const
{
    return (nombre == p.nombre &&
            color == p.color &&
            ataque == p.ataque &&
            vida == p.vida &&
            xp == p.xp &&
            nivel == p.nivel &&
            ataqueEspecial == p.ataqueEspecial);
}

ostream &operator<<(ostream &o, Pokemon p)
{
    return o << "\nNombre: " << p.getNombre() << " \n color: " << p.getColor() << "\n ataque: " << p.getAtaque() << "\n vida " << p.getVida() << " \n experiencia: " << p.getXp() << "\n nivel: " << p.getNivel() << "\n ataque especial: " << p.getAtaqueEspecial() << endl;
}