#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "config.h"
#include "cancion.h"

class Playlist {
private:
    char* nombre;
    Cancion** canciones;
    int cantidad_canciones;
    int capacidad_canciones;
    
    // Métodos auxiliares
    void copiarCadena(char*& destino, const char* origen);
    void liberarCadena(char*& cadena);
    void redimensionar();
    int buscarCancion(const Cancion* cancion) const;

public:
    Playlist();
    Playlist(const char* nombre);
    Playlist(const Playlist& otra);
    ~Playlist();
    
    // Operadores
    Playlist& operator=(const Playlist& otra);
    
    // Métodos principales
    bool agregarCancion(Cancion* cancion);
    bool quitarCancion(Cancion* cancion);
    bool contieneCancion(const Cancion* cancion) const;
    
    // Getters
    const char* obtenerNombre() const;
    int obtenerCantidadCanciones() const;
    Cancion* obtenerCancion(int indice) const;
    
    // Setters
    bool establecerNombre(const char* nuevo_nombre);
    
    // Utilidades
    void mostrarCanciones() const;
    void limpiar();
};

#endif // PLAYLIST_H