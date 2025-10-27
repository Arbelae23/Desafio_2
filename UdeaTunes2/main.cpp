#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "config.h"
#include "usuario.h"
#include "interfaz.h"
#include "cancion.h"
#include "album.h"
#include "artistas.h"
#include "playlist.h"

using namespace std;

// Prototipos de funciones
bool mostrarMenuParaUsuario(Usuario* u, Usuario users[], int nUsers, Cancion canciones[], int nCanciones, Interfaz &interfaz);
void mostrarCancionesDisponibles(Cancion canciones[], int nCanciones);

// ----------------------------------------------------------
int main() {
    srand((unsigned)time(nullptr));

    static Usuario users[MAX_USERS];
    static Cancion canciones[MAX_SONGS];
    static Album albunes[MAX_ALBUMS];  // Agregar array de álbumes
    Artista* artistas = new Artista[MAX_ARTISTS];  // Array dinámico para evitar stack overflow
    static Playlist playlists[MAX_PLAYLISTS];  // Agregar array de playlists
    Interfaz interfaz; // Nueva clase interfaz

    // Cargar archivos de datos usando funciones de Interfaz
    int nUsers = interfaz.cargarUsuariosDesdeArchivo("C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/users.txt", users, MAX_USERS);
    int nCanciones = interfaz.cargarCancionesDesdeArchivo("C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/songs.txt", canciones, MAX_SONGS);
    int nPlaylists = interfaz.cargarPlaylistsDesdeArchivo("C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/listaRepro.txt", playlists, MAX_PLAYLISTS, canciones, nCanciones);
    int nAlbunes = interfaz.cargarAlbunesDesdeArchivo("C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/albumes.txt", albunes, MAX_ALBUMS);
    int nArtistas = interfaz.cargarArtistasDesdeArchivo("C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/artistas.txt", artistas, MAX_ARTISTS);

    // Vincular datos despues de cargar todo
    interfaz.vincularCancionesConArtistas(canciones, nCanciones, artistas, nArtistas);
    interfaz.vincularCancionesConAlbumes(canciones, nCanciones, albunes, nAlbunes);
    interfaz.establecerCancionesSingle(canciones, nCanciones);

    // Si no hay archivos, usar datos de prueba
    if (nUsers == 0) {
        cout << "Usando datos de prueba para usuarios\n";
        users[0].setDatos("admin", "1234", "Premium");
        users[1].setDatos("juan", "abcd", "Free");
        users[2].setDatos("maria", "12345", "Premium");
        users[3].setDatos("carlos", "pass", "Free");
        nUsers = 4;
    }

    if (nCanciones == 0) {
        cout << "Usando datos de prueba para canciones\n";
        Cancion c;

        // Cancion 1
        c.setDatos(100010101, "A tu lado", "Claudia Lorelle", "Vuelo Libre", "Pop", 210);
        c.establecerRuta320("/users/storage/claudia_lorelle/audio/a_tu_lado.mp3");
        c.establecerRutaPortada("/users/storage/claudia_lorelle/covers/vuelo_libre.jpg");
        c.establecerCodigoArtista(101);
        canciones[nCanciones++] = c;

        // Cancion 2
        c.setDatos(100010102, "Lugar Secreto", "Claudia Lorelle", "Vuelo Libre", "Pop", 180);
        c.establecerRuta320("/users/storage/claudia_lorelle/audio/lugar_secreto.mp3");
        c.establecerRutaPortada("/users/storage/claudia_lorelle/covers/vuelo_libre.jpg");
        c.establecerCodigoArtista(101);
        canciones[nCanciones++] = c;

        // Cancion 3
        c.setDatos(200020101, "Ola Azul", "Artist 2", "Oceano", "Rock", 200);
        c.establecerRuta320("/users/storage/artist2/audio/ola_azul.mp3");
        c.establecerRutaPortada("/users/storage/artist2/covers/oceano.jpg");
        c.establecerCodigoArtista(102);
        canciones[nCanciones++] = c;

        // Cancion 4
        c.setDatos(300030101, "Noche de Paz", "Artist 3", "Fiestas", "Navidad", 240);
        c.establecerRuta320("/users/storage/artist3/audio/noche_de_paz.mp3");
        c.establecerRutaPortada("/users/storage/artist3/covers/fiestas.jpg");
        c.establecerCodigoArtista(103);
        canciones[nCanciones++] = c;

        // Cancion 5
        c.setDatos(400040101, "Vuela Alto", "Artist 4", "Libertad", "Pop", 195);
        c.establecerRuta320("/users/storage/artist4/audio/vuela_alto.mp3");
        c.establecerRutaPortada("/users/storage/artist4/covers/libertad.jpg");
        c.establecerCodigoArtista(104);
        canciones[nCanciones++] = c;
    }

    bool continuar = true;
    while (continuar) {
        // Inicio de sesión
        cout << MSG_WELCOME << "\n";
        char user[60], pass[60];
        Usuario* usuarioActivo = nullptr;

        while (!usuarioActivo) {
            cout << "Usuario: "; cin >> user;
            cout << "Contrasena: "; cin >> pass;
            int idx = interfaz.buscarUsuarioPorNombre(users, nUsers, user);
            if (idx >= 0 && users[idx].checkPassword(pass)) {
                usuarioActivo = &users[idx];
                cout << MSG_LOGIN << " " << usuarioActivo->getNombre() << " (" << usuarioActivo->getTipo() << ")\n";
            } else {
                cout << MSG_INVALID_CREDENTIALS << "\n";
            }
        }

        // Mostrar menú y gestionar la sesión
        bool salir = mostrarMenuParaUsuario(usuarioActivo, users, nUsers, canciones, nCanciones, interfaz);
        
        // Si el usuario eligió salir completamente
        if (salir) {
            continuar = false;
        } else {
            // Si solo cerró sesión, permitir nuevo login
            cout << "Sesion cerrada. Iniciando nuevo login...\n\n";
        }
    }

    cout << MSG_THANKS << "\n";
    delete[] artistas;  // Liberar memoria del array dinámico
    return 0;
}

