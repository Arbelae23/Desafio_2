#include "creditos.h"
#include <iostream>
#include <cstring>
using namespace std;

Creditos::Creditos() {
    nProductores = nMusicos = nCompositores = 0;
}

bool Creditos::agregarProductor(const char* nombre, const char* apellido, const char* codigo) {
    if (nProductores >= MAX_CREDITOS) return false;
    strncpy(productores[nProductores].nombre, nombre, 49);
    productores[nProductores].nombre[49] = 0;
    strncpy(productores[nProductores].apellido, apellido, 49);
    productores[nProductores].apellido[49] = 0;
    strncpy(productores[nProductores].codigoSAC, codigo, 10);
    productores[nProductores].codigoSAC[10] = 0;
    nProductores++;
    return true;
}

bool Creditos::agregarMusico(const char* nombre, const char* apellido, const char* codigo) {
    if (nMusicos >= MAX_CREDITOS) return false;
    strncpy(musicos[nMusicos].nombre, nombre, 49);
    musicos[nMusicos].nombre[49] = 0;
    strncpy(musicos[nMusicos].apellido, apellido, 49);
    musicos[nMusicos].apellido[49] = 0;
    strncpy(musicos[nMusicos].codigoSAC, codigo, 10);
    musicos[nMusicos].codigoSAC[10] = 0;
    nMusicos++;
    return true;
}

bool Creditos::agregarCompositor(const char* nombre, const char* apellido, const char* codigo) {
    if (nCompositores >= MAX_CREDITOS) return false;
    strncpy(compositores[nCompositores].nombre, nombre, 49);
    compositores[nCompositores].nombre[49] = 0;
    strncpy(compositores[nCompositores].apellido, apellido, 49);
    compositores[nCompositores].apellido[49] = 0;
    strncpy(compositores[nCompositores].codigoSAC, codigo, 10);
    compositores[nCompositores].codigoSAC[10] = 0;
    nCompositores++;
    return true;
}

void Creditos::imprimir() const {
    cout << " Productores (" << nProductores << "):\n";
    for (int i = 0; i < nProductores; i++) {
        cout << "  - " << productores[i].nombre << " " << productores[i].apellido << " (" << productores[i].codigoSAC << ")\n";
    }
    cout << " Musicos (" << nMusicos << "):\n";
    for (int i = 0; i < nMusicos; i++) {
        cout << "  - " << musicos[i].nombre << " " << musicos[i].apellido << " (" << musicos[i].codigoSAC << ")\n";
    }
    cout << " Compositores (" << nCompositores << "):\n";
    for (int i = 0; i < nCompositores; i++) {
        cout << "  - " << compositores[i].nombre << " " << compositores[i].apellido << " (" << compositores[i].codigoSAC << ")\n";
    }
}

int Creditos::sizeBytes() const {
    return sizeof(Creditos);
}
