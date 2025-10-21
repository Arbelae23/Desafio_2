#ifndef CREDITOS_H
#define CREDITOS_H

#include <iostream>

class Creditos {
private:
    // Arreglos dinámicos para cada categoría
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

    // Métodos auxiliares privados
    void inicializarArreglos();
    void liberarMemoria();
    void copiarCadena(char*& destino, const char* origen);
    void redimensionar(char**& nombres, char**& apellidos, char**& codigos,
                       int& capacidad, int categoria);
    void eliminarElemento(char** nombres, char** apellidos, char** codigos,
                          int& cantidad, int indice);

public:
    // Constructores y destructor
    Creditos();
    Creditos(const Creditos& otros);
    ~Creditos();

    // Operadores esenciales
    Creditos& operator=(const Creditos& otros);

    // Meodos principales para agregar
    bool agregarProductor(const char* nombres, const char* apellidos, const char* codigo);
    bool agregarMusico(const char* nombres, const char* apellidos, const char* codigo);
    bool agregarCompositor(const char* nombres, const char* apellidos, const char* codigo);

    // Metodos principales para eliminar
    bool eliminarProductor(const char* codigo_afiliacion);
    bool eliminarMusico(const char* codigo_afiliacion);
    bool eliminarCompositor(const char* codigo_afiliacion);

    // Metodo para mostrar creditos
    void mostrarCreditos() const;

    // Método de validación estático
    static bool validarCodigoAfiliacion(const char* codigo);
};

#endif
