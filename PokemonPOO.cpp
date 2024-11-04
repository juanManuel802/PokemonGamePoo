#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <exception>
using namespace std;

class Epersonalizado : public exception
{
private:
    const char *msg;
    const char *causa;

public:
    Epersonalizado(const char *mensaje, const char *cau) : msg(mensaje), causa(cau) {}
    const char *what() const noexcept override
    {
        cerr << "causa : " << causa << endl;
        return msg;
    }
};
class Pokemon
{
protected:
    string nombre;
    string color;
    int ataque;
    int vida;
    int xp;
    int nivel;

public:
    Pokemon() : nombre("Pokemon"), color("amarillo"), ataque(20), vida(100), xp(0), nivel(1) {}

    Pokemon(string nombre, string color, int ataque, int vida, int xp, int nivel)
    {
        this->nombre = nombre;
        this->color = color;
        this->ataque = ataque;
        this->vida = vida;
        this->xp = xp;
        this->nivel = nivel;
    }

    string getNombre() const { return nombre; }
    string getColor() const { return color; }
    int getAtaque() const { return ataque; }
    int getVida() const { return vida; }
    int getXp() const { return xp; }
    int getNivel() const { return nivel; }

    void setNombre(string nombre) { this->nombre = nombre; }
    void setColor(string color) { this->color = color; }
    void setPotenciaDeAtaque(int ataque) { this->ataque = ataque; }
    void setVida(int vida) { this->vida = vida; }
    void setXp(int xp) { this->xp = xp; }
    void setNivel(int nivel) { this->nivel = nivel; }

    void saludar()
    {
        cout << "¡Hola!, soy " << nombre << ", estoy a tu disposición." << endl;
    }

    void sanar()
    {
        if (vida < 100)
        {
            vida = 100;
        }
    }
    void mostrarDatos()
    {
        cout << "\nNombre: " << getNombre() << " \n color: " << getColor() << "\n ataque: " << getAtaque() << "\n vida " << getVida() << " \n experiencia: " << getXp() << "\n nivel: " << getNivel() << endl;
    }

