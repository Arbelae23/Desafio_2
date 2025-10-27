#include "album.h"
#include <iostream>
#include <cstring>
using namespace std;

Album::Album() {
    id = 0;
    nombre[0] = 0;
    nGeneros = 0;
    fechaLanzamiento[0] = 0;
    duracionTotal = 0;
    sello[0] = 0;
    portadaPath[0] = 0;
    puntuacion = 0;
    nCanciones = 0;
}

void Album::setDatos(long id_, const char* nombre_, const char* fecha_, int durTotal, const char* sello_, const char* portada_) {
    id = id_;
    strncpy(nombre, nombre_, 99);
    nombre[99] = 0;
    strncpy(fechaLanzamiento, fecha_, 19);
    fechaLanzamiento[19] = 0;
    duracionTotal = durTotal;
    strncpy(sello, sello_, 79);
    sello[79] = 0;
    strncpy(portadaPath, portada_, 299);
    portadaPath[299] = 0;
    nGeneros = 0;
    nCanciones = 0;
}

bool Album::agregarGenero(const char* g) {
    if (nGeneros >= MAX_GENRES) return false;
    strncpy(generos[nGeneros], g, 29);
    generos[nGeneros][29] = 0;
    nGeneros++;
    return true;
}

bool Album::agregarCancion(const Cancion& c) {
    if (nCanciones >= MAX_SONGS_PER_ALBUM) return false;
    canciones[nCanciones] = c;
    nCanciones++;
    return true;
}

void Album::setPuntuacion(int puntuacion_) {
    puntuacion = puntuacion_;
}

void Album::imprimir() const {
    cout << "Album: " << nombre << " id:" << id << " fecha:" << fechaLanzamiento << " dur:" << duracionTotal << "s\n";
    cout << " Portada: " << portadaPath << " Puntuacion: " << puntuacion << "\n";
    cout << " Generos: ";
    for (int i = 0; i < nGeneros; i++)
        cout << generos[i] << (i + 1 < nGeneros ? ", " : "");
    cout << "\n Canciones: " << nCanciones << "\n";
    for (int i = 0; i < nCanciones; i++) {
        cout << "  [" << i << "] ";
        canciones[i].imprimir();
    }
}

int Album::getNumeroCanciones() const { return nCanciones; }

const Cancion* Album::obtenerCancionPorIndice(int idx) const {
    if (idx < 0 || idx >= nCanciones) return nullptr;
    return &canciones[idx];
}

const char* Album::getPortada() const { return portadaPath; }

long Album::getId() const { return id; }

const char* Album::obtenerNombre() const { return nombre; }

int Album::sizeBytes() const { return sizeof(Album); }
