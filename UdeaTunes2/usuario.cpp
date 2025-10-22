#include "usuario.h"
#include "cancion.h"
#include <cstring>
#include <iostream>

using namespace std;


// CONSTRUCTORES Y DESTRUCTOR


Usuario::Usuario() {
    inicializarAtributos();
}

Usuario::Usuario(const char* nickname, const char* password, TipoMembresia tipo) {
    inicializarAtributos();
    establecerNickname(nickname);
    if (password) establecerPassword(password);
    tipo_membresia = tipo;
}

Usuario::Usuario(const Usuario& otro) {
    inicializarAtributos();
    *this = otro;
}

Usuario::~Usuario() {
    liberarMemoria();
}


// OPERADORES


Usuario& Usuario::operator=(const Usuario& otro) {
    if (this != &otro) {
        liberarMemoria();
        inicializarAtributos();

        if (otro.nickname) copiarCadena(nickname, otro.nickname);
        if (otro.password) copiarCadena(password, otro.password);
        if (otro.ciudad) copiarCadena(ciudad, otro.ciudad);
        if (otro.pais) copiarCadena(pais, otro.pais);
        if (otro.fecha_inscripcion) copiarCadena(fecha_inscripcion, otro.fecha_inscripcion);

        tipo_membresia = otro.tipo_membresia;
        contador_reproducciones = otro.contador_reproducciones;

        // Copiar lista de favoritos si existe
        if (otro.lista_favoritos) {
            lista_favoritos = new Playlist(*otro.lista_favoritos);
        }

        // No copiar usuario_seguido (solo referencia)
        usuario_seguido = otro.usuario_seguido;
    }
    return *this;
}

// METODOS AUXILIARES

void Usuario::inicializarAtributos() {
    nickname = nullptr;
    password = nullptr;
    ciudad = nullptr;
    pais = nullptr;
    fecha_inscripcion = nullptr;
    tipo_membresia = ESTANDAR;
    lista_favoritos = nullptr;
    usuario_seguido = nullptr;
    contador_reproducciones = 0;
}

void Usuario::liberarMemoria() {
    liberarCadena(nickname);
    liberarCadena(password);
    liberarCadena(ciudad);
    liberarCadena(pais);
    liberarCadena(fecha_inscripcion);

    if (lista_favoritos) {
        delete lista_favoritos;
        lista_favoritos = nullptr;
    }

    // No eliminar usuario_seguido (solo es una referencia)
    usuario_seguido = nullptr;
}

void Usuario::copiarCadena(char*& destino, const char* origen) {
    if (origen) {
        int longitud = strlen(origen);
        destino = new char[longitud + 1];
        strcpy(destino, origen);
    } else {
        destino = nullptr;
    }
}

void Usuario::liberarCadena(char*& cadena) {
    if (cadena) {
        delete[] cadena;
        cadena = nullptr;
    }
}


// SETTERS


bool Usuario::establecerNickname(const char* nickname) {
    if (!validarNickname(nickname)) return false;

    liberarCadena(this->nickname);
    copiarCadena(this->nickname, nickname);
    return true;
}

bool Usuario::establecerPassword(const char* password) {
    if (!password || strlen(password) == 0) return false;

    liberarCadena(this->password);
    copiarCadena(this->password, password);
    return true;
}

bool Usuario::establecerCiudad(const char* ciudad) {
    liberarCadena(this->ciudad);
    if (ciudad && strlen(ciudad) > 0) {
        copiarCadena(this->ciudad, ciudad);
    }
    return true;
}

bool Usuario::establecerPais(const char* pais) {
    liberarCadena(this->pais);
    if (pais && strlen(pais) > 0) {
        copiarCadena(this->pais, pais);
    }
    return true;
}

bool Usuario::establecerFechaInscripcion(const char* fecha) {
    if (!validarFecha(fecha)) return false;

    liberarCadena(fecha_inscripcion);
    copiarCadena(fecha_inscripcion, fecha);
    return true;
}

bool Usuario::establecerTipoMembresia(TipoMembresia tipo) {
    tipo_membresia = tipo;
    return true;
}


// GETTERS


const char* Usuario::obtenerNickname() const {
    return nickname ? nickname : "";
}

const char* Usuario::obtenerPassword() const {
    return password ? password : "";
}

const char* Usuario::obtenerCiudad() const {
    return ciudad ? ciudad : "";
}

const char* Usuario::obtenerPais() const {
    return pais ? pais : "";
}

const char* Usuario::obtenerFechaInscripcion() const {
    return fecha_inscripcion ? fecha_inscripcion : "";
}

Usuario::TipoMembresia Usuario::obtenerTipoMembresia() const {
    return tipo_membresia;
}

const char* Usuario::obtenerNombreTipoMembresia() const {
    return (tipo_membresia == PREMIUM) ? "Premium" : "Estandar";
}


// VALIDACIONES DE MEMBRESIA


bool Usuario::esPremium() const {
    return tipo_membresia == PREMIUM;
}

bool Usuario::esEstandar() const {
    return tipo_membresia == ESTANDAR;
}

int Usuario::obtenerCalidadAudio() const {
    return esPremium() ? 320 : 128;
}


// GESTION DE CONTADOR DE REPRODUCCIONES


void Usuario::incrementarContadorReproducciones() {
    contador_reproducciones++;
}

int Usuario::obtenerContadorReproducciones() const {
    return contador_reproducciones;
}

void Usuario::reiniciarContadorReproducciones() {
    contador_reproducciones = 0;
}

