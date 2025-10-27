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
    contadorRetroceso = 0;  // Inicializar contador de retroceso
    inicializarHistorial();
    
    // Inicializar estructura de usuarios seguidos
    usuariosSeguidos = nullptr;
    numUsuariosSeguidos = 0;
    capacidadUsuariosSeguidos = 0;
}

Interfaz::~Interfaz() {
    liberarMemoriaUsuariosSeguidos();
}

// === Manejo de teclado ===
bool Interfaz::hayEntradaDisponible() {
#ifdef _WIN32
    return _kbhit() != 0;
#else
    return false;
#endif
}

char Interfaz::getCharSinBloqueo() {
#ifdef _WIN32
    return _getch();
#else
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

// Sistema mejorado de medición de recursos
void Interfaz::iniciarMedicionRecursos(MetricasRecursos& metricas) {
    metricas.iteracionesDirectas = 0;
    metricas.iteracionesIndirectas = 0;
    metricas.memoriaEstructuras = 0;
    metricas.memoriaVariablesLocales = 0;
    metricas.memoriaParametros = 0;
    metricas.memoriaTotal = 0;
}

void Interfaz::finalizarMedicionRecursos(const MetricasRecursos& metricas, const char* nombreFuncionalidad) {
    cout << "\nIteraciones totales: " << (metricas.iteracionesDirectas + metricas.iteracionesIndirectas) 
         << " | Bytes: " << metricas.memoriaTotal << endl;
}

void Interfaz::contarIteracionDirecta(MetricasRecursos& metricas) {
    metricas.iteracionesDirectas++;
}

void Interfaz::contarIteracionIndirecta(MetricasRecursos& metricas) {
    metricas.iteracionesIndirectas++;
}

void Interfaz::agregarMemoriaEstructura(MetricasRecursos& metricas, int bytes) {
    metricas.memoriaEstructuras += bytes;
    metricas.memoriaTotal += bytes;
}

void Interfaz::agregarMemoriaVariable(MetricasRecursos& metricas, int bytes) {
    metricas.memoriaVariablesLocales += bytes;
    metricas.memoriaTotal += bytes;
}

void Interfaz::agregarMemoriaParametro(MetricasRecursos& metricas, int bytes) {
    metricas.memoriaParametros += bytes;
    metricas.memoriaTotal += bytes;
}

// Agregar cancion
bool Interfaz::agregarCancionDinamica(Cancion canciones[], int &nCanciones,
                                     const char* titulo, long id, int duracion, const char* ruta) {
    if (nCanciones >= 1000) return false;

    Cancion nueva;
    nueva.setDatos(titulo, id, duracion, ruta);
    canciones[nCanciones++] = nueva;
    return true;
}

//  Reproducción estandar
void Interfaz::reproducirCancion(Cancion* cancion, bool esPremium, int &iterCount, int &memUsed) {
    reproducirCancion(cancion, esPremium, iterCount, memUsed, "", "");
}

void Interfaz::reproducirCancion(Cancion* cancion, bool esPremium, int &iterCount, int &memUsed,
                                const char* mensajeAd, const char* categoriaAd) {
    // Suprimir advertencias de parametros no utilizados
    (void)mensajeAd;
    (void)categoriaAd;
    
    if (!cancion) {
        cout << "Cancion no valida.\n";
        return;
    }

    iterCount++;
    memUsed += sizeof(Cancion);

    // La información se mostrara en reproducirConContadorRegresivo para evitar duplicacion
    reproducirConContadorRegresivo(cancion, esPremium, iterCount, memUsed);
}

// Cuenta atras
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

    // Usar datos vinculados de la canción
    char cantante[100], album[100], rutaPortada[300], rutaAudio[300];
    
    // Obtener datos reales de la canción vinculada
    strcpy(cantante, c->obtenerArtistaPrincipal());
    strcpy(album, c->getAlbum());

    // Generar rutas dinamicas
    char tituloLimpio[100];
    strcpy(tituloLimpio, c->getTitulo());
    // Reemplazar espacios con guiones bajos para las rutas
    for (int i = 0; tituloLimpio[i]; i++) {
        if (tituloLimpio[i] == ' ') tituloLimpio[i] = '_';
    }
    
    // Convertir a minusculas
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

        // Disminuir el tiempo si no esta pausado
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
        
        // Si esta activada la repeticion para usuarios premium, reiniciar la canción
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
    // Suprimir advertencia de parámetro no utilizado
    (void)u;
    
    if (n <= 0) {
        cout << "Lista vacia.\n";
        return;
    }

    int indiceActual = 0;
    resetearContadorRetroceso();  // Inicializar contador de retroceso para esta sesión
    
    while (indiceActual >= 0 && indiceActual < n) {
        Cancion* cancion = lista[indiceActual];

        // Guardar la cancion actual en el historial
        avanzarEnHistorial(cancion);
        
        // Reproducir la canción con el sistema unificado y obtener el código de navegación
        int resultado = reproducirConContadorRegresivo(cancion, esPremium, iterCount, memUsed);
        
        if (resultado == 1 && esPremium) {
            // Anterior - solo para Premium y verificar límite de retrocesos
            if (puedeRetrocederConLimite()) {
                incrementarContadorRetroceso();
                indiceActual--;
                if (indiceActual < 0) {
                    indiceActual = 0; // No ir más atrás del inicio
                }
            } else {
                if (contadorRetroceso >= MAX_RETROCESOS) {
                    cout << "\nHas alcanzado el limite de " << MAX_RETROCESOS << " retrocesos.\n";
                    pausarSegundos(2);
                }
            }
        } else if (resultado == 2 && esPremium) {
            // Siguiente - solo para Premium
            resetearContadorRetroceso();  // Resetear contador al avanzar
            indiceActual++;
            if (indiceActual >= n) {
                break; // Salir del bucle
            }
        } else {
            // Reproducción normal completada, avanzar a la siguiente
            resetearContadorRetroceso();  // Resetear contador al avanzar
            indiceActual++;
        }
    }
}

