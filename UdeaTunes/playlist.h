#pragma once
#include <iostream>
#include <string>
using namespace std;

class Playlist {
private:
    string nombre;
    string* canciones;
    int numCanciones;
    int capacidad;
public:
    Playlist(string nombre="");
    ~Playlist();
    void agregarCancion(string id);
    void eliminarCancion(string id);
    void reproducir() const;
    void reproducirAleatorio() const;
};
