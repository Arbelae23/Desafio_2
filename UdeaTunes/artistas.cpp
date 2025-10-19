#include "artistas.h"

Artista::Artista(string id, string nombre, int edad, string pais)
    : id(id), nombre(nombre), edad(edad), pais(pais), seguidores(0), posicionTendencia(0) {}

void Artista::mostrarInfo() const {
    cout << "Artista: " << nombre << " (" << pais << "), seguidores: " << seguidores << endl;
}

void Artista::actualizarSeguidores(int delta) {
    seguidores += delta;
    if (seguidores < 0) seguidores = 0;
}
