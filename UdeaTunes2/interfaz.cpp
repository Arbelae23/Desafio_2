#include "interfaz.h"
#include "cancion.h"
#include "album.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

using namespace std;

// Variables globales para el temporizador
static atomic<int> tiempo_restante(0);
static atomic<bool> temporizador_activo(false);
static atomic<bool> saltar_cancion(false);
static mutex mtx_temporizador;


// CONSTRUCTOR Y DESTRUCTOR


Interfaz::Interfaz() {
    srand(time(0));

    inicializarPublicidad();
    inicializarHistorial();

    reproduciendo = false;
    repetir_cancion_actual = false;
    cancion_actual = nullptr;
    posicion_actual = -1;
}

Interfaz::~Interfaz() {
    liberarPublicidad();
    liberarHistorial();
}


// INICIALIZACION


void Interfaz::inicializarPublicidad() {
    capacidad_mensajes = 50;
    cantidad_mensajes = 0;
    ultimo_mensaje_mostrado = -1;
    mensajes_publicitarios = new MensajePublicitario*[capacidad_mensajes];

    for (int i = 0; i < capacidad_mensajes; i++) {
        mensajes_publicitarios[i] = nullptr;
    }
}

void Interfaz::liberarPublicidad() {
    for (int i = 0; i < cantidad_mensajes; i++) {
        if (mensajes_publicitarios[i]) {
            delete mensajes_publicitarios[i];
        }
    }
    delete[] mensajes_publicitarios;
}

void Interfaz::inicializarHistorial() {
    capacidad_historial = 10;  // Maximo 10 canciones en historial
    cantidad_historial = 0;
    historial_reproduccion = new Cancion*[capacidad_historial];
}

void Interfaz::liberarHistorial() {
    delete[] historial_reproduccion;
}


// METODOS AUXILIARES


void Interfaz::copiarCadena(char*& destino, const char* origen) {
    if (origen) {
        int longitud = strlen(origen);
        destino = new char[longitud + 1];
        strcpy(destino, origen);
    } else {
        destino = nullptr;
    }
}

void Interfaz::limpiarPantalla() const {
    // Limpiar pantalla (multiplataforma)
    cout << "\n\n\n";
}

