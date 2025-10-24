#ifndef CANCION_H
#define CANCION_H

class Cancion {
private:
    long id;
    char titulo[100];
    char artistaPrincipal[80];
    char album[80];
    char genero[30];
    int duracionSegundos;
    int reproducciones;
    char ruta320[300];
    int codigoArtista;

public:
    Cancion();
    void setDatos(long id, const char* titulo, const char* artista, const char* album, const char* genero, int duracion);
    void setDatos(const char* titulo, long id, int duracion, const char* ruta);
    
    // Setters
    void establecerTitulo(const char* titulo);
    void establecerArtistaPrincipal(const char* artista);
    void establecerAlbum(const char* album);
    void establecerGenero(const char* genero);
    void establecerDuracion(int duracion);
    void establecerRuta320(const char* ruta);
    void establecerCodigoArtista(int codigo);
    
    // Getters
    long getId() const;
    const char* getNombre() const;
    const char* getTitulo() const;
    const char* obtenerTitulo() const;
    const char* obtenerArtistaPrincipal() const;
    const char* getArtista() const;
    const char* getAlbum() const;
    const char* getGenero() const;
    int getDuracion() const;
    const char* getRuta320() const;
    int getReproducciones() const;
    int getCodigoArtista() const;
    
    // Métodos funcionales
    void imprimir() const;
    void incrementarReproducciones();
    int sizeBytes() const;
};

#endif // CANCION_H