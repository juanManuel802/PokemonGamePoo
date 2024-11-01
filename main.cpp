#include <iostream>
#include <vector>
#include <exception>
using namespace std;

class Epersonalizado : public exception {
private:
    const char *msg;
    const char *causa;
public:
    Epersonalizado(const char *mensaje, const char *cau) : msg(mensaje), causa(cau) {}
    const char *what() const noexcept override{
        cerr << "causa : " << causa << endl;
        return msg;
    }
};
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
    Pokemon(): nombre("Pokemon"), color("amarillo"), ataque(20), vida(100), xp(0), nivel(1), ataqueEspecial("") {}

    Pokemon(string nombre, string color, int ataque, int vida, int xp, int nivel, string ataqueEspecial)
    {
        this->nombre = nombre;
        this->color = color;
        this->ataque = ataque;
        this->vida = vida;
        this->xp = xp;
        this->nivel = nivel;
        this->ataqueEspecial = ataqueEspecial;
    }

    string getNombre() const { return nombre; }
    string getColor() const { return color; }
    string getAtaqueEspecial() const { return ataqueEspecial; }
    int getAtaque() const { return ataque; }
    int getVida() const { return vida; }
    int getXp() const { return xp; }
    int getNivel() const { return nivel; }

    void setNombre(string nombre) { this->nombre = nombre; }
    void setColor(string color) { this->color = color; }
    void setAtaque(int ataque) { this->ataque = ataque; }
    void setVida(int vida) { this->vida = vida; }
    void setXp(int xp) { this->xp = xp; }
    void setNivel(int nivel) { this->nivel = nivel; }
    void setAtaqueEspecial(string ataqueEspecial) { this->ataqueEspecial = ataqueEspecial; }

    void saludar()
    {
        cout << "¡Hola!, soy " << nombre << ", estoy a tu disposición." << endl;
        mostrarDatos();
    }

    void sanar()
    {
        if (vida < 100)
        {
            vida = 100;
        }
    }
    void mostrarDatos() {
        cout << "this" << endl; //?
    }

    void evolucionar(string nombre, string color)
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
    bool verificarAumentoNivel()
    {
        return xp > nivel * 100;
    }

    void aumentarNivel()
    {
        nivel++;
    }

    // sobrecarga del + para crear pokemon recargado
    Pokemon operator+(const Pokemon &c) const
    {
        // creamos un objeto nuevo de la clase cargo llamado "pokemonrecargado" e instantaneamente en sus parametros
        // sumamos los atributos de otros objetos para agregarlos en los atributos de "pokemonrecargado"
        // y luego se retorna el objeto
        Pokemon pokemonrecargado(" SuperPokemon! ", " multicolor! ", ataque + c.ataque, vida + c.vida, xp + c.xp, nivel + c.nivel, "Vacio infinito!");

        return pokemonrecargado;
    }
    bool operator==(const Pokemon &p) const {
        return (nombre == p.nombre &&
                color == p.color &&
                ataque == p.ataque &&
                vida == p.vida &&
                xp == p.xp &&
                nivel == p.nivel &&
                ataqueEspecial == p.ataqueEspecial);
    }
    friend ostream &operator<<(ostream &o, Pokemon p);
};
ostream &operator<<(ostream &o, Pokemon p)
{
    return o << "\nNombre: " << p.getNombre() << " \n color: " << p.getColor() << "\n ataque: " << p.getAtaque() << "\n vida " << p.getVida() << " \n experiencia: " << p.getXp() << "\n nivel: " << p.getNivel() << "\n ataque especial: " << p.getAtaqueEspecial() << endl;
}

class Entrenador {
private:
    vector<Pokemon> misPokemones; // aunque debe ser 3, eso se maneja en la excepción
    string nombre;
    int nivel;

public:
    Entrenador() : nombre(""), nivel(1) {}

