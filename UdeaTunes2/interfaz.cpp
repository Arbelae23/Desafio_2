#include "interfaz.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

using namespace std;

// Definición de constantes
typedef unsigned char byte;

Interfaz::Interfaz() {
    ultimaAdIndex = -1;
    contadorCancionesReproducidas = 0;
    mostrarSiguientePublicidad = false;
    inicializarHistorial();
}

Interfaz::~Interfaz() {}

// === Manejo de teclado (compatibilidad multiplataforma) ===
bool Interfaz::hayEntradaDisponible() {
#ifdef _WIN32
    return _kbhit() != 0;
#else
    // Implementación para otros sistemas
    return false;
#endif
}

char Interfaz::getCharSinBloqueo() {
#ifdef _WIN32
    return _getch();
#else
    // Implementación para otros sistemas
    return 0;
#endif
}

// === Funciones de publicidad ===
void Interfaz::mostrarPublicidad(const char* mensaje, char categoria) {
    cout << "\n=== PUBLICIDAD ===\n";
    cout << mensaje << "\n";
    cout << "Categoria: " << categoria << "\n";
    cout << "===================\n";
}

int Interfaz::seleccionarPublicidad(int nAds, int lastIndex) {
    if (nAds <= 0) return -1;

    int prioridades[] = {1, 2, 3}; // C=1, B=2, A=3
    int total = 0;
    for (int i = 0; i < nAds; i++)
        total += prioridades[i % 3];

    int r = rand() % total + 1;
    int acum = 0;
    for (int i = 0; i < nAds; i++) {
        acum += prioridades[i % 3];
        if (r <= acum) {
            if (i == lastIndex && nAds > 1)
                return (i + 1) % nAds;
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
    cout << "Ruta portada: " << portada << "\n";
    cout << "Titulo: " << titulo << "\n";
    cout << "Ruta audio: " << audio << "\n";
    cout << "Duracion: " << duracion << " segundos\n";
}

void Interfaz::mostrarTimer(int segundos) {
    cout << "\n=== TIMER ===\n";
    cout << "Tiempo transcurrido: " << segundos << " segundos\n";
    cout << "================\n";
}

void Interfaz::pausarSegundos(int s) {
#ifdef _WIN32
    Sleep(s * 1000);
#else
    // Implementación alternativa usando clock()
    clock_t end_time = clock() + (s * CLOCKS_PER_SEC);
    while (clock() < end_time) {}
#endif
}

void Interfaz::mostrarOpcionesReproduccion(bool esPremium) {
    cout << "\n=== CONTROLES DE REPRODUCCION ===\n";
    cout << "P - Reproducir/Pausar\n";
    if (esPremium) {
        cout << "A - Anterior\n";
        cout << "S - Siguiente\n";
    }
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

// === Reproducción estándar ===
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

    mostrarDatosReproduccion(mensajeAd, categoriaAd, cancion->getArtista(),
                            cancion->getAlbum(), cancion->getRutaPortada(),
                            cancion->getTitulo(), cancion->getRuta320(),
                            cancion->getDuracion());

    reproducirConContadorRegresivo(cancion, esPremium, iterCount, memUsed);
}

// === Reproducción con countdown mejorado ===
void Interfaz::mostrarContadorRegresivoCompleto(const char* mensajeAd, const char* categoriaAd,
                                               Cancion* cancion, int tiempoRestante, bool esPremium) {
    system("cls"); // limpiar pantalla en Windows

    if (mensajeAd && strlen(mensajeAd) > 0) {
        cout << "=== PUBLICIDAD ===\n";
        cout << mensajeAd << "\n";
        cout << "Categoria: " << categoriaAd << "\n";
        cout << "====================\n\n";
    }

    cout << "=== REPRODUCCION EN CURSO ===\n";
    cout << "Cantante: " << cancion->getArtista() << "\n";
    cout << "Album: " << cancion->getAlbum() << "\n";
    cout << "Portada: " << cancion->getRutaPortada() << "\n";
    cout << "Titulo: " << cancion->getTitulo() << "\n";
    cout << "Archivo: " << cancion->getRuta320() << "\n";

    int minDur = cancion->getDuracion() / 60;
    int segDur = cancion->getDuracion() % 60;
    cout << "Duracion: " << minDur << ":" << setw(2) << setfill('0') << segDur << "\n";

    int minRest = tiempoRestante / 60;
    int segRest = tiempoRestante % 60;
    cout << "Tiempo restante: " << minRest << ":" << setw(2) << setfill('0') << segRest << "\n";

    int progreso = ((cancion->getDuracion() - tiempoRestante) * 100) / cancion->getDuracion();
    cout << "Progreso: " << progreso << "%\n\n";

    cout << "=== CONTROLES ===\n";
    cout << "P - Reproducir/Pausar\n";
    if (esPremium) {
        cout << "A - Anterior\n";
        cout << "S - Siguiente\n";
    }
    cout << "=================\n";
}

int Interfaz::reproducirConContadorRegresivo(Cancion* c, bool esPremium, int &iter, int &mem) {
    if (!c) {
        cout << "\nNo hay cancion seleccionada.\n";
        return 0;
    }

    iter++;
    mem += sizeof(*c);

    bool pausado = false, salir = false;
    int tiempoRestante = 10;
    const char* mensajeAd = "";
    const char* categoriaAd = "";

    if (contadorCancionesReproducidas > 0 && contadorCancionesReproducidas % 2 == 0) {
        mensajeAd = "Descarga la nueva app de musica!";
        categoriaAd = "A";
        // mostrarPublicidad(mensajeAd, categoriaAd[0]);  // Se evita duplicar la publicidad
    }

    // Mostrar informacion inicial de la cancion
    cout << "\n=== INFORMACION DE LA CANCION ===\n";
    if (strlen(mensajeAd) > 0) {
        cout << "Mensaje publicitario: " << mensajeAd << "\n";
        cout << "Categoria del mensaje: " << categoriaAd << "\n";
    }
    cout << "Cantante: " << c->getArtista() << "\n";
    cout << "Album: " << c->getAlbum() << "\n";
    cout << "Ruta portada: " << c->getRutaPortada() << "\n";
    cout << "Titulo: " << c->getTitulo() << "\n";
    cout << "Ruta audio: " << c->getRuta320() << "\n";
    cout << "Duracion: " << c->getDuracion() << " segundos\n";
    cout << "===================================\n\n";
    // Mostrar controles de reproduccion
    mostrarOpcionesReproduccion(esPremium);



    while (tiempoRestante > 0 && !salir) {
        // Mostrar tiempo restante
        int minutos = tiempoRestante / 60;
        int segundos = tiempoRestante % 60;
        cout << "\rTiempo restante: " << minutos << ":" << setw(2) << setfill('0') << segundos;
        if (pausado) {
            cout << " [PAUSADO]";
        }
        cout << "   ";
        cout.flush();

        // Verificar si hay entrada del usuario
        if (hayEntradaDisponible()) {
            char tecla = getCharSinBloqueo();
            if (tecla == 'p' || tecla == 'P') {
                pausado = !pausado;
            } else if (esPremium && (tecla == 'a' || tecla == 'A')) {
                // Anterior - solo para Premium
                system("cls");
                return 1;
            } else if (esPremium && (tecla == 's' || tecla == 'S')) {
                // Siguiente - solo para Premium
                system("cls");
                return 2;
            }
        }

        // Disminuir el tiempo si no está pausado
        if (!pausado && !salir) {
            tiempoRestante--;
            pausarSegundos(1); // Esperar un segundo real
        } else {
            pausarSegundos(1); // Esperar un segundo para no consumir CPU
        }
    }

    if (!salir) {
        actualizarReproducciones(c);
        contadorCancionesReproducidas++;
        pausarSegundos(2);
        // Limpiar pantalla tras finalizar la cancion
        system("cls");
    }
    
    return 0; // Reproduccion normal completada
}

// === Reproducir lista ===
void Interfaz::reproducirLista(Cancion* lista[], int n, Usuario* u, bool esPremium, int &iterCount, int &memUsed) {
    if (n <= 0) {
        cout << "Lista vacia.\n";
        return;
    }

    int indiceActual = 0;
    
    while (indiceActual >= 0 && indiceActual < n) {
        Cancion* cancion = lista[indiceActual];

        // Guardar la canción actual en el historial
        avanzarEnHistorial(cancion);
        
        // Reproducir la canción con el sistema unificado y obtener el código de navegación
        int resultado = reproducirConContadorRegresivo(cancion, esPremium, iterCount, memUsed);
        
        if (resultado == 1 && esPremium) {
            // Anterior - solo para Premium
            indiceActual--;
            if (indiceActual < 0) {
                indiceActual = 0; // No ir más atrás del inicio
                cout << "\nYa estas en la primera cancion de la lista.\n";
                pausarSegundos(1);
            }
        } else if (resultado == 2 && esPremium) {
            // Siguiente - solo para Premium
            indiceActual++;
            if (indiceActual >= n) {
                cout << "\nYa estas en la ultima cancion de la lista.\n";
                pausarSegundos(1);
                break; // Salir del bucle
            }
        } else {
            // Reproducción normal completada, avanzar a la siguiente
            indiceActual++;
        }
    }
}

// === Reproducir aleatoria ===
void Interfaz::reproducirAleatoria(Cancion canciones[], int nCanciones, Usuario* u,
                                  bool esPremium, int &iterCount, int &memUsed) {
    if (nCanciones <= 0) {
        cout << "No hay canciones.\n";
        return;
    }

    // Reproducir TODAS las canciones en orden aleatorio (Fisher-Yates)
    int* indices = new int[nCanciones];
    for (int i = 0; i < nCanciones; i++) indices[i] = i;

    for (int i = nCanciones - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    for (int k = 0; k < nCanciones; k++) {
        Cancion* cancion = &canciones[indices[k]];

        const char* mensajeAd = "";
        const char* categoriaAd = "";
        if (contadorCancionesReproducidas > 0 && contadorCancionesReproducidas % 2 == 0) {
            mensajeAd = "Descarga la nueva app de musica!";
            categoriaAd = "A";
            // mostrarPublicidad(mensajeAd, categoriaAd[0]);  // Evitar duplicado; se muestra bajo 'Mensaje publicitario:'
        }

        reproducirCancion(cancion, esPremium, iterCount, memUsed);
        // contadorCancionesReproducidas++ se realiza dentro de reproducirConContadorRegresivo
    }

    delete[] indices;
}

// === Búsquedas ===
int Interfaz::buscarUsuarioPorNombre(Usuario usuarios[], int nUsuarios, const char* nombre) {
    for (int i = 0; i < nUsuarios; i++)
        if (strcmp(usuarios[i].getNombre(), nombre) == 0)
            return i;
    return -1;
}

Cancion* Interfaz::buscarCancionPorId(Cancion canciones[], int nCanciones, long id) {
    for (int i = 0; i < nCanciones; i++)
        if (canciones[i].getId() == id)
            return &canciones[i];
    return nullptr;
}

// === Seguimiento e historial ===
void Interfaz::inicializarHistorial() {
    for (int i = 0; i < MAX_HISTORIAL; i++) {
        historial[i] = nullptr;
    }
    inicioHistorial = 0;
    finHistorial = 0;
    tamanoHistorial = 0;
    posicionActualHistorial = -1;
}

void Interfaz::avanzarEnHistorial(Cancion* cancion) {
    if (!cancion) return;
    
    // Agregar la canción al final del historial
    historial[finHistorial] = cancion;
    finHistorial = (finHistorial + 1) % MAX_HISTORIAL;
    
    // Si el historial está lleno, avanzar el inicio
    if (tamanoHistorial == MAX_HISTORIAL) {
        inicioHistorial = (inicioHistorial + 1) % MAX_HISTORIAL;
    } else {
        tamanoHistorial++;
    }
    
    // Actualizar la posición actual al final del historial
    posicionActualHistorial = (finHistorial - 1 + MAX_HISTORIAL) % MAX_HISTORIAL;
}

bool Interfaz::puedeRetroceder() {
    return tamanoHistorial > 1 && posicionActualHistorial != inicioHistorial;
}

Cancion* Interfaz::obtenerCancionAnterior() {
    if (!puedeRetroceder()) return nullptr;
    
    // Retroceder la posición actual
    posicionActualHistorial = (posicionActualHistorial - 1 + MAX_HISTORIAL) % MAX_HISTORIAL;
    return historial[posicionActualHistorial];
}

Cancion* Interfaz::obtenerCancionSiguiente() {
    if (posicionActualHistorial == (finHistorial - 1 + MAX_HISTORIAL) % MAX_HISTORIAL) {
        return nullptr; // Ya estamos en la última canción
    }
    
    // Avanzar la posición actual
    posicionActualHistorial = (posicionActualHistorial + 1) % MAX_HISTORIAL;
    return historial[posicionActualHistorial];
}

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

// === Manejo de archivos ===
int Interfaz::cargarUsuariosDesdeArchivo(const char* ruta, Usuario usuarios[], int maxUsuarios) {
    FILE* archivo = fopen(ruta, "r");
    if (!archivo) {
        cout << "Error al abrir el archivo de usuarios: " << ruta << endl;
        return 0;
    }

    int count = 0;
    char linea[256];
    while (count < maxUsuarios && fgets(linea, sizeof(linea), archivo)) {
        // Saltar líneas vacías
        if (linea[0] == '\n' || linea[0] == '\r' || linea[0] == '\0') continue;

        // El archivo usa comas: nombre,contrasena,tipo
        char* nombre = strtok(linea, ",\r\n");
        char* contrasena = strtok(nullptr, ",\r\n");
        char* tipo = strtok(nullptr, ",\r\n");

        auto trim = [](char* s){
            if (!s) return s;
            while (*s == ' ' || *s == '\t') s++;
            char* end = s + strlen(s);
            while (end > s && (end[-1] == ' ' || end[-1] == '\t')) { end[-1] = '\0'; end--; }
            return s;
        };

        nombre = trim(nombre);
        contrasena = trim(contrasena);
        tipo = trim(tipo);

        if (nombre && contrasena && tipo && *nombre && *contrasena && *tipo) {
            usuarios[count].setDatos(nombre, contrasena, tipo);
            count++;
        }
    }

    fclose(archivo);
    cout << "Se cargaron " << count << " usuarios desde " << ruta << endl;
    return count;
}

int Interfaz::cargarCancionesDesdeArchivo(const char* ruta, Cancion canciones[], int maxCanciones) {
    FILE* archivo = fopen(ruta, "r");
    if (!archivo) {
        cout << "Error al abrir el archivo de canciones: " << ruta << endl;
        return 0;
    }

    int count = 0;
    char linea[512];

    auto trim = [](char* s){
        if (!s) return s;
        while (*s == ' ' || *s == '\t') s++;
        char* end = s + strlen(s);
        while (end > s && (end[-1] == ' ' || end[-1] == '\t' || end[-1] == '\r' || end[-1] == '\n')) { end[-1] = '\0'; end--; }
        return s;
    };

    while (count < maxCanciones && fgets(linea, sizeof(linea), archivo)) {
        if (linea[0] == '\n' || linea[0] == '\r' || linea[0] == '\0') continue;

        char* titulo = strtok(linea, ",\r\n");
        char* idStr = strtok(nullptr, ",\r\n");
        char* durStr = strtok(nullptr, ",\r\n");
        char* ruta320 = strtok(nullptr, ",\r\n");

        titulo = trim(titulo);
        idStr = trim(idStr);
        durStr = trim(durStr);
        ruta320 = trim(ruta320);

        if (titulo && idStr && durStr && ruta320 && *titulo && *idStr && *durStr && *ruta320) {
            long id = strtol(idStr, nullptr, 10);
            int duracion = atoi(durStr);
            canciones[count].setDatos(titulo, id, duracion, ruta320);
            count++;
        }
    }

    fclose(archivo);
    cout << "Se cargaron " << count << " canciones desde " << ruta << endl;
    return count;
}


