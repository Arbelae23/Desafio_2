#ifndef USUARIO_H
#define USUARIO_H

#include "config.h"

class Usuario {
private:
    char nombreUsuario[50];
    char contrasena[50];
    char tipo[10];
    long favoritos[MAX_FAVORITES];
    int nFavoritos;

public:
    Usuario();
    void setDatos(const char* user, const char* pass, const char* tipo_);
    
    // Getters
    const char* getNombre() const;
    const char* getTipo() const;
    bool checkPassword(const char* pass) const;
    int getNumFavoritos() const;
    long obtenerFavoritoPorIndice(int idx) const;
    
    // Métodos de favoritos
    bool agregarFavorito(long id);
    bool eliminarFavorito(long id);
    bool existeFavorito(long id) const;
    void imprimirFavoritos() const;
    int adicionarFavoritosDesde(const Usuario& other);
    
    // Utilidades
    int sizeBytes() const;
};

#endif // USUARIO_H