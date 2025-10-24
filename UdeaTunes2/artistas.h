#ifndef ARTISTAS_H
#define ARTISTAS_H

#include "config.h"
#include "album.h"

class Artista {
private:
    long id;
    char nombre[80];
    int edad;
    char pais[50];
    int seguidores;
    int posicionTendencias;
    Album albums[MAX_ALBUMS_PER_ARTIST];
    int nAlbums;

public:
    Artista();
    void setDatos(long id_, const char* nombre_, int edad_, const char* pais_);
    
    bool agregarAlbum(const Album& a);
    
    // Getters
    long getId() const;
    int getNumeroAlbums() const;
    const Album* obtenerAlbumPorIndice(int idx) const;
    
    // Utilidades
    void imprimir() const;
    int sizeBytes() const;
};

#endif // ARTISTAS_H