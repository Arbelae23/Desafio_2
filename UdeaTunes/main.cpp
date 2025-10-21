#include <iostream>
#include <fstream>
#include <cstring>   // Para strcmp, strcpy, strtok
using namespace std;

struct Usuario {
    char nombreUsuario[30];
    char contrasena[30];
    char tipoCuenta[15];
};

// === Funcion para contar lineas del archivo ===
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

// === Funcion para cargar los usuarios desde el archivo ===
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

        i++;
    }

    file.close();
    return usuarios;
}

// === Funcion de login ===
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

// === Menu Premium ===
void menuPremium() {
    cout << "\n=== MENU PREMIUM ===" << endl;
    cout << "1. Reproduccion aleatoria" << endl;
    cout << "2. Mi lista de favoritos" << endl;
    cout << "3. Medicion del consumo de recursos" << endl;
    cout << "4. Cerrar sesion" << endl;
}

// === Menu Free ===
void menuFree() {
    cout << "\n=== MENU FREE ===" << endl;
    cout << "1. Reproduccion aleatoria (con publicidad)" << endl;
    cout << "2. Medicion del consumo de recursos" << endl;
    cout << "3. Cerrar sesion" << endl;
}

int main() {
    int cantidad = 0;
    const char* rutaArchivo = "C:/Users/USER/Documents/GitHub/Desafio_2/UdeaTunes/DataUser.txt";

    Usuario* usuarios = cargarUsuarios(rutaArchivo, cantidad);
    if (!usuarios) return 1;

    bool continuarPrograma = true;

    while (continuarPrograma) {  // Bucle general del programa
        Usuario* usuarioActivo = login(usuarios, cantidad);

        if (strcmp(usuarioActivo->tipoCuenta, "Premium") == 0) {
            int opcion;
            do {
                menuPremium();
                cout << "\nSeleccione una opcion: ";
                cin >> opcion;

                switch (opcion) {
                case 1:
                    cout << "\nReproduciendo aleatoriamente (alta calidad)...\n";
                    break;
                case 2:
                    cout << "\nMostrando tu lista de favoritos...\n";
                    break;
                case 3:
                    cout << "\nMidiendo consumo de recursos...\n";
                    break;
                case 4:
                    cout << "\nCerrando sesion...\n";
                    break;
                default:
                    cout << "\nOpcion no valida. Intente nuevamente.\n";
                }
            } while (opcion != 4);
        }
        else {  // Usuario estandar
            int opcion;
            do {
                menuFree();
                cout << "\nSeleccione una opcion: ";
                cin >> opcion;

                switch (opcion) {
                case 1:
                    cout << "\nReproduciendo aleatoriamente con publicidad...\n";
                    break;
                case 2:
                    cout << "\nMidiendo consumo de recursos...\n";
                    break;
                case 3:
                    cout << "\nCerrando sesion...\n";
                    break;
                default:
                    cout << "\nOpcion no valida. Intente nuevamente.\n";
                }
            } while (opcion != 3);
        }

        // Al cerrar sesion vuelve al login automaticamente
        cout << "\nRegresando al inicio de sesion...\n";
    }

    delete[] usuarios;
    return 0;
}