// === Reproducir aleatoria ===
void Interfaz::reproducirAleatoria(Cancion canciones[], int nCanciones, Usuario* u,
                                  bool esPremium, int &iterCount, int &memUsed) {
    // Suprimir advertencia de parámetro no utilizado
    (void)u;
    
    if (nCanciones <= 0) {
        cout << "No hay canciones.\n";
        return;
    }

    // Crear lista aleatoria usando Fisher-Yates
    // Optimización: usar stack allocation para arrays pequeños
    const int STACK_THRESHOLD = 100;
    int* indices;
    int stackIndices[STACK_THRESHOLD];
    bool useStack = (nCanciones <= STACK_THRESHOLD);
    
    if (useStack) {
        indices = stackIndices; // Usar memoria del stack (más rápido)
    } else {
        indices = new int[nCanciones]; // Usar heap solo para arrays grandes
    }
    
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
    resetearContadorRetroceso();  // Inicializar contador de retroceso para esta sesión
    
    while (indiceActual >= 0 && indiceActual < nCanciones && cancionesReproducidas < MAX_CANCIONES_ALEATORIO) {
        Cancion* cancion = &canciones[indices[indiceActual]];

        // Guardar la canción actual en el historial
        avanzarEnHistorial(cancion);
        
        // Reproducir la canción y obtener el código de navegación
        int resultado = reproducirConContadorRegresivo(cancion, esPremium, iterCount, memUsed);
        
        if (resultado == 1 && esPremium) {
            // Anterior - solo para Premium y verificar límite de retrocesos
            if (puedeRetrocederConLimite()) {
                incrementarContadorRetroceso();
                indiceActual--;
                if (indiceActual < 0) {
                    indiceActual = 0; // No ir más atrás del inicio
                }
            } else {
                if (contadorRetroceso >= MAX_RETROCESOS) {
                    cout << "\nHas alcanzado el limite de " << MAX_RETROCESOS << " retrocesos.\n";
                    pausarSegundos(2);
                }
            }
        } else if (resultado == 2 && esPremium) {
            // Siguiente - solo para Premium
            resetearContadorRetroceso();  // Resetear contador al avanzar
            indiceActual++;
            cancionesReproducidas++; // Contar como reproducida
            if (indiceActual >= nCanciones) {
                break; // Salir del bucle
            }
        } else {
            // Reproducción normal completada, avanzar a la siguiente
            resetearContadorRetroceso();  // Resetear contador al avanzar
            indiceActual++;
            cancionesReproducidas++; // Contar como reproducida
        }
    }

    // liberar si se uso heap allocation
    if (!useStack) {
        delete[] indices;
    }
}

// === Busquedas ===
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

// === Gestion de contador de retroceso ===
void Interfaz::resetearContadorRetroceso() {
    contadorRetroceso = 0;
}

void Interfaz::incrementarContadorRetroceso() {
    contadorRetroceso++;
}

bool Interfaz::puedeRetrocederConLimite() {
    return puedeRetroceder() && contadorRetroceso < MAX_RETROCESOS;
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
                 mostrarUsuariosSeguidos(usuarios, nUsuarios);
                 if (numUsuariosSeguidos > 0) {
                     cout << "\nPresiona Enter para continuar...";
                     cin.ignore();
                     cin.get();
                 }
                 break;
             }
            
            case 3: {
                 if (numUsuariosSeguidos == 0) {
                     cout << "No sigues a ningun usuario.\n";
                     break;
                 }
                 
                 mostrarUsuariosSeguidos(usuarios, nUsuarios);
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
                cout << "Volviendo al menu anterior...\n";
                break;
               
           default:
               cout << "Opcion invalida.\n";
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
            
            // Agregar favoritos predefinidos para María
            if (strcmp(nombre, "maria") == 0) {
                // IDs de las primeras 10 canciones del archivo songs.txt
                long favoritosMaria[] = {100010101, 100010102, 100010103, 100010104, 200020101, 
                                       200020102, 200020103, 300030101, 300030102, 300030103};
                
                for (int i = 0; i < 10; i++) {
                    usuarios[count].agregarFavorito(favoritosMaria[i]);
                }
            }
            
            count++;
        }
    }

    fclose(archivo);
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
    return count;
}

int Interfaz::cargarAlbunesDesdeArchivo(const char* ruta, Album albunes[], int maxAlbunes) {
    FILE* archivo = fopen(ruta, "r");
    if (!archivo) {
        cout << "Error al abrir el archivo de albumes: " << ruta << endl;
        return 0;
    }

    int count = 0;
    char linea[1024];

    auto trim = [](char* s){
        if (!s) return s;
        while (*s == ' ' || *s == '\t') s++;
        char* end = s + strlen(s);
        while (end > s && (end[-1] == ' ' || end[-1] == '\t' || end[-1] == '\r' || end[-1] == '\n')) { end[-1] = '\0'; end--; }
        return s;
    };

    while (count < maxAlbunes && fgets(linea, sizeof(linea), archivo)) {
        if (linea[0] == '\n' || linea[0] == '\r' || linea[0] == '\0') continue;

        // Formato: id,nombre,fecha,duracion,sello,portada,puntuacion,genero1,genero2,genero3,genero4
        char* idStr = strtok(linea, ",\r\n");
        char* nombre = strtok(nullptr, ",\r\n");
        char* fecha = strtok(nullptr, ",\r\n");
        char* durStr = strtok(nullptr, ",\r\n");
        char* sello = strtok(nullptr, ",\r\n");
        char* portada = strtok(nullptr, ",\r\n");
        char* puntStr = strtok(nullptr, ",\r\n");

        // Trim de los campos básicos
        idStr = trim(idStr);
        nombre = trim(nombre);
        fecha = trim(fecha);
        durStr = trim(durStr);
        sello = trim(sello);
        portada = trim(portada);
        puntStr = trim(puntStr);

        if (idStr && nombre && fecha && durStr && sello && portada && puntStr &&
            *idStr && *nombre && *fecha && *durStr && *sello && *portada && *puntStr) {
            
            long id = strtol(idStr, nullptr, 10);
            int duracion = atoi(durStr);
            int puntuacion = atoi(puntStr);

            // Configurar datos básicos del álbum
            albunes[count].setDatos(id, nombre, fecha, duracion, sello, portada);
            albunes[count].setPuntuacion(puntuacion);

            // Procesar géneros (hasta 4)
            for (int i = 0; i < 4; i++) {
                char* genero = strtok(nullptr, ",\r\n");
                if (genero) {
                    genero = trim(genero);
                    if (genero && *genero && strlen(genero) > 0) {
                        albunes[count].agregarGenero(genero);
                    }
                }
            }

            count++;
        }
    }

    fclose(archivo);
    return count;
}

