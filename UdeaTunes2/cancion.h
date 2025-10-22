#ifndef CANCION_H
#define CANCION_H

#include "creditos.h"
#include <iostream>

class Cancion {
private:
    // Información básica
    char* titulo;
    char* artista_principal;
    char* album;
    char* genero;
    int duracion_segundos;
    int anio_lanzamiento;

    // Créditos
    Creditos creditos_cancion;

    // Métodos auxiliares
    void copiarCadena(char*& destino, const char* origen);
    void liberarCadena(char*& cadena);
    void inicializarAtributos();
    void liberarMemoria();

public:
    // Constructores y destructor
    Cancion();
    Cancion(const char* titulo, const char* artista_principal,
            const char* album = nullptr, const char* genero = nullptr,
            int duracion_segundos = 0, int anio_lanzamiento = 0);
    Cancion(const Cancion& otra);
    ~Cancion();
    Cancion& operator=(const Cancion& otra);

    // Métodos de información básica
    bool establecerTitulo(const char* nuevo_titulo);
    bool establecerArtistaPrincipal(const char* nuevo_artista);
    bool establecerAlbum(const char* nuevo_album);
    bool establecerGenero(const char* nuevo_genero);
    bool establecerDuracion(int segundos);
    bool establecerAnioLanzamiento(int anio);

    // Métodos de obtención
    const char* obtenerTitulo() const;
    const char* obtenerArtistaPrincipal() const;
    const char* obtenerAlbum() const;
    const char* obtenerGenero() const;
    int obtenerDuracion() const;
    int obtenerAnioLanzamiento() const;

    // Créditos
    bool agregarProductor(const char* nombres, const char* apellidos, const char* codigo);
    bool agregarMusico(const char* nombres, const char* apellidos, const char* codigo);
    bool agregarCompositor(const char* nombres, const char* apellidos, const char* codigo);
    const Creditos& obtenerCreditos() const;
    Creditos& obtenerCreditos();

    // Mostrar información
    void mostrarInformacionCompleta();

    // Validaciones
    static bool validarAnio(int anio);
    static bool validarDuracion(int segundos);
};

#endif
