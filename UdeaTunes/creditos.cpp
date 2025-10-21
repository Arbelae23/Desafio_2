#include "creditos.h"
#include <cstring>
#include <cctype>

Creditos::Creditos() {
    inicializarArreglos();
}

Creditos::Creditos(const Creditos& otros) {
    inicializarArreglos();
    *this = otros;
}

Creditos::~Creditos() {
    liberarMemoria();
}

Creditos& Creditos::operator=(const Creditos& otros) {
    if (this != &otros) {
        liberarMemoria();
        inicializarArreglos();

        // Copiar productores
        for (int i = 0; i < otros.cantidad_productores; i++) {
            agregarProductor(otros.nombres_productores[i],
                             otros.apellidos_productores[i],
                             otros.codigos_productores[i]);
        }

        // Copiar músicos
        for (int i = 0; i < otros.cantidad_musicos; i++) {
            agregarMusico(otros.nombres_musicos[i],
                          otros.apellidos_musicos[i],
                          otros.codigos_musicos[i]);
        }

        // Copiar compositores
        for (int i = 0; i < otros.cantidad_compositores; i++) {
            agregarCompositor(otros.nombres_compositores[i],
                              otros.apellidos_compositores[i],
                              otros.codigos_compositores[i]);
        }
    }
    return *this;
}

void Creditos::inicializarArreglos() {
    // Inicializar todas las categorías
    nombres_productores = nullptr;
    apellidos_productores = nullptr;
    codigos_productores = nullptr;
    capacidad_productores = 0;
    cantidad_productores = 0;

    nombres_musicos = nullptr;
    apellidos_musicos = nullptr;
    codigos_musicos = nullptr;
    capacidad_musicos = 0;
    cantidad_musicos = 0;

    nombres_compositores = nullptr;
    apellidos_compositores = nullptr;
    codigos_compositores = nullptr;
    capacidad_compositores = 0;
    cantidad_compositores = 0;
}

void Creditos::liberarMemoria() {
    // Liberar memoria de productores
    for (int i = 0; i < cantidad_productores; i++) {
        delete[] nombres_productores[i];
        delete[] apellidos_productores[i];
        delete[] codigos_productores[i];
    }
    delete[] nombres_productores;
    delete[] apellidos_productores;
    delete[] codigos_productores;

    // Liberar memoria de músicos
    for (int i = 0; i < cantidad_musicos; i++) {
        delete[] nombres_musicos[i];
        delete[] apellidos_musicos[i];
        delete[] codigos_musicos[i];
    }
    delete[] nombres_musicos;
    delete[] apellidos_musicos;
    delete[] codigos_musicos;

    // Liberar memoria de compositores
    for (int i = 0; i < cantidad_compositores; i++) {
        delete[] nombres_compositores[i];
        delete[] apellidos_compositores[i];
        delete[] codigos_compositores[i];
    }
    delete[] nombres_compositores;
    delete[] apellidos_compositores;
    delete[] codigos_compositores;
}

void Creditos::copiarCadena(char*& destino, const char* origen) {
    if (origen != nullptr) {
        int longitud = strlen(origen);
        destino = new char[longitud + 1];
        strcpy(destino, origen);
    } else {
        destino = nullptr;
    }
}

void Creditos::redimensionar(char**& nombres, char**& apellidos, char**& codigos,
                             int& capacidad, int categoria) {
    int nueva_capacidad = (capacidad == 0) ? 2 : capacidad * 2;

    char** nuevos_nombres = new char*[nueva_capacidad];
    char** nuevos_apellidos = new char*[nueva_capacidad];
    char** nuevos_codigos = new char*[nueva_capacidad];

    int cantidad;
    switch(categoria) {
    case 0: cantidad = cantidad_productores; break;
    case 1: cantidad = cantidad_musicos; break;
    case 2: cantidad = cantidad_compositores; break;
    default: cantidad = 0;
    }

    for (int i = 0; i < cantidad; i++) {
        nuevos_nombres[i] = nombres[i];
        nuevos_apellidos[i] = apellidos[i];
        nuevos_codigos[i] = codigos[i];
    }

    delete[] nombres;
    delete[] apellidos;
    delete[] codigos;

    nombres = nuevos_nombres;
    apellidos = nuevos_apellidos;
    codigos = nuevos_codigos;
    capacidad = nueva_capacidad;
}

void Creditos::eliminarElemento(char** nombres, char** apellidos, char** codigos,
                                int& cantidad, int indice) {
    delete[] nombres[indice];
    delete[] apellidos[indice];
    delete[] codigos[indice];

    for (int i = indice; i < cantidad - 1; i++) {
        nombres[i] = nombres[i + 1];
        apellidos[i] = apellidos[i + 1];
        codigos[i] = codigos[i + 1];
    }
    cantidad--;
}