bool Usuario::debeVerPublicidad() const {
    // Solo usuarios estandar ven publicidad cada 2 canciones
    return esEstandar() && (contador_reproducciones % 2 == 0) && (contador_reproducciones > 0);
}


// GESTION DE LISTA DE FAVORITOS


bool Usuario::crearListaFavoritos(const char* nombre) {
    if (!esPremium()) {
        cout << "Solo usuarios Premium pueden tener lista de favoritos.\n";
        return false;
    }

    if (lista_favoritos) {
        delete lista_favoritos;
    }

    lista_favoritos = new Playlist(nombre);
    return true;
}

Playlist* Usuario::obtenerListaFavoritos() {
    return lista_favoritos;
}

const Playlist* Usuario::obtenerListaFavoritos() const {
    return lista_favoritos;
}

bool Usuario::tieneListaFavoritos() const {
    return lista_favoritos != nullptr;
}

// SEGUIR USUARIO


bool Usuario::seguirUsuario(Usuario* otro_usuario) {
    if (!esPremium()) {
        cout << "Solo usuarios Premium pueden seguir a otros usuarios.\n";
        return false;
    }

    if (!otro_usuario || !otro_usuario->esPremium()) {
        cout << "Solo puedes seguir a usuarios Premium.\n";
        return false;
    }

    if (otro_usuario == this) {
        cout << "No puedes seguirte a ti mismo.\n";
        return false;
    }

    usuario_seguido = otro_usuario;

    // Si el otro usuario tiene lista de favoritos, agregar sus canciones
    if (otro_usuario->tieneListaFavoritos()) {
        // Crear lista propia si no existe
        if (!lista_favoritos) {
            crearListaFavoritos("Mis Favoritos");
        }

        // Agregar canciones del usuario seguido
        const Playlist* lista_seguido = otro_usuario->obtenerListaFavoritos();
        int agregadas = 0;

        for (int i = 0; i < lista_seguido->obtenerCantidadCanciones(); i++) {
            if (lista_favoritos->agregarCancion(lista_seguido->obtenerCancion(i))) {
                agregadas++;
            }
        }

        cout << "Se agregaron " << agregadas << " canciones de "
             << otro_usuario->obtenerNickname() << " a tu lista.\n";
    }

    return true;
}

Usuario* Usuario::obtenerUsuarioSeguido() {
    return usuario_seguido;
}

const Usuario* Usuario::obtenerUsuarioSeguido() const {
    return usuario_seguido;
}

bool Usuario::estaSiguiendoUsuario() const {
    return usuario_seguido != nullptr;
}


// CAPACIDADES SEGUN MEMBRESIA

bool Usuario::puedeRetrocederCanciones(int num_canciones) const {
    if (esEstandar()) return false;
    return num_canciones <= obtenerMaximoRetroceso();
}

int Usuario::obtenerMaximoRetroceso() const {
    // Estandar: 0, Premium: 4 en reproduccion aleatoria, 6 en lista favoritos
    return esPremium() ? 4 : 0;
}


// MOSTRAR INFORMACION


void Usuario::mostrarPerfil() const {
    cout << "\n=== PERFIL DE USUARIO ===\n";
    cout << "Nickname: " << obtenerNickname() << "\n";
    cout << "Tipo de membresia: " << obtenerNombreTipoMembresia() << "\n";

    if (ciudad && strlen(ciudad) > 0) {
        cout << "Ciudad: " << ciudad << "\n";
    }

    if (pais && strlen(pais) > 0) {
        cout << "Pais: " << pais << "\n";
    }

    if (fecha_inscripcion && strlen(fecha_inscripcion) > 0) {
        cout << "Fecha de inscripcion: " << fecha_inscripcion << "\n";
    }
}

void Usuario::mostrarInformacionCompleta() const {
    mostrarPerfil();

    cout << "\nCalidad de audio: " << obtenerCalidadAudio() << " kbps\n";

    if (esPremium()) {
        cout << "\nBeneficios Premium:\n";
        cout << "  - Sin publicidad\n";
        cout << "  - Lista de favoritos (hasta 10000 canciones)\n";
        cout << "  - Puede retroceder hasta " << obtenerMaximoRetroceso() << " canciones\n";
        cout << "  - Puede seguir a otros usuarios Premium\n";

        if (tieneListaFavoritos()) {
            cout << "\nLista de favoritos: "
                 << lista_favoritos->obtenerCantidadCanciones() << " canciones\n";
        } else {
            cout << "\nNo tiene lista de favoritos creada.\n";
        }

        if (estaSiguiendoUsuario()) {
            cout << "Siguiendo a: " << usuario_seguido->obtenerNickname() << "\n";
        }
    } else {
        cout << "\nLimitaciones Estandar:\n";
        cout << "  - Publicidad cada 2 canciones\n";
        cout << "  - No puede tener lista de favoritos\n";
        cout << "  - No puede retroceder canciones\n";
    }
}


// VALIDACIONES ESTATICAS


bool Usuario::validarNickname(const char* nickname) {
    if (!nickname || strlen(nickname) == 0) return false;
    if (strlen(nickname) > 50) return false;  // Maximo 50 caracteres
    return true;
}

bool Usuario::validarFecha(const char* fecha) {
    if (!fecha || strlen(fecha) != 10) return false;

    // Verificar formato DD/MM/YYYY
    if (fecha[2] != '/' || fecha[5] != '/') return false;

    // Verificar que sean digitos
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (fecha[i] < '0' || fecha[i] > '9') return false;
    }

    return true;
}
