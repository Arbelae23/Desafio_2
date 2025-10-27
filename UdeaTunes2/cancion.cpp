#include "cancion.h"
#include <cstring>
#include <iostream>
using namespace std;

// Constructor
Cancion::Cancion() {
    id = 0;
    titulo[0] = 0;
    artistaPrincipal[0] = 0;
    album[0] = 0;
    genero[0] = 0;
    duracionSegundos = 0;
    reproducciones = 0;
    ruta320[0] = 0;
    rutaPortada[0] = 0;
    codigoArtista = 0;
}

// Setters
void Cancion::establecerTitulo(const char* titulo) {
    if (titulo) {
        strncpy(this->titulo, titulo, 99);
        this->titulo[99] = 0;
    }
}

void Cancion::establecerArtistaPrincipal(const char* artista) {
    if (artista) {
        strncpy(this->artistaPrincipal, artista, 79);
        this->artistaPrincipal[79] = 0;
    }
}

void Cancion::establecerAlbum(const char* album) {
    if (album) {
        strncpy(this->album, album, 79);
        this->album[79] = 0;
    }
}

void Cancion::establecerGenero(const char* genero) {
    if (genero) {
        strncpy(this->genero, genero, 29);
        this->genero[29] = 0;
    }
}

void Cancion::establecerDuracion(int duracion) {
    this->duracionSegundos = duracion;
}

void Cancion::establecerRuta320(const char* ruta) {
    if (ruta) {
        strncpy(this->ruta320, ruta, 299);
        this->ruta320[299] = 0;
    }
}

void Cancion::establecerRutaPortada(const char* ruta) {
    if (ruta) {
        strncpy(this->rutaPortada, ruta, 299);
        this->rutaPortada[299] = 0;
    }
}

void Cancion::establecerCodigoArtista(int codigo) {
    this->codigoArtista = codigo;
}

void Cancion::setDatos(long id, const char* titulo, const char* artista, const char* album, const char* genero, int duracion) {
    this->id = id;
    establecerTitulo(titulo);
    establecerArtistaPrincipal(artista);
    establecerAlbum(album);
    establecerGenero(genero);
    establecerDuracion(duracion);
}

void Cancion::setDatos(const char* titulo, long id, int duracion, const char* ruta) {
    this->id = id;
    establecerTitulo(titulo);
    establecerDuracion(duracion);
    establecerRuta320(ruta);
}

// Getters
long Cancion::getId() const {
    return id;
}

const char* Cancion::getNombre() const {
    return titulo;
}

const char* Cancion::getTitulo() const {
    return titulo;
}

const char* Cancion::obtenerTitulo() const {
    return titulo;
}

const char* Cancion::obtenerArtistaPrincipal() const {
    return artistaPrincipal;
}

const char* Cancion::getArtista() const {
    return artistaPrincipal;
}

const char* Cancion::getAlbum() const {
    return album;
}

const char* Cancion::getGenero() const {
    return genero;
}

int Cancion::getDuracion() const {
    return duracionSegundos;
}

const char* Cancion::getRuta320() const {
    return ruta320;
}

const char* Cancion::getRutaPortada() const {
    return rutaPortada;
}

int Cancion::getReproducciones() const {
    return reproducciones;
}

int Cancion::getCodigoArtista() const {
    return codigoArtista;
}

// Metodos funcionales
void Cancion::imprimir() const {
    cout << "  " << titulo << " - " << artistaPrincipal
         << " [" << genero << "] (" << duracionSegundos << "s)" << endl;
}

void Cancion::incrementarReproducciones() {
    reproducciones++;
}

int Cancion::sizeBytes() const {
    return sizeof(Cancion);
}
