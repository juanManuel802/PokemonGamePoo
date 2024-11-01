#include "batalla.h"
#include <iostream>
using namespace std;

Batalla::Batalla() : registroDaño(0) {}

Batalla::Batalla(string ent1, string ent2) {
    contrincantes[0] = ent1;
    contrincantes[1] = ent2;
    registroDaño = 0;
}

int Batalla::getRegistroDaño() const { return registroDaño; }
string Batalla::getGanador() const { return ganador; }
string Batalla::getContrincante(int i) const { return contrincantes[i]; }
string Batalla::getGanadoresCombatesPok(int i) { return ganadoresCombatesPok[i]; }

void Batalla::setGanador(Entrenador &en) { ganador = en.getNombre(); }
void Batalla::setRegistroDaño(int registroDaño) { this->registroDaño = registroDaño; }

void Batalla::agregarPokGanador(Pokemon &pok) {
    ganadoresCombatesPok.push_back(pok.getNombre());
}

void Batalla::agregarRondas(int rond) {
    registroRondas.push_back(rond);
}

void Batalla::luchar(Pokemon &miPok, Pokemon &oponente, bool &ganador) {
    int vidaOponente, vidaMiPok, ataqueMiPok, ataqueOponente, nivelMipok, nivelOponente, xpMiPok, xpOponente, ronda = 1, atq = 0;
    char sig;
    vidaOponente = oponente.getVida();
    vidaMiPok = miPok.getVida();
    ataqueMiPok = miPok.getAtaque();
    ataqueOponente = oponente.getAtaque();
    nivelMipok = miPok.getNivel();
    nivelOponente = oponente.getNivel();
    cout << "\n\n\n\n QUE COMIENCE LA PELEA!\n ";
    miPok.mostrarDatos();
    cout << "\n          vs          \n";
    oponente.mostrarDatos();
    cout << "\n\n***********\n\n";
    cout << "Presiona (x) para lanzar un ataque normal o (p) para un ataque especial." << endl;
    cout << "Solo tienes una oportunidad para lanzar el ataque especial" << endl;
    while (vidaOponente > 0 && vidaMiPok > 0) {
        int restOp, restMi;
        char sig, tipoAtaque;
        cout << "Ronda " << ronda << endl; // Inicia ronda
        if (ronda % 3 == 0 || vidaOponente < 40) {
            vidaMiPok -= (ataqueOponente + ataqueOponente * .3);
            setRegistroDaño(getRegistroDaño() + (ataqueOponente + ataqueOponente * .4));
        } else {
            vidaMiPok -= ataqueOponente;
            setRegistroDaño(getRegistroDaño() + ataqueOponente);
        }
        miPok.setVida(vidaMiPok); 
        // Verifica si sigue vivo
        if (vidaMiPok <= 0) {
            vidaMiPok = 0;
            ganador = false; // Establece ganador
            break;
        }
        bool cond;
        do {
            try {
                cout << "Ataca!!" << endl;
                cin >> tipoAtaque;
                if (tipoAtaque == 'x') {
                    vidaOponente -= ataqueMiPok;
                    setRegistroDaño(getRegistroDaño() + ataqueMiPok);
                    cond = false;
                } else if (atq == 0 && tipoAtaque == 'p') {
                    vidaOponente -= (ataqueMiPok + ataqueMiPok * .4);
                    setRegistroDaño(getRegistroDaño() + (ataqueMiPok + ataqueMiPok * .4));
                    atq++;
                    cout << miPok.getNombre() << " lanzó su ataque especial de " << miPok.getAtaqueEspecial() << endl;
                    cond = false;
                } else if(atq != 0 && tipoAtaque == 'p') {
                    throw Epersonalizado("Error al lanzar el ataque", "Ataque especial ya usado");
                } else {
                    throw Epersonalizado("Opcion no valida", "Escoger otra opcion");
                }
            } catch (Epersonalizado &e) {
                cerr << e.what() << endl;
                cout << "Intenta otro ataque" << endl;
                cond = true;
                //continue;
            }
        } while (cond);
        cout << miPok.getNombre() << ": Vida: " << vidaMiPok << endl;
        cout << oponente.getNombre() << ": Vida: " << vidaOponente << endl;
        cout << "\n\n*********\n\n";
        do {
            cout << "Presiona (n) para continuar" << endl;
            cin >> sig;
        } while (sig != 'n' && sig != 'N');
        ronda++;
    }
    miPok.sanar();
    oponente.sanar();
    agregarRondas(ronda);
}

ostream &operator<<(ostream &o, Batalla c) {
    return o << c.getContrincante(0) << " vs " << c.getContrincante(1) << "\n"
             << "Daño en total que se hicieron los Pokemones: " << c.getRegistroDaño() << "\n"
             << "Ganador Combate 1:" << c.getGanadoresCombatesPok(0) << "\n"
             << "Ganador Combate 2:" << c.getGanadoresCombatesPok(1) << "\n"
             << "Ganador Combate 3:" << c.getGanadoresCombatesPok(3) << "\n"
             << "\nEntrenador Ganador: " << c.getGanador() << endl;
}
