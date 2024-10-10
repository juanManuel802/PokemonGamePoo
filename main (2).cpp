#include <iostream>
#include <vector>

using namespace std;


class Pokemon {
private:
    string nombre;
    string color;
    int ataque;
    int vida;
    int xp;
    int nivel;
    string ataqueEspecial; //Antes estaba como bool(para verificar el modo), aunque esa logica la podriamos
    //manehjar en el sistema de batalla con un random, para que segun cierta probabilidad lanza el ataque
    //especial y muestre en pantalla que tal pokemon ha lanzado el ataque tal, lo que podría ser más interesante

public:
    Pokemon(): nombre("Pokemon"), color("amarillo"), ataque(20), vida(100), xp(0), nivel(1), ataqueEspecial("") {}

    Pokemon(string nombre, string color, int ataque, int vida, int xp, int nivel, string ataqueEspecial) {
        this->nombre = nombre;
        this->color = color;
        this->ataque = ataque;
        this->vida = vida;
        this->xp = xp;
        this->nivel = nivel;
        this->ataqueEspecial = ataqueEspecial;
    }

    string getNombre() const { return nombre;}
    string getColor() const { return color;}
    string getAtaqueEspecial() const {return ataqueEspecial;}
    int getAtaque() const { return ataque;}
    int getVida() const { return vida;}
    int getXp() const { return xp;}
    int getNivel() const { return nivel;}

    void setNombre(string nombre) { this->nombre = nombre;}
    void setColor(string color) { this->color = color;}
    void setAtaque(int ataque) { this->ataque = ataque;}
    void setVida(int vida) { this->vida = vida;}
    void setXp(int xp) { this->xp = xp;}
    void setNivel(int nivel) { this->nivel = nivel;}
    void setAtaqueEspecial(string ataqueEspecial) {this->ataqueEspecial = ataqueEspecial;}

    void saludar() {
        cout << "¡Hola!, soy " << nombre << ", estoy a tu disposición." << endl;
        mostrarDatos();
    }

    void sanar() {
        if (vida < 100) {
            vida = 100;
        }
    }

    void evolucionar(string nombre, string color) {
        if (nivel==2){
            this->nombre = nombre;
            this->color = color;
            ataque += ataque * 0.2;
        } else if (nivel==3) {
            this->nombre = nombre;
            this->color = color;
            ataque += ataque * 0.2;
        }
        mostrarDatos();
    }
    bool inline verificarAumentoNivel() {
        return xp > nivel*100;
    }

    void inline aumentarNivel() {
        nivel++;
    }

    void inline mostrarDatos() {
        cout << nombre << " Color: " << color << " || Nivel de Vida: " << vida << " || Potencia de Ataque: " << ataque << " || Xp: " << xp << " || Nivel: " << nivel <<endl;
    }

    //sobrecarga del + para crear pokemon recargado
    Pokemon  operator + (const Pokemon & c) const {
        //creamos un objeto nuevo de la clase cargo llamado "pokemonrecargado" e instantaneamente en sus parametros
        //sumamos los atributos de otros objetos para agregarlos en los atributos de "pokemonrecargado"
        //y luego se retorna el objeto
        Pokemon pokemonrecargado (" SuperPokemon! "," multicolor! ",ataque+c.ataque,vida+c.vida, xp+c.xp,nivel+c.nivel,"Vacio infinito!" );

        return pokemonrecargado;

    }
};

class Entrenador {
private:
    vector<Pokemon> misPokemones; //aunque debe ser 3, eso se maneja en la excepci+on
    string nombre;
    int nivel;
public:
    Entrenador(): nombre(""), nivel(1) {}
    string getNombre()const {return nombre;}
    int getNivel()const {return nivel;}
    void setNombre(string nombre) {this->nombre = nombre;}
    void setNivel(int nivel) {this->nivel = nivel;}
    //IMPORTANTE
    //aqui se devuelve un valor por referencia, si no colocan el & no sirve
    Pokemon &getPokemon(int i) {
        return misPokemones[i];
    }

    //metodo para agregar pokemones en el Dec del entrenador
    void agregarpokemon(Pokemon &poke){
        misPokemones.push_back(poke);
    }

    void entrenar(Pokemon &miPok, const Pokemon &oponente) {
        int xpGanado;
        miPok.setXp(miPok.getXp()+ oponente.getNivel()*nivel);
        cout << "El entrenador " << nombre <<" ha entrenado a " << miPok.getNombre() << endl;
        if(miPok.verificarAumentoNivel()) {
            string nombre, color;
            //Cambiar mensajes
            cout << "Enhorabuena, haz subido de nivel!!\nPuedes cambiar el nombre y color de tu Pokemon. Además la potencia de ataque se aumentó un 20%\n";
            cout << "Nuevo nombre:\n";
            cin >> nombre;
            cout << "Nuevo color:\n";
            cin >> color;
            miPok.aumentarNivel();
            miPok.evolucionar(nombre,color);
            aumentarNivel();
        }
    }

