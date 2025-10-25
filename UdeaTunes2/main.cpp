#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "config.h"
#include "usuario.h"
#include "interfaz.h"
#include "artistas.h"
#include "album.h"
#include "cancion.h"

using namespace std;

// Prototipos de funciones
bool mostrarMenuParaUsuario(Usuario* u, Usuario users[], int nUsers, Cancion canciones[], int nCanciones, Interfaz &interfaz);
void mostrarCancionesDisponibles(Cancion canciones[], int nCanciones);

// ----------------------------------------------------------
int main() {
    srand((unsigned)time(nullptr));

    static Usuario users[MAX_USERS];
    static Cancion canciones[MAX_SONGS];
    Interfaz interfaz; // Nueva clase interfaz

    // Cargar archivos de datos usando funciones de Interfaz
    int nUsers = interfaz.cargarUsuariosDesdeArchivo("C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/users.txt", users, MAX_USERS);
    int nCanciones = interfaz.cargarCancionesDesdeArchivo("C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/songs.txt", canciones, MAX_SONGS);

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

        // ---------------- OPCIONES DISPONIBLES ----------------
        switch(opcion) {
        case 1: {
            // Reproducción aleatoria con nuevo sistema
            int iter = 0, mem = 0;
            bool esPremium = (strcmp(u->getTipo(), "Premium") == 0);

            cout << "Reproduciendo canciones aleatoriamente con el nuevo sistema...\n";
            interfaz.reproducirAleatoria(canciones, nCanciones, u, esPremium, iter, mem);
            iterCountTotal += iter;
            memoriaTotal += mem;
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
                    // Editar favoritos usando ID de canción
                    cout << "\n=== EDITAR FAVORITOS ===\n";
                    cout << "Ingrese el ID de la cancion: ";
                    long idCancion;
                    cin >> idCancion;

                    // Buscar la canción por ID
                    Cancion* cancionEncontrada = interfaz.buscarCancionPorId(canciones, nCanciones, idCancion);
                    
                    if (cancionEncontrada == nullptr) {
                        cout << "No se encontro ninguna cancion con ID: " << idCancion << "\n";
                    } else {
                        // Mostrar información de la canción en el formato solicitado
                        cout << "\n" << cancionEncontrada->getTitulo() << "\n";
                        cout << "Artista: " << cancionEncontrada->getArtista() << "\n";
                        cout << "Album: " << cancionEncontrada->getAlbum() << "\n";
                        cout << "Duracion: " << cancionEncontrada->getDuracion() << " segundos\n";
                        
                        // Verificar si ya está en favoritos
                        bool yaEsFavorito = u->existeFavorito(idCancion);
                        
                        if (yaEsFavorito) {
                            cout << "\nEsta cancion YA esta en tu lista de favoritos.\n";
                            cout << "¿Deseas eliminarla? (1=Si, 0=No): ";
                            int eliminar;
                            cin >> eliminar;
                            
                            if (eliminar == 1) {
                                if (u->eliminarFavorito(idCancion)) {
                                    cout << "Cancion eliminada de favoritos exitosamente.\n";
                                } else {
                                    cout << "Error al eliminar la cancion de favoritos.\n";
                                }
                            }
                        } else {
                            cout << "\nEsta cancion NO esta en tu lista de favoritos.\n";
                            cout << "¿Deseas agregarla? (1=Si, 0=No): ";
                            int agregar;
                            cin >> agregar;
                            
                            if (agregar == 1) {
                                if (u->agregarFavorito(idCancion)) {
                                    cout << "Cancion agregada a favoritos exitosamente.\n";
                                } else {
                                    cout << "No se pudo agregar la cancion (lista llena o error).\n";
                                }
                            }
                        }

                        // Mostrar lista actualizada de favoritos
                        cout << "\n=== LISTA ACTUAL DE FAVORITOS (" << u->getNumFavoritos() << "/" << MAX_FAVORITES << ") ===\n";
                        if (u->getNumFavoritos() == 0) {
                            cout << "Tu lista de favoritos esta vacia.\n";
                        } else {
                            for (int i = 0; i < u->getNumFavoritos(); i++) {
                                long fid = u->obtenerFavoritoPorIndice(i);
                                Cancion* fc = interfaz.buscarCancionPorId(canciones, nCanciones, fid);
                                if (fc) {
                                    cout << (i + 1) << ". ID:" << fc->getId() << " - " 
                                         << fc->getTitulo() << " (" << fc->getArtista() << ")\n";
                                }
                            }
                        }
                    }
                }
                else if (sub == 2) {
                    // Ver todas las canciones disponibles
                    mostrarCancionesDisponibles(canciones, nCanciones);
                }
                else if (sub == 3) {
                    int iterSeguir = 0;
                    interfaz.seguirUsuario(u, users, nUsers, canciones, nCanciones, iterSeguir);
                    iterCountTotal += iterSeguir;
                }
                else if (sub == 4) {
                    int nFav = u->getNumFavoritos();
                    if (nFav == 0) {
                        cout << "Tu lista de favoritos esta vacia.\n";
                    } else {
                        Cancion* lista[1000];
                        int nLista = 0;
                        for (int i = 0; i < nFav; i++) {
                            long id = u->obtenerFavoritoPorIndice(i);
                            Cancion* c = interfaz.buscarCancionPorId(canciones, nCanciones, id);
                            if (c) lista[nLista++] = c;
                        }

                        if (nLista == 0) {
                            cout << "No hay canciones validas para reproducir.\n";
                        } else {
                            cout << "Reproducir en orden (0) o aleatorio (1)? ";
                            int modo;
                            cin >> modo;
                            int iter = 0, mem = 0;

                            if (modo == 1) {
                                int K = (nLista < 5 ? nLista : 5);
                                Cancion* ses[5];
                                bool used[1000] = {false};
                                int chosen = 0;
                                while (chosen < K) {
                                    int r = rand() % nLista;
                                    if (!used[r]) {
                                        used[r] = true;
                                        ses[chosen++] = lista[r];
                                    }
                                }
                                bool esPremium = (strcmp(u->getTipo(), "Premium") == 0);
                                interfaz.reproducirLista(ses, K, u, esPremium, iter, mem);
                            } else {
                                bool esPremium = (strcmp(u->getTipo(), "Premium") == 0);
                                interfaz.reproducirLista(lista, nLista, u, esPremium, iter, mem);
                            }
                            iterCountTotal += iter;
                            memoriaTotal += mem;
                        }
                    }
                }
                else if (sub == 5) {
                    // Reproducir favoritos de usuario seguido
                    interfaz.mostrarUsuariosSeguidos();
                    
                    cout << "\nIngrese el nombre del usuario seguido: ";
                    char nombreUsuario[50];
                    cin >> nombreUsuario;
                    
                    int iter = 0, mem = 0;
                    bool esPremium = (strcmp(u->getTipo(), "Premium") == 0);
                    interfaz.reproducirFavoritosUsuarioSeguido(nombreUsuario, users, nUsers, 
                                                             canciones, nCanciones, esPremium, iter, mem);
                    iterCountTotal += iter;
                    memoriaTotal += mem;
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
// Función para mostrar canciones disponibles
void mostrarCancionesDisponibles(Cancion canciones[], int nCanciones) {
    cout << "\n=== CANCIONES DISPONIBLES ===\n";
    for (int i = 0; i < nCanciones; i++) {
        cout << "ID:" << canciones[i].getId() << " - " << canciones[i].getTitulo() << " - "
             << canciones[i].getArtista() << " - " << canciones[i].getAlbum()
             << " (" << canciones[i].getDuracion() << "s)\n";
    }
}