    void evolucionar()
    {
        int aumentoPot;
        if (nivel > 3)
        {
            this->nombre = nombre;
            this->color = color;
            ataque += ataque * 0.2;
            aumentoPot = 20;
        }
        else
        {
            ataque += ataque * 0.1;
            aumentoPot = 10;
        }
        cout << "La potencia ha aumentado un " << aumentoPot << endl;
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

    bool operator==(const Pokemon &p) const
    {
        return (nombre == p.nombre &&
                color == p.color &&
                ataque == p.ataque &&
                vida == p.vida &&
                xp == p.xp &&
                nivel == p.nivel);
    }
    friend ostream &operator<<(ostream &o, Pokemon *p);

    virtual void hacerGritoDeAsalto()
    {
        cout << getNombre() << ": ";
    }
    virtual string getAtaqueEspecial() const = 0;
};
ostream &operator<<(ostream &o, Pokemon *p)
{
    return o << "\nNombre: " << p->getNombre() << " \n color: " << p->getColor() << "\n ataque: " << p->getAtaque() << "\n vida " << p->getVida() << " \n experiencia: " << p->getXp() << "\n nivel: " << p->getNivel() << "\n ataque especial: " << p->getAtaqueEspecial() << endl;
}

class PokemonHielo : public Pokemon
{
private:
    string ataqueEspecial;

public:
    PokemonHielo() : Pokemon(), ataqueEspecial("Congelamiento") {}
    PokemonHielo(string nombre, string color, int ataque, int vida, int xp, int nivel) : Pokemon(nombre, color, ataque, vida, xp, nivel), ataqueEspecial("Congelamiento") {}
    string getAtaqueEspecial() const override { return ataqueEspecial; }
    void hacerGritoDeAsalto() override
    {
        Pokemon::hacerGritoDeAsalto();
        cout << "Aaaaa CHU! frrrrrss!! " << endl;
    }
};

class PokemonVeneno : public Pokemon
{
private:
    string ataqueEspecial;
    int toxicidad;

public:
    PokemonVeneno() : Pokemon(), ataqueEspecial("Intoxicacion"), toxicidad(3) {}
    PokemonVeneno(string nombre, string color, int ataque, int vida, int xp, int nivel) : Pokemon(nombre, color, ataque, vida, xp, nivel), ataqueEspecial("Intoxicacion"), toxicidad(3) {}
    string getAtaqueEspecial() const override { return ataqueEspecial; }
    int getToxicidad() const { return toxicidad; }
    void hacerGritoDeAsalto() override
    {
        Pokemon::hacerGritoDeAsalto();
        cout << "Tssssss Splashhh BOOOM!!" << endl;
    }
    void aumentarToxicidad(int plus)
    {
        toxicidad += plus;
    }
};

class PokemonAcero : public Pokemon
{
private:
    string ataqueEspecial;
    int escudoAcero;

public:
    PokemonAcero() : Pokemon(), ataqueEspecial("Escudo de acero"), escudoAcero(100) {}
    PokemonAcero(string nombre, string color, int ataque, int vida, int xp, int nivel) : Pokemon(nombre, color, ataque, vida, xp, nivel), ataqueEspecial("Escudo de Acero"), escudoAcero(100) {}
    string getAtaqueEspecial() const override { return ataqueEspecial; }
    int getEscudoAcero() const { return escudoAcero; }
    void hacerGritoDeAsalto() override
    {
        Pokemon::hacerGritoDeAsalto();
        cout << "TSK TSK escudo activado!! " << endl;
    }
    void desgastarEscudo(int desgaste)
    {
        escudoAcero -= desgaste;
    }
};

class Entrenador
{
private:
    vector<Pokemon *> misPokemones; // aunque debe ser 3, eso se maneja en la excepción
    string nombre;
    int nivel;

public:
    Entrenador() : nombre(""), nivel(1) {}
    Entrenador(const string &nombre, const vector<Pokemon *> &pokemones) : nombre(nombre), misPokemones(pokemones), nivel(1) {}
    string getNombre() const { return nombre; }
    int getNivel() const { return nivel; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setNivel(int nivel) { this->nivel = nivel; }

    Pokemon *getPokemon(int i)
    {
        return misPokemones[i];
    }
    int getCantidadPokemones()
    {
        return misPokemones.size();
    }

    void agregarpokemon(Pokemon *poke)
    {
        if (misPokemones.size() < 3)
        {
            misPokemones.push_back(poke);
        }
        else
        {
            throw Epersonalizado("Error al agregar el pokemon", "El limite son 3 pokemones");
        }
    }

    void entrenar(Pokemon *poke)
    { // X: &
        poke->setXp(poke->getXp() + 25 * getNivel());
        cout << "El entrenador " << nombre << " ha entrenado a " << poke->getNombre() << endl;
        cout << poke;
    }

    void mostrarPokemones()
    {
        for (const auto &poke : misPokemones)
        {
            cout << poke << " " << endl;
        }
    }

    void aumentarNivel()
    {
        setNivel(getNivel() + 1);
        cout << getNombre() << " aumento su nivel a " << getNivel() << endl;
    }
    // const despues de parentesis

    friend ostream &operator<<(ostream &o, Entrenador *c);
};
ostream &operator<<(ostream &o, Entrenador *c)
{
    //    return o << "\nNombre: " << p->getNombre() << " \n color: " << p->getColor() << "\n ataque: " << p->getAtaque() << "\n vida " << p->getVida() << " \n experiencia: " << p->getXp() << "\n nivel: "
    // << p->getNivel() << "\n ataque especial: " << p->getAtaqueEspecial() << endl;
    return o << "Entrenador: " << c->getNombre() << endl
             << "Nivel:  " << c->getNivel() << endl;
}
// system("cls");
class Batalla
{
private:
    int registroDaño;
    vector<string> ganadoresCombatesPok;
    string contrincantes[2];
    string ganador;
    vector<int> registroRondas;

public:
    Batalla() : registroDaño(0) {}
    Batalla(string ent1, string ent2)
    {
        contrincantes[0] = ent1;
        contrincantes[1] = ent2;
        registroDaño = 0;
    }
    int getRegistroDaño() const { return registroDaño; }
    string getGanador() const { return ganador; }
    string getContrincante(int i) const { return contrincantes[i]; }
    string getGanadoresCombatesPok(int i) { return ganadoresCombatesPok[i]; }

    void setGanador(Entrenador *en) { ganador = en->getNombre(); }
    void setRegistroDaño(int registroDaño) { this->registroDaño = registroDaño; }

    void agregarPokGanador(Pokemon *pok)
    {
        ganadoresCombatesPok.push_back(pok->getNombre());
    }

    void agregarRondas(int rond)
    {
        registroRondas.push_back(rond);
    }

