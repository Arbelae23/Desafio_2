#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "config.h"
#include "cancion.h"
#include "usuario.h"
#include <iostream>
#include <iomanip> // para setw y setfill

class Interfaz {
private:
    int ultimaAdIndex;
    int contadorCancionesReproducidas;
    bool mostrarSiguientePublicidad;

    // Historial de reproducción
    static const int MAX_HISTORIAL = 50;
    Cancion* historial[MAX_HISTORIAL];
    int inicioHistorial;
    int finHistorial;
    int tamanoHistorial;
    int posicionActualHistorial;

public:
    Interfaz();
    ~Interfaz();

    // Manejo de archivos
    int cargarUsuariosDesdeArchivo(const char* ruta, Usuario usuarios[], int maxUsuarios);
    int cargarCancionesDesdeArchivo(const char* ruta, Cancion canciones[], int maxCanciones);

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

    // Reproducción mejorada (nuevo countdown)
    // Retorna: 0=normal, 1=anterior, 2=siguiente
    int reproducirConContadorRegresivo(Cancion* c, bool esPremium, int &iter, int &mem);
    void mostrarContadorRegresivoCompleto(const char* mensajeAd, const char* categoriaAd,
                                          Cancion* cancion, int tiempoRestante, bool esPremium);

    // Gestión de historial
    void inicializarHistorial();
    void avanzarEnHistorial(Cancion* cancion);
    Cancion* obtenerCancionAnterior();
    Cancion* obtenerCancionSiguiente();
    bool puedeRetroceder();

    // Control de publicidad
    bool debeMostrarPublicidad();
    void incrementarContadorCanciones();
    void resetContadorCanciones();

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
    void mostrarEstadoPausado(Cancion* cancion, int tiempoRestante, bool esPremium);

    // Control de tiempo
    void pausarSegundos(int s);
    bool hayEntradaDisponible();
    char getCharSinBloqueo();
    int seleccionarPublicidad(int nAds, int lastIndex);
};

#endif // INTERFAZ_H
