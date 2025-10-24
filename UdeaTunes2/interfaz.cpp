#include "interfaz.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>    // Para usleep() en sistemas Unix/Linux

using namespace std;

Interfaz::Interfaz() {
    ultimaAdIndex = -1;
}

Interfaz::~Interfaz() {
}

// === Manejo de teclado (compatibilidad multiplataforma) ===
bool Interfaz::hayEntradaDisponible() {
    // Implementación simple sin detección de entrada para mayor compatibilidad
    return false;
}

char Interfaz::getCharSinBloqueo() {
    // Implementación simple
    return 0;
}

// === Funciones de publicidad ===
void Interfaz::mostrarPublicidad(const char* mensaje, char categoria) {
    cout << "\nMensaje publicitario: " << mensaje << "\n";
    cout << "Categoria del mensaje: " << categoria << "\n";
    cout << "----------------------------------------\n";
}

int Interfaz::seleccionarPublicidad(int nAds, int lastIndex) {
    if (nAds <= 0) return -1;

    int prioridades[] = {1, 2, 3}; // C=1, B=2, A=3
    int total = 0;
    for (int i = 0; i < nAds; i++) {
        total += prioridades[i % 3];
    }

    int r = rand() % total + 1;
    int acum = 0;
    for (int i = 0; i < nAds; i++) {
        acum += prioridades[i % 3];
        if (r <= acum) {
            if (i == lastIndex && nAds > 1) {
                int next = (i + 1) % nAds;
                return next;
            }
            return i;
        }
    }
    return nAds - 1;
}

// === Mostrar datos de reproducción ===
void Interfaz::mostrarDatosReproduccion(const char* mensajeAd, const char* categoriaAd,
                                        const char* artista, const char* album,
                                        const char* portada, const char* titulo,
                                        const char* audio, int duracion) {
    cout << "\n=== DATOS DE REPRODUCCION ===\n";

    if (mensajeAd && strlen(mensajeAd) > 0)
        cout << "Mensaje publicitario: " << mensajeAd << "\n";

    if (categoriaAd && strlen(categoriaAd) > 0)
        cout << "Categoria del mensaje: " << categoriaAd << "\n";

    cout << "Cantante: " << artista << "\n";
    cout << "Album: " << album << "\n";
    cout << "Ruta a la portada del album: " << portada << "\n";
    cout << "Titulo: " << titulo << "\n";
    cout << "Ruta al audio: " << audio << "\n";
    cout << "Duracion: " << duracion << " segundos\n";

    cout << "\nOpciones de reproduccion:\n";
    cout << "1.- Reproducir\n2.- Detener\n";
}

void Interfaz::mostrarTimer(int segundos) {
    cout << "\n=== TIMER ===\n";
    cout << "Tiempo transcurrido: " << segundos << " segundos\n";
    cout << "================\n";
}

void Interfaz::pausarSegundos(int s) {
    usleep(s * 1000000); // usleep usa microsegundos
}

void Interfaz::mostrarOpcionesReproduccion(bool esPremium) {
    cout << "\n=== CONTROLES DE REPRODUCCION ===\n";
    if (esPremium)
        cout << "[P] Pausar/Reanudar   [N] Siguiente   [B] Anterior   [S] Salir\n";
    else
        cout << "[P] Pausar/Reanudar   [S] Salir\n";
    cout << "================================\n";
}

void Interfaz::actualizarReproducciones(Cancion* cancion) {
    if (cancion)
        cancion->incrementarReproducciones();
}

void Interfaz::medirRecursos(int iterCount, int memoria) {
    cout << "\n=== MEDICION DE RECURSOS ===\n";
    cout << "Iteraciones requeridas: " << iterCount << "\n";
    cout << "Memoria consumida: " << memoria << " bytes\n";
    cout << "============================\n";
}

// === Agregar canción ===
bool Interfaz::agregarCancionDinamica(Cancion canciones[], int &nCanciones,
                                      const char* titulo, long id, int duracion, const char* ruta) {
    if (nCanciones >= 1000) return false;

    Cancion nueva;
    nueva.setDatos(titulo, id, duracion, ruta);
    canciones[nCanciones++] = nueva;
    return true;
}

// === Reproducción ===
void Interfaz::reproducirCancion(Cancion* cancion, bool esPremium, int &iterCount, int &memUsed) {
    reproducirCancion(cancion, esPremium, iterCount, memUsed, "", "");
}

