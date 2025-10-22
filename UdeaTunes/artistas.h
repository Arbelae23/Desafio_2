#pragma once
#include <iostream>
#include <string>
using namespace std;

class Artista {
private:
    string id, nombre, pais;
    int edad, seguidores, posicionTendencia;
public:
    Artista(string id="", string nombre="", int edad=0, string pais="");
    void mostrarInfo() const;
    void actualizarSeguidores(int delta);
};
