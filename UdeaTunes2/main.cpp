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
void mostrarMenuParaUsuario(Usuario* u, Usuario users[], int nUsers, Cancion canciones[], int nCanciones, Interfaz &interfaz);

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
        c.setDatos("A tu lado", 100010101, 210, "/users/storage/claudia_lorelle/audio/a_tu_lado");
        canciones[nCanciones++] = c;
        c.setDatos("Lugar Secreto", 100010102, 180, "/users/storage/claudia_lorelle/audio/lugar_secreto");
        canciones[nCanciones++] = c;
        c.setDatos("Ola Azul", 200020101, 200, "/users/storage/artist2/audio/ola_azul");
        canciones[nCanciones++] = c;
        c.setDatos("Noche de Paz", 300030101, 240, "/users/storage/artist3/audio/noche_de_paz");
        canciones[nCanciones++] = c;
        c.setDatos("Vuela Alto", 400040101, 195, "/users/storage/artist4/audio/vuela_alto");
        canciones[nCanciones++] = c;
    }

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

    mostrarMenuParaUsuario(usuarioActivo, users, nUsers, canciones, nCanciones, interfaz);

    cout << MSG_THANKS << "\n";
    return 0;
}

// ----------------------------------------------------------
// Menu principal del usuario
void mostrarMenuParaUsuario(Usuario* u, Usuario users[], int nUsers,
                            Cancion canciones[], int nCanciones, Interfaz &interfaz) {
    int opcion = 0;
    int iterCountTotal = 0;
    int memoriaTotal = 0;

    do {
        cout << "\n=== MENU ===\n";
        if (strcmp(u->getTipo(), "Premium") == 0) {
            cout << "1. Reproduccion aleatoria\n";
            cout << "2. Mi lista de favoritos\n";
            cout << "3. Medicion de recursos\n";
            cout << "4. Salir\n";
        } else {
            cout << "1. Reproduccion aleatoria (con publicidad)\n";
            cout << "2. Medicion de recursos\n";
            cout << "3. Salir\n";
        }

        cout << "Opcion: ";
        cin >> opcion;

        // ---------------- USUARIO PREMIUM ----------------
        if (strcmp(u->getTipo(), "Premium") == 0) {
            if (opcion == 1) {
                int iter = 0, mem = 0;
                interfaz.reproducirAleatoria(canciones, nCanciones, u, true, iter, mem);
                iterCountTotal += iter;
                memoriaTotal += mem;
            }
            else if (opcion == 2) {
                int sub;
                do {
                    cout << "\n=== FAVORITOS ===\n";
                    cout << "1. Editar (agregar/eliminar)\n2. Seguir otro usuario\n3. Ejecutar mi lista\n4. Volver\n";
                    cout << "Opcion: ";
                    cin >> sub;

                    if (sub == 1) {
                        cout << "\nCanciones disponibles:\n";
                        for (int i = 0; i < nCanciones; i++) {
                            cout << "ID=" << canciones[i].getId() << " - " << canciones[i].getNombre() << "\n";
                        }

                        cout << "Ingrese ID de cancion para agregar o eliminar: ";
                        long id;
                        cin >> id;

                        Cancion* c = interfaz.buscarCancionPorId(canciones, nCanciones, id);
                        if (!c) {
                            cout << "No existe ninguna cancion con ese ID.\n";
                        } else {
                            if (u->existeFavorito(id)) {
                                u->eliminarFavorito(id);
                                cout << "Eliminado de favoritos: " << c->getNombre() << "\n";
                            } else {
                                if (u->agregarFavorito(id)) {
                                    cout << "Agregado a favoritos: " << c->getNombre() << "\n";
                                } else {
                                    cout << "No se pudo agregar (lista llena o duplicada)\n";
                                }
                            }

                            cout << "\nFavoritos actuales (" << u->getNumFavoritos() << "):\n";
                            for (int i = 0; i < u->getNumFavoritos(); i++) {
                                long fid = u->obtenerFavoritoPorIndice(i);
                                Cancion* fc = interfaz.buscarCancionPorId(canciones, nCanciones, fid);
                                if (fc) cout << "ID=" << fid << " - " << fc->getNombre() << "\n";
                            }
                        }
                    }
                    else if (sub == 2) {
                        int iterSeguir = 0;
                        interfaz.seguirUsuario(u, users, nUsers, iterSeguir);
                        iterCountTotal += iterSeguir;
                    }
                    else if (sub == 3) {
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
                                    interfaz.reproducirLista(ses, K, u, true, iter, mem);
                                } else {
                                    interfaz.reproducirLista(lista, nLista, u, true, iter, mem);
                                }
                                iterCountTotal += iter;
                                memoriaTotal += mem;
                            }
                        }
                    }
                } while (sub != 4);
            }
            else if (opcion == 3) {
                int memoria = interfaz.calcularMemoriaUsadaEstimado(users, nUsers, canciones, nCanciones);
                interfaz.medirRecursos(iterCountTotal, memoria);
            }
        }
        // ---------------- USUARIO FREE ----------------
        else {
            if (opcion == 1) {
                int iter = 0, mem = 0;
                interfaz.reproducirAleatoria(canciones, nCanciones, u, false, iter, mem);
                iterCountTotal += iter;
                memoriaTotal += mem;
            }
            else if (opcion == 2) {
                int memoria = interfaz.calcularMemoriaUsadaEstimado(users, nUsers, canciones, nCanciones);
                interfaz.medirRecursos(iterCountTotal, memoria);
            }
            else if (opcion == 3) break;
        }
    } while (true);
}
