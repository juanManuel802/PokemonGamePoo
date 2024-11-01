#include <iostream>
#include <vector>
#include <exception>
#include "epersonalizado.h"
#include "pokemon.h"
#include "entrenador.h"
#include "batalla.h"

using namespace std;

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
            if(entrenadores.size()<2) {
                cout << "Primero crea entrenadores para que luchen" << endl;
                break;
            }
            do
            {
                Batalla game;
                cout << "Selecciona tu entrenador " << endl;
                cin >> pro1;
                cout << "Selecciona tu adversario" << endl;
                cin >> pro2;

                game = lucharEntrenadores(entrenadores[pro1 - 1], entrenadores[pro2 - 1]);

                batallas.push_back(game);
                cout << "Quieres volvera jugar? " << endl;
                cin >> cond;
                // Agregar excepcion aquí por si el usuario ingresa un valor que no sea si o no
            } while (cond == "si");
            break;
        case 3:
            if(entrenadores.size()==0){
                cout<<"Primero crea un entrenador!!"<<endl;
                break;
            }
            cout << "Que entrenador desea analizar? " << endl;
            cout << "Entrenadores disponibles: " << endl;

            for (int i = 0; i < entrenadores.size(); i++)
            {
                cout << i + 1 << ") " << entrenadores[i].getNombre() << endl;
            }
            int openanalizar;
            cin >> openanalizar;
            
            if (openanalizar == 1 || openanalizar == 2 || openanalizar == 3)
            {
                cout << entrenadores[openanalizar - 1] << endl;
            }
            
            break;

        case 4:
            cout << "imagino que deseas recargar dos pokemones... cierto? 1) si, 2) no" << endl;

            cin >> opcion;

            if (opcion == 1)
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
            else
            {
                cout << "okey..siguiendo con el programa" << endl;
            }

            break;
        case 6:
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

        cout << "Deseas seguir en el programa? (si/no)" << endl;
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
        system("cls");
        cout << "Combate " << i + 1 << endl;
        epicGame.luchar(rude1.getPokemon(i), rude2.getPokemon(i), ganador); // Revisar método getPokemon de la clase Entrenador
        if (ganador)
        {
            rude1.entrenar(rude1.getPokemon(i), rude2.getPokemon(i));
            epicGame.agregarPokGanador(rude1.getPokemon(i));
            puntajeRude1++;

            
        }
        else
        {
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