    string getNombre() const { return nombre; }
    int getNivel() const { return nivel; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setNivel(int nivel) { this->nivel = nivel; }

    Pokemon &getPokemon(int i) {
        return misPokemones[i];
    }

    void agregarpokemon(Pokemon &poke) {
        if (misPokemones.size() < 3) {
            misPokemones.push_back(poke);
        } else {
            throw Epersonalizado("Error al agregar el pokemon", "El limite son 3 pokemones");
        }
    }

    void entrenar(Pokemon &miPok, const Pokemon &oponente) {
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

    void aumentarNivel() {
        setNivel(getNivel() + 1);
    }
    //const despues de parentesis
    bool operator==(const Entrenador &ec) const{
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
    friend ostream &operator<<(ostream &o, Entrenador c);
};
ostream &operator<<(ostream &o, Entrenador c) {
    for (const auto &poke : c.misPokemones) {
        o << poke << " ";
    }
    return o;
}

class Batalla {
private:
    int registroDaño;
    vector<string> ganadoresCombatesPok;
    string contrincantes[2];
    string ganador;
    vector<int> registroRondas;

public:
    Batalla(): registroDaño(0) {}
    Batalla(string ent1, string ent2) {
        contrincantes[0] = ent1;
        contrincantes[1] = ent2;
        registroDaño = 0;
    }   
    int getRegistroDaño() const { return registroDaño; }
    string getGanador() const { return ganador; }
    string getContrincante(int i) const { return contrincantes[i]; }
    string getGanadoresCombatesPok(int i) { return ganadoresCombatesPok[i]; }

    void setGanador(Entrenador &en) { ganador = en.getNombre(); }
    void setRegistroDaño(int registroDaño) { this->registroDaño = registroDaño; }

    void agregarPokGanador(Pokemon &pok) {
        ganadoresCombatesPok.push_back(pok.getNombre());
    }

    void agregarRondas(int rond) {
        registroRondas.push_back(rond);
    }

    void luchar(Pokemon &miPok, Pokemon &oponente, bool &ganador) {
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
};

ostream &operator<<(ostream &o, Batalla c) {
    return o << c.getContrincante(0) << " vs " << c.getContrincante(1) << "\n"
             << "Daño en total que se hicieron los Pokemones: " << c.getRegistroDaño() << "\n"
             << "Ganador Combate 1:" << c.getGanadoresCombatesPok(0) << "\n"
             << "Ganador Combate 2:" << c.getGanadoresCombatesPok(1) << "\n"
             << "Ganador Combate 3:" << c.getGanadoresCombatesPok(2) << "\n"
             << "\nEntrenador Ganador: " << c.getGanador() << endl;
}


Batalla lucharEntrenadores(Entrenador &rude1, Entrenador &rude2);

int main()
{
    string cond = "Si";
    int pro1, pro2, op, opcion = 0, eop = 0;
    vector<Entrenador> entrenadores; // entrenadores del juego
    vector<Batalla> batallas;

    do
    {

        system("cls");

        cout << "1) Agregar entrenadores" << endl;
        cout << "2) Combatir" << endl;
        cout << "3) Analizar entrenador" << endl;
        cout << "4) Crear pokemon recargado" << endl;
        cout << "5) Agregar pokemon a entrenador" << endl; //Aqui por idea NUESTRAA, vamos a hacer compra de pokemones para agregarlos a los entreadores(ximena y los metidos)
        cout << "6) Comparar" << endl; 
        cout << "7) Historial" << endl;
        cin >> op;

       switch (op)
        {
        case 1:
        system("cls");
            cout << "Crea los entrenadores: " << endl;
            while (cond == "Si" || cond == "si")
            {
                Entrenador papuN;
                string nombre;
                int nivel;

                cout << "Dale un nombre al entrenador: " << endl;
                cin >> nombre;
                papuN.setNombre(nombre);
                cout << "Ahora crea sus tres pokemones " << endl;
                for (int i = 0; i < 4; ++i) //este 4 es para hacer demostracion de la excepcion
                {
                    if (i > 0) 
                        system("cls");
                    Pokemon poki;
                    string nombrePok, colorPok, ataqueEspecial;

                    cout << "Nombre del Pokemon " << i + 1 << ":" << endl;
                    cin >> nombrePok;
                    poki.setNombre(nombrePok);

                    cout << "Color del Pokemon " << i + 1 << ":" << endl;
                    cin >> colorPok;
                    poki.setColor(colorPok);

                    cout << "Ataque especial: " << endl;
                    cin >> ataqueEspecial;
                    poki.setAtaqueEspecial(ataqueEspecial);
                    try
                    {
                        papuN.agregarpokemon(poki);
                    }
                    catch (const Epersonalizado &e)
                    {
                        cerr << e.what() << endl;
                    }
                }
                entrenadores.push_back(papuN);

                cout << "Deseas agregar otro entrenador? (Si/no)" << endl;
                cin >> cond;
            }
            cond = "";
            system("cls");
            cout << "Entrenadores disponibles: " << endl;
            for (int i = 0; i < entrenadores.size(); i++)
            {
                cout << i + 1 << ") " << entrenadores[i].getNombre() << endl;
            }
            break;
        case 2:
        system("cls");
            do
            {
                Batalla game;
                cout << "Selecciona tu entrenador " << endl;
                cin >> pro1;
                cout << "Selecciona tu adversario" << endl;
                cin >> pro2;
                    
                if(pro1!=pro2) {
                    game = lucharEntrenadores(entrenadores[pro1 - 1], entrenadores[pro2 - 1]);

                    batallas.push_back(game);
                } else {
                    cout << "Elegiste al mismo, ahora no haces nada :(" << endl;
                }
                cout << "Quieres volvera jugar? " << endl;
                cin >> cond;
                // Agregar excepcion aquí por si el usuario ingresa un valor que no sea si o no
            } while (cond == "si");
            break;
        case 3:
        system("cls");
            cout << "Ver info de entrenadores? 1.si 2.no" << endl;
            cin >> opcion;

            if (opcion == 1)
            {
                cout << "Que entrenador desea analizar? " << endl;
                cout << "Entrenadores disponibles: " << endl;

                for (int i = 0; i < entrenadores.size(); i++)
                {
                    cout << i + 1 << ") " << entrenadores[i].getNombre() << endl;
                }
                int openanalizar;
                cin >> openanalizar;
                // excepcion que suelte error si escoge algo distinto a 1 2 o 3
                if (openanalizar == 1 || openanalizar == 2 || openanalizar == 3)
                {
                    cout << entrenadores[openanalizar - 1] << endl;
                }
            }
            else
            {
                cout << "siguiendo normalmente con el programa (señor usuario, ignore este mensaje)" << endl;
            }
            // hasta la linea 325 llega la opcion "analizar entrenadores" del menú que haremos
            break;

        case 4:
        system("cls");
            {
                cout << "primero elige el entrenador para asi acceder a sus pokemones" << endl;

                for (int i = 0; i < entrenadores.size(); i++)
                {
                    cout << "1) " << entrenadores[i].getNombre() << endl;
                }
                int pepitoperez = 0;
                cout << "que entrenador escoges:" << endl;

                cin >> pepitoperez;
                cout << "a continuacion te muestro la hoja de vida del entrenador: " << endl;
                cout << entrenadores[pepitoperez - 1] << endl;
                cout << endl;
                int pac1 = 0;
                cout << "elige el primer pokemon a combinar" << endl;

                cin >> pac1;

                int pac2 = 0;
                cout << "elige el segundo" << endl;

                cin >> pac2;
                // aplicacion de la sobrecarga del operador + (creando el pokemon recargado)
                cout << "se esta creando el pokemon..." << endl;
                Pokemon pokemonrecargado = entrenadores[pepitoperez - 1].getPokemon(pac1 - 1) + entrenadores[pepitoperez - 1].getPokemon(pac2 - 1);
                cout << "Pokemon recargado creado!! datos a continuacion: " << endl;
                cout << pokemonrecargado;
            }
            
            break;
        case 6:
        system("cls");
            cout << "Deseas comparar dos entrenadores? o dos pokemones? 1)entrenadores 2)pokemones " << endl;
            cin >> eop;
            if (eop == 1)
            {
                cout << "Que entrenadores desea comparar?" << endl;
                cout << "Entrenadores disponibles: " << endl;

                for (int i = 0; i < entrenadores.size(); i++)
                {
                    cout << i + 1 << ") " << entrenadores[i].getNombre() << endl;
                }
                int ecom;
                cout << "Entrenador a analizar 1: " << endl;
                cin >> ecom;
                int ecom2;
                cout << "Entrenador a analizar 2: " << endl;
                cin >> ecom2;

                if (entrenadores[ecom - 1] == entrenadores[ecom2 - 1])
                {
                    cout << "Los entrenadores son iguales!" << endl;
                }
                else
                {
                    cout << "Los entrenadores no son iguales!" << endl;
                }
            }
            else
            {
                cout << "A que entrenador le deseas comparar sus pokemones?" << endl;
                cout << "Entrenadores disponibles: " << endl;

                for (int i = 0; i < entrenadores.size(); i++)
                {
                    cout << i + 1 << ") " << entrenadores[i].getNombre() << endl;
                }
                int ecompo;
                cin >> ecompo;
                cout << "Entrenador escogido: " << endl;
                cout << entrenadores[ecompo - 1] << endl;
                int pokecomparar1, pokecomparar2;
                cout << "Escoja 2 pokemones para comparar " << endl;
                cin >> pokecomparar1;
                cin >> pokecomparar2;

                if (entrenadores[ecompo - 1].getPokemon(pokecomparar1 - 1).getNombre() == entrenadores[ecompo - 1].getPokemon(pokecomparar2 - 1).getNombre())
                {
                    cout << "Los pokemones se llaman igual!" << endl;
                }
                else
                {
                    cout << "Los pokemones no se llaman igual " << endl;
                }

                if (entrenadores[ecompo - 1].getPokemon(pokecomparar1 - 1).getNivel() == entrenadores[ecompo - 1].getPokemon(pokecomparar2).getNivel())
                {
                    cout << "Los pokemones tienen el mismo nivel!" << endl;
                }
                else
                {
                    cout << "Los pokemones no tienen el mismo nivel" << endl;
                }

                if (entrenadores[ecompo - 1].getPokemon(pokecomparar1 - 1).getAtaque() == entrenadores[ecompo - 1].getPokemon(pokecomparar2).getAtaque())
                {
                    cout << "Los pokemones tienen el mismo ataque!" << endl;
                }
                else
                {
                    cout << "Los pokemones no tienen el mismo ataque!" << endl;
                }

                if (entrenadores[ecompo - 1].getPokemon(pokecomparar1 - 1).getVida() == entrenadores[ecompo - 1].getPokemon(pokecomparar2).getVida())
                {
                    cout << "Los pokemones tienen la misma vida!" << endl;
                }
                else
                {
                    cout << "Los pokemones no tienen la misma vida!" << endl;
                }

                if (entrenadores[ecompo - 1].getPokemon(pokecomparar1 - 1).getXp() == entrenadores[ecompo - 1].getPokemon(pokecomparar2).getXp())
                {
                    cout << "Los pokemones tienen la misma experiencia!" << endl;
                }
                else
                {
                    cout << "Los pokemones no tienen la misma experiencia!" << endl;
                }

                if (entrenadores[ecompo - 1].getPokemon(pokecomparar1 - 1).getColor() == entrenadores[ecompo - 1].getPokemon(pokecomparar2).getColor())
                {
                    cout << "Los pokemones tienen el mismo color!" << endl;
                }
                else
                {
                    cout << "Los pokemones no tienen el mismo color!" << endl;
                }

                if (entrenadores[ecompo - 1].getPokemon(pokecomparar1 - 1).getAtaqueEspecial() == entrenadores[ecompo - 1].getPokemon(pokecomparar2).getAtaqueEspecial())
                {
                    cout << "Los pokemones tienen el mismo ataque especial!" << endl;
                }
                else
                {
                    cout << "Los pokemones no tienen el mismo ataque especial!" << endl;
                }
            }
            break;
        case 7:
        system("cls");
            for (int i = 0; i < batallas.size(); i++)
            {
                cout << "Batalla " << i + 1 << endl;
                cout << batallas[i] << endl;
            }
            break;
        default:
            cout << "Opcion incorrecta, escoja otra" << endl;
            break;
        }
        cout << "Deseas seguir en el juego!? (si/no)" << endl;
        cin >> cond;
    } while (cond == "si" || cond == "Si");

    return 0;
}

Batalla lucharEntrenadores(Entrenador &rude1, Entrenador &rude2){
    Batalla epicGame(rude1.getNombre(), rude2.getNombre());
    bool ganador;
    int puntajeRude1 = 0, puntajeRude2 = 0;

    // ACLARACION:
    // Este va a ser un sistema de lucha uno a uno. El primero con el primero, etc. Ya despues hacemos herencia para diferentes tipos de batalla

    for (int i = 0; i < 3; i++)
    {
        cout << "Combate " << i + 1 << endl;
        cout << rude1.getNombre() << ": " << puntajeRude1 << "|| " << rude2.getNombre() << ": " << puntajeRude2 << endl;
        epicGame.luchar(rude1.getPokemon(i), rude2.getPokemon(i), ganador); // Revisar método getPokemon de la clase Entrenador
        if (ganador)
        {
            cout << "Tu pokemon " << rude1.getPokemon(i).getNombre() << " ha ganado!!" << endl;
            rude1.entrenar(rude1.getPokemon(i), rude2.getPokemon(i));
            epicGame.agregarPokGanador(rude1.getPokemon(i));
            puntajeRude1++;            
        }
        else
        {
            cout << rude2.getPokemon(i).getNombre() << "te ha vencido, y se ha vuelto más fuerte" <<endl;
            rude2.entrenar(rude2.getPokemon(i), rude1.getPokemon(i));
            epicGame.agregarPokGanador(rude2.getPokemon(i));
            puntajeRude2++;
        }
    }

    if (puntajeRude1 > puntajeRude2)
    {
        epicGame.setGanador(rude1);
        cout << "Felicidades, has ganado!!!" << endl;
    }
    else
    {
        cout << "Has perdido" << endl;
        epicGame.setGanador(rude2);
    }

    return epicGame;
}