    void luchar(Pokemon *miPok, Pokemon *oponente, bool &ganador)
    {
        int vidaOponente, vidaMiPok, ataqueMiPok, ataqueOponente, nivelMipok, nivelOponente, xpMiPok, xpOponente, ronda = 1, atq = 0, atqO = 0;
        char sig;
        vidaOponente = oponente->getVida();
        vidaMiPok = miPok->getVida();
        ataqueMiPok = miPok->getAtaque();
        ataqueOponente = oponente->getAtaque();
        nivelMipok = miPok->getNivel();
        nivelOponente = oponente->getNivel();
        cout << "\n**************************************************************\n";
        cout << "\n          QUE COMIENCE LA PELEA!          \n ";
        cout << miPok;
        cout << "\n          vs          \n";
        cout << oponente;
        cout << "\n**************************************************************\n";

        while (vidaOponente > 0 && vidaMiPok > 0)
        {
            srand(static_cast<unsigned>(time(0)));

            // comento esto para probar siempre con variablealeatoria1 solo para probar el programa mas facil
            int variableAleatoria = rand() % 2 + 1;
            // variableAleatoria=1;
            bool congeladoverop = false;
            bool congeladovermi = false;
            int restOp, restMi;
            int  vidaMiPokantes=0,vidaOponenteantes=0, dañoTotalOponente = 0, dañoTotalMiPok = 0; // dañoTotal para extraer la informacion deel daño que hizo el pokemon luego del ataque cualquiera que sea
            char sig, tipoAtaque;
            dañoTotalOponente = ataqueOponente;
            dañoTotalMiPok = ataqueMiPok;

            cout << "Presiona (x) para lanzar un ataque normal o (p) para un ataque especial." << endl;
            cout << "Solo tienes una oportunidad para lanzar el ataque especial" << endl;
            cout << "\n\n{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-} RONDA " << ronda << " {,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}" << endl; // Inicia ronda
            cout << endl;
            // esto es para confirmar si si sirvio la variable aleatoria
            cout << "variable aletoria : " << variableAleatoria << endl;
            if (atq == 0 || atq > 1)

            { // atq>1 para confirmar si ya se usó el especial y si es asi, mandar solo normales ahora
                vidaMiPok -= dañoTotalOponente;
                setRegistroDaño(getRegistroDaño() + ataqueOponente);
            }
            else if (atq == 1 && miPok->getAtaqueEspecial() == "Congelamiento")
            {
                dañoTotalOponente = 0;
                cout << oponente->getNombre() << " esta congelado!!!! " << endl;
                atq++;
                congeladoverop = true;
            }
            else if (atq == 1 && miPok->getAtaqueEspecial() == "Intoxicacion")
            {
                cout << oponente->getNombre() << " esta intoxicado y el veneno empeora! D: " << endl;
                cout << vidaOponente << " - " << dynamic_cast<PokemonVeneno *>(miPok)->getToxicidad() << " = ";
                vidaMiPok -= dañoTotalOponente;
                vidaOponente -= dynamic_cast<PokemonVeneno *>(miPok)->getToxicidad();
                cout << vidaOponente << endl;
                setRegistroDaño(getRegistroDaño() + ataqueOponente + dynamic_cast<PokemonVeneno *>(miPok)->getToxicidad());
                dynamic_cast<PokemonVeneno *>(miPok)->aumentarToxicidad(3);
            }
            else if (atq == 1 && miPok->getAtaqueEspecial() == "Escudo de Acero" && dynamic_cast<PokemonAcero *>(miPok)->getEscudoAcero() > 0)
            {
                cout<< oponente->getNombre() << " atacó pero el escudo de Acero mitiga parte del ataque!!" << endl;
                cout<<"Escudo actual de "<<miPok->getNombre()<<" : "<< dynamic_cast<PokemonAcero *>(oponente)->getEscudoAcero() <<endl;
                vidaMiPokantes=vidaMiPok;
                dynamic_cast<PokemonAcero *>(miPok)->desgastarEscudo(ataqueOponente * 0.2);
                vidaMiPok -= (ataqueOponente - (ataqueOponente * 0.2));

            }
            cout << "\n**************************************************************\n";
            if (congeladoverop)
            {
                cout << oponente->getNombre() << "esta descongelandose... preparate! " << endl;
            }
            else
            {
                // si la variable es 1, usa su ataque especial, aqui solo muestra al usuario que la usó
                if (variableAleatoria == 1 && atqO == 0)
                {
                    vidaMiPokantes=vidaMiPok;
                    // aqui le cambio el valor para que el programa siga, si no hago eso pailas jaja Rojo
                    // ES MIENTRAS PRUEBO
                    // variableAleatoria++;

                    //le suma a atqO para que se diferencie de: (NO SE USÓ=0) &  (SE USÓ =1)
                    atqO++;
                    if (atqO == 1)
                    {
                        cout << oponente->getNombre() << " Ha usado su ataque especial:";
                        if (oponente->getAtaqueEspecial() == "Congelamiento")
                        {
                            cout << " Congelamiento!! : ";
                            oponente->hacerGritoDeAsalto();
                        }
                        else if (oponente->getAtaqueEspecial() == "Intoxicacion")
                        {
                            cout << " Intoxicacion!! : ";
                            oponente->hacerGritoDeAsalto();
                            cout << "Vida de " << miPok->getNombre() << ": " << vidaMiPok + dañoTotalOponente << " - " << dañoTotalOponente << " ->  " << vidaMiPok << endl;
                        }
                        else
                        {
                            cout << " Escudo de Acero!! : ";
                            oponente->hacerGritoDeAsalto();

                            //aca al activar el escudo (cosa que se muestra solo una vez, va a atacar)
                            cout << "Vida de " << miPok->getNombre() << ": " << vidaMiPok+ dañoTotalOponente << " - " <<ataqueOponente<< " ->  " << vidaMiPok << endl;

                        }
                    }
                }
                else if(vidaMiPokantes>0){

                                cout << oponente->getNombre() << " ha atacado " << endl;
                                 cout << "Vida de " << miPok->getNombre() << ": " << vidaMiPokantes<< " - " << (ataqueOponente - (ataqueOponente * 0.2)) << " ->  " << vidaMiPok << endl;


                            }else

                {
                    cout << oponente->getNombre() << " ha atacado " << endl;
                    cout << "Vida de " << miPok->getNombre() << ": " << vidaMiPok + dañoTotalOponente << " - " << dañoTotalOponente << " ->  " << vidaMiPok << endl;
                }
                cout << "\n**************************************************************\n\n";
            }

            miPok->setVida(vidaMiPok);
            // Verifica si sigue vivo
            if (vidaMiPok <= 0)
            {
                vidaMiPok = 0;
                ganador = false; // Establece ganador
                break;
            }
            bool cond;
            do
            {
                try
                {
                    if (variableAleatoria == 1 && atqO == 1 && oponente->getAtaqueEspecial() == "Intoxicacion")
                    {
                        variableAleatoria=2;
                        cout << miPok->getNombre() << " esta intoxicado y el veneno empeora! NOOOO " << endl;
                        cout << vidaMiPok << " - " << dynamic_cast<PokemonVeneno *>(oponente)->getToxicidad() << " = ";
                        // vidaOponente -= dañoTotalMiPok;
                        vidaMiPok -= dynamic_cast<PokemonVeneno *>(oponente)->getToxicidad();
                        cout << vidaMiPok << endl;
                        setRegistroDaño(getRegistroDaño() + ataqueMiPok + dynamic_cast<PokemonVeneno *>(oponente)->getToxicidad());
                        dynamic_cast<PokemonVeneno *>(oponente)->aumentarToxicidad(3);
                    }
                    // Verifica si el pokemon sigue vivo, porque pudo haber muerto por intoxicacion
                    // IMPORTANTE
                    // Antes estaba despues de que se le solicitara al usuario atacar, y si moria mor intoxicacion no atacaba,
                    // asi que no tenia sentido
                    if (vidaMiPok <= 0)
                    {
                        vidaMiPok = 0;
                        ganador = false; // Establece ganador
                        break;
                    }
                    else
                    {
                        cout << "Ataca!!" << endl;
                        cin >> tipoAtaque;
                    }
                    if (tipoAtaque == 'x' && variableAleatoria == 1)
                    {
                         variableAleatoria=2;
                        if (oponente->getAtaqueEspecial() == "Congelamiento" && atqO == 1)
                        {
                            dañoTotalMiPok = 0;
                            cout << miPok->getNombre() << " esta congelado!!!! " << endl;
                            atqO++;
                            congeladovermi = true;
                        }
                        else if (oponente->getAtaqueEspecial() == "Escudo de Acero" && (dynamic_cast<PokemonAcero *>(oponente)->getEscudoAcero() > 0) && atqO == 1)
                        {

                            cout<<"Escudo actual de "<<oponente->getNombre()<<" : "<< dynamic_cast<PokemonAcero *>(oponente)->getEscudoAcero() <<endl;

                            dynamic_cast<PokemonAcero *>(oponente)->desgastarEscudo(ataqueMiPok * 0.2);
                            //variable que guarda la vida del oponente ANTES de recibir el daño reducido
                            vidaOponenteantes = vidaOponente;
                            vidaOponente -= (ataqueMiPok - (ataqueMiPok * 0.2));
                            setRegistroDaño(getRegistroDaño() + ataqueMiPok - ataqueMiPok * 0.2);

                        }
                        cout << "\n**************************************************************\n";
                        if (congeladovermi)
                        {
                            cout << miPok->getNombre() << " esta descongelandose... " << endl;
                        }
                        else
                        {
                            if(vidaOponenteantes>0){
                                cout<<"no se cumple no me va a pegar de nuevo"<<endl;
                            }else{
                            cout<<"me volvio a bajar vida"<<endl;
                            vidaOponente -= ataqueMiPok;
                            setRegistroDaño(getRegistroDaño() + ataqueMiPok);
                            cond = false;
                        }}
                    }
                    else if (tipoAtaque == 'x')
                    {
                        cout << "vida oponente antes de atacarlo: " << vidaOponente << endl;
                        vidaOponente -= ataqueMiPok;
                        setRegistroDaño(getRegistroDaño() + ataqueMiPok);
                        cond = false;
                    }

                    // ataque especial de nuestro pokemon
                    else if (atq == 0 && tipoAtaque == 'p' && variableAleatoria == 1)
                    {
                        variableAleatoria = 2;

                        if (oponente->getAtaqueEspecial() == "Congelamiento" && atqO == 1)
                        {
                            dañoTotalMiPok = 0;
                            cout << miPok->getNombre() << " esta congelado!!!! " << endl;
                            atqO++;
                            congeladovermi = true;
                        }
                        else if ( atqO==1 && oponente->getAtaqueEspecial() == "Escudo de Acero" &&  dynamic_cast<PokemonAcero *>(oponente)->getEscudoAcero() > 0)
                        {

                            cout<<"Escudo actual de "<<oponente->getNombre()<<" : "<< dynamic_cast<PokemonAcero *>(oponente)->getEscudoAcero() <<endl;

                            //variable que guarda la vida del oponente ANTES de recibir el daño reducido
                            vidaOponenteantes = vidaOponente;
                            //este es el daño extra por usar ataque especial
                            dañoTotalMiPok = ataqueMiPok + ataqueMiPok * .4;
                            //aqui esta el proceso para mitigar un 20% del daño de nuestro pokemon hacia el enemigo (ya que este ultimo usó su ataque especial )
                            dynamic_cast<PokemonAcero *>(oponente)->desgastarEscudo((ataqueMiPok + ataqueMiPok * .4) * 0.2);
                            vidaOponente -= ((ataqueMiPok + ataqueMiPok * .4) - ((ataqueMiPok + ataqueMiPok * .4) * 0.2));
                            setRegistroDaño(getRegistroDaño() + (ataqueMiPok + ataqueMiPok * .4) - ((ataqueMiPok + ataqueMiPok * .4) * 0.2));
                            cout<<vidaOponente;
                            cout<<vidaOponente;
                        }
                        if (congeladovermi)
                        {
                            cout << miPok->getNombre() << " esta descongelandose... " << endl;
                        }
                        else
                        {
                            if(vidaOponenteantes>0){
                                cout<<"hola no se cumplio jiji"<<endl;
                            }else{
                            dañoTotalMiPok = ataqueMiPok + ataqueMiPok * .4;
                            vidaOponente -= dañoTotalMiPok;
                            setRegistroDaño(getRegistroDaño() + dañoTotalMiPok);
                            atq++;
                            }
                            // Aplicamos funcion virtual
                            cout << miPok->getNombre() << " Ha usado su ataque especial:";
                            if (miPok->getAtaqueEspecial() == "Congelamiento")
                            {
                                cout << " Congelamiento!! : ";
                            }
                            else if (miPok->getAtaqueEspecial() == "Intoxicacion")
                            {
                                cout << " Intoxicacion!! : ";
                            }
                            else
                            {
                                cout << " Escudo de Acero!! : ";
                            }
                            miPok->hacerGritoDeAsalto();
                            cond = false;
                        }
                    }
                    else if (atq == 0 && tipoAtaque == 'p' && variableAleatoria != 1)
                    {
                        cout << miPok->getNombre() << " Ha usado su ataque especial:";
                        if (miPok->getAtaqueEspecial() == "Congelamiento")
                        {
                            cout << " Congelamiento!! : ";
                        }
                        else if (miPok->getAtaqueEspecial() == "Intoxicacion")
                        {
                            cout << " Intoxicacion!! : ";
                        }
                        else
                        {
                            cout << " Escudo de Acero!! : ";
                        }
                        miPok->hacerGritoDeAsalto();
                        cond = false;
                        dañoTotalMiPok = ataqueMiPok + ataqueMiPok * .4;
                        vidaOponente -= dañoTotalMiPok;
                        setRegistroDaño(getRegistroDaño() + dañoTotalMiPok);
                        atq++;
                    }
                    else if (atq != 0 && tipoAtaque == 'p')
                    {
                        throw Epersonalizado("Error al lanzar el ataque", "Ataque especial ya usado");
                    }
                    else
                    {
                        throw Epersonalizado("Opcion no valida", "Escoger otra opcion");
                    }
                }
                catch (Epersonalizado &e)
                {
                    cerr << e.what() << endl;
                    cout << "Intenta otro ataque" << endl;
                    cond = true;
                    // continue;
                }
            } while (cond);
            if (vidaMiPok > 0)
            {
                if(vidaOponenteantes>0){
                    cout << "\n**************************************************************\n";
                cout << miPok->getNombre() << " ha atacado pero el escudo de " <<oponente->getNombre()<<" mitiga parte del daño "<< endl;
                cout << oponente->getNombre() << ": Vida: " << vidaOponenteantes << " - " <<((ataqueMiPok + ataqueMiPok * .4) - ((ataqueMiPok + ataqueMiPok * .4) * 0.2))  << " ->  " << vidaOponente << endl;
                cout << "\n**************************************************************\n\n";
                }else
                {
                cout << "\n**************************************************************\n";
                cout << miPok->getNombre() << " ha atacado " << endl;
                cout << oponente->getNombre() << ": Vida: " << vidaOponente + dañoTotalMiPok << " - " << dañoTotalMiPok << " ->  " << vidaOponente << endl;
                cout << "\n**************************************************************\n\n";
                }
            }
            else
            {
                cout << miPok->getNombre() << " ha muerto en batalla " << endl;
            }
            cout << endl;
            cout << "                    Resultado ronda " << ronda << endl;
            cout << "(Tu)->      || " << miPok->getNombre() << ": Vida: " << vidaMiPok << endl;
            cout << "(Oponente)->|| " << oponente->getNombre() << ": Vida: " << vidaOponente << endl;
            cout << "\n\n**************************************************************\n\n";
            do
            {
                cout << "Presiona (n) para continuar" << endl;
                cin >> sig;
            } while (sig != 'n' && sig != 'N');
            ronda++;
        }
        miPok->sanar();
        oponente->sanar();
        agregarRondas(ronda);
    }
    friend Batalla *lucharEntrenadores(Entrenador *rude1, Entrenador *rude2);
};

ostream &operator<<(ostream &o, Batalla *c)
{
    return o << c->getContrincante(0) << " vs " << c->getContrincante(1) << "\n"
             << "Daño en total que se hicieron los Pokemones: " << c->getRegistroDaño() << "\n"
             << "Ganador Combate 1:" << c->getGanadoresCombatesPok(0) << "\n"
             << "Ganador Combate 2:" << c->getGanadoresCombatesPok(1) << "\n"
             << "Ganador Combate 3:" << c->getGanadoresCombatesPok(2) << "\n"
             << "\nEntrenador Ganador: " << c->getGanador() << endl;
}

Batalla *lucharEntrenadores(Entrenador *rude1, Entrenador *rude2);
int ingresaPorRango(int inicio, int fin);
int main()
{
    string cond = "Si";
    int pro1, pro2, op = 0, opcion = 0, eop = 0;
    vector<Entrenador *> entrenadores; // entrenadores del juego
    vector<Batalla *> batallas;

    Pokemon *pikachu = new PokemonHielo("Pikachu", "Verde", 30, 100, 0, 1);
    Pokemon *charmander = new PokemonVeneno("Charmander", "Fuxia", 32, 100, 0, 1);
    Pokemon *bulbasaur = new PokemonAcero("Bulbasaur", "Rojo", 30, 100, 0, 1);

    // Crear Pokemones para el segundo entrenador
    Pokemon *squirtle = new PokemonHielo("Squirtle", "Azul", 30, 100, 0, 1);
    Pokemon *pidgey = new PokemonVeneno("Pidgey", "Violeta", 30, 100, 0, 1);
    Pokemon *rattata = new PokemonAcero("Rattata", "Naranja", 30, 100, 0, 1);

    // Crear entrenadores
    vector<Pokemon *> pokemonesAsh = {bulbasaur, pikachu,charmander};
    Entrenador *ash = new Entrenador("Ash", pokemonesAsh);

    vector<Pokemon *> pokemonesMisty = {rattata, squirtle, pidgey};
    Entrenador *misty = new Entrenador("Misty", pokemonesMisty);

    // Agregar entrenadores al vector
    entrenadores.push_back(ash);
    entrenadores.push_back(misty);

    while (op != 6)
    {
        // system("cls");
        cout << "1) Agregar entrenadores" << endl;
        cout << "2) Agregar pokemon a entrenador" << endl;
        cout << "3) Combatir" << endl;
        cout << "4) Analizar entrenador" << endl;
        cout << "5) Historial" << endl;
        cout << "6) Salir" << endl;
        cin >> op;

        switch (op)
        {
        case 1:
        {
            int i = 0;
            int cantidadEntrenadores;
            cantidadEntrenadores = entrenadores.size();
            // system("cls");
            cout << "Crea los entrenadores: " << endl;
            cond = "Si";
            while (cond == "Si" || cond == "si")
            {
                Entrenador *papuN = new Entrenador;
                string nombre, condPok = "Si";
                int nivel, vida, potAtaque, i = 0;

                cout << "Dale un nombre al entrenador: " << endl;
                cin >> nombre;
                papuN->setNombre(nombre);

                entrenadores.push_back(papuN);

                cout << "Entrenador añadido: " << entrenadores[cantidadEntrenadores]->getNombre() << endl;
                cout << "Deseas agregar otro entrenador? (Si/no)" << endl;
                cin >> cond;
                i++;
            }
            cond = "";
            // system("cls");
            /* cout << "Entrenadores disponibles: " << endl;
           for (int i = 0; i < entrenadores.size(); i++)
           {
               cout << i + 1 << ") " << entrenadores[i]->getNombre() << endl;
           } */
            break;
        }
        case 2:
        {
            int op, i = 0;
            string condPok = "si";
            for (int i = 0; i < entrenadores.size(); i++)
            {
                cout << i + 1 << ") " << entrenadores[i] << endl;
            }

            cout << "Elige un entrenador para añadir pokemones" << endl;
            cin >> op;
            while (condPok == "si" || condPok == "Si")
            {
                try
                {
                    if (entrenadores[op - 1]->getCantidadPokemones() == 3)
                    {
                        throw Epersonalizado("Error al agregar el pokemon", "El limite son 3 pokemones");
                    }

                    int vida, potAtaque, tipoPoke;
                    string nombrePok, colorPok; // no ataqueEspecial

                    cout << "Que tipo de pokemon quieres elegir? " << endl;
                    cout << "1. Hielo" << endl;
                    cout << "2. Veneno" << endl;
                    cout << "3. Acero" << endl;
                    cin >> tipoPoke;

                    Pokemon *poki; // Pienso
                    if (tipoPoke == 1)
                    { // Luego existo
                        poki = new PokemonHielo;
                    }
                    else if (tipoPoke == 2)
                    {
                        poki = new PokemonVeneno;
                    }
                    else if (tipoPoke == 3)
                    {
                        poki = new PokemonAcero;
                    }

                    cout << "Nombre del Pokemon " << i + 1 << ":" << endl;
                    cin >> nombrePok;
                    poki->setNombre(nombrePok);

                    cout << "Color de " << poki->getNombre() << ":" << endl;
                    cin >> colorPok;
                    poki->setColor(colorPok);

                    cout << "Vida de " << poki->getNombre() << ":" << endl;
                    cout << "Desde 70 a 100" << endl;
                    vida = ingresaPorRango(70, 100);
                    poki->setVida(vida);

                    cout << "Potencia de ataque de " << poki->getNombre() << ":" << endl;
                    cout << "Desde 10 a 30" << endl;
                    potAtaque = ingresaPorRango(10, 30);
                    poki->setPotenciaDeAtaque(potAtaque);

                    entrenadores[op - 1]->agregarpokemon(poki);

                    cout << "Deseas agregar otro pokemon?" << endl;
                    cin >> condPok;
                    i++;
                }
                catch (const Epersonalizado &e)
                {
                    string x;
                    cerr << e.what() << endl;
                    cout << "presu¿iona una tecla y enter para aceptar" << endl;
                    cin >> x;
                    break;
                }
            }
            break;
        }
        case 3:
        {
            // system("cls");
            do
            {
                Batalla *game = new Batalla;
                for (int i = 0; i < entrenadores.size(); i++)
                {
                    cout << "*************************************************************" << endl;
                    cout << i + 1 << ") " << entrenadores[i] << endl;
                    cout << "Pokemones: " << endl;
                    entrenadores[i]->mostrarPokemones();
                }
                cout << "Selecciona tu entrenador " << endl;
                cin >> pro1;
                cout << "Selecciona tu adversario" << endl;
                cin >> pro2;

                if (pro1 != pro2)
                {
                    game = lucharEntrenadores(entrenadores[pro1 - 1], entrenadores[pro2 - 1]);

                    batallas.push_back(game);
                }
                else
                {
                    cout << "Elegiste al mismo, ahora no haces nada :(" << endl;
                }
                cout << "Quieres volvera jugar? " << endl;
                cin >> cond;
                // Agregar excepcion aquí por si el usuario ingresa un valor que no sea si o no
            } while (cond == "si");
            break;
        }
        case 4:
        {

            cout << "Que entrenador desea analizar? " << endl;
            cout << "Entrenadores disponibles: " << endl;

            for (int i = 0; i < entrenadores.size(); i++)
            {
                cout << i + 1 << ") " << entrenadores[i]->getNombre() << endl;
            }
            int openanalizar;
            cin >> openanalizar;
            // excepcion que suelte error si escoge algo distinto a 1 2 o 3
            if (openanalizar <= entrenadores.size() && openanalizar > 0)
            {
                cout << entrenadores[openanalizar - 1] << endl;
                entrenadores[openanalizar - 1]->mostrarPokemones();
            }
            break;
        }
        case 5:
        {
            // system("cls");
            cout << "Registro  de batallas" << endl;
            for (int i = 0; i < batallas.size(); i++)
            {
                cout << "Batalla " << i + 1 << endl;
                cout << batallas[i] << endl;
            }
            break;
        }
        case 6:
            // system("cls");
            cout << "Fin del juego" << endl;
            break;
        default:
            cout << "Opcion incorrecta, escoja otra" << endl;
            break;
        }
    }
    return 0;
}

int ingresaPorRango(int inicio, int fin)
{
    int valor;
    bool repetir = true;
    while (repetir)
    {
        cin >> valor;
        if (valor >= inicio && valor <= fin)
        {
            repetir = false;
        }
        else
        {
            cout << "Valor fuera de rango" << endl;
        }
    }
    return valor;
}

Batalla *lucharEntrenadores(Entrenador *rude1, Entrenador *rude2)
{
    Batalla *epicGame = new Batalla(rude1->getNombre(), rude2->getNombre());
    bool ganador = true;
    int puntajeRude1 = 0, puntajeRude2 = 0;

    // ACLARACION:
    // Este va a ser un sistema de lucha uno a uno. El primero con el primero, etc-> Ya despues hacemos herencia para diferentes tipos de batalla
    // system("cls");
    for (int i = 0; i < 3; i++)
    {

        char s;
        cout << "Presiona una tecla y enter para continuar" << endl;
        cin >> s;

        cout << "Combate " << i + 1 << endl;
        cout << rude1->getNombre() << ": " << puntajeRude1 << "|| " << rude2->getNombre() << ": " << puntajeRude2 << endl;
        epicGame->luchar(rude1->getPokemon(i), rude2->getPokemon(i), ganador); // Revisar método getPokemon de la clase Entrenador
        if (ganador)
        {
            cout << "Tu pokemon " << rude1->getPokemon(i)->getNombre() << " ha ganado!!" << endl;
            rude1->entrenar(rude1->getPokemon(i));
            if (rude1->getPokemon(i)->verificarAumentoNivel())
            {
                rude1->getPokemon(i)->aumentarNivel();
                rude1->getPokemon(i)->evolucionar();
                rude1->aumentarNivel();
            }
            epicGame->agregarPokGanador(rude1->getPokemon(i));
            puntajeRude1++;
        }
        else
        {
            cout << rude2->getPokemon(i)->getNombre() << " te ha vencido, y se ha vuelto más fuerte" << endl;
            rude2->entrenar(rude2->getPokemon(i));
            if (rude2->getPokemon(i)->verificarAumentoNivel())
            {
                rude2->getPokemon(i)->aumentarNivel();
                rude2->aumentarNivel();
            }
            epicGame->agregarPokGanador(rude2->getPokemon(i));
            puntajeRude2++;
        }
    }

    if (puntajeRude1 > puntajeRude2)
    {
        epicGame->setGanador(rude1);
        cout << "Felicidades, has ganado!!!" << endl;
    }
    else
    {
        cout << "Has perdido" << endl;
        epicGame->setGanador(rude2);
    }

    return epicGame;
}