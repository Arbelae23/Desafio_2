#include "cancion.h"
#include <cstring>
#include <iostream>

using namespace std;

Cancion::Cancion() {
    inicializarAtributos();
}

Cancion::Cancion(const char* titulo, const char* artista_principal,
                 const char* album, const char* genero,
                 int duracion_segundos, int anio_lanzamiento) {
    inicializarAtributos();
    establecerTitulo(titulo);
    establecerArtistaPrincipal(artista_principal);
    if (album) establecerAlbum(album);
    if (genero) establecerGenero(genero);
    establecerDuracion(duracion_segundos);
    establecerAnioLanzamiento(anio_lanzamiento);
}

Cancion::Cancion(const Cancion& otra) {
    inicializarAtributos();
    *this = otra;
}

Cancion::~Cancion() {
    liberarMemoria();
}

Cancion& Cancion::operator=(const Cancion& otra) {
    if (this != &otra) {
        liberarMemoria();
        inicializarAtributos();

        if (otra.titulo) copiarCadena(titulo, otra.titulo);
        if (otra.artista_principal) copiarCadena(artista_principal, otra.artista_principal);
        if (otra.album) copiarCadena(album, otra.album);
        if (otra.genero) copiarCadena(genero, otra.genero);

        duracion_segundos = otra.duracion_segundos;
        anio_lanzamiento = otra.anio_lanzamiento;
        creditos_cancion = otra.creditos_cancion;
    }
    return *this;
}

void Cancion::inicializarAtributos() {
    titulo = artista_principal = album = genero = nullptr;
    duracion_segundos = anio_lanzamiento = 0;
}

void Cancion::liberarMemoria() {
    liberarCadena(titulo);
    liberarCadena(artista_principal);
    liberarCadena(album);
    liberarCadena(genero);
}

void Cancion::copiarCadena(char*& destino, const char* origen) {
    if (origen) {
        int longitud = strlen(origen);
        destino = new char[longitud + 1];
        strcpy(destino, origen);
    } else {
        destino = nullptr;
    }
}

void Cancion::liberarCadena(char*& cadena) {
    if (cadena) {
        delete[] cadena;
        cadena = nullptr;
    }
}

// ----- Métodos de establecimiento -----
bool Cancion::establecerTitulo(const char* nuevo_titulo) {
    if (!nuevo_titulo || strlen(nuevo_titulo) == 0) return false;
    liberarCadena(titulo);
    copiarCadena(titulo, nuevo_titulo);
    return true;
}

bool Cancion::establecerArtistaPrincipal(const char* nuevo_artista) {
    if (!nuevo_artista || strlen(nuevo_artista) == 0) return false;
    liberarCadena(artista_principal);
    copiarCadena(artista_principal, nuevo_artista);
    return true;
}

bool Cancion::establecerAlbum(const char* nuevo_album) {
    liberarCadena(album);
    if (nuevo_album && strlen(nuevo_album) > 0) copiarCadena(album, nuevo_album);
    return true;
}

bool Cancion::establecerGenero(const char* nuevo_genero) {
    liberarCadena(genero);
    if (nuevo_genero && strlen(nuevo_genero) > 0) copiarCadena(genero, nuevo_genero);
    return true;
}

bool Cancion::establecerDuracion(int segundos) {
    if (!validarDuracion(segundos)) return false;
    duracion_segundos = segundos;
    return true;
}

bool Cancion::establecerAnioLanzamiento(int anio) {
    if (!validarAnio(anio)) return false;
    anio_lanzamiento = anio;
    return true;
}

// ----- Métodos de obtención -----
const char* Cancion::obtenerTitulo() const { return titulo; }
const char* Cancion::obtenerArtistaPrincipal() const { return artista_principal; }
const char* Cancion::obtenerAlbum() const { return album; }
const char* Cancion::obtenerGenero() const { return genero; }
int Cancion::obtenerDuracion() const { return duracion_segundos; }
int Cancion::obtenerAnioLanzamiento() const { return anio_lanzamiento; }

// ----- Créditos -----
bool Cancion::agregarProductor(const char* n, const char* a, const char* c) {
    return creditos_cancion.agregarProductor(n, a, c);
}
bool Cancion::agregarMusico(const char* n, const char* a, const char* c) {
    return creditos_cancion.agregarMusico(n, a, c);
}
bool Cancion::agregarCompositor(const char* n, const char* a, const char* c) {
    return creditos_cancion.agregarCompositor(n, a, c);
}

const Creditos& Cancion::obtenerCreditos() const { return creditos_cancion; }
Creditos& Cancion::obtenerCreditos() { return creditos_cancion; }

// ----- Mostrar información -----
void Cancion::mostrarInformacionCompleta() {
    cout << "\n===== INFORMACION DE LA CANCION =====\n";
    cout << "Titulo: " << (titulo ? titulo : "(sin titulo)") << "\n";
    cout << "Artista: " << (artista_principal ? artista_principal : "(sin artista)") << "\n";
    if (album) cout << "Album: " << album << "\n";
    if (genero) cout << "Genero: " << genero << "\n";
    cout << "Duracion: " << duracion_segundos << " segundos\n";
    cout << "Año de lanzamiento: " << anio_lanzamiento << "\n";
    creditos_cancion.mostrarCreditos();
}

// ----- Validaciones -----
bool Cancion::validarAnio(int anio) { return anio >= 1800 && anio <= 2025; }
bool Cancion::validarDuracion(int segundos) { return segundos >= 0 && segundos <= 7200; }