void Interfaz::reproducirCancion(Cancion* cancion, bool esPremium, int &iterCount, int &memUsed,
                                 const char* mensajeAd, const char* categoriaAd) {
    if (!cancion) {
        cout << "Cancion no valida.\n";
        return;
    }

    iterCount++;
    memUsed += sizeof(Cancion);

    char artista[] = "Artista Simulado";
    char album[] = "Album Ejemplo";
    char portada[300];
    snprintf(portada, sizeof(portada), "%s/image/portada_album.png", cancion->getRuta320());

    mostrarDatosReproduccion(mensajeAd, categoriaAd, artista, album, portada,
                             cancion->getNombre(), cancion->getRuta320(), cancion->getDuracion());
    mostrarTimer(0);
    mostrarOpcionesReproduccion(esPremium);

    bool pausa = false;
    bool salir = false;
    int t = 0;

    while (t < cancion->getDuracion() && !salir) {
        if (hayEntradaDisponible()) {
            char c = getCharSinBloqueo();
            if (c == 'p' || c == 'P') {
                pausa = !pausa;
                cout << (pausa ? "\n[Pausa]\n" : "\n[Reanudar]\n");
            } else if (c == 's' || c == 'S') {
                salir = true;
                cout << "\n[Saliendo de la cancion]\n";
            }
        }

        if (!pausa) {
            if (t % 10 == 0)
                mostrarTimer(t);
            t++;
        }

        pausarSegundos(1);
    }

    if (!salir) {
        actualizarReproducciones(cancion);
        cout << "\nCancion finalizada: " << cancion->getNombre() << "\n";
    }
}

// === Reproducir lista ===
void Interfaz::reproducirLista(Cancion* lista[], int n, Usuario* u, bool esPremium, int &iterCount, int &memUsed) {
    if (n <= 0) {
        cout << "Lista vacia.\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        reproducirCancion(lista[i], esPremium, iterCount, memUsed);

        if (!esPremium && i % 2 == 1)
            mostrarPublicidad("Compra ya el producto X!", 'C');
    }

    cout << "\nReproduccion finalizada.\n";
}

// === Reproducir aleatoria ===
void Interfaz::reproducirAleatoria(Cancion canciones[], int nCanciones, Usuario* u,
                                   bool esPremium, int &iterCount, int &memUsed) {
    if (nCanciones <= 0) {
        cout << "No hay canciones.\n";
        return;
    }

    int K = (nCanciones < 5 ? nCanciones : 5);
    Cancion* sesion[5];
    bool usado[1000] = {false};
    int elegidos = 0;

    srand((unsigned)time(nullptr));

    while (elegidos < K) {
        int r = rand() % nCanciones;
        if (!usado[r]) {
            usado[r] = true;
            sesion[elegidos++] = &canciones[r];
        }
    }
    
    reproducirLista(sesion, K, u, esPremium, iterCount, memUsed);
}

// === Cargar archivos ===
int Interfaz::cargarUsuariosDesdeArchivo(const char* archivo, Usuario usuarios[], int maxUsuarios) {
    // Por simplicidad, retornamos 0 ya que no tenemos archivos reales
    return 0;
}

int Interfaz::cargarCancionesDesdeArchivo(const char* archivo, Cancion canciones[], int maxCanciones) {
    // Por simplicidad, retornamos 0 ya que no tenemos archivos reales
    return 0;
}

// === Búsquedas ===
int Interfaz::buscarUsuarioPorNombre(Usuario usuarios[], int nUsuarios, const char* nombre) {
    for (int i = 0; i < nUsuarios; i++) {
        if (strcmp(usuarios[i].getNombre(), nombre) == 0) {
            return i;
        }
    }
    return -1;
}

Cancion* Interfaz::buscarCancionPorId(Cancion canciones[], int nCanciones, long id) {
    for (int i = 0; i < nCanciones; i++) {
        if (canciones[i].getId() == id) {
            return &canciones[i];
        }
    }
    return nullptr;
}

// === Gestión de usuarios ===
void Interfaz::seguirUsuario(Usuario* usuario, Usuario usuarios[], int nUsuarios, int& iteraciones) {
    iteraciones++;
    cout << "Funcionalidad de seguir usuario no implementada completamente.\n";
}

// === Cálculo de memoria ===
int Interfaz::calcularMemoriaUsadaEstimado(Usuario usuarios[], int nUsuarios, Cancion canciones[], int nCanciones) {
    int memoria = 0;
    memoria += nUsuarios * sizeof(Usuario);
    memoria += nCanciones * sizeof(Cancion);
    memoria += sizeof(Interfaz);
    return memoria;
}