int Interfaz::cargarArtistasDesdeArchivo(const char* ruta, Artista artistas[], int maxArtistas) {
    FILE* archivo = fopen(ruta, "r");
    if (!archivo) {
        cout << "Error al abrir el archivo de artistas: " << ruta << endl;
        return 0;
    }

    int count = 0;
    char linea[1024];

    auto trim = [](char* s){
        if (!s) return s;
        while (*s == ' ' || *s == '\t') s++;
        char* end = s + strlen(s);
        while (end > s && (end[-1] == ' ' || end[-1] == '\t' || end[-1] == '\r' || end[-1] == '\n')) { end[-1] = '\0'; end--; }
        return s;
    };

    while (count < maxArtistas && fgets(linea, sizeof(linea), archivo)) {
        if (linea[0] == '\n' || linea[0] == '\r' || linea[0] == '\0') continue;

        // Formato: id,nombre,edad,pais,seguidores,posicionTendencias
        char* idStr = strtok(linea, ",\r\n");
        char* nombre = strtok(nullptr, ",\r\n");
        char* edadStr = strtok(nullptr, ",\r\n");
        char* pais = strtok(nullptr, ",\r\n");
        char* seguidoresStr = strtok(nullptr, ",\r\n");
        char* posicionStr = strtok(nullptr, ",\r\n");

        // Trim de los campos
        idStr = trim(idStr);
        nombre = trim(nombre);
        edadStr = trim(edadStr);
        pais = trim(pais);
        seguidoresStr = trim(seguidoresStr);
        posicionStr = trim(posicionStr);

        if (idStr && nombre && edadStr && pais && seguidoresStr && posicionStr &&
            *idStr && *nombre && *edadStr && *pais && *seguidoresStr && *posicionStr) {
            
            long id = strtol(idStr, nullptr, 10);
            int edad = atoi(edadStr);
            int seguidores = atoi(seguidoresStr);
            int posicion = atoi(posicionStr);

            // Configurar datos del artista
            artistas[count].setDatos(id, nombre, edad, pais, seguidores, posicion);
            count++;
        }
    }

    fclose(archivo);
    return count;
}

int Interfaz::cargarPlaylistsDesdeArchivo(const char* ruta, Playlist playlists[], int maxPlaylists, Cancion canciones[], int nCanciones) {
    FILE* archivo = fopen(ruta, "r");
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo " << ruta << endl;
        return 0;
    }

    char linea[1000];
    int count = 0;

    // Función lambda para eliminar espacios en blanco
    auto trim = [](char* str) {
        char* end;
        while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r') str++;
        if (*str == 0) return str;
        end = str + strlen(str) - 1;
        while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) end--;
        end[1] = '\0';
        return str;
    };

    while (fgets(linea, sizeof(linea), archivo) && count < maxPlaylists) {
        char* lineaTrimmed = trim(linea);
        if (strlen(lineaTrimmed) == 0) continue;

        // Parsear la línea: nombre,id1,id2,id3,...
        char* token = strtok(lineaTrimmed, ",");
        if (!token) continue;

        // Primer token es el nombre de la playlist
        char* nombrePlaylist = trim(token);
        
        // Crear la playlist con el nombre
        playlists[count] = Playlist(nombrePlaylist);

        // Procesar los IDs de las canciones
        while ((token = strtok(nullptr, ",")) != nullptr) {
            char* idStr = trim(token);
            if (strlen(idStr) == 0) continue;

            long cancionId = atol(idStr);
            
            // Buscar la canción por ID
            Cancion* cancionEncontrada = nullptr;
            for (int i = 0; i < nCanciones; i++) {
                if (canciones[i].getId() == cancionId) {
                    cancionEncontrada = &canciones[i];
                    break;
                }
            }

            // Si se encontró la canción, agregarla a la playlist
            if (cancionEncontrada) {
                playlists[count].agregarCancion(cancionEncontrada);
            } else {
                cout << "Advertencia: Canción con ID " << cancionId << " no encontrada para playlist '" << nombrePlaylist << "'" << endl;
            }
        }

        count++;
    }

    fclose(archivo);
    return count;
}

// === Gestion de usuarios seguidos (arreglos dinámicos) ===
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
            cout << "Ya estas siguiendo a '" << nombreUsuario << "'.\n";
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
    
    // Expandir cache solo si es realmente necesario
    if (numFavoritosActual > seguido.capacidadFavoritos) {
        delete[] seguido.favoritosCache;
        seguido.capacidadFavoritos = numFavoritosActual + 5; // Un poco de espacio extra
        seguido.favoritosCache = new long[seguido.capacidadFavoritos];
    }
    // Si el cache ya existe y es suficiente, no hacer nada (optimización)
    
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

void Interfaz::marcarUsuarioSeguidoParaActualizacion(const char* nombreUsuario) {
    for (int i = 0; i < numUsuariosSeguidos; i++) {
        if (strcmp(usuariosSeguidos[i].nombreUsuario, nombreUsuario) == 0) {
            usuariosSeguidos[i].necesitaActualizacion = true;
            break;
        }
    }
}

void Interfaz::notificarCambioFavoritos(const char* nombreUsuario) {
    // Marcar que este usuario necesita actualización en el cache de seguimiento
    marcarUsuarioSeguidoParaActualizacion(nombreUsuario);
}