// ----------------------------------------------------------
// Menu principal del usuario
bool mostrarMenuParaUsuario(Usuario* u, Usuario users[], int nUsers,
                            Cancion canciones[], int nCanciones, Interfaz &interfaz) {
    int opcion = 0;
    int iterCountTotal = 0;
    int memoriaTotal = 0;
    bool salirCompletamente = false;

    do {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Reproduccion aleatoria\n";
        if (strcmp(u->getTipo(), "Premium") == 0) {
            cout << "2. Mi lista de favoritos\n";
        } else {
            cout << "2. Mi lista de favoritos (Solo Premium)\n";
        }
        cout << "3. Medicion de recursos\n";
        cout << "4. Cerrar sesion\n";
        cout << "5. Salir completamente\n";

        cout << "Opcion: ";
        cin >> opcion;

        // Validar entrada
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = 0; // Valor inválido para continuar el bucle
            cout << "Entrada invalida. Debe ingresar un numero del 1 al 5.\n";
            continue;
        }

        // ---------------- OPCIONES DISPONIBLES ----------------
        switch(opcion) {
        case 1: {
            // Reproducción aleatoria con medición de recursos
            bool esPremium = (strcmp(u->getTipo(), "Premium") == 0);

            cout << "Reproduciendo canciones aleatoriamente...\n";
            interfaz.reproducirAleatoriaConMedicion(canciones, nCanciones, u, esPremium);
            break;
        }

        case 2: {
            if (strcmp(u->getTipo(), "Premium") == 0) {
                // Mi lista de favoritos (solo para Premium)
                int sub;
                do {
                    cout << "\n=== FAVORITOS ===\n";
                    cout << "1. Editar (agregar/eliminar)\n";
                    cout << "2. Ver todas las canciones disponibles\n";
                    cout << "3. Seguir otro usuario\n";
                    cout << "4. Ejecutar mi lista\n";
                    cout << "5. Reproducir favoritos de usuario seguido\n";
                    cout << "6. Volver\n";
                    cout << "Opcion: ";
                    cin >> sub;
                    
                    // Validar entrada
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        sub = 0; // Valor inválido para continuar el bucle
                        cout << "Entrada invalida. Intente nuevamente.\n";
                        continue;
                    }

                if (sub == 1) {
                    // Editar favoritos con medición de recursos
                    interfaz.editarFavoritosConMedicion(u, canciones, nCanciones);
                }
                else if (sub == 2) {
                    // Ver todas las canciones disponibles con medición de recursos
                    interfaz.mostrarCancionesConMedicion(canciones, nCanciones);
                }
                else if (sub == 3) {
                    // Seguir usuario con medición de recursos
                    interfaz.seguirUsuarioConMedicion(u, users, nUsers, canciones, nCanciones);
                }
                else if (sub == 4) {
                    // Ejecutar lista de favoritos con medición de recursos
                    bool esPremium = (strcmp(u->getTipo(), "Premium") == 0);
                    interfaz.ejecutarListaFavoritosConMedicion(u, canciones, nCanciones, esPremium);
                }
                else if (sub == 5) {
                    // Reproducir favoritos de usuario seguido con medición de recursos
                    interfaz.mostrarUsuariosSeguidos(users, nUsers);
                    
                    cout << "\nIngrese el nombre del usuario seguido: ";
                    char nombreUsuario[50];
                    cin >> nombreUsuario;
                    
                    bool esPremium = (strcmp(u->getTipo(), "Premium") == 0);
                    interfaz.reproducirFavoritosUsuarioSeguidoConMedicion(nombreUsuario, users, nUsers, 
                                                                        canciones, nCanciones, esPremium);
                }
                else if (sub != 6) {
                    cout << "Opcion invalida. Seleccione una opcion del 1 al 6.\n";
                }
            } while (sub != 6);
            }
            else {
                cout << "Opcion solo disponible para usuarios Premium.\n";
            }
            break;
        }

        case 3: {
            // Medición de recursos
            int memoria = interfaz.calcularMemoriaUsadaEstimado(users, nUsers, canciones, nCanciones);
            interfaz.medirRecursos(iterCountTotal, memoria);
            break;
        }

        case 4: {
            // Cerrar sesión
            cout << "Cerrando sesion...\n";
            return false; // Retorna false para indicar que solo se cierra sesión
        }
        
        case 5: {
            // Salir completamente
            cout << "Saliendo del sistema...\n";
            return true; // Retorna true para indicar salida completa
        }

        default: {
            cout << "Opcion no valida. Intente nuevamente.\n";
            break;
        }
        }
    } while (opcion != 4 && opcion != 5);
    
    return false; // Por defecto
}

// ----------------------------------------------------------
// Funcion para mostrar canciones disponibles
void mostrarCancionesDisponibles(Cancion canciones[], int nCanciones) {
    cout << "\n=== CANCIONES DISPONIBLES ===\n";
    for (int i = 0; i < nCanciones; i++) {
        cout << "ID:" << canciones[i].getId() << " - " << canciones[i].getTitulo() << " - "
             << canciones[i].getArtista() << " - " << canciones[i].getAlbum()
             << " (" << canciones[i].getDuracion() << "s)\n";
    }
}
