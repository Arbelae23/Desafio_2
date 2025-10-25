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
    ultimaAdIndex = 0;
    contadorCancionesReproducidas = 0;
    mostrarSiguientePublicidad = false;
    repetirCancionActual = false;  // Inicializar repetición desactivada
    inicializarHistorial();
    
    // Inicializar estructura de usuarios seguidos
    usuariosSeguidos = nullptr;
    numUsuariosSeguidos = 0;
    capacidadUsuariosSeguidos = 0;
}

Interfaz::~Interfaz() {
    liberarMemoriaUsuariosSeguidos();
}

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
        cout << "R - Repetir cancion " << (repetirCancionActual ? "(ACTIVADO)" : "(DESACTIVADO)") << "\n";
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

    // La información se mostrará en reproducirConContadorRegresivo para evitar duplicación
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
    int tiempoRestante = 3;
    const char* mensajeAd = "";
    const char* categoriaAd = "";

    // Solo mostrar anuncios para usuarios Free (no Premium)
    if (!esPremium && contadorCancionesReproducidas > 0 && contadorCancionesReproducidas % 2 == 0) {
        mensajeAd = "Descarga la nueva app de musica!";
        categoriaAd = "A";
    }

    // Generar datos dinámicos para cantante y álbum
    char cantante[100], album[100], rutaPortada[300], rutaAudio[300];
    
    // Extraer nombre del artista de la ruta original
    const char* rutaOriginal = c->getRuta320();
    if (strstr(rutaOriginal, "claudia_lorelle")) {
        strcpy(cantante, "Claudia Lorelle");
        strcpy(album, "Melodias del Corazon");
    } else if (strstr(rutaOriginal, "artist2")) {
        strcpy(cantante, "Marina Azul");
        strcpy(album, "Ondas Sonoras");
    } else if (strstr(rutaOriginal, "artist3")) {
        strcpy(cantante, "Armonia Nocturna");
        strcpy(album, "Serenatas de Invierno");
    } else if (strstr(rutaOriginal, "artist4")) {
        strcpy(cantante, "Vuelo Libre");
        strcpy(album, "Alturas Musicales");
    } else {
        strcpy(cantante, "Artista Desconocido");
        strcpy(album, "Album Desconocido");
    }

    // Generar rutas dinámicas
    char tituloLimpio[100];
    strcpy(tituloLimpio, c->getTitulo());
    // Reemplazar espacios con guiones bajos para las rutas
    for (int i = 0; tituloLimpio[i]; i++) {
        if (tituloLimpio[i] == ' ') tituloLimpio[i] = '_';
    }
    
    // Convertir a minúsculas
    for (int i = 0; tituloLimpio[i]; i++) {
        if (tituloLimpio[i] >= 'A' && tituloLimpio[i] <= 'Z') {
            tituloLimpio[i] = tituloLimpio[i] + 32;
        }
    }

    // Ruta de audio según tipo de usuario
    if (esPremium) {
        sprintf(rutaAudio, "/users/storage/premium_vault/%s/audio/%s_320.ogg", cantante, tituloLimpio);
    } else {
        sprintf(rutaAudio, "/users/storage/free_tier/%s/audio/%s_128.ogg", cantante, tituloLimpio);
    }
    
    // Ruta de portada
    sprintf(rutaPortada, "/users/storage/covers/%s/image/%s.png", cantante, tituloLimpio);

    // Mostrar informacion inicial de la cancion
    cout << "\n=== INFORMACION DE LA CANCION ===\n";
    if (!esPremium && strlen(mensajeAd) > 0) {
        cout << "Mensaje publicitario: " << mensajeAd << "\n";
        cout << "Categoria del mensaje: " << categoriaAd << "\n";
    }
    cout << "Cantante: " << cantante << "\n";
    cout << "Album: " << album << "\n";
    cout << "Ruta portada: " << rutaPortada << "\n";
    cout << "Titulo: " << c->getTitulo() << "\n";
    cout << "Ruta audio: " << rutaAudio << "\n";
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
            } else if (esPremium && (tecla == 'r' || tecla == 'R')) {
                // Repetir canción - solo para Premium
                repetirCancionActual = !repetirCancionActual;
                system("cls");
                // Mostrar información actualizada con el nuevo estado de repetición
                cout << "\n=== INFORMACION DE LA CANCION ===\n";
                if (!esPremium && strlen(mensajeAd) > 0) {
                    cout << "Mensaje publicitario: " << mensajeAd << "\n";
                    cout << "Categoria del mensaje: " << categoriaAd << "\n";
                }
                cout << "Cantante: " << cantante << "\n";
                cout << "Album: " << album << "\n";
                cout << "Ruta portada: " << rutaPortada << "\n";
                cout << "Titulo: " << c->getTitulo() << "\n";
                cout << "Ruta audio: " << rutaAudio << "\n";
                cout << "Duracion: " << c->getDuracion() << " segundos\n";
                cout << "===================================\n\n";
                mostrarOpcionesReproduccion(esPremium);
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
        
        // Si está activada la repetición para usuarios premium, reiniciar la canción
        if (esPremium && repetirCancionActual) {
            cout << "\n[REPETICION ACTIVADA] Reiniciando cancion...\n";
            pausarSegundos(1);
            system("cls");
            // Llamada recursiva para repetir la canción
            return reproducirConContadorRegresivo(c, esPremium, iter, mem);
        }
        
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

    // Crear lista aleatoria usando Fisher-Yates
    int* indices = new int[nCanciones];
    for (int i = 0; i < nCanciones; i++) indices[i] = i;

    for (int i = nCanciones - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    // Reproducir con navegación como en reproducirLista, pero limitado a 5 canciones
    int indiceActual = 0;
    int cancionesReproducidas = 0;
    const int MAX_CANCIONES_ALEATORIO = 5;
    
    while (indiceActual >= 0 && indiceActual < nCanciones && cancionesReproducidas < MAX_CANCIONES_ALEATORIO) {
        Cancion* cancion = &canciones[indices[indiceActual]];

        // Guardar la canción actual en el historial
        avanzarEnHistorial(cancion);
        
        // Reproducir la canción y obtener el código de navegación
        int resultado = reproducirConContadorRegresivo(cancion, esPremium, iterCount, memUsed);
        
        if (resultado == 1 && esPremium) {
            // Anterior - solo para Premium
            indiceActual--;
            if (indiceActual < 0) {
                indiceActual = 0; // No ir más atrás del inicio
                cout << "\nYa estas en la primera cancion de la lista aleatoria.\n";
                pausarSegundos(1);
            }
            // No incrementar contador si va hacia atrás
        } else if (resultado == 2 && esPremium) {
            // Siguiente - solo para Premium
            indiceActual++;
            cancionesReproducidas++; // Contar como reproducida
            if (indiceActual >= nCanciones) {
                cout << "\nYa estas en la ultima cancion de la lista aleatoria.\n";
                pausarSegundos(1);
                break; // Salir del bucle
            }
        } else {
            // Reproducción normal completada, avanzar a la siguiente
            indiceActual++;
            cancionesReproducidas++; // Contar como reproducida
        }
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

void Interfaz::seguirUsuario(Usuario* usuario, Usuario usuarios[], int nUsuarios, Cancion canciones[], int nCanciones, int& iteraciones) {
    int opcion;
    do {
        cout << "\n=== SEGUIR USUARIOS ===\n";
        cout << "1. Seguir nuevo usuario\n";
        cout << "2. Ver usuarios seguidos\n";
        cout << "3. Reproducir favoritos de usuario seguido\n";
        cout << "4. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                cout << "\n=== USUARIOS DISPONIBLES ===\n";
                for (int i = 0; i < nUsuarios; i++) {
                    if (strcmp(usuarios[i].getNombre(), usuario->getNombre()) != 0) {
                        cout << (i + 1) << ". " << usuarios[i].getNombre() 
                             << " (" << usuarios[i].getTipo() << ") - " 
                             << usuarios[i].getNumFavoritos() << " favoritos\n";
                    }
                }
                
                cout << "\nIngrese el nombre del usuario a seguir: ";
                char nombreSeguir[50];
                cin.ignore();
                cin.getline(nombreSeguir, 50);
                
                if (strcmp(nombreSeguir, usuario->getNombre()) == 0) {
                    cout << "No puedes seguirte a ti mismo.\n";
                } else {
                    agregarUsuarioSeguido(nombreSeguir, usuarios, nUsuarios);
                }
                break;
            }
            
            case 2: {
                 // Actualizar automáticamente antes de mostrar
                 actualizarTodosLosUsuariosSeguidos(usuarios, nUsuarios);
                 mostrarUsuariosSeguidos();
                 if (numUsuariosSeguidos > 0) {
                     cout << "\nPresiona Enter para continuar...";
                     cin.ignore();
                     cin.get();
                 }
                 break;
             }
            
            case 3: {
                 if (numUsuariosSeguidos == 0) {
                     cout << "No sigues a ningún usuario.\n";
                     break;
                 }
                 
                 // Actualizar automáticamente antes de mostrar
                 actualizarTodosLosUsuariosSeguidos(usuarios, nUsuarios);
                 mostrarUsuariosSeguidos();
                 cout << "\nIngresa el nombre del usuario: ";
                 char nombreUsuario[50];
                 cin.ignore();
                 cin.getline(nombreUsuario, 50);
                 
                 // Usar la función ya implementada
                 int memUsed = 0;
                 bool esPremium = (strcmp(usuario->getTipo(), "Premium") == 0);
                 reproducirFavoritosUsuarioSeguido(nombreUsuario, usuarios, nUsuarios, 
                                                 canciones, nCanciones, 
                                                 esPremium, iteraciones, memUsed);
                 
                 cout << "\nPresiona Enter para continuar...";
                 cin.get();
                 break;
             }
             
             case 4:
                 cout << "Volviendo al menú anterior...\n";
                 break;
                
            default:
                cout << "Opción inválida.\n";
                break;
        }
        
        if (opcion != 4) {
             pausarSegundos(2);
         }
         
     } while (opcion != 4);
}

// === Cálculo de memoria ===
int Interfaz::calcularMemoriaUsadaEstimado(Usuario usuarios[], int nUsuarios, Cancion canciones[], int nCanciones) {
    int memoria = 0;
    
    // Memoria base de la interfaz
    memoria += sizeof(Interfaz);
    
    // Memoria de usuarios
    memoria += nUsuarios * sizeof(Usuario);
    
    // Memoria de canciones
    memoria += nCanciones * sizeof(Cancion);
    
    // Memoria adicional de usuarios seguidos (arreglos dinámicos)
    memoria += numUsuariosSeguidos * sizeof(UsuarioSeguido);
    for (int i = 0; i < numUsuariosSeguidos; i++) {
        memoria += usuariosSeguidos[i].capacidadFavoritos * sizeof(long);
    }
    
    // Suprimir warnings de parámetros no utilizados directamente
    (void)usuarios;
    (void)canciones;
    
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

// === Gestión de usuarios seguidos (arreglos dinámicos) ===
void Interfaz::liberarMemoriaUsuariosSeguidos() {
    if (usuariosSeguidos) {
        for (int i = 0; i < numUsuariosSeguidos; i++) {
            if (usuariosSeguidos[i].favoritosCache) {
                delete[] usuariosSeguidos[i].favoritosCache;
            }
        }
        delete[] usuariosSeguidos;
        usuariosSeguidos = nullptr;
    }
    numUsuariosSeguidos = 0;
    capacidadUsuariosSeguidos = 0;
}

bool Interfaz::agregarUsuarioSeguido(const char* nombreUsuario, Usuario usuarios[], int nUsuarios) {
    // Verificar que el usuario existe
    int indiceUsuario = buscarUsuarioPorNombre(usuarios, nUsuarios, nombreUsuario);
    if (indiceUsuario == -1) {
        cout << "Usuario '" << nombreUsuario << "' no encontrado.\n";
        return false;
    }
    
    // Verificar si ya está siendo seguido
    for (int i = 0; i < numUsuariosSeguidos; i++) {
        if (strcmp(usuariosSeguidos[i].nombreUsuario, nombreUsuario) == 0) {
            cout << "Ya estás siguiendo a '" << nombreUsuario << "'.\n";
            return false;
        }
    }
    
    // Expandir arreglo si es necesario
    if (numUsuariosSeguidos >= capacidadUsuariosSeguidos) {
        int nuevaCapacidad = (capacidadUsuariosSeguidos == 0) ? 2 : capacidadUsuariosSeguidos * 2;
        UsuarioSeguido* nuevoArreglo = new UsuarioSeguido[nuevaCapacidad];
        
        // Copiar datos existentes
        for (int i = 0; i < numUsuariosSeguidos; i++) {
            nuevoArreglo[i] = usuariosSeguidos[i];
        }
        
        delete[] usuariosSeguidos;
        usuariosSeguidos = nuevoArreglo;
        capacidadUsuariosSeguidos = nuevaCapacidad;
    }
    
    // Agregar nuevo usuario seguido
    UsuarioSeguido& nuevo = usuariosSeguidos[numUsuariosSeguidos];
    strcpy(nuevo.nombreUsuario, nombreUsuario);
    nuevo.favoritosCache = nullptr;
    nuevo.numFavoritos = 0;
    nuevo.capacidadFavoritos = 0;
    nuevo.necesitaActualizacion = true;
    
    numUsuariosSeguidos++;
    
    // Actualizar favoritos inmediatamente
    actualizarFavoritosUsuarioSeguido(nombreUsuario, usuarios, nUsuarios);
    
    cout << "Ahora sigues a '" << nombreUsuario << "'.\n";
    return true;
}

void Interfaz::actualizarFavoritosUsuarioSeguido(const char* nombreUsuario, Usuario usuarios[], int nUsuarios) {
    // Buscar el usuario seguido
    int indiceSeguido = -1;
    for (int i = 0; i < numUsuariosSeguidos; i++) {
        if (strcmp(usuariosSeguidos[i].nombreUsuario, nombreUsuario) == 0) {
            indiceSeguido = i;
            break;
        }
    }
    
    if (indiceSeguido == -1) return;
    
    // Buscar el usuario en la lista de usuarios
    int indiceUsuario = buscarUsuarioPorNombre(usuarios, nUsuarios, nombreUsuario);
    if (indiceUsuario == -1) return;
    
    Usuario& usuario = usuarios[indiceUsuario];
    UsuarioSeguido& seguido = usuariosSeguidos[indiceSeguido];
    
    // Obtener número actual de favoritos
    int numFavoritosActual = usuario.getNumFavoritos();
    
    // Expandir cache si es necesario
    if (numFavoritosActual > seguido.capacidadFavoritos) {
        delete[] seguido.favoritosCache;
        seguido.capacidadFavoritos = numFavoritosActual + 5; // Un poco de espacio extra
        seguido.favoritosCache = new long[seguido.capacidadFavoritos];
    }
    
    // Copiar favoritos
    seguido.numFavoritos = numFavoritosActual;
    for (int i = 0; i < numFavoritosActual; i++) {
        seguido.favoritosCache[i] = usuario.obtenerFavoritoPorIndice(i);
    }
    
    seguido.necesitaActualizacion = false;
}

void Interfaz::actualizarTodosLosUsuariosSeguidos(Usuario usuarios[], int nUsuarios) {
    for (int i = 0; i < numUsuariosSeguidos; i++) {
        actualizarFavoritosUsuarioSeguido(usuariosSeguidos[i].nombreUsuario, usuarios, nUsuarios);
    }
}

void Interfaz::mostrarUsuariosSeguidos() {
    if (numUsuariosSeguidos == 0) {
        cout << "No sigues a ningún usuario.\n";
        return;
    }
    
    cout << "\n=== USUARIOS SEGUIDOS ===\n";
    for (int i = 0; i < numUsuariosSeguidos; i++) {
        cout << (i + 1) << ". " << usuariosSeguidos[i].nombreUsuario 
             << " (" << usuariosSeguidos[i].numFavoritos << " favoritos)\n";
    }
}

void Interfaz::reproducirFavoritosUsuarioSeguido(const char* nombreUsuario, Usuario usuarios[], int nUsuarios, 
                                               Cancion canciones[], int nCanciones, bool esPremium, int& iterCount, int& memUsed) {
    // Buscar el usuario seguido
    int indiceSeguido = -1;
    for (int i = 0; i < numUsuariosSeguidos; i++) {
        if (strcmp(usuariosSeguidos[i].nombreUsuario, nombreUsuario) == 0) {
            indiceSeguido = i;
            break;
        }
    }
    
    if (indiceSeguido == -1) {
        cout << "No sigues a '" << nombreUsuario << "'.\n";
        return;
    }
    
    UsuarioSeguido& seguido = usuariosSeguidos[indiceSeguido];
    
    // Actualizar favoritos si es necesario
    if (seguido.necesitaActualizacion) {
        actualizarFavoritosUsuarioSeguido(nombreUsuario, usuarios, nUsuarios);
    }
    
    if (seguido.numFavoritos == 0) {
        cout << "'" << nombreUsuario << "' no tiene favoritos.\n";
        return;
    }
    
    // Crear arreglo de punteros a canciones favoritas
    Cancion** listaFavoritos = new Cancion*[seguido.numFavoritos];
    int numValidados = 0;
    
    for (int i = 0; i < seguido.numFavoritos; i++) {
        Cancion* cancion = buscarCancionPorId(canciones, nCanciones, seguido.favoritosCache[i]);
        if (cancion) {
            listaFavoritos[numValidados++] = cancion;
        }
    }
    
    if (numValidados == 0) {
        cout << "No se encontraron canciones válidas en los favoritos de '" << nombreUsuario << "'.\n";
        delete[] listaFavoritos;
        return;
    }
    
    cout << "\n=== REPRODUCIENDO FAVORITOS DE " << nombreUsuario << " ===\n";
    cout << "Total de canciones: " << numValidados << "\n";
    pausarSegundos(2);
    
    // Reproducir lista con navegación
    int indiceActual = 0;
    while (indiceActual >= 0 && indiceActual < numValidados) {
        Cancion* cancionActual = listaFavoritos[indiceActual];
        
        cout << "\n[" << (indiceActual + 1) << "/" << numValidados << "] ";
        
        int resultado = reproducirConContadorRegresivo(cancionActual, esPremium, iterCount, memUsed);
        
        if (resultado == 1) { // Anterior
            if (esPremium) {
                if (indiceActual > 0) {
                    indiceActual--;
                    cout << "\nCambiando a cancion anterior: " << listaFavoritos[indiceActual]->getTitulo() << "\n";
                    pausarSegundos(1);
                } else {
                    cout << "\nYa estas en la primera cancion de los favoritos de " << nombreUsuario << ".\n";
                    pausarSegundos(2);
                }
            }
        } else if (resultado == 2) { // Siguiente
            if (esPremium) {
                if (indiceActual < numValidados - 1) {
                    indiceActual++;
                    cout << "\nCambiando a siguiente cancion: " << listaFavoritos[indiceActual]->getTitulo() << "\n";
                    pausarSegundos(1);
                } else {
                    cout << "\nYa estas en la ultima cancion de los favoritos de " << nombreUsuario << ".\n";
                    pausarSegundos(2);
                }
            }
        } else {
            // Reproducción normal, avanzar automáticamente
            indiceActual++;
        }
    }
    
    delete[] listaFavoritos;
    cout << "\nReproduccion de favoritos de '" << nombreUsuario << "' completada.\n";
}