void Interfaz::mostrarUsuariosSeguidos(Usuario usuarios[], int nUsuarios) {
    if (numUsuariosSeguidos == 0) {
        cout << "No sigues a ningun usuario.\n";
        return;
    }
    
    // Actualizar automáticamente el cache antes de mostrar para reflejar cambios recientes
    actualizarTodosLosUsuariosSeguidos(usuarios, nUsuarios);
    
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
        return; // Retorno temprano - no necesita asignar memoria
    }
    
    // Crear arreglo de punteros a canciones favoritas
    // Optimización: usar stack allocation para listas pequeñas
    const int STACK_THRESHOLD = 50;
    Cancion** listaFavoritos;
    Cancion* stackFavoritos[STACK_THRESHOLD];
    bool useStack = (seguido.numFavoritos <= STACK_THRESHOLD);
    
    if (useStack) {
        listaFavoritos = stackFavoritos; // Usar memoria del stack (más rápido)
    } else {
        listaFavoritos = new Cancion*[seguido.numFavoritos]; // Usar heap solo para listas grandes
    }
    int numValidados = 0;
    
    for (int i = 0; i < seguido.numFavoritos; i++) {
        Cancion* cancion = buscarCancionPorId(canciones, nCanciones, seguido.favoritosCache[i]);
        if (cancion) {
            listaFavoritos[numValidados++] = cancion;
        }
    }
    
    if (numValidados == 0) {
        cout << "No se encontraron canciones validas en los favoritos de '" << nombreUsuario << "'.\n";
        // Solo liberar si se usó heap allocation
        if (!useStack) {
            delete[] listaFavoritos;
        }
        return;
    }
    
    cout << "\n=== REPRODUCIENDO FAVORITOS DE " << nombreUsuario << " ===\n";
    cout << "Total de canciones: " << numValidados << "\n";
    pausarSegundos(2);
    
    // Inicializar contador de retroceso y historial
    resetearContadorRetroceso();
    inicializarHistorial();
    
    // Reproducir lista con navegación
    int indiceActual = 0;
    while (indiceActual >= 0 && indiceActual < numValidados) {
        Cancion* cancionActual = listaFavoritos[indiceActual];
        
        cout << "\n[" << (indiceActual + 1) << "/" << numValidados << "] ";
        
        // Agregar canción al historial
        avanzarEnHistorial(cancionActual);
        
        int resultado = reproducirConContadorRegresivo(cancionActual, esPremium, iterCount, memUsed);
        
        if (resultado == 1) { // Anterior
            if (esPremium) {
                if (puedeRetrocederConLimite() && indiceActual > 0) {
                    incrementarContadorRetroceso();
                    indiceActual--;
                } else if (!puedeRetrocederConLimite()) {
                    cout << "\nHas alcanzado el limite de " << MAX_RETROCESOS << " retrocesos.\n";
                    pausarSegundos(2);
                } else {
                    cout << "\nYa estas en la primera cancion.\n";
                    pausarSegundos(2);
                }
            }
        } else if (resultado == 2) { // Siguiente
            if (esPremium) {
                resetearContadorRetroceso(); // Resetear contador al avanzar
                if (indiceActual < numValidados - 1) {
                    indiceActual++;
                } else {
                    cout << "\nYa estas en la ultima cancion.\n";
                    pausarSegundos(2);
                }
            }
        } else {
            // Reproducción normal, avanzar automáticamente
            resetearContadorRetroceso(); // Resetear contador en reproducción normal
            indiceActual++;
        }
    }
    
    // Solo liberar si se usó heap allocation
    if (!useStack) {
        delete[] listaFavoritos;
    }
    cout << "\nReproduccion de favoritos de '" << nombreUsuario << "' completada.\n";
}

// Función para vincular canciones con sus artistas correspondientes
void Interfaz::vincularCancionesConArtistas(Cancion canciones[], int nCanciones, Artista artistas[], int nArtistas) {
    
    for (int i = 0; i < nCanciones; i++) {
        long cancionId = canciones[i].getId();
        // Extraer el ID del artista de los primeros 6 dígitos del ID de la canción
        long artistaId = cancionId / 1000; // Esto convierte 100010101 a 100010
        
        // Buscar el artista correspondiente
        for (int j = 0; j < nArtistas; j++) {
            if (artistas[j].getId() == artistaId) {
                // Encontramos el artista, establecer el nombre
                canciones[i].establecerArtistaPrincipal(artistas[j].obtenerNombre());
                canciones[i].establecerCodigoArtista(artistaId);
                break;
            }
        }
    }
}

// Función para vincular canciones con sus álbumes correspondientes
void Interfaz::vincularCancionesConAlbumes(Cancion canciones[], int nCanciones, Album albumes[], int nAlbumes) {
    
    for (int i = 0; i < nCanciones; i++) {
        long cancionId = canciones[i].getId();
        // Extraer el ID del álbum de los primeros 4 dígitos del ID de la canción
        long albumId = cancionId / 100000; // Esto convierte 100010101 a 1000
        
        // Buscar el álbum correspondiente
        bool encontrado = false;
        for (int j = 0; j < nAlbumes; j++) {
            if (albumes[j].getId() == albumId) {
                // Encontramos el álbum, establecer el nombre
                canciones[i].establecerAlbum(albumes[j].obtenerNombre());
                // También establecer la ruta de la portada del álbum
                canciones[i].establecerRutaPortada(albumes[j].getPortada());
                encontrado = true;
                break;
            }
        }
        
        // Si no se encontró álbum, marcar como Single
        if (!encontrado) {
            canciones[i].establecerAlbum("Single");
        }
    }
}

// Función para establecer canciones como Single cuando no pertenecen a un álbum
void Interfaz::establecerCancionesSingle(Cancion canciones[], int nCanciones) {
    
    for (int i = 0; i < nCanciones; i++) {
        // Si el álbum está vacío o es "Album Desconocido", marcarlo como Single
        if (strlen(canciones[i].getAlbum()) == 0 || 
            strcmp(canciones[i].getAlbum(), "Album Desconocido") == 0) {
            canciones[i].establecerAlbum("Single");
        }
    }
}

// === Funciones con medición integrada ===

