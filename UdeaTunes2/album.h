#ifndef ALBUM_H
#define ALBUM_H

#include "config.h"
#include "cancion.h"

class Album {
private:
    long id;
    char nombre[100];
    char fechaLanzamiento[20];
    int duracionTotal;
    char sello[80];
    char portadaPath[300];
    int puntuacion;
    char generos[MAX_GENRES][30];
    int nGeneros;
    Cancion canciones[MAX_SONGS_PER_ALBUM];
    int nCanciones;

public:
    Album();
    void setDatos(long id_, const char* nombre_, const char* fecha_, int durTotal, const char* sello_, const char* portada_);
    
    bool agregarGenero(const char* g);
    bool agregarCancion(const Cancion& c);
    
    // Getters
    long getId() const;
    int getNumeroCanciones() const;
    const char* getPortada() const;
    const Cancion* obtenerCancionPorIndice(int idx) const;
    
    // Utilidades
    void imprimir() const;
    int sizeBytes() const;
};

#endif // ALBUM_H