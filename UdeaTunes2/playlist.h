#ifndef PLAYLIST_H
#define PLAYLIST_H

class Cancion;  // Forward declaration

class Playlist {
private:
    // Informacion basica
    char* nombre;

    // Arreglo dinamico de canciones (referencias, no copias)
    Cancion** canciones;
    int cantidad_canciones;
    int capacidad_canciones;

    // Metodos auxiliares
    void copiarCadena(char*& destino, const char* origen);
    void liberarCadena(char*& cadena);
    void redimensionar();
    int buscarCancion(const Cancion* cancion) const;

public:
    // Constructores y destructor
    Playlist();
    Playlist(const char* nombre);
    Playlist(const Playlist& otra);
    ~Playlist();

    // Operador de asignacion
    Playlist& operator=(const Playlist& otra);

    // Metodos principales
    bool agregarCancion(Cancion* cancion);  // Retorna false si ya existe o limite alcanzado
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
    void limpiar();  // Quita todas las canciones

    // Constante de limite para premium
    static const int LIMITE_PREMIUM = 10000;
};

#endif