    void aumentarNivel() {
        setNivel(getNivel()+ 1);
    }

    //Se hace sobrecarga del operador cout para mostrar info
    friend ostream& operator << (ostream &o,Entrenador c);
};
//sobrecarga del operador << para mostrar informacion de entrenadores
ostream& operator << (ostream &o,Entrenador c){

for(int i=0;i<c.misPokemones.size();i++){
    //pasé el return de antes del o para ponerlo afuera
    //sirve, pero toca que los juanes califiquen
    o<<"Nombre del entrenador: "<<c.nombre<< " / Nivel del entrenador: "<<c.nivel
    <<"\n---- Pokemon "<<i+1<<"----"<<"\n Nombre: "<<c.misPokemones[i].getNombre()<<
    " \n color: "<<c.misPokemones[i].getColor()<<"\n ataque: "<<
    c.misPokemones[i].getAtaque()<<"\n vida "<<c.misPokemones[i].getVida()<<
    " \n experiencia: "<<c.misPokemones[i].getXp()<<"\n nivel: "<<
    c.misPokemones[i].getNivel()<<"\n ataque especial: "<<c.misPokemones[i].getAtaqueEspecial()<<endl;


}
    return o;

}

class Batalla {
private:
    int numeroDeBatalla;


public:
    //Este metodo recibe entrenadores para utilizar sus pokemones para la batalla
    Batalla(): numeroDeBatalla(0) {}
    void luchar(Pokemon &miPok, Pokemon &oponente, bool &ganador) {
        int vidaOponente, vidaMiPok, ataqueMiPok, ataqueOponente, nivelMipok, nivelOponente, xpMiPok, xpOponente, ronda = 1;
        char sig;

        vidaOponente = oponente.getVida();
        vidaMiPok = miPok.getVida();
        ataqueMiPok = miPok.getAtaque();
        ataqueOponente = oponente.getAtaque();
        nivelMipok = miPok.getNivel();
        nivelOponente = oponente.getNivel();
        system("cls");
        cout << "\n\n\n QUE COMIENCE LA PELEA!\n ";
        miPok.mostrarDatos();
        cout << "\n          vs          \n";
        oponente.mostrarDatos();
        cout << "\n\n***********\n\n";

        while (vidaOponente > 0 && vidaMiPok > 0) {
            int restOp, restMi;
            char sig;
            cout << "Ronda " << ronda << endl; //Inicia ronda
            vidaMiPok -= ataqueOponente; //Ataque  y resta vida a miPok(pok1)
            miPok.setVida(vidaMiPok); //Verifica si sigue vivo
            if (vidaMiPok <= 0) {
                vidaMiPok = 0;
                ganador = false; //Establece ganador
                break;
            }
            vidaOponente -= ataqueMiPok; //Otro pokemon recibe daño
            oponente.setVida(vidaOponente);
            if (vidaOponente <= 0) { //Verifica si el otro sigue vivo
                vidaOponente = 0;
                break; //Rompe la lucha
            }

            cout << miPok.getNombre() << ": Vida: " << vidaMiPok << endl;
            cout << oponente.getNombre() << ": Vida: " << vidaOponente << endl;
            cout << "\n\n" <<"*********" << "\n\n";
            do {
                cout << "Presiona X para continuar" << endl;
                cin >> sig;
            } while (sig != 'x' && sig != 'X');

            ronda++;
        }
        miPok.sanar();
        oponente.sanar();
    }

};


void lucharEntrenadores(Entrenador &rude1, Entrenador &rude2) {
    Batalla epicGame;
    bool ganador;
    //ACLARACION:
    //Este va a ser un sistema de lucha uno a uno. El primero con el primero, etc. Ya despues hacemos herencia para diferentes tipos de batalla
    //Otra posible forma, si vos sos unos genios pueden hacer marchin learning... no mentiras, solo
    //usar la sobrecarga del operador < o >, para comparar los pokemones y peliarlos según se deba.
    //Ejemplo, se pelean los que esten en un nivel más cercano.


    //Si quieren, hagan un for y remplazen el 0 por 1.
    epicGame.luchar(rude1.getPokemon(0), rude2.getPokemon(0), ganador); //Revisar método getPokemon de la clase Entrenador


    if (ganador) {
        rude1.entrenar(rude1.getPokemon(0), rude2.getPokemon(0));
    } else {
        rude2.entrenar(rude2.getPokemon(0), rude1.getPokemon(0));
    } //Ni se les ocurra agregar otra condicion o else, aqui no les genera aun lo que queremos,
    //pero es porque toca agragar una aleatoriedad (random en el daño) para que gane solo uno

}


