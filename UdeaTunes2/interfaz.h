#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "config.h"
#include "cancion.h"
#include "usuario.h"

class Interfaz {
private:
    int ultimaAdIndex;

public:
    Interfaz();
    ~Interfaz();
    
    // Manejo de archivos
    int cargarUsuariosDesdeArchivo(const char* archivo, Usuario usuarios[], int maxUsuarios);
    int cargarCancionesDesdeArchivo(const char* archivo, Cancion canciones[], int maxCanciones);
    
    // Búsquedas
    int buscarUsuarioPorNombre(Usuario usuarios[], int nUsuarios, const char* nombre);
    Cancion* buscarCancionPorId(Cancion canciones[], int nCanciones, long id);
    
    // Gestión de usuarios
    void seguirUsuario(Usuario* usuario, Usuario usuarios[], int nUsuarios, int& iteraciones);
    
    // Reproducción
    void reproducirCancion(Cancion* cancion, bool esPremium, int& iterCount, int& memUsed);
    void reproducirCancion(Cancion* cancion, bool esPremium, int& iterCount, int& memUsed,
                          const char* mensajeAd, const char* categoriaAd);
    void reproducirLista(Cancion* lista[], int n, Usuario* u, bool esPremium, int& iterCount, int& memUsed);
    void reproducirAleatoria(Cancion canciones[], int nCanciones, Usuario* u,
                           bool esPremium, int& iterCount, int& memUsed);
    
    // Gestión de canciones
    bool agregarCancionDinamica(Cancion canciones[], int& nCanciones,
                              const char* titulo, long id, int duracion, const char* ruta);
    
    // Utilidades
    int calcularMemoriaUsadaEstimado(Usuario usuarios[], int nUsuarios, Cancion canciones[], int nCanciones);
    void medirRecursos(int iterCount, int memoria);
    void actualizarReproducciones(Cancion* cancion);
    
    // Interfaz de usuario
    void mostrarDatosReproduccion(const char* mensajeAd, const char* categoriaAd,
                                const char* artista, const char* album,
                                const char* portada, const char* titulo,
                                const char* audio, int duracion);
    void mostrarTimer(int segundos);
    void mostrarOpcionesReproduccion(bool esPremium);
    void mostrarPublicidad(const char* mensaje, char categoria);
    
    // Control de tiempo
    void pausarSegundos(int s);
    bool hayEntradaDisponible();
    char getCharSinBloqueo();
    int seleccionarPublicidad(int nAds, int lastIndex);
};

#endif // INTERFAZ_H