#ifndef CREDITOS_H
#define CREDITOS_H

#include <iostream>

class Creditos {
private:
    // Arreglos dinamicos para cada categoria
    char** nombres_productores;
    char** apellidos_productores;
    char** codigos_productores;
    int capacidad_productores;
    int cantidad_productores;

    char** nombres_musicos;
    char** apellidos_musicos;
    char** codigos_musicos;
    int capacidad_musicos;
    int cantidad_musicos;

    char** nombres_compositores;
    char** apellidos_compositores;
    char** codigos_compositores;
    int capacidad_compositores;
    int cantidad_compositores;

    // Metodos auxiliares privados
    void inicializarArreglos();
    void liberarMemoria();
    void copiarCadena(char*& destino, const char* origen);
    void redimensionar(char**& nombres, char**& apellidos, char**& codigos,
                       int& capacidad, int categoria);

public:
    // Constructores y destructor
    Creditos();
    Creditos(const Creditos& otros);
    ~Creditos();

    // Operadores esenciales
    Creditos& operator=(const Creditos& otros);

    // Metodos principales para agregar (SOLO agregar, sin eliminacion)
    bool agregarProductor(const char* nombres, const char* apellidos, const char* codigo);
    bool agregarMusico(const char* nombres, const char* apellidos, const char* codigo);
    bool agregarCompositor(const char* nombres, const char* apellidos, const char* codigo);

    // Metodos de consulta
    int obtenerCantidadProductores() const;
    int obtenerCantidadMusicos() const;
    int obtenerCantidadCompositores() const;
    int obtenerTotalPersonas() const;

    // Metodo para mostrar creditos
    void mostrarCreditos() const;

    // Metodo de validacion estatico
    static bool validarCodigoAfiliacion(const char* codigo);
};

#endif
