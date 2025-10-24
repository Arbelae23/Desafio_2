#include "usuario.h"
#include <cstring>
#include <iostream>
using namespace std;

Usuario::Usuario() {
    nombreUsuario[0] = 0;
    contrasena[0] = 0;
    tipo[0] = 0;
    nFavoritos = 0;
    for (int i = 0; i < MAX_FAVORITES; i++) favoritos[i] = 0;
}

void Usuario::setDatos(const char* user, const char* pass, const char* tipo_) {
    strncpy(nombreUsuario, user, 49); nombreUsuario[49] = 0;
    strncpy(contrasena, pass, 49); contrasena[49] = 0;
    strncpy(tipo, tipo_, 9); tipo[9] = 0;
}

const char* Usuario::getNombre() const { return nombreUsuario; }
const char* Usuario::getTipo() const { return tipo; }
bool Usuario::checkPassword(const char* pass) const { return strcmp(contrasena, pass) == 0; }

bool Usuario::agregarFavorito(long id) {
    if (nFavoritos >= MAX_FAVORITES) return false;
    if (existeFavorito(id)) return false;
    favoritos[nFavoritos++] = id;
    return true;
}

bool Usuario::eliminarFavorito(long id) {
    for (int i = 0; i < nFavoritos; i++) {
        if (favoritos[i] == id) {
            for (int j = i; j < nFavoritos - 1; j++)
                favoritos[j] = favoritos[j + 1];
            nFavoritos--;
            return true;
        }
    }
    return false;
}

bool Usuario::existeFavorito(long id) const {
    for (int i = 0; i < nFavoritos; i++)
        if (favoritos[i] == id) return true;
    return false;
}

void Usuario::imprimirFavoritos() const {
    cout << "Favoritos (" << nFavoritos << "):\n";
    for (int i = 0; i < nFavoritos; i++)
        cout << " - " << favoritos[i] << "\n";
}

int Usuario::getNumFavoritos() const { return nFavoritos; }

long Usuario::obtenerFavoritoPorIndice(int idx) const {
    if (idx < 0 || idx >= nFavoritos) return -1;
    return favoritos[idx];
}

int Usuario::adicionarFavoritosDesde(const Usuario& other) {
    int added = 0;
    for (int i = 0; i < other.nFavoritos; i++) {
        if (nFavoritos >= MAX_FAVORITES) break;
        long id = other.favoritos[i];
        if (!existeFavorito(id)) {
            favoritos[nFavoritos++] = id;
            added++;
        }
    }
    return added;
}

int Usuario::sizeBytes() const {
    return sizeof(Usuario);
}
