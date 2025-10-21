#include "playlist.h"
#include <cstdlib>
#include <ctime>

Playlist::Playlist(string nombre): nombre(nombre), numCanciones(0), capacidad(100) {
    canciones = new string[capacidad];
}
Playlist::~Playlist() { delete[] canciones; }

void Playlist::agregarCancion(string id) {
    if (numCanciones < capacidad) canciones[numCanciones++] = id;
}
void Playlist::eliminarCancion(string id) {
    for (int i=0; i<numCanciones; i++) {
        if (canciones[i] == id) {
            for (int j=i; j<numCanciones-1; j++) canciones[j] = canciones[j+1];
            numCanciones--;
            break;
        }
    }
}
void Playlist::reproducir() const {
    for (int i=0; i<numCanciones; i++)
        cout << "Reproduciendo: " << canciones[i] << endl;

}
void Playlist::reproducirAleatorio() const {
    srand(time(0));
    for (int i=0; i<numCanciones; i++) {
        int r = rand() % numCanciones;
        cout << "Aleatoria: " << canciones[r] << endl;
    }
}
