#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>   

using namespace std;

// Estructura para guardar los datos de un Pokemon
struct Pokemon {
    int numero;
    string nombre;
    string tipo1;
    string tipo2;
    int total;
    int hp;
    int ataque;
    int defensa;
    int atqEsp;
    int defEsp;
    int velocidad;
};

// Esta funcion imprime un Pokemon en la pantalla
void imprimirPokemon(Pokemon p) {
    cout << "#" << p.numero << " | " << p.nombre;
    cout << " | Tipos: " << p.tipo1;
    if (p.tipo2 != "") {
        cout << ", " << p.tipo2;
    }
    cout << " | Total Stats: " << p.total;
    cout << " (HP:" << p.hp << " Atq:" << p.ataque << " Def:" << p.defensa << ")" << endl;
}

// Esta funcion toma una linea del archivo CSV y la convierte en un Pokemon
// Regresa true si se pudo, y false si es el encabezado
bool parsearLinea(string linea, Pokemon &p) {
    if (linea == "") {
        return false;
    }

    // Si la linea no empieza con un numero la saltamos
    if (linea[0] < '0' || linea[0] > '9') {
        return false;
    }

    stringstream ss(linea);
    string dato;

    getline(ss, dato, ',');
    p.numero = atoi(dato.c_str());

    getline(ss, p.nombre, ',');
    getline(ss, p.tipo1, ',');
    getline(ss, p.tipo2, ',');

    getline(ss, dato, ','); p.total    = atoi(dato.c_str());
    getline(ss, dato, ','); p.hp       = atoi(dato.c_str());
    getline(ss, dato, ','); p.ataque   = atoi(dato.c_str());
    getline(ss, dato, ','); p.defensa  = atoi(dato.c_str());
    getline(ss, dato, ','); p.atqEsp   = atoi(dato.c_str());
    getline(ss, dato, ','); p.defEsp   = atoi(dato.c_str());
    getline(ss, dato, ','); p.velocidad = atoi(dato.c_str());

    return true;
}

// Opcion 1: buscar un pokemon por su numero de pokedex
void buscarPorNumero(string nombreArchivo, int numero) {
    ifstream archivo;
    archivo.open(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    string linea;
    bool loEncontre = false;

    while (getline(archivo, linea)) {
        Pokemon p;
        if (parsearLinea(linea, p) == true) {
            if (p.numero == numero) {
                imprimirPokemon(p);
                loEncontre = true;
                break;
            }
        }
    }

    if (loEncontre == false) {
        cout << "No se encontro ningun Pokemon con el numero " << numero << endl;
    }

    archivo.close();
}

// Opcion 2: buscar un pokemon por su nombre
void buscarPorNombre(string nombreArchivo, string nombre) {
    ifstream archivo;
    archivo.open(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    string linea;
    bool loEncontre = false;

    while (getline(archivo, linea)) {
        Pokemon p;
        if (parsearLinea(linea, p) == true) {
            if (p.nombre == nombre) {
                imprimirPokemon(p);
                loEncontre = true;
                break;
            }
        }
    }

    if (loEncontre == false) {
        cout << "No se encontro ningun Pokemon con el nombre " << nombre << endl;
    }

    archivo.close();
}

// Opcion 3: mostrar todos los pokemones de un tipo dado
void buscarPorTipo(string nombreArchivo, string tipo) {
    ifstream archivo;
    archivo.open(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    string linea;
    bool loEncontre = false;

    while (getline(archivo, linea)) {
        Pokemon p;
        if (parsearLinea(linea, p) == true) {
            if (p.tipo1 == tipo) {
                imprimirPokemon(p);
                loEncontre = true;
            }
            else if (p.tipo2 == tipo) {
                imprimirPokemon(p);
                loEncontre = true;
            }
        }
    }

    if (loEncontre == false) {
        cout << "No se encontraron Pokemon del tipo " << tipo << endl;
    }

    archivo.close();
}

// Opcion 4: top 3 mas fuertes y top 3 mas debiles
void mostrarTopEstadisticas(string nombreArchivo) {
    ifstream archivo;
    archivo.open(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    // Metemos todos los pokemones en un arreglo grande
    Pokemon todos[500];
    int cuantos = 0;

    string linea;
    while (getline(archivo, linea)) {
        Pokemon p;
        if (parsearLinea(linea, p) == true) {
            todos[cuantos] = p;
            cuantos = cuantos + 1;
        }
    }
    archivo.close();

    // Ordenamos de menor a mayor con el metodo burbuja
    for (int i = 0; i < cuantos - 1; i++) {
        for (int j = 0; j < cuantos - 1 - i; j++) {
            if (todos[j].total > todos[j + 1].total) {
                Pokemon auxiliar = todos[j];
                todos[j] = todos[j + 1];
                todos[j + 1] = auxiliar;
            }
        }
    }

    cout << "\n--- TOP 3 POKEMON MAS FUERTES ---" << endl;
    if (cuantos >= 1) imprimirPokemon(todos[cuantos - 1]);
    if (cuantos >= 2) imprimirPokemon(todos[cuantos - 2]);
    if (cuantos >= 3) imprimirPokemon(todos[cuantos - 3]);

    cout << "\n--- TOP 3 POKEMON MAS DEBILES ---" << endl;
    if (cuantos >= 1) imprimirPokemon(todos[0]);
    if (cuantos >= 2) imprimirPokemon(todos[1]);
    if (cuantos >= 3) imprimirPokemon(todos[2]);
}

int main() {
    string nombreArchivo = "pokemon_150_registros.csv";

    // revisamos que el archivo exista
    ifstream revision;
    revision.open(nombreArchivo.c_str());
    if (!revision.is_open()) {
        cout << "Error: No se encontro el archivo '" << nombreArchivo << "' en la misma carpeta." << endl;
        return 1;
    }
    revision.close();

    int opcion = -1;

    while (opcion != 0) {
        cout << "\n=== MENU POKEDEX (Modo Fstream Directo) ===" << endl;
        cout << "1. Ver info de pokemon por numero de pokedex" << endl;
        cout << "2. Buscar/Ver info de pokemon por nombre" << endl;
        cout << "3. Ver pokemons de un tipo" << endl;
        cout << "4. Ver top 3 mas fuertes y top 3 mas debiles" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int num;
            cout << "Ingrese el numero de Pokedex: ";
            cin >> num;
            buscarPorNumero(nombreArchivo, num);
        }
        else if (opcion == 2) {
            string nombre;
            cout << "Ingrese el nombre del Pokemon (Respetando mayusculas iniciales): ";
            cin >> nombre;
            buscarPorNombre(nombreArchivo, nombre);
        }
        else if (opcion == 3) {
            string tipo;
            cout << "Ingrese el tipo en ingles (Ej. Fire, Water, Grass): ";
            cin >> tipo;
            buscarPorTipo(nombreArchivo, tipo);
        }
        else if (opcion == 4) {
            mostrarTopEstadisticas(nombreArchivo);
        }
    }

    return 0;
}