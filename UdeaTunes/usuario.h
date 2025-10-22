#pragma once
#include <iostream>
#include <string>
#include "Playlist.h"
using namespace std;

class Usuario {
private:
    string idUsuario, nombre, ciudad, pais, tipoMembresia;
    Playlist* miPlaylist;
public:
    Usuario(string id="", string nombre="", string tipo="Estandar");
    ~Usuario();
    void crearPlaylist(string nombre);
    void reproducirPlaylist();
    void mostrarPerfil() const;
};