bool Creditos::agregarProductor(const char* nombres, const char* apellidos, const char* codigo) {
    if (!validarCodigoAfiliacion(codigo)) return false;

    // Verificar duplicados
    for (int i = 0; i < cantidad_productores; i++) {
        if (strcmp(codigos_productores[i], codigo) == 0) return false;
    }

    if (cantidad_productores >= capacidad_productores) {
        redimensionar(nombres_productores, apellidos_productores, codigos_productores,
                      capacidad_productores, 0);
    }

    copiarCadena(nombres_productores[cantidad_productores], nombres);
    copiarCadena(apellidos_productores[cantidad_productores], apellidos);
    copiarCadena(codigos_productores[cantidad_productores], codigo);
    cantidad_productores++;
    return true;
}

bool Creditos::agregarMusico(const char* nombres, const char* apellidos, const char* codigo) {
    if (!validarCodigoAfiliacion(codigo)) return false;

    for (int i = 0; i < cantidad_musicos; i++) {
        if (strcmp(codigos_musicos[i], codigo) == 0) return false;
    }

    if (cantidad_musicos >= capacidad_musicos) {
        redimensionar(nombres_musicos, apellidos_musicos, codigos_musicos,
                      capacidad_musicos, 1);
    }

    copiarCadena(nombres_musicos[cantidad_musicos], nombres);
    copiarCadena(apellidos_musicos[cantidad_musicos], apellidos);
    copiarCadena(codigos_musicos[cantidad_musicos], codigo);
    cantidad_musicos++;
    return true;
}

bool Creditos::agregarCompositor(const char* nombres, const char* apellidos, const char* codigo) {
    if (!validarCodigoAfiliacion(codigo)) return false;

    for (int i = 0; i < cantidad_compositores; i++) {
        if (strcmp(codigos_compositores[i], codigo) == 0) return false;
    }

    if (cantidad_compositores >= capacidad_compositores) {
        redimensionar(nombres_compositores, apellidos_compositores, codigos_compositores,
                      capacidad_compositores, 2);
    }

    copiarCadena(nombres_compositores[cantidad_compositores], nombres);
    copiarCadena(apellidos_compositores[cantidad_compositores], apellidos);
    copiarCadena(codigos_compositores[cantidad_compositores], codigo);
    cantidad_compositores++;
    return true;
}

bool Creditos::eliminarProductor(const char* codigo_afiliacion) {
    for (int i = 0; i < cantidad_productores; i++) {
        if (strcmp(codigos_productores[i], codigo_afiliacion) == 0) {
            eliminarElemento(nombres_productores, apellidos_productores, codigos_productores,
                             cantidad_productores, i);
            return true;
        }
    }
    return false;
}

bool Creditos::eliminarMusico(const char* codigo_afiliacion) {
    for (int i = 0; i < cantidad_musicos; i++) {
        if (strcmp(codigos_musicos[i], codigo_afiliacion) == 0) {
            eliminarElemento(nombres_musicos, apellidos_musicos, codigos_musicos,
                             cantidad_musicos, i);
            return true;
        }
    }
    return false;
}

bool Creditos::eliminarCompositor(const char* codigo_afiliacion) {
    for (int i = 0; i < cantidad_compositores; i++) {
        if (strcmp(codigos_compositores[i], codigo_afiliacion) == 0) {
            eliminarElemento(nombres_compositores, apellidos_compositores, codigos_compositores,
                             cantidad_compositores, i);
            return true;
        }
    }
    return false;
}

void Creditos::mostrarCreditos() const {
    std::cout << "\n=== CREDITOS DE LA CANCION ===\n";

    if (cantidad_productores > 0) {
        std::cout << "\nPRODUCTORES:\n";
        for (int i = 0; i < cantidad_productores; i++) {
            std::cout << "  - " << nombres_productores[i] << " " << apellidos_productores[i]
                      << " (Codigo: " << codigos_productores[i] << ")\n";
        }
    }

    if (cantidad_musicos > 0) {
        std::cout << "\nMUSICOS:\n";
        for (int i = 0; i < cantidad_musicos; i++) {
            std::cout << "  - " << nombres_musicos[i] << " " << apellidos_musicos[i]
                      << " (Codigo: " << codigos_musicos[i] << ")\n";
        }
    }

    if (cantidad_compositores > 0) {
        std::cout << "\nCOMPOSITORES:\n";
        for (int i = 0; i < cantidad_compositores; i++) {
            std::cout << "  - " << nombres_compositores[i] << " " << apellidos_compositores[i]
                      << " (Codigo: " << codigos_compositores[i] << ")\n";
        }
    }

    if (cantidad_productores == 0 && cantidad_musicos == 0 && cantidad_compositores == 0) {
        std::cout << "No hay creditos registrados.\n";
    }
}

bool Creditos::validarCodigoAfiliacion(const char* codigo) {
    if (codigo == nullptr || strlen(codigo) != 10) {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (!isalnum(codigo[i])) {
            return false;
        }
    }
    return true;
}
