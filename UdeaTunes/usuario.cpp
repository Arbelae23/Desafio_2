#include "usuario.h"

Usuario::Usuario(string id, string nombre, string tipo)
    : idUsuario(id), nombre(nombre), tipoMembresia(tipo), miPlaylist(nullptr) {}

Usuario::~Usuario() { delete miPlaylist; }

void Usuario::crearPlaylist(string nombre) {
    delete miPlaylist;
    miPlaylist = new Playlist(nombre);
    cout << "Playlist '" << nombre << "' creada para " << this->nombre << endl;
}

void Usuario::reproducirPlaylist() {
    if (miPlaylist) miPlaylist->reproducirAleatorio();
    else cout << "No tienes playlist creada.\n";
}

void Usuario::mostrarPerfil() const {
    cout << "Usuario: " << nombre << " (" << tipoMembresia << ")\n";
}
