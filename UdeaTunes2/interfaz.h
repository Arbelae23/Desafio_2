#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "config.h"
#include "cancion.h"
#include "usuario.h"
#include "artistas.h"
#include "album.h"
#include "playlist.h"
#include <iostream>
#include <iomanip> // para setw y setfill

class Interfaz {
private:
    int ultimaAdIndex;
    int contadorCancionesReproducidas;
    bool mostrarSiguientePublicidad;
    bool repetirCancionActual;  // Estado para repetir cancion (solo premium)

    // Historial de reproduccion
    static const int MAX_HISTORIAL = 50;
    static const int MAX_RETROCESOS = 6;  // Límite de retrocesos permitidos
    Cancion* historial[MAX_HISTORIAL];
    int inicioHistorial;
    int finHistorial;
    int tamanoHistorial;
    int posicionActualHistorial;
    int contadorRetroceso;  // Contador de retrocesos en la sesion actual

    // Estructura dinamica para seguir favoritos de otros usuarios
    struct UsuarioSeguido {
        char nombreUsuario[50];
        long* favoritosCache;  // Arreglo dinamico de favoritos
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
    int cargarAlbunesDesdeArchivo(const char* ruta, Album albunes[], int maxAlbunes);
    int cargarArtistasDesdeArchivo(const char* ruta, Artista artistas[], int maxArtistas);
    int cargarPlaylistsDesdeArchivo(const char* ruta, Playlist playlists[], int maxPlaylists, Cancion canciones[], int nCanciones);

    // Busquedas
    int buscarUsuarioPorNombre(Usuario usuarios[], int nUsuarios, const char* nombre);
    Cancion* buscarCancionPorId(Cancion canciones[], int nCanciones, long id);
    
    // Vinculación de datos
    void vincularCancionesConArtistas(Cancion canciones[], int nCanciones, Artista artistas[], int nArtistas);
    void vincularCancionesConAlbumes(Cancion canciones[], int nCanciones, Album albumes[], int nAlbumes);
    void establecerCancionesSingle(Cancion canciones[], int nCanciones);

    // Gestion de usuarios
    void seguirUsuario(Usuario* usuario, Usuario usuarios[], int nUsuarios, Cancion canciones[], int nCanciones, int& iteraciones);
    
    // Gestión de usuarios seguidos (arreglos dinámicos)
    bool agregarUsuarioSeguido(const char* nombreUsuario, Usuario usuarios[], int nUsuarios);
    void actualizarFavoritosUsuarioSeguido(const char* nombreUsuario, Usuario usuarios[], int nUsuarios);
    void reproducirFavoritosUsuarioSeguido(const char* nombreUsuario, Usuario usuarios[], int nUsuarios, 
                                          Cancion canciones[], int nCanciones, bool esPremium, int& iterCount, int& memUsed);
    void mostrarUsuariosSeguidos(Usuario usuarios[], int nUsuarios);
    void actualizarTodosLosUsuariosSeguidos(Usuario usuarios[], int nUsuarios);
    void marcarUsuarioSeguidoParaActualizacion(const char* nombreUsuario);
    void notificarCambioFavoritos(const char* nombreUsuario);
    void liberarMemoriaUsuariosSeguidos();

    // Reproduccion
    void reproducirCancion(Cancion* cancion, bool esPremium, int& iterCount, int& memUsed);
    void reproducirCancion(Cancion* cancion, bool esPremium, int& iterCount, int& memUsed,
                           const char* mensajeAd, const char* categoriaAd);
    void reproducirLista(Cancion* lista[], int n, Usuario* u, bool esPremium, int& iterCount, int& memUsed);
    void reproducirAleatoria(Cancion canciones[], int nCanciones, Usuario* u,
                             bool esPremium, int& iterCount, int& memUsed);

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
    
    // Gestión de contador de retroceso
    void resetearContadorRetroceso();
    void incrementarContadorRetroceso();
    bool puedeRetrocederConLimite();

    // Control de publicidad
    bool debeMostrarPublicidad();
    void incrementarContadorCanciones();
    void resetContadorCanciones();

    // Gestion de canciones
    bool agregarCancionDinamica(Cancion canciones[], int& nCanciones,
                                const char* titulo, long id, int duracion, const char* ruta);

    // Utilidades
    int calcularMemoriaUsadaEstimado(Usuario usuarios[], int nUsuarios, Cancion canciones[], int nCanciones);
    void medirRecursos(int iterCount, int memoria);
    void actualizarReproducciones(Cancion* cancion);
    
    // Sistema mejorado de medición de recursos
    struct MetricasRecursos {
        int iteracionesDirectas;
        int iteracionesIndirectas;
        int memoriaEstructuras;
        int memoriaVariablesLocales;
        int memoriaParametros;
        int memoriaTotal;
        
        MetricasRecursos() : iteracionesDirectas(0), iteracionesIndirectas(0), 
                           memoriaEstructuras(0), memoriaVariablesLocales(0), 
                           memoriaParametros(0), memoriaTotal(0) {}
    };
    
    void iniciarMedicionRecursos(MetricasRecursos& metricas);
    void finalizarMedicionRecursos(const MetricasRecursos& metricas, const char* nombreFuncionalidad);
    void contarIteracionDirecta(MetricasRecursos& metricas);
    void contarIteracionIndirecta(MetricasRecursos& metricas);
    void agregarMemoriaEstructura(MetricasRecursos& metricas, int bytes);
    void agregarMemoriaVariable(MetricasRecursos& metricas, int bytes);
    void agregarMemoriaParametro(MetricasRecursos& metricas, int bytes);
    
    // Funciones con medición integrada
    void editarFavoritosConMedicion(Usuario* usuario, Cancion canciones[], int nCanciones);
    void mostrarCancionesConMedicion(Cancion canciones[], int nCanciones);
    void seguirUsuarioConMedicion(Usuario* usuario, Usuario usuarios[], int nUsuarios, Cancion canciones[], int nCanciones);
    void reproducirAleatoriaConMedicion(Cancion canciones[], int nCanciones, Usuario* u, bool esPremium);
    void ejecutarListaFavoritosConMedicion(Usuario* usuario, Cancion canciones[], int nCanciones, bool esPremium);
    void reproducirFavoritosUsuarioSeguidoConMedicion(const char* nombreUsuario, Usuario usuarios[], int nUsuarios, 
                                                     Cancion canciones[], int nCanciones, bool esPremium);

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