int main() {
    string cond = "Si";
    int pro1, pro2;
    vector<Entrenador> entrenadores; //entrenadores del juego
    vector<Batalla> batallas;

    cout<<"Crea los entrenadores: " << endl;
    while (cond == "Si" || cond == "si") {
        Entrenador papuN;
        string nombre;
        int nivel;

        cout << "Dale un nombre al entrenador: " << endl;
        cin >> nombre;
        papuN.setNombre(nombre);

        cout << "Ahora crea sus tres pokemones " << endl;

        for (int i = 0; i < 3; ++i) {
            if(i>0) //este if solo ejecuta como verdadero la siguiente línea. Es un if de tipo parchado
                system("cls");
            Pokemon poki;
            string nombrePok, colorPok, ataqueEspecial;

            cout << "Nombre del Pokemon " << i+1 << ":" << endl;
            cin >> nombrePok;
            poki.setNombre(nombrePok);

            cout << "Color del Pokemon " << i+1 << ":" << endl;
            cin >> colorPok;
            poki.setColor(colorPok);

            cout << "Ataque especial: " << endl;
            cin >> ataqueEspecial;
            poki.setAtaqueEspecial(ataqueEspecial);

            papuN.agregarpokemon(poki);
        }
        entrenadores.push_back(papuN);

        cout << "Deseas agregar otro entrenador? (Si/no)" << endl;
        cin >> cond;
    }

    system("cls");
    cout<<"Entrenadores disponibles: "<<endl;
    for(int i=0; i<entrenadores.size(); i++) {
        cout << "1) " << entrenadores[i].getNombre() << endl;
    }




    //mostrar mediante sobrecarga del cout, la informacion de entrenadores
    //iria en la opcion de mostrar info de entrenadores del menu
    //esto es testeo, se acomodarátodo en el menú
    int open=0;
    cout<<"Ver info de entrenadores? 1.si 2.no"<<endl;
    cin>>open;

    if(open==1){
        cout<<"Que entrenador desea analizar? "<<endl;
        cout<<"Entrenadores disponibles: "<<endl;

        for(int i=0; i<entrenadores.size(); i++) {
            cout <<"1) "<< entrenadores[i].getNombre() << endl;
        }
        int openanalizar;
        cin>>openanalizar;
        //excepcion que suelte error si escoge algo distinto a 1 2 o 3
        if(openanalizar==1 || openanalizar==2 || openanalizar==3){
            cout<<entrenadores[openanalizar-1]<<endl;
        }


        for(int i=0;i<entrenadores.size();i++){
            cout<<entrenadores[i]<<endl;
        }
    }else{
        cout<<"siguiendo normalmente con el programa (señor usuario, ignore este mensaje)"<<endl;
    }
//hasta la linea 325 llega la opcion "analizar entrenadores" del menú que haremos





//generar un pokemon recargado mediante la sobrecarga del + que está en la clase pokemon
    int opcion=0;
cout<<"imagino que deseas recargar dos pokemones... cierto? 1) si, 2) no"<<endl;

    cin>>opcion;

    if(opcion==1){
        cout<<"primero elige el entrenador para asi acceder a sus pokemones"<<endl;

        for(int i=0; i<entrenadores.size(); i++) {
            cout <<"1) "<< entrenadores[i].getNombre() << endl;
        }
        int pepitoperez=0;
        cout<<"que entrenador escoges:"<<endl;

        cin>>pepitoperez;
        cout<<"a continuacion te muestro la hoja de vida del entrenador: "<<endl;
        cout<<entrenadores[pepitoperez-1]<<endl;
        cout<<endl;
        int pac1=0;
        cout<<"elige el primer pokemon a combinar"<<endl;

        cin>>pac1;

        int pac2=0;
        cout<<"elige el segundo"<<endl;

        cin>>pac2;
        //aplicacion de la sobrecarga del operador + (creando el pokemon recargado)
        cout<<"se esta creando el pokemon..."<<endl;
        Pokemon pokemonrecargado=entrenadores[pepitoperez-1].getPokemon(pac1-1)+entrenadores[pepitoperez-1].getPokemon(pac2-1);
        cout<<"Pokemon recargado creado!! datos a continuacion: "<<endl;
        pokemonrecargado.mostrarDatos();
    }else{
        cout<<"okey..siguiendo con el programa"<<endl;
    }







    //Aquí hacer un menú para opciones como:
    //1)Combatir dos entrenadores modo campal (idea de santiago)
    //2)Ver nopor de pokemones (reproducirlos utilizando sobrecarga de operadores)
    //..)las otras funcionalidades que nos pide la projesora

    //IMPORTANTE
    //Yo solo voy a hacer la opcion uno. Ustedes hagan el resto y configuren lo siguiente para que quede dentro del menu
    //pongo en comentarios para que no me moleste

    /* cout << "Selecciona dos entrenadores "<<endl;
    cout << "Entrenador 1: "<<endl;
    cin >> pro1;
    cout << "Entrenador 2"<<endl;
    cin >> pro2; */

    lucharEntrenadores(entrenadores[pro1-1],entrenadores[pro2-1]);


    return 0;
}