#ifndef CREDITOS_H
#define CREDITOS_H

#include "config.h"

struct Persona {
    char nombre[50];
    char apellido[50];
    char codigoSAC[11];
};

class Creditos {
private:
    Persona productores[MAX_CREDITOS];
    Persona musicos[MAX_CREDITOS];
    Persona compositores[MAX_CREDITOS];
    int nProductores;
    int nMusicos;
    int nCompositores;

public:
    Creditos();
    
    bool agregarProductor(const char* nombre, const char* apellido, const char* codigo);
    bool agregarMusico(const char* nombre, const char* apellido, const char* codigo);
    bool agregarCompositor(const char* nombre, const char* apellido, const char* codigo);
    
    // Utilidades
    void imprimir() const;
    int sizeBytes() const;
};

#endif // CREDITOS_H