void Interfaz::editarFavoritosConMedicion(Usuario* usuario, Cancion canciones[], int nCanciones) {
    MetricasRecursos metricas;
    iniciarMedicionRecursos(metricas);
    
    // Calcular memoria de parámetros
    agregarMemoriaParametro(metricas, sizeof(Usuario*));
    agregarMemoriaParametro(metricas, sizeof(Cancion*));
    agregarMemoriaParametro(metricas, sizeof(int));
    
    // Calcular memoria de estructuras existentes
    agregarMemoriaEstructura(metricas, sizeof(Usuario));
    agregarMemoriaEstructura(metricas, nCanciones * sizeof(Cancion));
    
    // Variables locales
    int opcion;
    agregarMemoriaVariable(metricas, sizeof(int));
    
    do {
        contarIteracionDirecta(metricas);
        
        cout << "\n=== EDITAR FAVORITOS ===" << endl;
        cout << "1. Agregar cancion a favoritos" << endl;
        cout << "2. Eliminar cancion de favoritos" << endl;
        cout << "3. Ver favoritos actuales" << endl;
        cout << "4. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        // Validar entrada
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = 0; // Valor inválido para continuar el bucle
            cout << "Entrada invalida. Intente nuevamente.\n";
            continue;
        }
        
        switch (opcion) {
            case 1: {
                contarIteracionDirecta(metricas);
                int idCancion;
                agregarMemoriaVariable(metricas, sizeof(int));
                
                cout << "\nIngrese el ID de la cancion: ";
                cin >> idCancion;
                
                // Validar entrada del ID
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "ID invalido. Debe ingresar un numero.\n";
                    break;
                }
                
                // Buscar canción
                bool encontrada = false;
                agregarMemoriaVariable(metricas, sizeof(bool));
                
                for (int i = 0; i < nCanciones; i++) {
                    contarIteracionIndirecta(metricas);
                    if (canciones[i].getId() == idCancion) {
                        encontrada = true;
                        
                        // Mostrar información de la canción
                        cout << "\n=== INFORMACION DE LA CANCION ===" << endl;
                        cout << "ID: " << canciones[i].getId() << endl;
                        cout << "Titulo: " << canciones[i].getTitulo() << endl;
                        cout << "Artista: " << canciones[i].obtenerArtistaPrincipal() << endl;
                        cout << "Album: " << canciones[i].getAlbum() << endl;
                        cout << "Duracion: " << canciones[i].getDuracion() << " segundos" << endl;
                        
                        // Verificar si ya está en favoritos
                        bool yaEsFavorito = false;
                        agregarMemoriaVariable(metricas, sizeof(bool));
                        
                        for (int j = 0; j < usuario->getNumFavoritos(); j++) {
                            contarIteracionIndirecta(metricas);
                            if (usuario->obtenerFavoritoPorIndice(j) == idCancion) {
                                yaEsFavorito = true;
                                break;
                            }
                        }
                        
                        if (yaEsFavorito) {
                            cout << "\nEsta cancion YA ESTA en tus favoritos." << endl;
                            cout << "Que deseas hacer?" << endl;
                            cout << "1. Eliminar de favoritos" << endl;
                            cout << "2. Mantener en favoritos (no hacer nada)" << endl;
                            cout << "Opcion: ";
                            
                            int opcionFav;
                            agregarMemoriaVariable(metricas, sizeof(int));
                            cin >> opcionFav;
                            
                            // Validar entrada de opción
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << "Opcion invalida. Debe ingresar un numero.\n";
                                break;
                            }
                            
                            if (opcionFav == 1) {
                                if (usuario->eliminarFavorito(idCancion)) {
                                    cout << "Cancion eliminada de favoritos!" << endl;
                                } else {
                                    cout << "Error al eliminar la cancion de favoritos." << endl;
                                }
                            } else {
                                cout << "La cancion se mantiene en favoritos." << endl;
                            }
                        } else {
                            cout << "\nEsta cancion NO ESTA en tus favoritos." << endl;
                            cout << "Que deseas hacer?" << endl;
                            cout << "1. Agregar a favoritos" << endl;
                            cout << "2. No agregar (cancelar)" << endl;
                            cout << "Opcion: ";
                            
                            int opcionFav;
                            agregarMemoriaVariable(metricas, sizeof(int));
                            cin >> opcionFav;
                            
                            // Validar entrada de opción
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << "Opcion invalida. Debe ingresar un numero.\n";
                                break;
                            }
                            
                            if (opcionFav == 1) {
                                if (usuario->agregarFavorito(idCancion)) {
                                    cout << "Cancion agregada a favoritos!" << endl;
                                } else {
                                    cout << "Lista de favoritos llena!" << endl;
                                }
                            } else {
                                cout << "Operacion cancelada." << endl;
                            }
                        }
                        break;
                    }
                }
                
                if (!encontrada) {
                    cout << "Cancion con ID " << idCancion << " no encontrada!" << endl;
                }
                break;
            }
            case 2: {
                contarIteracionDirecta(metricas);
                if (usuario->getNumFavoritos() == 0) {
                    cout << "No tienes canciones favoritas!" << endl;
                    break;
                }
                
                cout << "\n=== TUS FAVORITOS ===" << endl;
                for (int i = 0; i < usuario->getNumFavoritos(); i++) {
                    contarIteracionIndirecta(metricas);
                    long idFav = usuario->obtenerFavoritoPorIndice(i);
                    // Buscar la canción para mostrar el título
                    for (int j = 0; j < nCanciones; j++) {
                        if (canciones[j].getId() == idFav) {
                            cout << "ID: " << idFav << " - " << canciones[j].getTitulo() << endl;
                            break;
                        }
                    }
                }
                
                long idEliminar;
                agregarMemoriaVariable(metricas, sizeof(long));
                cout << "Ingrese el ID de la cancion a eliminar: ";
                cin >> idEliminar;
                
                // Validar entrada del ID
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "ID invalido. Debe ingresar un numero.\n";
                    break;
                }
                
                if (usuario->eliminarFavorito(idEliminar)) {
                    cout << "Cancion eliminada de favoritos!" << endl;
                } else {
                    cout << "Cancion no encontrada en favoritos!" << endl;
                }
                break;
            }
            case 3: {
                contarIteracionDirecta(metricas);
                if (usuario->getNumFavoritos() == 0) {
                    cout << "No tienes canciones favoritas!" << endl;
                } else {
                    cout << "\n=== TUS FAVORITOS ===" << endl;
                    for (int i = 0; i < usuario->getNumFavoritos(); i++) {
                        contarIteracionIndirecta(metricas);
                        long idFav = usuario->obtenerFavoritoPorIndice(i);
                        // Buscar la canción para mostrar información completa
                        for (int j = 0; j < nCanciones; j++) {
                            if (canciones[j].getId() == idFav) {
                                cout << "ID: " << idFav << " - " << canciones[j].getTitulo() 
                                     << " (" << canciones[j].obtenerArtistaPrincipal() << ")" << endl;
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case 4:
                contarIteracionDirecta(metricas);
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                contarIteracionDirecta(metricas);
                cout << "Opcion invalida!" << endl;
                break;
        }
    } while (opcion != 4);
    
    finalizarMedicionRecursos(metricas, "EDITAR FAVORITOS");
}

void Interfaz::mostrarCancionesConMedicion(Cancion canciones[], int nCanciones) {
    MetricasRecursos metricas;
    iniciarMedicionRecursos(metricas);
    
    // Calcular memoria de parámetros
    agregarMemoriaParametro(metricas, sizeof(Cancion*));
    agregarMemoriaParametro(metricas, sizeof(int));
    
    // Calcular memoria de estructuras
    agregarMemoriaEstructura(metricas, nCanciones * sizeof(Cancion));
    
    cout << "\n=== CANCIONES DISPONIBLES ===" << endl;
    cout << "Total de canciones: " << nCanciones << endl;
    cout << "--------------------------------" << endl;
    
    for (int i = 0; i < nCanciones; i++) {
        contarIteracionDirecta(metricas);
        cout << "ID: " << canciones[i].getId() << endl;
        cout << "Titulo: " << canciones[i].getTitulo() << endl;
        cout << "Artista: " << canciones[i].obtenerArtistaPrincipal() << endl;
        cout << "Album: " << canciones[i].getAlbum() << endl;
        cout << "Duracion: " << canciones[i].getDuracion() << " segundos" << endl;
        cout << "Reproducciones: " << canciones[i].getReproducciones() << endl;
        cout << "--------------------------------" << endl;
    }
    
    finalizarMedicionRecursos(metricas, "MOSTRAR CANCIONES");
}

void Interfaz::seguirUsuarioConMedicion(Usuario* usuario, Usuario usuarios[], int nUsuarios, Cancion canciones[], int nCanciones) {
    MetricasRecursos metricas;
    iniciarMedicionRecursos(metricas);
    
    // Calcular memoria de parámetros
    agregarMemoriaParametro(metricas, sizeof(Usuario*));
    agregarMemoriaParametro(metricas, sizeof(Usuario*));
    agregarMemoriaParametro(metricas, sizeof(int));
    agregarMemoriaParametro(metricas, sizeof(Cancion*));
    agregarMemoriaParametro(metricas, sizeof(int));
    
    // Calcular memoria de estructuras
    agregarMemoriaEstructura(metricas, sizeof(Usuario));
    agregarMemoriaEstructura(metricas, nUsuarios * sizeof(Usuario));
    agregarMemoriaEstructura(metricas, nCanciones * sizeof(Cancion));
    
    // Variables locales
    char nombreUsuario[50];
    agregarMemoriaVariable(metricas, sizeof(nombreUsuario));
    
    cout << "\n=== SEGUIR USUARIO ===" << endl;
    cout << "Usuarios disponibles para seguir:" << endl;
    
    for (int i = 0; i < nUsuarios; i++) {
        contarIteracionDirecta(metricas);
        if (strcmp(usuarios[i].getNombre(), usuario->getNombre()) != 0) {
            // Verificar si ya lo sigue
            bool yaSigue = false;
            agregarMemoriaVariable(metricas, sizeof(bool));
            
            for (int j = 0; j < numUsuariosSeguidos; j++) {
                contarIteracionIndirecta(metricas);
                if (strcmp(usuariosSeguidos[j].nombreUsuario, usuarios[i].getNombre()) == 0) {
                    yaSigue = true;
                    break;
                }
            }
            
            if (!yaSigue) {
                cout << "- " << usuarios[i].getNombre() << " (Favoritos: " << usuarios[i].getNumFavoritos() << ")" << endl;
            }
        }
    }
    
    cout << "Ingrese el nombre del usuario a seguir: ";
    cin.ignore();
    cin.getline(nombreUsuario, sizeof(nombreUsuario));
    
    // Usar la función existente para agregar usuario seguido
    if (strcmp(nombreUsuario, usuario->getNombre()) == 0) {
        cout << "No puedes seguirte a ti mismo!" << endl;
    } else {
        agregarUsuarioSeguido(nombreUsuario, usuarios, nUsuarios);
    }
    
    finalizarMedicionRecursos(metricas, "SEGUIR USUARIO");
}

void Interfaz::reproducirAleatoriaConMedicion(Cancion canciones[], int nCanciones, Usuario* u, bool esPremium) {
    MetricasRecursos metricas;
    iniciarMedicionRecursos(metricas);
    
    // Calcular memoria de parámetros
    agregarMemoriaParametro(metricas, sizeof(Cancion*));
    agregarMemoriaParametro(metricas, sizeof(int));
    agregarMemoriaParametro(metricas, sizeof(Usuario*));
    agregarMemoriaParametro(metricas, sizeof(bool));
    
    // Calcular memoria de estructuras
    agregarMemoriaEstructura(metricas, nCanciones * sizeof(Cancion));
    agregarMemoriaEstructura(metricas, sizeof(Usuario));
    
    // Variables locales
    int iterCount = 0, memUsed = 0;
    agregarMemoriaVariable(metricas, sizeof(int) * 2);
    
    if (nCanciones <= 0) {
        contarIteracionDirecta(metricas);
        cout << "No hay canciones.\n";
        finalizarMedicionRecursos(metricas, "REPRODUCCION ALEATORIA");
        return;
    }

    // Crear lista aleatoria usando Fisher-Yates
    const int STACK_THRESHOLD = 100;
    int* indices;
    int stackIndices[STACK_THRESHOLD];
    bool useStack = (nCanciones <= STACK_THRESHOLD);
    agregarMemoriaVariable(metricas, sizeof(int*));
    agregarMemoriaVariable(metricas, sizeof(bool));
    
    if (useStack) {
        indices = stackIndices;
        agregarMemoriaVariable(metricas, sizeof(stackIndices));
    } else {
        indices = new int[nCanciones];
        agregarMemoriaVariable(metricas, nCanciones * sizeof(int));
    }
    
    // Inicializar índices
    for (int i = 0; i < nCanciones; i++) {
        contarIteracionDirecta(metricas);
        indices[i] = i;
    }

    // Algoritmo Fisher-Yates
    for (int i = nCanciones - 1; i > 0; --i) {
        contarIteracionDirecta(metricas);
        int j = rand() % (i + 1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
        agregarMemoriaVariable(metricas, sizeof(int) * 2);
    }

    // Variables para navegación
    int indiceActual = 0;
    int cancionesReproducidas = 0;
    const int MAX_CANCIONES_ALEATORIO = 5;
    agregarMemoriaVariable(metricas, sizeof(int) * 3);
    
    contarIteracionIndirecta(metricas);
    resetearContadorRetroceso();
    
    while (indiceActual >= 0 && indiceActual < nCanciones && cancionesReproducidas < MAX_CANCIONES_ALEATORIO) {
        contarIteracionDirecta(metricas);
        
        Cancion* cancion = &canciones[indices[indiceActual]];
        agregarMemoriaVariable(metricas, sizeof(Cancion*));

        // Guardar la canción actual en el historial
        contarIteracionIndirecta(metricas);
        avanzarEnHistorial(cancion);
        
        // Reproducir la canción y obtener el código de navegación
        contarIteracionIndirecta(metricas);
        int resultado = reproducirConContadorRegresivo(cancion, esPremium, iterCount, memUsed);
        agregarMemoriaVariable(metricas, sizeof(int));
        
        if (resultado == 1 && esPremium) {
            contarIteracionDirecta(metricas);
            // Anterior - solo para Premium y verificar límite de retrocesos
            if (puedeRetrocederConLimite()) {
                contarIteracionIndirecta(metricas);
                incrementarContadorRetroceso();
                indiceActual--;
                if (indiceActual < 0) {
                    indiceActual = 0;
                }
            } else {
                if (contadorRetroceso >= MAX_RETROCESOS) {
                    cout << "\nHas alcanzado el limite de " << MAX_RETROCESOS << " retrocesos.\n";
                    pausarSegundos(2);
                }
            }
        } else if (resultado == 2 && esPremium) {
            contarIteracionDirecta(metricas);
            // Siguiente - solo para Premium
            contarIteracionIndirecta(metricas);
            resetearContadorRetroceso();
            indiceActual++;
            cancionesReproducidas++;
            if (indiceActual >= nCanciones) {
                break;
            }
        } else {
            contarIteracionDirecta(metricas);
            // Reproducción normal completada, avanzar a la siguiente
            contarIteracionIndirecta(metricas);
            resetearContadorRetroceso();
            indiceActual++;
            cancionesReproducidas++;
        }
    }

    // Solo liberar si se usó heap allocation
    if (!useStack) {
        delete[] indices;
    }
    
    finalizarMedicionRecursos(metricas, "REPRODUCCION ALEATORIA");
}

void Interfaz::ejecutarListaFavoritosConMedicion(Usuario* usuario, Cancion canciones[], int nCanciones, bool esPremium) {
    MetricasRecursos metricas;
    iniciarMedicionRecursos(metricas);
    
    // Calcular memoria de parámetros
    agregarMemoriaParametro(metricas, sizeof(Usuario*));
    agregarMemoriaParametro(metricas, sizeof(Cancion*));
    agregarMemoriaParametro(metricas, sizeof(int));
    agregarMemoriaParametro(metricas, sizeof(bool));
    
    // Calcular memoria de estructuras
    agregarMemoriaEstructura(metricas, sizeof(Usuario));
    agregarMemoriaEstructura(metricas, nCanciones * sizeof(Cancion));
    
    if (usuario->getNumFavoritos() == 0) {
        contarIteracionDirecta(metricas);
        cout << "No tienes canciones favoritas!" << endl;
        finalizarMedicionRecursos(metricas, "EJECUTAR LISTA FAVORITOS");
        return;
    }
    
    // Variables locales
    int iterCount = 0, memUsed = 0;
    agregarMemoriaVariable(metricas, sizeof(int) * 2);
    
    cout << "\n=== REPRODUCIENDO LISTA DE FAVORITOS ===" << endl;
    cout << "Total de favoritos: " << usuario->getNumFavoritos() << endl;
    
    // Crear array de punteros a canciones favoritas
    Cancion** listaFavoritos = new Cancion*[usuario->getNumFavoritos()];
    agregarMemoriaVariable(metricas, usuario->getNumFavoritos() * sizeof(Cancion*));
    
    int favoritosEncontrados = 0;
    agregarMemoriaVariable(metricas, sizeof(int));
    
    // Buscar las canciones favoritas en el array de canciones
    for (int i = 0; i < usuario->getNumFavoritos(); i++) {
        contarIteracionDirecta(metricas);
        long idFavorito = usuario->obtenerFavoritoPorIndice(i);
        
        for (int j = 0; j < nCanciones; j++) {
            contarIteracionIndirecta(metricas);
            if (canciones[j].getId() == idFavorito) {
                listaFavoritos[favoritosEncontrados] = &canciones[j];
                favoritosEncontrados++;
                break;
            }
        }
    }
    
    if (favoritosEncontrados == 0) {
        contarIteracionDirecta(metricas);
        cout << "No se encontraron canciones favoritas válidas!" << endl;
        delete[] listaFavoritos;
        finalizarMedicionRecursos(metricas, "EJECUTAR LISTA FAVORITOS");
        return;
    }
    
    cout << "Canciones encontradas: " << favoritosEncontrados << endl;
    
    // Reproducir la lista de favoritos
    contarIteracionIndirecta(metricas);
    reproducirLista(listaFavoritos, favoritosEncontrados, usuario, esPremium, iterCount, memUsed);
    
    delete[] listaFavoritos;
    finalizarMedicionRecursos(metricas, "EJECUTAR LISTA FAVORITOS");
}

void Interfaz::reproducirFavoritosUsuarioSeguidoConMedicion(const char* nombreUsuario, Usuario usuarios[], int nUsuarios, 
                                                          Cancion canciones[], int nCanciones, bool esPremium) {
    MetricasRecursos metricas;
    iniciarMedicionRecursos(metricas);
    
    // Memoria de parámetros
    agregarMemoriaParametro(metricas, strlen(nombreUsuario) + 1); // nombreUsuario
    agregarMemoriaParametro(metricas, sizeof(Usuario*)); // usuarios
    agregarMemoriaParametro(metricas, sizeof(int)); // nUsuarios
    agregarMemoriaParametro(metricas, sizeof(Cancion*)); // canciones
    agregarMemoriaParametro(metricas, sizeof(int)); // nCanciones
    agregarMemoriaParametro(metricas, sizeof(bool)); // esPremium
    
    // Memoria de estructuras principales
    agregarMemoriaEstructura(metricas, sizeof(Interfaz)); // this
    agregarMemoriaEstructura(metricas, nUsuarios * sizeof(Usuario)); // array usuarios
    agregarMemoriaEstructura(metricas, nCanciones * sizeof(Cancion)); // array canciones
    
    // Variables locales
    int indiceSeguido = -1;
    agregarMemoriaVariable(metricas, sizeof(int)); // indiceSeguido
    
    // Buscar el usuario seguido
    for (int i = 0; i < numUsuariosSeguidos; i++) {
        contarIteracionDirecta(metricas);
        if (strcmp(usuariosSeguidos[i].nombreUsuario, nombreUsuario) == 0) {
            contarIteracionIndirecta(metricas); // strcmp
            indiceSeguido = i;
            break;
        }
        contarIteracionIndirecta(metricas); // strcmp
    }
    
    if (indiceSeguido == -1) {
        cout << "No sigues a '" << nombreUsuario << "'.\n";
        finalizarMedicionRecursos(metricas, "REPRODUCIR FAVORITOS USUARIO SEGUIDO");
        return;
    }
    
    UsuarioSeguido& seguido = usuariosSeguidos[indiceSeguido];
    agregarMemoriaVariable(metricas, sizeof(UsuarioSeguido*)); // referencia seguido
    
    // Actualizar favoritos si es necesario
    if (seguido.necesitaActualizacion) {
        contarIteracionIndirecta(metricas); // llamada a actualizarFavoritosUsuarioSeguido
        actualizarFavoritosUsuarioSeguido(nombreUsuario, usuarios, nUsuarios);
    }
    
    if (seguido.numFavoritos == 0) {
        cout << "'" << nombreUsuario << "' no tiene favoritos.\n";
        finalizarMedicionRecursos(metricas, "REPRODUCIR FAVORITOS USUARIO SEGUIDO");
        return;
    }
    
    // Crear arreglo de punteros a canciones favoritas
    const int STACK_THRESHOLD = 50;
    agregarMemoriaVariable(metricas, sizeof(int)); // STACK_THRESHOLD
    
    Cancion** listaFavoritos;
    Cancion* stackFavoritos[STACK_THRESHOLD];
    bool useStack = (seguido.numFavoritos <= STACK_THRESHOLD);
    
    agregarMemoriaVariable(metricas, sizeof(Cancion**)); // listaFavoritos
    agregarMemoriaVariable(metricas, sizeof(bool)); // useStack
    
    if (useStack) {
        listaFavoritos = stackFavoritos;
        agregarMemoriaVariable(metricas, STACK_THRESHOLD * sizeof(Cancion*)); // stackFavoritos
    } else {
        listaFavoritos = new Cancion*[seguido.numFavoritos];
        agregarMemoriaVariable(metricas, seguido.numFavoritos * sizeof(Cancion*)); // heap allocation
    }
    
    int numCancionesValidas = 0;
    agregarMemoriaVariable(metricas, sizeof(int)); // numCancionesValidas
    
    // Llenar el arreglo con canciones válidas
    for (int i = 0; i < seguido.numFavoritos; i++) {
        contarIteracionDirecta(metricas);
        long idFavorito = seguido.favoritosCache[i];
        agregarMemoriaVariable(metricas, sizeof(long)); // idFavorito
        
        Cancion* cancion = buscarCancionPorId(canciones, nCanciones, idFavorito);
        contarIteracionIndirecta(metricas); // llamada a buscarCancionPorId
        agregarMemoriaVariable(metricas, sizeof(Cancion*)); // cancion
        
        if (cancion != nullptr) {
            listaFavoritos[numCancionesValidas++] = cancion;
        }
    }
    
    if (numCancionesValidas == 0) {
        cout << "No hay canciones válidas en los favoritos de '" << nombreUsuario << "'.\n";
        if (!useStack) {
            delete[] listaFavoritos;
        }
        finalizarMedicionRecursos(metricas, "REPRODUCIR FAVORITOS USUARIO SEGUIDO");
        return;
    }
    
    cout << "\n=== FAVORITOS DE " << nombreUsuario << " ===\n";
    cout << "Canciones encontradas: " << numCancionesValidas << "\n";
    
    // Reproducir las canciones
    cout << "Reproducir en orden (0) o aleatorio (1)? ";
    int modo;
    cin >> modo;
    agregarMemoriaVariable(metricas, sizeof(int)); // modo
    
    if (modo == 1) {
        // Modo aleatorio - máximo 5 canciones
        int K = (numCancionesValidas < 5 ? numCancionesValidas : 5);
        agregarMemoriaVariable(metricas, sizeof(int)); // K
        
        Cancion* sesionAleatoria[5];
        bool used[1000] = {false};
        agregarMemoriaVariable(metricas, 5 * sizeof(Cancion*)); // sesionAleatoria
        agregarMemoriaVariable(metricas, 1000 * sizeof(bool)); // used
        
        int chosen = 0;
        agregarMemoriaVariable(metricas, sizeof(int)); // chosen
        
        while (chosen < K) {
            contarIteracionDirecta(metricas);
            int r = rand() % numCancionesValidas;
            contarIteracionIndirecta(metricas); // rand()
            agregarMemoriaVariable(metricas, sizeof(int)); // r
            
            if (!used[r]) {
                used[r] = true;
                sesionAleatoria[chosen++] = listaFavoritos[r];
            }
        }
        
        // Reproducir lista aleatoria
        int iter = 0, mem = 0;
        agregarMemoriaVariable(metricas, sizeof(int) * 2); // iter, mem
        
        reproducirLista(sesionAleatoria, K, nullptr, esPremium, iter, mem);
        contarIteracionIndirecta(metricas); // llamada a reproducirLista
        
    } else {
        // Modo secuencial
        int iter = 0, mem = 0;
        agregarMemoriaVariable(metricas, sizeof(int) * 2); // iter, mem
        
        reproducirLista(listaFavoritos, numCancionesValidas, nullptr, esPremium, iter, mem);
        contarIteracionIndirecta(metricas); // llamada a reproducirLista
    }
    
    // Limpiar memoria dinámica si se usó
    if (!useStack) {
        delete[] listaFavoritos;
    }
    
    finalizarMedicionRecursos(metricas, "REPRODUCIR FAVORITOS USUARIO SEGUIDO");
}