void Interfaz::pausar() const {
    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void Interfaz::mostrarEncabezado(const char* titulo) const {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  " << titulo << "\n";
    cout << string(60, '=') << "\n";
}


// GESTION DE PUBLICIDAD

bool Interfaz::agregarMensajePublicitario(const char* mensaje, char categoria) {
    if (cantidad_mensajes >= capacidad_mensajes) return false;
    if (!mensaje || strlen(mensaje) == 0 || strlen(mensaje) > 500) return false;
    if (categoria != 'C' && categoria != 'B' && categoria != 'A') return false;

    MensajePublicitario* nuevo = new MensajePublicitario();
    copiarCadena(nuevo->mensaje, mensaje);
    nuevo->categoria = categoria;
    nuevo->id = cantidad_mensajes;

    mensajes_publicitarios[cantidad_mensajes] = nuevo;
    cantidad_mensajes++;
    return true;
}

int Interfaz::obtenerCantidadMensajes() const {
    return cantidad_mensajes;
}

int Interfaz::seleccionarMensajeAleatorio() {
    if (cantidad_mensajes == 0) return -1;

    // Crear arreglo ponderado por prioridad
    int total_prioridad = 0;
    for (int i = 0; i < cantidad_mensajes; i++) {
        total_prioridad += mensajes_publicitarios[i]->obtenerPrioridad();
    }

    // Seleccionar aleatorio segun prioridad
    int seleccion = rand() % total_prioridad;
    int acumulado = 0;

    for (int i = 0; i < cantidad_mensajes; i++) {
        acumulado += mensajes_publicitarios[i]->obtenerPrioridad();
        if (seleccion < acumulado) {
            // Evitar repetir el mismo mensaje
            if (i == ultimo_mensaje_mostrado && cantidad_mensajes > 1) {
                continue;
            }
            return i;
        }
    }

    return 0;
}

void Interfaz::mostrarPublicidad() {
    int indice = seleccionarMensajeAleatorio();
    if (indice < 0) return;

    MensajePublicitario* msg = mensajes_publicitarios[indice];

    cout << "\n" << string(60, '*') << "\n";
    cout << "  PUBLICIDAD";

    // Mostrar categoria
    if (msg->categoria == 'A') {
        cout << " - CATEGORIA AAA";
    } else {
        cout << " - CATEGORIA " << msg->categoria;
    }

    cout << "\n" << string(60, '*') << "\n";
    cout << msg->mensaje << "\n";
    cout << string(60, '*') << "\n";

    ultimo_mensaje_mostrado = indice;

    // Pausa de 2 segundos
    this_thread::sleep_for(chrono::seconds(2));
}


// GESTION DE HISTORIAL


void Interfaz::agregarAHistorial(Cancion* cancion) {
    if (!cancion) return;

    // Si el historial esta lleno, desplazar
    if (cantidad_historial >= capacidad_historial) {
        for (int i = 0; i < capacidad_historial - 1; i++) {
            historial_reproduccion[i] = historial_reproduccion[i + 1];
        }
        historial_reproduccion[capacidad_historial - 1] = cancion;
    } else {
        historial_reproduccion[cantidad_historial] = cancion;
        cantidad_historial++;
    }

    posicion_actual = cantidad_historial - 1;
}

void Interfaz::limpiarHistorial() {
    cantidad_historial = 0;
    posicion_actual = -1;
}


// REPRODUCCION DE CANCIONES


void Interfaz::mostrarInfoCancionReproduciendo(const Cancion* cancion, const Usuario& usuario) const {
    if (!cancion) return;

    cout << "\n" << string(60, '=') << "\n";
    cout << "  REPRODUCIENDO";
    if (repetir_cancion_actual) {
        cout << " (MODO REPETIR)";
    }
    cout << "\n" << string(60, '=') << "\n";

    cout << "Titulo: " << cancion->obtenerTitulo() << "\n";
    cout << "Artista: " << cancion->obtenerArtistaPrincipal() << "\n";

    if (cancion->obtenerAlbum() && strlen(cancion->obtenerAlbum()) > 0) {
        cout << "Album: " << cancion->obtenerAlbum() << "\n";
    }

    if (cancion->obtenerGenero() && strlen(cancion->obtenerGenero()) > 0) {
        cout << "Genero: " << cancion->obtenerGenero() << "\n";
    }

    // Mostrar rutas de archivos
    cout << "\nCalidad de audio: " << usuario.obtenerCalidadAudio() << " kbps\n";

    // Simular ruta del archivo de audio
    cout << "Archivo: /users/storage/audio/"
         << cancion->obtenerArtistaPrincipal() << "/"
         << cancion->obtenerTitulo() << "_"
         << usuario.obtenerCalidadAudio() << ".ogg\n";

    // Simular ruta de portada
    if (cancion->obtenerAlbum() && strlen(cancion->obtenerAlbum()) > 0) {
        cout << "Portada: /users/storage/images/"
             << cancion->obtenerArtistaPrincipal() << "/"
             << cancion->obtenerAlbum() << ".png\n";
    }

    int duracion = cancion->obtenerDuracion();
    int minutos = duracion / 60;
    int segundos = duracion % 60;
    cout << "Duracion: " << minutos << ":"
         << (segundos < 10 ? "0" : "") << segundos << "\n";

    cout << string(60, '=') << "\n";
}

void Interfaz::reproducirConTemporizador(Cancion* cancion, Usuario& usuario) {
    if (!cancion) return;

    int duracion = cancion->obtenerDuracion();
    tiempo_restante = duracion;
    temporizador_activo = true;
    saltar_cancion = false;

    // Mostrar info de la cancion
    mostrarInfoCancionReproduciendo(cancion, usuario);

    // Cuenta regresiva
    while (tiempo_restante > 0 && temporizador_activo && !saltar_cancion) {
        int mins = tiempo_restante / 60;
        int segs = tiempo_restante % 60;

        cout << "\rTiempo restante: " << mins << ":"
             << (segs < 10 ? "0" : "") << segs << "  " << flush;

        this_thread::sleep_for(chrono::seconds(1));
        tiempo_restante--;
    }

    if (tiempo_restante <= 0 && !saltar_cancion) {
        cout << "\r" << string(40, ' ') << "\r";
        cout << "[Cancion finalizada]\n";
    }

    temporizador_activo = false;
}

void Interfaz::reproducirCancion(Cancion* cancion, Usuario& usuario, bool es_aleatoria) {
    if (!cancion) return;

    cancion_actual = cancion;
    reproduciendo = true;

    // Incrementar contador de reproducciones del usuario
    usuario.incrementarContadorReproducciones();

    // Mostrar publicidad si corresponde
    if (usuario.debeVerPublicidad()) {
        mostrarPublicidad();
    }

    // Agregar al historial
    if (!repetir_cancion_actual) {
        agregarAHistorial(cancion);
    }

    // Reproducir con temporizador (3 segundos para testing)
    tiempo_restante = 3;  // Para pruebas, usar 3 segundos
    //tiempo_restante = cancion->obtenerDuracion();  // Para produccion

    temporizador_activo = true;
    saltar_cancion = false;

    mostrarInfoCancionReproduciendo(cancion, usuario);

    // Cuenta regresiva
    while (tiempo_restante > 0 && temporizador_activo && !saltar_cancion) {
        int mins = tiempo_restante / 60;
        int segs = tiempo_restante % 60;

        cout << "\rTiempo restante: " << mins << ":"
             << (segs < 10 ? "0" : "") << segs << "  " << flush;

        this_thread::sleep_for(chrono::seconds(1));
        tiempo_restante--;
    }

    cout << "\n";
    temporizador_activo = false;
}


// CONTROL DE REPRODUCCION


bool Interfaz::avanzarCancion() {
    saltar_cancion = true;
    temporizador_activo = false;
    return true;
}

bool Interfaz::retrocederCancion(int num_canciones) {
    if (num_canciones <= 0 || posicion_actual - num_canciones < 0) {
        return false;
    }

    posicion_actual -= num_canciones;
    cancion_actual = historial_reproduccion[posicion_actual];
    return true;
}

void Interfaz::detenerReproduccion() {
    reproduciendo = false;
    temporizador_activo = false;
    saltar_cancion = true;
}

void Interfaz::toggleRepetir() {
    repetir_cancion_actual = !repetir_cancion_actual;
}


// MENUS


void Interfaz::menuPrincipal(Usuario& usuario) {
    int opcion;

    do {
        mostrarEncabezado("UDEATUNES - MENU PRINCIPAL");
        cout << "Usuario: " << usuario.obtenerNickname()
             << " (" << usuario.obtenerNombreTipoMembresia() << ")\n";
        cout << "\n";
        cout << "1. Ver perfil\n";
        cout << "2. Reproduccion aleatoria\n";

        if (usuario.esPremium()) {
            cout << "3. Mi lista de favoritos\n";
        }

        cout << "0. Salir\n";
        cout << "\nOpcion: ";

        opcion = solicitarOpcion(0, usuario.esPremium() ? 3 : 2);

        switch (opcion) {
        case 1:
            usuario.mostrarInformacionCompleta();
            pausar();
            break;
        case 2:
            // menuReproduccionAleatoria se llamaria aqui
            // con el catalogo completo de canciones
            cout << "\n[Funcion no implementada en este demo]\n";
            pausar();
            break;
        case 3:
            if (usuario.esPremium()) {
                // menuListaFavoritos(usuario);
                cout << "\n[Funcion no implementada en este demo]\n";
                pausar();
            }
            break;
        }

    } while (opcion != 0);

    cout << "\nGracias por usar UdeATunes!\n";
}

void Interfaz::menuReproduccionAleatoria(Usuario& usuario, Cancion** todas_canciones, int total_canciones) {
    if (!todas_canciones || total_canciones == 0) {
        mostrarError("No hay canciones disponibles");
        return;
    }

    mostrarEncabezado("REPRODUCCION ALEATORIA");
    cout << "\nReproduciendo hasta 5 canciones aleatorias...\n";
    cout << "(Temporizador de 3 segundos por cancion)\n\n";

    limpiarHistorial();
    reproduciendo = true;

    for (int i = 0; i < 5 && reproduciendo; i++) {
        // Seleccionar cancion aleatoria
        int indice = rand() % total_canciones;
        Cancion* cancion = todas_canciones[indice];

        reproducirCancion(cancion, usuario, true);

        if (!saltar_cancion && reproduciendo) {
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }

    cout << "\nReproduccion aleatoria finalizada.\n";
    pausar();
}

void Interfaz::menuListaFavoritos(Usuario& usuario) {
    if (!usuario.esPremium()) {
        mostrarError("Solo usuarios Premium tienen acceso a esta funcion");
        return;
    }

    int opcion;

    do {
        mostrarEncabezado("MI LISTA DE FAVORITOS");
        cout << "1. Editar mi lista de favoritos\n";
        cout << "2. Seguir a otro usuario\n";
        cout << "3. Reproducir mi lista de favoritos\n";
        cout << "0. Volver\n";
        cout << "\nOpcion: ";

        opcion = solicitarOpcion(0, 3);

        switch (opcion) {
        case 1:
            cout << "\n[Funcion no implementada]\n";
            pausar();
            break;
        case 2:
            cout << "\n[Funcion no implementada]\n";
            pausar();
            break;
        case 3:
            cout << "\n[Funcion no implementada]\n";
            pausar();
            break;
        }

    } while (opcion != 0);
}


// UTILIDADES


void Interfaz::mostrarMensaje(const char* mensaje) const {
    cout << "\n" << mensaje << "\n";
}

void Interfaz::mostrarError(const char* error) const {
    cout << "\n[ERROR] " << error << "\n";
}

int Interfaz::solicitarOpcion(int min, int max) {
    int opcion;

    while (true) {
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida. Intente de nuevo: ";
            continue;
        }

        if (opcion >= min && opcion <= max) {
            cin.ignore(10000, '\n');
            return opcion;
        }

        cout << "Opcion fuera de rango. Intente de nuevo: ";
    }
}

bool Interfaz::confirmar(const char* pregunta) const {
    cout << pregunta << " (s/n): ";
    char respuesta;
    cin >> respuesta;
    cin.ignore(10000, '\n');
    return (respuesta == 's' || respuesta == 'S');
}
