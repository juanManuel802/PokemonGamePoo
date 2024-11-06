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

    virtual ~Pokemon() = default;

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

    ~Entrenador() {
        for (Pokemon* p : misPokemones) {
            delete p;
        }
    }

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

//aqui empieza lo bueno la lucha

    void luchar(Pokemon *miPok, Pokemon *oponente, bool &ganador){

        int vidaOponente,vidaOponenteantesX=0,vidaOponenteantesP=0, vidaMiPok, ataqueMiPok, ataqueOponente, nivelMipok, nivelOponente, xpMiPok, xpOponente, ronda = 1, atq = 0, atqO = 0;
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

        //hasta que algun pokemon enemigo o amigo muera, sucede este ciclo: cada ciclo es una RONDA
        while (vidaOponente > 0 && vidaMiPok > 0){

            //inicializamos semilla para numeros  pseudo-aleatorios
            srand(static_cast<unsigned>(time(0)));

            //crea numeros aleatorios por ronda
            int variableAleatoria = rand() % 2 + 1;

            //variables para verificar si hay un pokemon congelado o no
            //e inciizalicacion de otras variables que se usarán
             bool congeladoverop = false;
            bool congeladovermi = false;
            int restOp, restMi;
            int  vidaMiPokantes=0, dañoTotalOponente = 0, dañoTotalMiPok = 0; // dañoTotal para extraer la informacion deel daño que hizo el pokemon luego del ataque cualquiera que sea
            char sig, tipoAtaque;
            dañoTotalOponente = ataqueOponente;
            dañoTotalMiPok = ataqueMiPok;



            cout << "                              Presiona (x) para lanzar un ataque normal o (p) para un ataque especial." << endl;
            cout << "                                        Solo tienes una oportunidad para lanzar el ataque especial" << endl;
            cout << "\n\n{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-} RONDA " << ronda << " {,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}{,.-}" << endl; // Inicia ronda
            cout << endl;

            // esto muestra la variable aleatoria generada en cada ronda
            cout << "variable aletoria : " << variableAleatoria;

            //si variable aleatoria es 1, indica que el enemigo usará su ataque especial!!
            if(variableAleatoria==1){

                cout<<" Preparate... "<<endl;
            }else{

                cout<<endl;
            }

            //si atq es distinto a 1, (indicando asi que no hemos usado ningun ataque especial en la ronda anterior), se ejecuta un ataque normal...
            if (atq == 0 || atq > 1)

            { // atq>1 para confirmar si ya se usó el especial y si es asi, mandar solo normales ahora

                vidaMiPok -= dañoTotalOponente;

                setRegistroDaño(getRegistroDaño() + ataqueOponente);
            }

            //si no, se pregunta que tipo de ataque especial es, y dependiendo de eso, hace interacciones distintas...
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
                cout << oponente->getNombre() << " esta descongelandose... preparate! " << endl;
            }
            else
            {
                // si la variable es 1, usa su ataque especial, aqui solo muestra al usuario que la usó
                //atqO es la variable que nos indica si ya se usó o no el ataque especial del enemigo (0= no se ha usado)(1= si)
                //si variableAleatoria=1, indica que el ataque especial del enemigo esta en marcha..
                if (variableAleatoria == 1 && atqO == 0)
                {
                    //vidaMiPokantes es una variable que guarda la vida de mi pokemon...  (una copia)
                    //vidaMiPokantes=vidaMiPok;

                  //se le suma a atqO para definir que ya se usó....
                    atqO++;

                    if (atqO == 1)
                    {
                        cout << oponente->getNombre() << " Ha usado su ataque especial: ";

                        if (oponente->getAtaqueEspecial() == "Congelamiento")
                        {
                            cout << " Congelamiento!! : ";
                            oponente->hacerGritoDeAsalto();
                         cout << "Vida de " << miPok->getNombre() << ": " << vidaMiPok + dañoTotalOponente << " - " << dañoTotalOponente << " ->  " << vidaMiPok << endl;


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
                            cout << "Vida de " << miPok->getNombre() << ": " << (vidaMiPok+ataqueOponente) << " - " <<ataqueOponente<< " ->  " << vidaMiPok << endl;

                        }
                    }
                }
                else if(vidaMiPokantes>0){

                                cout << oponente->getNombre() << " ha atacado pero el escudo de " <<miPok->getNombre()<<"mitiga parte del daño! "<< endl;
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
                    //antes de nosotros atacar ya sea con ataque normal o especial... si estamos intoxicados el veneno actua...
                    if (variableAleatoria == 1 && atqO == 1 && oponente->getAtaqueEspecial() == "Intoxicacion")
                    {
                        //variableAleatoria=2;

                        cout << miPok->getNombre() << " esta intoxicado y el veneno empeora! NOOOO " << endl;

                        //muestra graficamente la vida de nuestro pokemon menos el nivel del veneno actualmente...
                        cout << vidaMiPok << " - " << dynamic_cast<PokemonVeneno *>(oponente)->getToxicidad() << " = ";


                        //aqui hace ya internamente lo que se mostró graficamente anteriormente...
                        vidaMiPok -= dynamic_cast<PokemonVeneno *>(oponente)->getToxicidad();

                        //aqui imprime la vida de nuestro pokemon luego de recibir el veneno actual
                        cout << vidaMiPok << endl;

                        //registramos el daño..
                        setRegistroDaño(getRegistroDaño() + ataqueMiPok + dynamic_cast<PokemonVeneno *>(oponente)->getToxicidad());

                        //finalmente el veneno aumenta en 3 para la siguiente ronda!!
                        dynamic_cast<PokemonVeneno *>(oponente)->aumentarToxicidad(3);

                    }

                    // Verifica si el pokemon sigue vivo, porque pudo haber muerto por intoxicacion
                    if (vidaMiPok <= 0)
                    {
                        vidaMiPok = 0;
                        ganador = false; // Establece ganador
                        break;
                    }

                    else
                    //ahora si atacamos, y elegimos entre ataque normal o especial (x ó p)
                    {
                        //posible solucion a un bug
                        if(vidaOponenteantesX != 0){

                            variableAleatoria=1;

                        }




                        if( !(oponente->getAtaqueEspecial()=="Congelamiento" &&  atqO==1) ){
                            cout << "Ataca!!" << endl;
                            cin >> tipoAtaque;
                        }



                    }
                        //si el usuario ataca normal y la variablealeatoria que nos indica que el ataque especial del enemigo esta en marcha, entramos a este if...
                    if (tipoAtaque == 'x' && variableAleatoria == 1)
                    {

                         //variableAleatoria=2;

                         //aca empieza a preguntar si es congelamiento o escudo de acero...
                         //recordar que atqO es una variable que nos indica que el ataque especial enemigo ya fue usado o no...
                        if (oponente->getAtaqueEspecial() == "Congelamiento" && atqO == 1)
                        {
                            //no hará daño asi que hacemos esta igualacion
                            dañoTotalMiPok = 0;

                            cout << miPok->getNombre() << " esta congelado!!!! " << endl;

                            //atqO++ ya que este ataque especial es único.. no como los otros 2
                            atqO++;

                            //el booleano congeladovermi lo vuelve true para usarlo mas adelante
                            congeladovermi = true;

                        }

                        //si no es congelamiento entra al ataque especial escudo de acero...
                        //pregunta si la via del escudo de acero del enemigo es mayor a cero y si atqO es 1...
                        else if (oponente->getAtaqueEspecial() == "Escudo de Acero" && (dynamic_cast<PokemonAcero *>(oponente)->getEscudoAcero() > 0) && atqO == 1)
                        {

                            //indica la vida del escudo del enemigo...
                            cout<<"Escudo actual de "<<oponente->getNombre()<<" : "<< dynamic_cast<PokemonAcero *>(oponente)->getEscudoAcero() <<endl;

                            //como es ataque normal, desgasta el escudo solamente con el 20% del daño normal del enemigo (EJ: si es 100, le quita 20)
                            dynamic_cast<PokemonAcero *>(oponente)->desgastarEscudo(ataqueMiPok * 0.2);

                            //variable que guarda la vida del oponente ANTES de recibir el daño reducido 20% (recordar, que es daño normal en este caso)
                            vidaOponenteantesX = vidaOponente;

                            //como el ataque especial es escudo de acero, le quitamos el daño normal menos un 20% ...
                            vidaOponente -= (ataqueMiPok - (ataqueMiPok * 0.2));

                            //registramos el daño hecho en total
                            setRegistroDaño(getRegistroDaño() + (ataqueMiPok - ataqueMiPok * 0.2));

                        }

                       // cout << "\n**************************************************************\n";

                        //la variable booleana congeladovermi verifica si el ataque espcial era congelado, y si es asi entra a este if
                        if (congeladovermi)
                        {
                            //imprime este cout y nada mas...
                            cout << miPok->getNombre() << " esta descongelandose... " << endl;

                        }
                        else
                        {

                            //pregunta si vidaOponenteantesX es mayor a cero, si es cierto quiere decir que el ataque especial es escudo de Acero
                            if(vidaOponenteantesX != 0){


                            }else{

                            //si no es congelamiento ni escudo de acero , es Intoxicacion y en Intoxicacion el ataque es normal
                            vidaOponente -= ataqueMiPok;

                            //registramos el daño hecho...
                            setRegistroDaño(getRegistroDaño() + ataqueMiPok);


                            cond = false;
                        }}
                    }


                    //si el ataque especial del enemigo no esta en uso, pegamos normal
                    else if (tipoAtaque == 'x')
                    {

                        vidaOponente -= ataqueMiPok;

                        //registramos daño..
                        setRegistroDaño(getRegistroDaño() + ataqueMiPok);

                        cond = false;
                    }


                    //si usamos el ataque especial de nuestro pokemon Y el ataque especial del enemigo esta en uso entramos a este if
                    else if (atq == 0 && tipoAtaque == 'p' && variableAleatoria == 1)
                    {

                        //variableAleatoria = 2;
                        atq++;

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

                            //variable que guarda la vida del oponente ANTES de recibir el daño reducido EN EL IF DE USAR P
                            vidaOponenteantesP = vidaOponente;

                            //este es el daño extra por usar ataque especial
                            dañoTotalMiPok = ataqueMiPok + ataqueMiPok * .4;

                            //aqui esta el proceso para mitigar un 20% del daño de nuestro pokemon hacia el enemigo (ya que este ultimo usó su ataque especial )
                            dynamic_cast<PokemonAcero *>(oponente)->desgastarEscudo((ataqueMiPok + ataqueMiPok * .4) * 0.2);

                            vidaOponente -= ((ataqueMiPok + ataqueMiPok * .4) - ((ataqueMiPok + ataqueMiPok * .4) * 0.2));

                            //registro del daño hecho...
                            setRegistroDaño(getRegistroDaño() + (ataqueMiPok + ataqueMiPok * .4) - ((ataqueMiPok + ataqueMiPok * .4) * 0.2));

                        }

                        //si el pokemon esta congelado, no mostrará que atacó sino que esta descongelandose...
                        if (congeladovermi)
                        {
                            cout << miPok->getNombre() << " esta descongelandose... " << endl;
                        }

                        //si no, va a entrar a este else...
                        else
                        {
                            //vidaOponenteantesP es una variable que nos ayuda a diferenciar si el ataque especial del enemigo era escudo de acero...
                            //ya que esta variable llega a ser mayor a cero solamente si entra al if de escudo de acero...
                            if(vidaOponenteantesP>0){

                                cout<<"este cout sirve para verificar que efectivamente, no atacó de nuevo si es escudo de acero el ataque especial del enemigo"<<endl;

                            }

                            else
                            {
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
                if(vidaOponenteantesP>0){
                    cout << "\n**************************************************************\n";
                cout << miPok->getNombre() << " ha atacado pero el escudo de " <<oponente->getNombre()<<" mitiga parte del daño "<< endl;
                cout << oponente->getNombre() << ": Vida: " << vidaOponente + ((ataqueMiPok + (ataqueMiPok * .4)) - ((ataqueMiPok + ataqueMiPok * .4) * 0.2)) << " - " <<((ataqueMiPok + ataqueMiPok * .4) - ((ataqueMiPok + ataqueMiPok * .4) * 0.2))  << " ->  " << vidaOponente << endl;
                cout << "\n**************************************************************\n\n";

                }else if (vidaOponenteantesX>0){
                cout << miPok->getNombre() << " ha atacado pero el escudo de " <<oponente->getNombre()<<" mitiga parte del daño "<< endl;
                cout << oponente->getNombre() << ": Vida: " << vidaOponente + (ataqueMiPok - (ataqueMiPok * 0.2)) << " - " <<(ataqueMiPok - (ataqueMiPok * 0.2))<< " ->  " << vidaOponente << endl;
                cout << "\n**************************************************************\n\n";
                }
                else if (vidaOponenteantesP==0)
                {
                    if((oponente->getAtaqueEspecial()=="Congelamiento" &&  atqO==2)){
                        cout<<endl;
                    }else{

                cout << "\n**************************************************************\n";
                cout << miPok->getNombre() << " ha atacado " << endl;
                cout << oponente->getNombre() << ": Vida: " << vidaOponente + dañoTotalMiPok << " - " << dañoTotalMiPok << " ->  " << vidaOponente << endl;
                cout << "\n**************************************************************\n\n";
                    }
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
                    cout << "presiona una tecla y enter para aceptar" << endl;
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

    for(int i=0;i<entrenadores.size();i++){
        delete entrenadores[i];
        for(int j=0;j<3;j++){
            delete entrenadores[i]->getPokemon(j);
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