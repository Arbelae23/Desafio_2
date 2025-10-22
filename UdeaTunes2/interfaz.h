#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "usuario.h"
#include "cancion.h"

class Interfaz {
private:
    // Estructura para mensajes publicitarios (sin crear clase nueva)
    struct MensajePublicitario {
        char* mensaje;  // Hasta 500 caracteres
        char categoria;  // 'C', 'B', o 'A' (AAA)
        int id;

        MensajePublicitario() : mensaje(nullptr), categoria('C'), id(0) {}

        ~MensajePublicitario() {
            if (mensaje) {
                delete[] mensaje;
                mensaje = nullptr;
            }
        }

        int obtenerPrioridad() const {
            // C = 1, B = 2, AAA = 3
            if (categoria == 'A') return 3;
            if (categoria == 'B') return 2;
            return 1;
        }
    };

    // Base de datos de publicidad (hasta 50 mensajes)
    MensajePublicitario** mensajes_publicitarios;
    int cantidad_mensajes;
    int capacidad_mensajes;
    int ultimo_mensaje_mostrado;  // Para evitar repeticion

    // Historial de reproduccion (para controlar retroceso)
    Cancion** historial_reproduccion;
    int cantidad_historial;
    int capacidad_historial;
    int posicion_actual;

    // Estado de reproduccion
    bool reproduciendo;
    bool repetir_cancion_actual;
    Cancion* cancion_actual;

    // Metodos auxiliares para publicidad
    void inicializarPublicidad();
    void liberarPublicidad();
    void copiarCadena(char*& destino, const char* origen);
    int seleccionarMensajeAleatorio();
    void mostrarPublicidad();

    // Metodos auxiliares para historial
    void inicializarHistorial();
    void liberarHistorial();
    void agregarAHistorial(Cancion* cancion);
    void limpiarHistorial();

    // Metodos auxiliares de interfaz
    void limpiarPantalla() const;
    void pausar() const;
    void mostrarEncabezado(const char* titulo) const;

public:
    // Constructor y destructor
    Interfaz();
    ~Interfaz();

    // Gestion de mensajes publicitarios
    bool agregarMensajePublicitario(const char* mensaje, char categoria);
    int obtenerCantidadMensajes() const;

    // Menu principal
    void menuPrincipal(Usuario& usuario);

    // Menus secundarios
    void menuReproduccionAleatoria(Usuario& usuario, Cancion** todas_canciones, int total_canciones);
    void menuListaFavoritos(Usuario& usuario);
    void menuEditarFavoritos(Usuario& usuario, Cancion** todas_canciones, int total_canciones);
    void menuSeguirUsuario(Usuario& usuario, Usuario** todos_usuarios, int total_usuarios);

    // Reproduccion de canciones
    void reproducirCancion(Cancion* cancion, Usuario& usuario, bool es_aleatoria = true);
    void reproducirConTemporizador(Cancion* cancion, Usuario& usuario);
    void mostrarInfoCancionReproduciendo(const Cancion* cancion, const Usuario& usuario) const;

    // Control de reproduccion
    bool avanzarCancion();
    bool retrocederCancion(int num_canciones = 1);
    void detenerReproduccion();
    void toggleRepetir();

    // Utilidades
    void mostrarMensaje(const char* mensaje) const;
    void mostrarError(const char* error) const;
    int solicitarOpcion(int min, int max);
    bool confirmar(const char* pregunta) const;
};

#endif
