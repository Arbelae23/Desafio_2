#include "artistas.h"
#include "album.h"
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;


// CONSTRUCTORES Y DESTRUCTOR


Artista::Artista() {
    inicializarAtributos();
}

Artista::Artista(const char* nombre, int codigo, int edad, const char* pais) {
    inicializarAtributos();
    establecerNombre(nombre);
    establecerCodigoIdentificador(codigo);
    establecerEdad(edad);
    if (pais) establecerPaisOrigen(pais);
}

Artista::Artista(const Artista& otro) {
    inicializarAtributos();
    *this = otro;
}

Artista::~Artista() {
    liberarMemoria();
}


// OPERADORES


Artista& Artista::operator=(const Artista& otro) {
    if (this != &otro) {
        liberarMemoria();
        inicializarAtributos();

        if (otro.nombre) copiarCadena(nombre, otro.nombre);
        if (otro.pais_origen) copiarCadena(pais_origen, otro.pais_origen);

        codigo_identificador = otro.codigo_identificador;
        edad = otro.edad;
        cantidad_seguidores = otro.cantidad_seguidores;
        posicion_tendencias_global = otro.posicion_tendencias_global;

        // Copiar referencias de albumes (no los albumes en si)
        for (int i = 0; i < otro.cantidad_albumes; i++) {
            agregarAlbum(otro.albumes[i]);
        }
    }
    return *this;
}


// METODOS AUXILIARES


void Artista::inicializarAtributos() {
    nombre = nullptr;
    codigo_identificador = 0;
    edad = 0;
    pais_origen = nullptr;
    cantidad_seguidores = 0;
    posicion_tendencias_global = 0;
    albumes = nullptr;
    cantidad_albumes = 0;
    capacidad_albumes = 0;
}

void Artista::liberarMemoria() {
    liberarCadena(nombre);
    liberarCadena(pais_origen);
    delete[] albumes;  // Solo el arreglo, no los albumes
}

void Artista::copiarCadena(char*& destino, const char* origen) {
    if (origen) {
        int longitud = strlen(origen);
        destino = new char[longitud + 1];
        strcpy(destino, origen);
    } else {
        destino = nullptr;
    }
}

void Artista::liberarCadena(char*& cadena) {
    if (cadena) {
        delete[] cadena;
        cadena = nullptr;
    }
}

void Artista::redimensionarAlbumes() {
    int nueva_capacidad = (capacidad_albumes == 0) ? 5 : capacidad_albumes * 2;

    Album** nuevo_arreglo = new Album*[nueva_capacidad];

    for (int i = 0; i < cantidad_albumes; i++) {
        nuevo_arreglo[i] = albumes[i];
    }

    delete[] albumes;
    albumes = nuevo_arreglo;
    capacidad_albumes = nueva_capacidad;
}


// SETTERS


bool Artista::establecerNombre(const char* nombre) {
    if (!nombre || strlen(nombre) == 0) return false;

    liberarCadena(this->nombre);
    copiarCadena(this->nombre, nombre);
    return true;
}

bool Artista::establecerCodigoIdentificador(int codigo) {
    if (!validarCodigo(codigo)) return false;

    codigo_identificador = codigo;
    return true;
}

bool Artista::establecerEdad(int edad) {
    if (!validarEdad(edad)) return false;

    this->edad = edad;
    return true;
}

bool Artista::establecerPaisOrigen(const char* pais) {
    liberarCadena(pais_origen);
    if (pais && strlen(pais) > 0) {
        copiarCadena(pais_origen, pais);
    }
    return true;
}

bool Artista::establecerCantidadSeguidores(int seguidores) {
    if (seguidores < 0) return false;
    cantidad_seguidores = seguidores;
    return true;
}

bool Artista::establecerPosicionTendencias(int posicion) {
    if (posicion < 0) return false;
    posicion_tendencias_global = posicion;
    return true;
}


// GETTERS


const char* Artista::obtenerNombre() const {
    return nombre ? nombre : "";
}

int Artista::obtenerCodigoIdentificador() const {
    return codigo_identificador;
}

int Artista::obtenerEdad() const {
    return edad;
}

const char* Artista::obtenerPaisOrigen() const {
    return pais_origen ? pais_origen : "";
}

int Artista::obtenerCantidadSeguidores() const {
    return cantidad_seguidores;
}

int Artista::obtenerPosicionTendencias() const {
    return posicion_tendencias_global;
}


// GESTION DE SEGUIDORES


void Artista::incrementarSeguidores(int cantidad) {
    cantidad_seguidores += cantidad;
    if (cantidad_seguidores < 0) cantidad_seguidores = 0;
}

void Artista::decrementarSeguidores(int cantidad) {
    cantidad_seguidores -= cantidad;
    if (cantidad_seguidores < 0) cantidad_seguidores = 0;
}


// GESTION DE ALBUMES


bool Artista::agregarAlbum(Album* album) {
    if (!album) return false;

    // Verificar si ya existe
    if (tieneAlbum(album)) return false;

    // Redimensionar si es necesario
    if (cantidad_albumes >= capacidad_albumes) {
        redimensionarAlbumes();
    }

    albumes[cantidad_albumes] = album;
    cantidad_albumes++;
    return true;
}

int Artista::obtenerCantidadAlbumes() const {
    return cantidad_albumes;
}

Album* Artista::obtenerAlbum(int indice) const {
    if (indice >= 0 && indice < cantidad_albumes) {
        return albumes[indice];
    }
    return nullptr;
}

bool Artista::tieneAlbum(const Album* album) const {
    for (int i = 0; i < cantidad_albumes; i++) {
        if (albumes[i] == album) return true;
    }
    return false;
}


// MOSTRAR INFORMACION


void Artista::mostrarInformacion() const {
    cout << "Artista: " << obtenerNombre();

    if (pais_origen && strlen(pais_origen) > 0) {
        cout << " (" << pais_origen << ")";
    }

    cout << "\nSeguidores: " << cantidad_seguidores;

    if (posicion_tendencias_global > 0) {
        cout << " - Posicion en tendencias: #" << posicion_tendencias_global;
    }

    cout << "\n";
}

void Artista::mostrarInformacionCompleta() const {
    cout << "\n INFORMACION DEL ARTISTA \n";
    cout << "Nombre: " << obtenerNombre() << "\n";
    cout << "Codigo: " << setfill('0') << setw(5) << codigo_identificador << "\n";

    if (edad > 0) {
        cout << "Edad: " << edad << " años\n";
    }

    if (pais_origen && strlen(pais_origen) > 0) {
        cout << "Pais de origen: " << pais_origen << "\n";
    }

    cout << "Seguidores: " << cantidad_seguidores << "\n";

    if (posicion_tendencias_global > 0) {
        cout << "Posicion en tendencias globales: #" << posicion_tendencias_global << "\n";
    }

    cout << "Albumes en catalogo: " << cantidad_albumes << "\n";
}

void Artista::mostrarAlbumes() const {
    cout << "\n ALBUMES DE " << obtenerNombre() << "\n";

    if (cantidad_albumes == 0) {
        cout << "(sin albumes)\n";
        return;
    }

    for (int i = 0; i < cantidad_albumes; i++) {
        cout << "  " << (i + 1) << ". ";
        if (albumes[i]) {
            albumes[i]->mostrarInformacionBasica();
        }
    }
}


// VALIDACIONES ESTATICAS


bool Artista::validarCodigo(int codigo) {
    // Codigo de 5 digitos: 00000-99999
    return codigo >= 0 && codigo <= 99999;
}

bool Artista::validarEdad(int edad) {
    return edad >= 0 && edad <= 120;
}
