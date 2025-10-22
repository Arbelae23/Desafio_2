#include "interfaz.h"
#include <iostream>
using namespace std;

void Interfaz::menuPrincipal(Usuario& user) {
    int opc;
    do {
        cout << "\n=== Menu de Usuario ===\n";
        cout << "1. Ver perfil\n";
        cout << "2. Crear playlist\n";
        cout << "3. Reproducir playlist\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opc;
        switch (opc) {
        case 1: user.mostrarPerfil(); break;
        case 2: {
            string nombre;
            cout << "Nombre de la playlist: ";
            cin >> nombre;
            user.crearPlaylist(nombre);
            break;
        }
        case 3: user.reproducirPlaylist(); break;
        case 4: cout << "Saliendo...\n"; break;
        default: cout << "Opcion invalida\n";
        }
    } while (opc != 4);
}
