/*
#include "cancion.h"
#include "creditos.h"
#include "album.h"
#include "artistas.h"
#include "playlist.h"
#include "usuario.h"
#include "interfaz.h"
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    cout << "\n" << string(80, '=') << "\n";
    cout << "           UDEATUNES - SISTEMA FASE 1 DE STREAMING\n";
    cout << string(80, '=') << "\n";


    // 1. CREAR ARTISTAS


    cout << "\n1. Creando artistas...\n";

    Artista* pink_floyd = new Artista("Pink Floyd", 12345, 0, "Reino Unido");
    pink_floyd->establecerCantidadSeguidores(50000000);
    pink_floyd->establecerPosicionTendencias(10);

    Artista* the_beatles = new Artista("The Beatles", 54321, 0, "Reino Unido");
    the_beatles->establecerCantidadSeguidores(80000000);
    the_beatles->establecerPosicionTendencias(1);

    cout << "   -> 2 artistas creados\n";


    // 2. CREAR ALBUMES Y CANCIONES

    cout << "\n2. Creando albumes y canciones...\n";

    // Album de Pink Floyd
    Album* dark_side = new Album("The Dark Side of the Moon", 73,
                                 "Harvest Records",
                                 "/storage/pink_floyd/images/dark_side_moon.png",
                                 1, 3, 1973);
    dark_side->establecerPuntuacion(10);
    dark_side->agregarGenero("Rock");
    dark_side->agregarGenero("Musica Clasica");

    // Canciones del album
    Cancion* cancion1 = new Cancion("Speak to Me", "Pink Floyd",
                                    "The Dark Side of the Moon", "Rock",
                                    90, 1973);
    cancion1->agregarCompositor("Nick", "Mason", "COMP001122");

    Cancion* cancion2 = new Cancion("Time", "Pink Floyd",
                                    "The Dark Side of the Moon", "Rock",
                                    421, 1973);
    cancion2->agregarCompositor("Roger", "Waters", "COMP667788");

    Cancion* cancion3 = new Cancion("Money", "Pink Floyd",
                                    "The Dark Side of the Moon", "Rock",
                                    382, 1973);
    cancion3->agregarCompositor("Roger", "Waters", "COMP667788");

    dark_side->agregarCancion(cancion1);
    dark_side->agregarCancion(cancion2);
    dark_side->agregarCancion(cancion3);

    // Agregar album al artista
    pink_floyd->agregarAlbum(dark_side);

    // Album de The Beatles
    Album* abbey_road = new Album("Abbey Road", 69,
                                  "Apple Records",
                                  "/storage/beatles/images/abbey_road.png",
                                  26, 9, 1969);
    abbey_road->establecerPuntuacion(10);
    abbey_road->agregarGenero("Rock");
    abbey_road->agregarGenero("Pop");

    Cancion* cancion4 = new Cancion("Come Together", "The Beatles",
                                    "Abbey Road", "Rock", 259, 1969);
    cancion4->agregarCompositor("John", "Lennon", "COMP778899");

    Cancion* cancion5 = new Cancion("Here Comes The Sun", "The Beatles",
                                    "Abbey Road", "Pop", 185, 1969);
    cancion5->agregarCompositor("George", "Harrison", "COMP223344");

    abbey_road->agregarCancion(cancion4);
    abbey_road->agregarCancion(cancion5);

    the_beatles->agregarAlbum(abbey_road);

    cout << "   -> 2 albumes con 5 canciones creados\n";


    // 3. CREAR CATALOGO DE CANCIONES


    const int TOTAL_CANCIONES = 5;
    Cancion* catalogo_canciones[TOTAL_CANCIONES] = {
        cancion1, cancion2, cancion3, cancion4, cancion5
    };


    // 4. CREAR USUARIOS


    cout << "\n3. Creando usuarios...\n";

    // Usuario Premium
    Usuario* usuario_premium = new Usuario("rockfan2025", "pass123",
                                           Usuario::PREMIUM);
    usuario_premium->establecerCiudad("Bucaramanga");
    usuario_premium->establecerPais("Colombia");
    usuario_premium->establecerFechaInscripcion("01/10/2025");

    // Usuario Estandar
    Usuario* usuario_estandar = new Usuario("musiclover", "pass456",
                                            Usuario::ESTANDAR);
    usuario_estandar->establecerCiudad("Bogota");
    usuario_estandar->establecerPais("Colombia");
    usuario_estandar->establecerFechaInscripcion("15/09/2025");

    cout << "   -> Usuario Premium: " << usuario_premium->obtenerNickname() << "\n";
    cout << "   -> Usuario Estandar: " << usuario_estandar->obtenerNickname() << "\n";


    // 5. CREAR PLAYLIST PARA USUARIO PREMIUM


    cout << "\n4. Creando lista de favoritos para usuario Premium...\n";

    usuario_premium->crearListaFavoritos("Mis Clasicos de Rock");
    Playlist* favoritos = usuario_premium->obtenerListaFavoritos();

    if (favoritos) {
        favoritos->agregarCancion(cancion2);  // Time
        favoritos->agregarCancion(cancion3);  // Money
        favoritos->agregarCancion(cancion5);  // Here Comes The Sun

        cout << "   -> " << favoritos->obtenerCantidadCanciones()
             << " canciones agregadas a favoritos\n";
    }


    // 6. CREAR INTERFAZ Y CONFIGURAR PUBLICIDAD


    cout << "\n5. Configurando sistema de publicidad...\n";

    Interfaz interfaz;

    // Agregar mensajes publicitarios
    interfaz.agregarMensajePublicitario(
        "Descubre los nuevos audifonos inalambricos con cancelacion de ruido. Calidad premium para tu musica!",
        'A'  // Categoria AAA
        );

    interfaz.agregarMensajePublicitario(
        "Aprovecha el 50% de descuento en tu suscripcion Premium. Musica sin limites!",
        'A'  // Categoria AAA
        );

    interfaz.agregarMensajePublicitario(
        "Visita nuestra tienda online y encuentra los mejores productos para amantes de la musica.",
        'B'  // Categoria B
        );

    interfaz.agregarMensajePublicitario(
        "Conoce los proximos conciertos en tu ciudad. No te pierdas a tus artistas favoritos en vivo!",
        'C'  // Categoria C
        );

    interfaz.agregarMensajePublicitario(
        "Nuevo album disponible! Descubre lo ultimo de tus artistas favoritos en UdeATunes.",
        'B'  // Categoria B
        );

    cout << "   -> " << interfaz.obtenerCantidadMensajes()
         << " mensajes publicitarios agregados\n";


    // 7. DEMOSTRAR FUNCIONALIDADES


    cout << "\n6. Demostracion de funcionalidades:\n";
    cout << string(80, '-') << "\n";

    // Mostrar perfil de usuarios
    cout << "\nPERFIL USUARIO PREMIUM \n";
    usuario_premium->mostrarInformacionCompleta();

    cout << "\n PERFIL USUARIO ESTANDAR \n";
    usuario_estandar->mostrarInformacionCompleta();

    // Mostrar artistas
    cout << "\n ARTISTA 1 \n";
    pink_floyd->mostrarInformacionCompleta();
    pink_floyd->mostrarAlbumes();

    cout << "\n ARTISTA 2 \n";
    the_beatles->mostrarInformacionCompleta();
    the_beatles->mostrarAlbumes();

    // Mostrar albumes
    cout << "\n";
    dark_side->mostrarInformacionCompleta();

    cout << "\n";
    abbey_road->mostrarInformacionCompleta();

    // Mostrar playlist
    if (favoritos) {
        favoritos->mostrarCanciones();
    }


    // 8. SIMULACION DE REPRODUCCION

    cout << "\n\n7. SIMULACION DE REPRODUCCION:\n";
    cout << string(80, '=') << "\n";

    cout << "\n REPRODUCCION CON USUARIO ESTANDAR (con publicidad) \n";
    cout << "Reproduciendo 3 canciones...\n";
    cout << "\nPresiona ENTER para comenzar...";
    cin.get();

    // Reproducir 3 canciones como usuario estandar
    for (int i = 0; i < 3; i++) {
        interfaz.reproducirCancion(catalogo_canciones[i], *usuario_estandar, true);
        cout << "\n";
    }

    cout << "\n REPRODUCCION CON USUARIO PREMIUM (sin publicidad) \n";
    cout << "Reproduciendo 2 canciones...\n";
    cout << "\nPresiona ENTER para continuar...";
    cin.get();

    // Reproducir 2 canciones como usuario premium
    for (int i = 0; i < 2; i++) {
        interfaz.reproducirCancion(catalogo_canciones[i], *usuario_premium, true);
        cout << "\n";
    }


    // 9. PRUEBA DE SEGUIR USUARIO


    cout << "\n8. PRUEBA DE SEGUIR A OTRO USUARIO:\n";
    cout << string(80, '-') << "\n";

    // Crear segundo usuario premium
    Usuario* otro_premium = new Usuario("melodylover", "pass789", Usuario::PREMIUM);
    otro_premium->crearListaFavoritos("Mis Favoritos");
    otro_premium->obtenerListaFavoritos()->agregarCancion(cancion1);
    otro_premium->obtenerListaFavoritos()->agregarCancion(cancion4);

    cout << "\nUsuario '" << otro_premium->obtenerNickname()
         << "' tiene " << otro_premium->obtenerListaFavoritos()->obtenerCantidadCanciones()
         << " canciones en favoritos\n";

    cout << "\nUsuario '" << usuario_premium->obtenerNickname()
         << "' seguira a '" << otro_premium->obtenerNickname() << "'\n\n";

    usuario_premium->seguirUsuario(otro_premium);

    cout << "\nAhora '" << usuario_premium->obtenerNickname()
         << "' tiene " << usuario_premium->obtenerListaFavoritos()->obtenerCantidadCanciones()
         << " canciones en favoritos\n";


    // 10. LIMPIEZA DE MEMORIA


    cout << "\n\n9. Liberando memoria...\n";

    delete cancion1;
    delete cancion2;
    delete cancion3;
    delete cancion4;
    delete cancion5;

    delete dark_side;
    delete abbey_road;

    delete pink_floyd;
    delete the_beatles;

    delete usuario_premium;
    delete usuario_estandar;
    delete otro_premium;

    cout << "   -> Memoria liberada correctamente\n";



    cout << "\n" << string(80, '=') << "\n";

    return 0;
}
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <conio.h>   // Para _kbhit() y _getch()
#include <windows.h> // Para Sleep()

using namespace std;

struct Usuario {
    char nombreUsuario[30];
    char contrasena[30];
    char tipoCuenta[15];
    int contadorCanciones;        // Contador de canciones reproducidas
    int cancionesHastaPublicidad; // Canciones hasta próxima publicidad
};

struct Cancion {
    char titulo[100];
    char artista[100];
    char album[100];
    int duracionSegundos;
};

const int MAX_CANCIONES = 20;
Cancion catalogoCanciones[MAX_CANCIONES];
int totalCanciones = 0;

const int MAX_PUBLICIDAD = 10;
char mensajesPublicidad[MAX_PUBLICIDAD][200];
int totalPublicidad = 0;


void inicializarCatalogo() {
    // Agregar canciones de ejemplo
    strcpy(catalogoCanciones[0].titulo, "Bohemian Rhapsody");
    strcpy(catalogoCanciones[0].artista, "Queen");
    strcpy(catalogoCanciones[0].album, "A Night at the Opera");
    catalogoCanciones[0].duracionSegundos = 15; // 15 segundos para prueba

    strcpy(catalogoCanciones[1].titulo, "Stairway to Heaven");
    strcpy(catalogoCanciones[1].artista, "Led Zeppelin");
    strcpy(catalogoCanciones[1].album, "Led Zeppelin IV");
    catalogoCanciones[1].duracionSegundos = 12;

    strcpy(catalogoCanciones[2].titulo, "Imagine");
    strcpy(catalogoCanciones[2].artista, "John Lennon");
    strcpy(catalogoCanciones[2].album, "Imagine");
    catalogoCanciones[2].duracionSegundos = 10;

    strcpy(catalogoCanciones[3].titulo, "Hotel California");
    strcpy(catalogoCanciones[3].artista, "Eagles");
    strcpy(catalogoCanciones[3].album, "Hotel California");
    catalogoCanciones[3].duracionSegundos = 13;

    strcpy(catalogoCanciones[4].titulo, "Smells Like Teen Spirit");
    strcpy(catalogoCanciones[4].artista, "Nirvana");
    strcpy(catalogoCanciones[4].album, "Nevermind");
    catalogoCanciones[4].duracionSegundos = 11;

    strcpy(catalogoCanciones[5].titulo, "Sweet Child O' Mine");
    strcpy(catalogoCanciones[5].artista, "Guns N' Roses");
    strcpy(catalogoCanciones[5].album, "Appetite for Destruction");
    catalogoCanciones[5].duracionSegundos = 14;

    strcpy(catalogoCanciones[6].titulo, "Billie Jean");
    strcpy(catalogoCanciones[6].artista, "Michael Jackson");
    strcpy(catalogoCanciones[6].album, "Thriller");
    catalogoCanciones[6].duracionSegundos = 12;

    strcpy(catalogoCanciones[7].titulo, "Wonderwall");
    strcpy(catalogoCanciones[7].artista, "Oasis");
    strcpy(catalogoCanciones[7].album, "(What's the Story) Morning Glory?");
    catalogoCanciones[7].duracionSegundos = 10;

    strcpy(catalogoCanciones[8].titulo, "Yesterday");
    strcpy(catalogoCanciones[8].artista, "The Beatles");
    strcpy(catalogoCanciones[8].album, "Help!");
    catalogoCanciones[8].duracionSegundos = 8;

    strcpy(catalogoCanciones[9].titulo, "Losing My Religion");
    strcpy(catalogoCanciones[9].artista, "R.E.M.");
    strcpy(catalogoCanciones[9].album, "Out of Time");
    catalogoCanciones[9].duracionSegundos = 11;

    totalCanciones = 10;
}

void inicializarPublicidad() {
    strcpy(mensajesPublicidad[0], "¡OFERTA ESPECIAL! Actualiza a Premium y disfruta sin interrupciones.");
    strcpy(mensajesPublicidad[1], "¿Cansado de la publicidad? Hazte Premium por solo $9.99 al mes.");
    strcpy(mensajesPublicidad[2], "Premium: Musica sin limites, sin anuncios, sin interrupciones.");
    strcpy(mensajesPublicidad[3], "¡Prueba Premium GRATIS por 30 dias! Sin anuncios, sin esperas.");
    strcpy(mensajesPublicidad[4], "Con Premium: Calidad HD, descargas ilimitadas y cero publicidad.");
    totalPublicidad = 5;
}


int contarLineas(const char* archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo para contar lineas." << endl;
        return 0;
    }

    int count = 0;
    char buffer[200];
    while (file.getline(buffer, 200)) {
        if (strlen(buffer) > 0) count++;
    }

    file.close();
    return count;
}

Usuario* cargarUsuarios(const char* archivo, int& cantidad) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo de usuarios." << endl;
        return nullptr;
    }

    cantidad = contarLineas(archivo);
    Usuario* usuarios = new Usuario[cantidad];

    char linea[200];
    int i = 0;

    while (file.getline(linea, 200)) {
        char* token = strtok(linea, ",");
        if (token != nullptr) strcpy(usuarios[i].nombreUsuario, token);

        token = strtok(nullptr, ",");
        if (token != nullptr) strcpy(usuarios[i].contrasena, token);

        token = strtok(nullptr, ",");
        if (token != nullptr) strcpy(usuarios[i].tipoCuenta, token);

        // Inicializar contadores
        usuarios[i].contadorCanciones = 0;
        usuarios[i].cancionesHastaPublicidad = 2;

        i++;
    }

    file.close();
    return usuarios;
}
// FUNCION DE LOGIN

Usuario* login(Usuario* usuarios, int cantidad) {
    char user[30];
    char pass[30];

    while (true) {
        cout << "\n=== INICIO DE SESION ===" << endl;
        cout << "Usuario: ";
        cin >> user;
        cout << "Contrasena: ";
        cin >> pass;

        for (int i = 0; i < cantidad; i++) {
            if (strcmp(usuarios[i].nombreUsuario, user) == 0 &&
                strcmp(usuarios[i].contrasena, pass) == 0) {
                cout << "\nBienvenido " << usuarios[i].nombreUsuario << " ("
                     << usuarios[i].tipoCuenta << ")" << endl;
                return &usuarios[i];
            }
        }

        cout << "\nUsuario o contrasena incorrectos. Intente nuevamente.\n" << endl;
    }
}

// FUNCIONES DE PUBLICIDAD

void mostrarPublicidad() {
    int indice = rand() % totalPublicidad;

    cout << "\n" << string(70, '*') << endl;
    cout << "                        PUBLICIDAD" << endl;
    cout << string(70, '*') << endl;
    cout << mensajesPublicidad[indice] << endl;
    cout << string(70, '*') << endl;

    cout << "\nEsperando 3 segundos..." << endl;
    Sleep(3000);
}

// FUNCION DE REPRODUCCION CON CONTROL EN TIEMPO REAL

void reproducirCancionConControles(Cancion* cancion, Usuario& usuario, bool& adelantada, bool& retroceder) {
    if (!cancion) return;

    adelantada = false;
    retroceder = false;
    int tiempo = cancion->duracionSegundos;
    bool pausado = false;
    bool esPremium = strcmp(usuario.tipoCuenta, "Premium") == 0;

    system("cls");

    cout << "\n" << string(70, '=') << endl;
    cout << "                    REPRODUCIENDO" << endl;
    cout << string(70, '=') << endl;
    cout << "Titulo: " << cancion->titulo << endl;
    cout << "Artista: " << cancion->artista << endl;
    cout << "Album: " << cancion->album << endl;
    cout << "Calidad: " << (esPremium ? "320 kbps" : "128 kbps") << endl;
    cout << string(70, '=') << endl;
    cout << "\nCanciones reproducidas: " << usuario.contadorCanciones << endl;

    if (!esPremium) {
        cout << "Canciones hasta proxima publicidad: " << usuario.cancionesHastaPublicidad << endl;
    }

    cout << "\nCONTROLES:" << endl;
    cout << "  [P] = Pausar/Reanudar reproduccion" << endl;

    if (esPremium) {
        cout << "  [N] = Siguiente cancion" << endl;
        cout << "  [A] = Cancion anterior" << endl;
    }

    cout << string(70, '-') << endl;

    while (tiempo >= 0) {
        // Mostrar tiempo restante
        if (pausado) {
            cout << "\r[PAUSADO] Tiempo restante: " << tiempo << " segundos    ";
        } else {
            cout << "\rTiempo restante: " << tiempo << " segundos    ";
        }
        cout.flush();

        // Esperar 1 segundo dividido en intervalos pequeños para detectar teclas
        for (int i = 0; i < 10; i++) {
            Sleep(100);

            if (_kbhit()) {
                char tecla = _getch();

                if (tecla == 'p' || tecla == 'P') {
                    pausado = !pausado;
                    if (pausado) {
                        cout << "\n\n[Reproduccion pausada - Presiona P para reanudar]" << endl;
                    } else {
                        cout << "\n\n[Reproduccion reanudada]" << endl;
                    }
                    Sleep(1000);
                    // Redibujar pantalla
                    system("cls");
                    cout << "\n" << string(70, '=') << endl;
                    cout << "                    " << (pausado ? "PAUSADO" : "REPRODUCIENDO") << endl;
                    cout << string(70, '=') << endl;
                    cout << "Titulo: " << cancion->titulo << endl;
                    cout << "Artista: " << cancion->artista << endl;
                    cout << "Album: " << cancion->album << endl;
                    cout << "\nCONTROLES:" << endl;
                    cout << "  [P] = Pausar/Reanudar reproduccion" << endl;
                    if (esPremium) {
                        cout << "  [N] = Siguiente cancion" << endl;
                        cout << "  [A] = Cancion anterior" << endl;
                    }
                    cout << string(70, '-') << endl;
                }
                else if (esPremium && (tecla == 'n' || tecla == 'N')) {
                    cout << "\n\n[Siguiente cancion]" << endl;
                    adelantada = true;
                    Sleep(1000);
                    return;
                }
                else if (esPremium && (tecla == 'a' || tecla == 'A')) {
                    cout << "\n\n[Cancion anterior]" << endl;
                    retroceder = true;
                    Sleep(1000);
                    return;
                }
            }
        }

        // Solo reducir tiempo si no está pausado
        if (!pausado) {
            tiempo--;
        }
    }

    if (!adelantada && !retroceder) {
        cout << "\n\n[Cancion finalizada]" << endl;
        Sleep(1000);
    }
}

// FUNCIONES DE REPRODUCCION ALEATORIA

void reproduccionAleatoria(Usuario& usuario) {
    cout << "\n=== REPRODUCCION ALEATORIA ===" << endl;
    cout << "Reproduciendo 5 canciones aleatorias..." << endl;
    cout << "\nPresiona ENTER para comenzar...";
    cin.ignore();
    cin.get();

    bool esPremium = strcmp(usuario.tipoCuenta, "Premium") == 0;

    // Historial para usuarios Premium (para retroceder)
    const int MAX_HISTORIAL = 10;
    int historial[MAX_HISTORIAL];
    int cantidadHistorial = 0;
    int posicionActual = -1;

    int i = 0;
    while (i < 5) {
        // Verificar si debe ver publicidad ANTES de reproducir
        if (strcmp(usuario.tipoCuenta, "Estandar") == 0) {
            if (usuario.cancionesHastaPublicidad == 0) {
                mostrarPublicidad();
                usuario.cancionesHastaPublicidad = 2;
            }
        }

        int indice;

        // Si está retrocediendo en el historial (Premium)
        if (esPremium && posicionActual >= 0 && posicionActual < cantidadHistorial) {
            indice = historial[posicionActual];
        } else {
            // Seleccionar cancion aleatoria nueva
            indice = rand() % totalCanciones;

            // Agregar al historial si es Premium
            if (esPremium) {
                if (cantidadHistorial < MAX_HISTORIAL) {
                    historial[cantidadHistorial] = indice;
                    posicionActual = cantidadHistorial;
                    cantidadHistorial++;
                } else {
                    // Desplazar historial
                    for (int j = 0; j < MAX_HISTORIAL - 1; j++) {
                        historial[j] = historial[j + 1];
                    }
                    historial[MAX_HISTORIAL - 1] = indice;
                    posicionActual = MAX_HISTORIAL - 1;
                }
            }
        }

        Cancion* cancion = &catalogoCanciones[indice];

        bool adelantada = false;
        bool retroceder = false;
        reproducirCancionConControles(cancion, usuario, adelantada, retroceder);

        if (retroceder && esPremium) {
            // Retroceder en el historial
            if (posicionActual > 0) {
                posicionActual--;
                i--; // No incrementar i para no contar como canción adicional
            } else {
                cout << "\nNo hay cancion anterior" << endl;
                Sleep(1000);
            }
        } else if (adelantada && esPremium) {
            // Adelantar (solo Premium)
            if (posicionActual < cantidadHistorial - 1) {
                posicionActual++;
            } else {
                posicionActual = -1; // Siguiente será nueva canción
            }

            // Incrementar contador normalmente
            usuario.contadorCanciones++;
            usuario.cancionesHastaPublicidad--;
        } else {
            // Canción terminó normalmente
            usuario.contadorCanciones++;
            usuario.cancionesHastaPublicidad--;

            if (esPremium) {
                posicionActual = -1; // Siguiente será nueva canción
            }
        }

        i++;

        // Pequeña pausa entre canciones
        if (i < 5) {
            Sleep(500);
        }
    }

    cout << "\n\nReproduccion aleatoria finalizada." << endl;
    cout << "Total de canciones reproducidas: " << usuario.contadorCanciones << endl;
    cout << "\nPresiona ENTER para continuar...";
    cin.get();
}

// FUNCIONES DE REPRODUCCION CON PUBLICIDAD (SOLO FREE)

void reproduccionAleatoriaConPublicidad(Usuario& usuario) {
    cout << "\n=== REPRODUCCION ALEATORIA (Con publicidad) ===" << endl;
    cout << "Reproduciendo 5 canciones aleatorias..." << endl;
    cout << "NOTA: Se mostrara publicidad cada 2 canciones" << endl;
    cout << "\nPresiona ENTER para comenzar...";
    cin.ignore();
    cin.get();

    for (int i = 0; i < 5; i++) {
        // Verificar si debe ver publicidad ANTES de reproducir
        if (usuario.cancionesHastaPublicidad == 0) {
            mostrarPublicidad();
            usuario.cancionesHastaPublicidad = 2;
        }

        // Seleccionar cancion aleatoria
        int indice = rand() % totalCanciones;
        Cancion* cancion = &catalogoCanciones[indice];

        bool adelantada = false;
        bool retroceder = false; // No se usa en Free, pero necesario para la firma
        reproducirCancionConControles(cancion, usuario, adelantada, retroceder);

        // Siempre incrementar contador (Free solo tiene pausa/reproducir)
        usuario.contadorCanciones++;
        usuario.cancionesHastaPublicidad--;

        // Pequeña pausa entre canciones
        if (i < 4) {
            Sleep(500);
        }
    }

    cout << "\n\nReproduccion aleatoria finalizada." << endl;
    cout << "Total de canciones reproducidas: " << usuario.contadorCanciones << endl;
    cout << "\nPresiona ENTER para continuar...";
    cin.get();
}


// FUNCION DE MEDICION DE RECURSOS (Incompleta)

void medicionRecursos(Usuario& usuario) {
    cout << "\n=== MEDICION DEL CONSUMO DE RECURSOS ===" << endl;
    cout << "\nUsuario: " << usuario.nombreUsuario << endl;
    cout << "Tipo de cuenta: " << usuario.tipoCuenta << endl;
    cout << "Calidad de audio: " << (strcmp(usuario.tipoCuenta, "Premium") == 0 ? "320 kbps" : "128 kbps") << endl;
    cout << "\nCanciones reproducidas en esta sesion: " << usuario.contadorCanciones << endl;

    int consumoEstimado = usuario.contadorCanciones * (strcmp(usuario.tipoCuenta, "Premium") == 0 ? 8 : 3);
    cout << "Consumo estimado de datos: " << consumoEstimado << " MB" << endl;

    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Menus

void menuPremium(Usuario& usuario) {
    int opcion;

    do {
        system("cls");
        cout << "\n=== MENU PREMIUM ===" << endl;
        cout << "Usuario: " << usuario.nombreUsuario << endl;
        cout << "Canciones reproducidas: " << usuario.contadorCanciones << endl;
        cout << "\n1. Reproduccion aleatoria" << endl;
        cout << "2. Mi lista de favoritos" << endl;
        cout << "3. Medicion del consumo de recursos" << endl;
        cout << "4. Cerrar sesion" << endl;
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            reproduccionAleatoria(usuario);
            break;
        case 2:
            cout << "\n[Funcionalidad de lista de favoritos no implementada]\n";
            cout << "Presiona ENTER para continuar...";
            cin.ignore();
            cin.get();
            break;
        case 3:
            medicionRecursos(usuario);
            break;
        case 4:
            cout << "\nCerrando sesion...\n";
            break;
        default:
            cout << "\nOpcion no valida. Intente nuevamente.\n";
            Sleep(1500);
        }
    } while (opcion != 4);
}

void menuFree(Usuario& usuario) {
    int opcion;

    do {
        system("cls");
        cout << "\n=== MENU FREE ===" << endl;
        cout << "Usuario: " << usuario.nombreUsuario << endl;
        cout << "Canciones reproducidas: " << usuario.contadorCanciones << endl;
        cout << "Canciones hasta proxima publicidad: " << usuario.cancionesHastaPublicidad << endl;
        cout << "\n1. Reproduccion aleatoria (con publicidad)" << endl;
        cout << "2. Medicion del consumo de recursos" << endl;
        cout << "3. Cerrar sesion" << endl;
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            reproduccionAleatoriaConPublicidad(usuario);
            break;
        case 2:
            medicionRecursos(usuario);
            break;
        case 3:
            cout << "\nCerrando sesion...\n";
            break;
        default:
            cout << "\nOpcion no valida. Intente nuevamente.\n";
            Sleep(1500);
        }
    } while (opcion != 3);
}

int main() {
    srand(time(0));

    // Inicializar catálogo y publicidad
    inicializarCatalogo();
    inicializarPublicidad();

    int cantidad = 0;
    const char* rutaArchivo = "C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/DataUser.txt";

    Usuario* usuarios = cargarUsuarios(rutaArchivo, cantidad);
    if (!usuarios) return 1;

    bool continuarPrograma = true;

    while (continuarPrograma) {
        Usuario* usuarioActivo = login(usuarios, cantidad);

        // Reiniciar contadores al iniciar sesión
        usuarioActivo->contadorCanciones = 0;
        usuarioActivo->cancionesHastaPublicidad = 2;

        Sleep(1000);

        if (strcmp(usuarioActivo->tipoCuenta, "Premium") == 0) {
            menuPremium(*usuarioActivo);
        }
        else {
            menuFree(*usuarioActivo);
        }

        cout << "\nRegresando al inicio de sesion...\n";
        Sleep(1500);
    }

    delete[] usuarios;
    return 0;
}

