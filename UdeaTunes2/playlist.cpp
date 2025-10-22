#include "playlist.h"
#include "cancion.h"
#include <cstring>
#include <iostream>

using namespace std;


// CONSTRUCTORES Y DESTRUCTOR

Playlist::Playlist() {
    nombre = nullptr;
    canciones = nullptr;
    cantidad_canciones = 0;
    capacidad_canciones = 0;
}

Playlist::Playlist(const char* nombre) {
    this->nombre = nullptr;
    canciones = nullptr;
    cantidad_canciones = 0;
    capacidad_canciones = 0;

    if (nombre) copiarCadena(this->nombre, nombre);
}

Playlist::Playlist(const Playlist& otra) {
    nombre = nullptr;
    canciones = nullptr;
    cantidad_canciones = 0;
    capacidad_canciones = 0;
    *this = otra;
}

Playlist::~Playlist() {
    liberarCadena(nombre);
    delete[] canciones;  // Solo liberar el arreglo, no las canciones
}


// OPERADORES


Playlist& Playlist::operator=(const Playlist& otra) {
    if (this != &otra) {
        // Liberar memoria actual
        liberarCadena(nombre);
        delete[] canciones;

        // Copiar datos
        cantidad_canciones = 0;
        capacidad_canciones = 0;
        canciones = nullptr;

        if (otra.nombre) copiarCadena(nombre, otra.nombre);

        // Copiar referencias de canciones
        for (int i = 0; i < otra.cantidad_canciones; i++) {
            agregarCancion(otra.canciones[i]);
        }
    }
    return *this;
}


// METODOS AUXILIARES

void Playlist::copiarCadena(char*& destino, const char* origen) {
    if (origen) {
        int longitud = strlen(origen);
        destino = new char[longitud + 1];
        strcpy(destino, origen);
    } else {
        destino = nullptr;
    }
}

void Playlist::liberarCadena(char*& cadena) {
    if (cadena) {
        delete[] cadena;
        cadena = nullptr;
    }
}

void Playlist::redimensionar() {
    int nueva_capacidad = (capacidad_canciones == 0) ? 10 : capacidad_canciones * 2;

    // No exceder el limite premium
    if (nueva_capacidad > LIMITE_PREMIUM) {
        nueva_capacidad = LIMITE_PREMIUM;
    }

    Cancion** nuevo_arreglo = new Cancion*[nueva_capacidad];

    // Copiar referencias existentes
    for (int i = 0; i < cantidad_canciones; i++) {
        nuevo_arreglo[i] = canciones[i];
    }

    delete[] canciones;
    canciones = nuevo_arreglo;
    capacidad_canciones = nueva_capacidad;
}

int Playlist::buscarCancion(const Cancion* cancion) const {
    for (int i = 0; i < cantidad_canciones; i++) {
        if (canciones[i] == cancion) {
            return i;
        }
    }
    return -1;
}


// METODOS PRINCIPALES


bool Playlist::agregarCancion(Cancion* cancion) {
    if (!cancion) return false;

    // Verificar si ya existe
    if (contieneCancion(cancion)) {
        return false;
    }

    // Verificar limite
    if (cantidad_canciones >= LIMITE_PREMIUM) {
        return false;
    }

    // Redimensionar si es necesario
    if (cantidad_canciones >= capacidad_canciones) {
        redimensionar();
    }

    canciones[cantidad_canciones] = cancion;
    cantidad_canciones++;
    return true;
}

bool Playlist::quitarCancion(Cancion* cancion) {
    int indice = buscarCancion(cancion);
    if (indice == -1) return false;

    // Desplazar elementos
    for (int i = indice; i < cantidad_canciones - 1; i++) {
        canciones[i] = canciones[i + 1];
    }

    cantidad_canciones--;
    return true;
}

bool Playlist::contieneCancion(const Cancion* cancion) const {
    return buscarCancion(cancion) != -1;
}


// GETTERS


const char* Playlist::obtenerNombre() const {
    return nombre ? nombre : "";
}

int Playlist::obtenerCantidadCanciones() const {
    return cantidad_canciones;
}

Cancion* Playlist::obtenerCancion(int indice) const {
    if (indice >= 0 && indice < cantidad_canciones) {
        return canciones[indice];
    }
    return nullptr;
}


// SETTERS


bool Playlist::establecerNombre(const char* nuevo_nombre) {
    if (!nuevo_nombre || strlen(nuevo_nombre) == 0) return false;

    liberarCadena(nombre);
    copiarCadena(nombre, nuevo_nombre);
    return true;
}

// UTILIDADES


void Playlist::mostrarCanciones() const {
    cout << "\n=== Playlist: " << (nombre ? nombre : "Sin nombre") << " ===\n";
    cout << "Cantidad de canciones: " << cantidad_canciones << "\n";

    if (cantidad_canciones == 0) {
        cout << "(vacia)\n";
        return;
    }

    for (int i = 0; i < cantidad_canciones; i++) {
        cout << "  " << (i + 1) << ". ";
        if (canciones[i]) {
            cout << canciones[i]->obtenerTitulo() << " - "
                 << canciones[i]->obtenerArtistaPrincipal();
        } else {
            cout << "(cancion invalida)";
        }
        cout << "\n";
    }
}

void Playlist::limpiar() {
    cantidad_canciones = 0;
}
