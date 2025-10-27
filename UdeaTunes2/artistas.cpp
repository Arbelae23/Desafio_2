#include "artistas.h"
#include <iostream>
#include <cstring>
using namespace std;

Artista::Artista() {
    id = 0;
    nombre[0] = 0;
    edad = 0;
    pais[0] = 0;
    seguidores = 0;
    posicionTendencias = 0;
    nAlbums = 0;
}

void Artista::setDatos(long id_, const char* nombre_, int edad_, const char* pais_) {
    id = id_;
    strncpy(nombre, nombre_, 79);
    nombre[79] = 0;
    edad = edad_;
    strncpy(pais, pais_, 49);
    pais[49] = 0;
    seguidores = 0;
    posicionTendencias = 0;
    nAlbums = 0;
}

void Artista::setDatos(long id_, const char* nombre_, int edad_, const char* pais_, int seguidores_, int posicionTendencias_) {
    id = id_;
    strncpy(nombre, nombre_, 79);
    nombre[79] = 0;
    edad = edad_;
    strncpy(pais, pais_, 49);
    pais[49] = 0;
    seguidores = seguidores_;
    posicionTendencias = posicionTendencias_;
    nAlbums = 0;
}

bool Artista::agregarAlbum(const Album& a) {
    if (nAlbums >= MAX_ALBUMS_PER_ARTIST) return false;
    albums[nAlbums] = a;
    nAlbums++;
    return true;
}

void Artista::imprimir() const {
    cout << "Artista: " << nombre << " id:" << id << " edad:" << edad
         << " pais:" << pais << " seguidores:" << seguidores
         << " pos:" << posicionTendencias << "\n";
    cout << " Albums: " << nAlbums << "\n";
    for (int i = 0; i < nAlbums; i++) {
        cout << "  Album[" << i << "] ";
        albums[i].imprimir();
    }
}

int Artista::getNumeroAlbums() const { return nAlbums; }

const Album* Artista::obtenerAlbumPorIndice(int idx) const {
    if (idx < 0 || idx >= nAlbums) return nullptr;
    return &albums[idx];
}

long Artista::getId() const { return id; }

const char* Artista::obtenerNombre() const { return nombre; }

int Artista::sizeBytes() const { return sizeof(Artista); }
