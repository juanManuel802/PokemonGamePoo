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

public:
    Pokemon(): nombre("Pokemon"), color("amarillo"), ataque(20), vida(100), xp(0), nivel(1) {}

    Pokemon(string nombre, string color, int ataque, int vida, int xp, int nivel) {
        this->nombre = nombre;
        this->color = color;
        this->ataque = ataque;
        this->vida = vida;
        this->xp = xp;
        this->nivel = nivel;
    }

    string getNombre() const { return nombre;}
    string getColor() const { return color;}
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

    void inline saludar() {
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
};

class Entrenador {
    private:
    vector<Pokemon> misPokemones[5];
    int nivel;
    string nombre, rango;
    public: 
    Entrenador(string nombre, int nivel, string rango) {
        _nombre = nombre;
        _nivel = nivel;
        _rango = rango;
    };
    string getNombre()const {return nombre;}
    string getRango()const {return rango;}
    int getNivel()const {return nivel;}
    void setNombre(string nombre) {_nombre = nombre;}
    void setRango(string rango) {_rango = rango;}
    void setNivel(int nivel) {_nivel = nivel;}

    void ascenderRango() {
        if (nivel>=10){
            setRango("Novato");
        } 
        else if (nivel>=20) {
            setRango("Experimentado");
        } else if (nivel>=50) {
            setRango("Líder de Gimnasio");
        } else if (nivel>=60) {
            setRango("Maestro");
        }
        else if (nivel>=80) {
            setRango("Gran Maestro");
        }
    }
    void entrenar(Pokemon &miPok, int nivel, Pokemon &oponente) {
        int xpGanado;
        miPok.setXp(miPok.getXp()+ oponente.getNivel*getNivel());
        cout << "El entrenador " << getNombre() <<" ha entrenado a " << miPok.getNombre() << endl;
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

    void aumentarNivel() {
        setNivel(getNivel()+ 5);
    }
    

    
}

class Batalla {
    private:
    int numeroDeBatallas;
    

    public:
    //Este metodo recibe entrenadores para utilizar sus pokemones para la batalla
    void luchar(Entrenador &yo, Pokemon &oponente) {
    int vidaOponente, vidaMiPok, ataqueMiPok, ataqueOponente, nivelMipok, nivelOponente, xpMiPok, xpOponente, ronda = 1;
    bool ganador = true; // true para mi pokemon, false si no
    string sig;
    
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
    cout << "\n\n***************************\n\n";
    
    while (vidaOponente > 0 && vidaMiPok > 0) {
        int restOp, restMi;
        string sig;
        cout << "Ronda " << ronda << endl;
        restMi = ataqueOponente + 2*nivelOponente;
        vidaMiPok -= restMi;
        miPok.setVida(vidaMiPok);
        if (vidaMiPok <= 0) {
            vidaMiPok = 0;
            ganador = false;
            break;
        }
        restOp = ataqueMiPok + 2*nivelMipok;
        vidaOponente -= restOp;
        if (vidaOponente <= 0) {
            vidaOponente = 0;
            break;
        }
        oponente.setVida(vidaOponente);

        cout << miPok.getNombre() << ": Vida: " << vidaMiPok << endl;
        cout << oponente.getNombre() << ": Vida: " << vidaOponente << endl;
         cout << "\n\n" <<"*************************" << "\n\n";
        do {
            cout << "Presiona X para continuar" << endl;
            getline(cin, sig);
        } while (sig != "x" && sig != "X");
       
        ronda++;
    }

    if (ganador) {
        //El entrenador de mi pok
        entrenador.entrenar();
    } else {
        int xpGanado;
        xpGanado = 40 + miPok.getNivel()*ronda;
        xpOponente = oponente.getXp() + xpGanado;
        miPok.setXp(xpOponente);
        cout << "Derrota, " << oponente.getNombre() << " te ha vencido... y se ha vuelto más fuerte!!!." << endl;
        if(oponente.verificarAumentoNivel()) {
        string nombre, color;
        nombre = oponente.getNombre();
        miPok.aumentarNivel();
        oponente.setNombre("Mega " + nombre);
        }
        
    }

    
    miPok.sanar();
    oponente.sanar();        
}

}



int main() {
    int opA, opB;
    string nombre;
    char quit, rep; //variables para continuar
    vector<Pokemon> misPokemones; //[]
    misPokemones.push_back(Pokemon("Pikachu", "Amarillo",20,100,0,1));
    misPokemones.push_back(Pokemon("Bulbasaur", "Azul",20,100,0,1));
    misPokemones.push_back(Pokemon("Wooloo", "Violeta",20,100,0,1));
    vector<Pokemon> contrincantes;
    contrincantes.push_back(Pokemon("Wartortle", "Azul",5,100,0,1));
    contrincantes.push_back(Pokemon("Arbok", "Violeta",15,100,0,2));
    contrincantes.push_back(Pokemon("Charizartl", "Naranja",25,100,0,3));



    
    do {
        do {
        cout << "Selecciona tu pokemon: " << endl;
        cout << "1. " << misPokemones[0].getNombre() <<"\n2. " << misPokemones[1].getNombre() << "\n3. " << misPokemones[2].getNombre() <<endl;
        cin >> opA;
        opA--;
        misPokemones[opA].saludar();
        cout << "Y/n" << endl;
        cin >> quit;
        if (quit=='n') {
            system("cls");
        }
        } while(quit!='Y');
        do {
        cout << "Selecciona tu pokemon oponente: " << endl;
        cout << "1. Wartortle \n2. Arbok\n3. Charizartl" << endl;
        cin >> opB;
        opB--;
        contrincantes[opB].mostrarDatos();
        cout << "Y/n" << endl;
        cin >> quit;
        } while(quit!='Y');

        luchar(misPokemones[opA], contrincantes[opB]);
        cout << "¿Deseas seguir jugando?\nY/n\n";
        cin >> rep;
    
    } while (rep =='Y');

    return 0;
}