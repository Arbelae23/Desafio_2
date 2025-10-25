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
    bool repetirCancionActual;  // Estado para repetir canción (solo premium)

    // Historial de reproducción
    static const int MAX_HISTORIAL = 50;
    Cancion* historial[MAX_HISTORIAL];
    int inicioHistorial;
    int finHistorial;
    int tamanoHistorial;
    int posicionActualHistorial;

    // Estructura dinámica para seguir favoritos de otros usuarios
    struct UsuarioSeguido {
        char nombreUsuario[50];
        long* favoritosCache;  // Arreglo dinámico de favoritos
        int numFavoritos;
        int capacidadFavoritos;
        bool necesitaActualizacion;
    };
    
    UsuarioSeguido* usuariosSeguidos;  // Arreglo dinámico de usuarios seguidos
    int numUsuariosSeguidos;
    int capacidadUsuariosSeguidos;

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
    void seguirUsuario(Usuario* usuario, Usuario usuarios[], int nUsuarios, Cancion canciones[], int nCanciones, int& iteraciones);
    
    // Gestión de usuarios seguidos (arreglos dinámicos)
    bool agregarUsuarioSeguido(const char* nombreUsuario, Usuario usuarios[], int nUsuarios);
    void actualizarFavoritosUsuarioSeguido(const char* nombreUsuario, Usuario usuarios[], int nUsuarios);
    void reproducirFavoritosUsuarioSeguido(const char* nombreUsuario, Usuario usuarios[], int nUsuarios, 
                                          Cancion canciones[], int nCanciones, bool esPremium, int& iterCount, int& memUsed);
    void mostrarUsuariosSeguidos();
    void actualizarTodosLosUsuariosSeguidos(Usuario usuarios[], int nUsuarios);
    void liberarMemoriaUsuariosSeguidos();

    // Reproducción
    void reproducirCancion(Cancion* cancion, bool esPremium, int& iterCount, int& memUsed);
    void reproducirCancion(Cancion* cancion, bool esPremium, int& iterCount, int& memUsed,
                           const char* mensajeAd, const char* categoriaAd);
    void reproducirLista(Cancion* lista[], int n, Usuario* u, bool esPremium, int& iterCount, int& memUsed);
    void reproducirAleatoria(Cancion canciones[], int nCanciones, Usuario* u,
                             bool esPremium, int& iterCount, int& memUsed);

    // Reproducción mejorada (nuevo countdown)
    // Reproducción
    int reproducirConContadorRegresivo(Cancion* c, bool esPremium, int &iter, int &mem);
    int reproducirConContadorRegresivoAleatorio(Cancion* c, bool esPremium, int &iter, int &mem);
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
