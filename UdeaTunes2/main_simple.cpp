#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "config.h"
#include "usuario.h"
#include "interfaz.h"
#include "cancion.h"
#include "album.h"

using namespace std;

// Declaraciones de funciones
bool mostrarMenuParaUsuario(Usuario* u, Usuario users[], int nUsers, Cancion canciones[], int nCanciones, Interfaz &interfaz);
void mostrarCancionesDisponibles(Cancion canciones[], int nCanciones);

int main() {
    cout << MSG_WELCOME << endl;

    static Usuario users[MAX_USERS];
    static Cancion canciones[MAX_SONGS];
    static Album albunes[MAX_ALBUMS];  // Agregar array de álbumes
    // COMENTADO TEMPORALMENTE: static Artista artistas[MAX_ARTISTS];  // Agregar array de artistas
    Interfaz interfaz; // Nueva clase interfaz

    // Cargar archivos de datos usando funciones de Interfaz
    int nUsers = interfaz.cargarUsuariosDesdeArchivo("C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/users.txt", users, MAX_USERS);
    int nCanciones = interfaz.cargarCancionesDesdeArchivo("C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/songs.txt", canciones, MAX_SONGS);
    int nAlbunes = interfaz.cargarAlbunesDesdeArchivo("C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/albunes.txt", albunes, MAX_ALBUMS);
    // COMENTADO TEMPORALMENTE: int nArtistas = interfaz.cargarArtistasDesdeArchivo("C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes2/artistas.txt", artistas, MAX_ARTISTS);

    cout << "Carga completada. Usuarios: " << nUsers << ", Canciones: " << nCanciones << ", Albumes: " << nAlbunes << endl;

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
        canciones[0].setDatos("Bohemian Rhapsody", 1001, 355, "audio/bohemian.mp3");
        canciones[1].setDatos("Hotel California", 1002, 391, "audio/hotel.mp3");
        canciones[2].setDatos("Imagine", 1003, 183, "audio/imagine.mp3");
        canciones[3].setDatos("Stairway to Heaven", 1004, 482, "audio/stairway.mp3");
        canciones[4].setDatos("Sweet Child O' Mine", 1005, 356, "audio/sweet.mp3");
        nCanciones = 5;
    }

    cout << "Iniciando bucle principal del programa..." << endl;

    // Bucle principal del programa
    while (true) {
        cout << "\n=== LOGIN ===" << endl;
        cout << "Usuario: ";
        char username[50];
        cin >> username;

        cout << "Password: ";
        char password[50];
        cin >> password;

        // Buscar usuario
        int userIndex = interfaz.buscarUsuarioPorNombre(users, nUsers, username);
        if (userIndex != -1 && strcmp(users[userIndex].getPassword(), password) == 0) {
            cout << MSG_LOGIN << " " << username << endl;
            
            // Mostrar menú para el usuario
            if (!mostrarMenuParaUsuario(&users[userIndex], users, nUsers, canciones, nCanciones, interfaz)) {
                break; // Salir del programa
            }
        } else {
            cout << MSG_INVALID_CREDENTIALS << endl;
        }
    }

    cout << MSG_THANKS << endl;
    return 0;
}

bool mostrarMenuParaUsuario(Usuario* u, Usuario users[], int nUsers,
                            Cancion canciones[], int nCanciones, Interfaz &interfaz) {
    cout << "Función mostrarMenuParaUsuario ejecutándose correctamente" << endl;
    return false; // Salir por ahora para probar
}

void mostrarCancionesDisponibles(Cancion canciones[], int nCanciones) {
    cout << "=== CANCIONES DISPONIBLES ===" << endl;
    for (int i = 0; i < nCanciones; i++) {
        cout << (i+1) << ". ";
        canciones[i].imprimir();
    }
    cout << "=============================" << endl;
}