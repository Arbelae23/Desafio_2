#include "album.h"
#include "cancion.h"
#include <cstring>
#include <cctype>
#include <iomanip>

Album::Album() {
    inicializarAtributos();
}

Album::Album(const char* nombre, int codigo_identificador,
             const char* sello_disquero, const char* ruta_portada,
             int dia, int mes, int anio) {
    inicializarAtributos();

    establecerNombre(nombre);
    establecerCodigoIdentificador(codigo_identificador);
    if (sello_disquero) establecerSelloDisquero(sello_disquero);
    if (ruta_portada) establecerRutaPortada(ruta_portada);
    establecerFechaLanzamiento(dia, mes, anio);
}

Album::Album(const Album& otro) {
    inicializarAtributos();
    *this = otro;
}

Album::~Album() {
    liberarMemoria();
}

Album& Album::operator=(const Album& otro) {
    if (this != &otro) {
        liberarMemoria();
        inicializarAtributos();

        // Copiar informacion basica
        if (otro.nombre) copiarCadena(nombre, otro.nombre);
        if (otro.sello_disquero) copiarCadena(sello_disquero, otro.sello_disquero);
        if (otro.ruta_portada) copiarCadena(ruta_portada, otro.ruta_portada);

        codigo_identificador = otro.codigo_identificador;
        puntuacion = otro.puntuacion;
        dia_lanzamiento = otro.dia_lanzamiento;
        mes_lanzamiento = otro.mes_lanzamiento;
        anio_lanzamiento = otro.anio_lanzamiento;
        duracion_total_segundos = otro.duracion_total_segundos;

        // Copiar generos
        for (int i = 0; i < otro.cantidad_generos; i++) {
            agregarGenero(otro.generos[i]);
        }

        // Copiar canciones (solo referencias, no copiar las canciones)
        for (int i = 0; i < otro.cantidad_canciones; i++) {
            agregarCancion(otro.canciones[i]);
        }
    }
    return *this;
}

void Album::inicializarAtributos() {
    nombre = nullptr;
    codigo_identificador = 0;
    sello_disquero = nullptr;
    ruta_portada = nullptr;
    puntuacion = 0;

    dia_lanzamiento = 1;
    mes_lanzamiento = 1;
    anio_lanzamiento = 2000;

    // Inicializar generos (maximo 4)
    capacidad_generos = 4;
    cantidad_generos = 0;
    generos = new char*[capacidad_generos];
    for (int i = 0; i < capacidad_generos; i++) {
        generos[i] = nullptr;
    }

    // Inicializar canciones
    capacidad_canciones = 0;
    cantidad_canciones = 0;
    canciones = nullptr;

    duracion_total_segundos = 0;
}

void Album::liberarMemoria() {
    liberarCadena(nombre);
    liberarCadena(sello_disquero);
    liberarCadena(ruta_portada);

    // Liberar generos
    for (int i = 0; i < cantidad_generos; i++) {
        liberarCadena(generos[i]);
    }
    delete[] generos;

    // Liberar array de canciones (no las canciones en si, solo las referencias)
    delete[] canciones;
}

void Album::copiarCadena(char*& destino, const char* origen) {
    if (origen != nullptr) {
        int longitud = strlen(origen);
        destino = new char[longitud + 1];
        strcpy(destino, origen);
    } else {
        destino = nullptr;
    }
}

void Album::liberarCadena(char*& cadena) {
    if (cadena != nullptr) {
        delete[] cadena;
        cadena = nullptr;
    }
}

void Album::redimensionarCanciones() {
    int nueva_capacidad = (capacidad_canciones == 0) ? 2 : capacidad_canciones * 2;

    Cancion** nuevas_canciones = new Cancion*[nueva_capacidad];

    for (int i = 0; i < cantidad_canciones; i++) {
        nuevas_canciones[i] = canciones[i];
    }

    delete[] canciones;
    canciones = nuevas_canciones;
    capacidad_canciones = nueva_capacidad;
}

void Album::recalcularDuracionTotal() {
    duracion_total_segundos = 0;
    for (int i = 0; i < cantidad_canciones; i++) {
        if (canciones[i] != nullptr) {
            duracion_total_segundos += canciones[i]->obtenerDuracion();
        }
    }
}

// METODOS PARA ESTABLECER INFORMACION BASICA

bool Album::establecerNombre(const char* nuevo_nombre) {
    if (nuevo_nombre == nullptr || strlen(nuevo_nombre) == 0) {
        return false;
    }

    liberarCadena(nombre);
    copiarCadena(nombre, nuevo_nombre);
    return true;
}

bool Album::establecerCodigoIdentificador(int codigo) {
    if (!validarCodigoIdentificador(codigo)) {
        return false;
    }

    codigo_identificador = codigo;
    return true;
}

bool Album::establecerSelloDisquero(const char* sello) {
    liberarCadena(sello_disquero);
    if (sello != nullptr && strlen(sello) > 0) {
        copiarCadena(sello_disquero, sello);
    }
    return true;
}

bool Album::establecerRutaPortada(const char* ruta) {
    if (ruta != nullptr && !validarRutaPortada(ruta)) {
        return false;
    }

    liberarCadena(ruta_portada);
    if (ruta != nullptr && strlen(ruta) > 0) {
        copiarCadena(ruta_portada, ruta);
    }
    return true;
}

bool Album::establecerPuntuacion(int nueva_puntuacion) {
    if (!validarPuntuacion(nueva_puntuacion)) {
        return false;
    }

    puntuacion = nueva_puntuacion;
    return true;
}

bool Album::establecerFechaLanzamiento(int dia, int mes, int anio) {
    if (!validarFecha(dia, mes, anio)) {
        return false;
    }

    dia_lanzamiento = dia;
    mes_lanzamiento = mes;
    anio_lanzamiento = anio;
    return true;
}

// METODOS PARA OBTENER INFORMACION BASICA

const char* Album::obtenerNombre() const {
    return nombre ? nombre : "";
}

int Album::obtenerCodigoIdentificador() const {
    return codigo_identificador;
}

const char* Album::obtenerSelloDisquero() const {
    return sello_disquero ? sello_disquero : "";
}

const char* Album::obtenerRutaPortada() const {
    return ruta_portada ? ruta_portada : "";
}

int Album::obtenerPuntuacion() const {
    return puntuacion;
}

int Album::obtenerDiaLanzamiento() const {
    return dia_lanzamiento;
}

int Album::obtenerMesLanzamiento() const {
    return mes_lanzamiento;
}

int Album::obtenerAnioLanzamiento() const {
    return anio_lanzamiento;
}

int Album::obtenerDuracionTotal() const {
    return duracion_total_segundos;
}

// METODOS PARA GESTIONAR GENEROS (MAXIMO 4, SOLO AGREGAR)

bool Album::agregarGenero(const char* genero) {
    // Validar genero
    if (!validarGenero(genero)) {
        return false;
    }

    // Verificar si ya existe
    if (tieneGenero(genero)) {
        return false;
    }

    // Verificar si ya tiene 4 generos
    if (cantidad_generos >= capacidad_generos) {
        std::cout << "Error: El album ya tiene el maximo de 4 generos\n";
        return false;
    }

    copiarCadena(generos[cantidad_generos], genero);
    cantidad_generos++;
    return true;
}

int Album::obtenerCantidadGeneros() const {
    return cantidad_generos;
}

const char* Album::obtenerGenero(int indice) const {
    if (indice >= 0 && indice < cantidad_generos) {
        return generos[indice];
    }
    return nullptr;
}

bool Album::tieneGenero(const char* genero) const {
    for (int i = 0; i < cantidad_generos; i++) {
        if (strcmp(generos[i], genero) == 0) {
            return true;
        }
    }
    return false;
}

// METODOS PARA GESTIONAR CANCIONES (SOLO AGREGAR)

bool Album::agregarCancion(Cancion* cancion) {
    if (cancion == nullptr) {
        return false;
    }

    // Verificar duplicados
    if (contieneCancion(cancion)) {
        return false;
    }

    // Redimensionar si es necesario
    if (cantidad_canciones >= capacidad_canciones) {
        redimensionarCanciones();
    }

    canciones[cantidad_canciones] = cancion;
    cantidad_canciones++;

    // Recalcular duracion total
    recalcularDuracionTotal();

    return true;
}

int Album::obtenerCantidadCanciones() const {
    return cantidad_canciones;
}

Cancion* Album::obtenerCancion(int indice) const {
    if (indice >= 0 && indice < cantidad_canciones) {
        return canciones[indice];
    }
    return nullptr;
}

bool Album::contieneCancion(Cancion* cancion) const {
    for (int i = 0; i < cantidad_canciones; i++) {
        if (canciones[i] == cancion) {
            return true;
        }
    }
    return false;
}

// METODOS DE UTILIDAD

void Album::mostrarInformacionCompleta() const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "              INFORMACION DEL ALBUM\n";
    std::cout << std::string(60, '=') << "\n";

    std::cout << "Nombre: " << obtenerNombre() << "\n";
    std::cout << "Codigo Identificador: " << std::setfill('0') << std::setw(2)
              << codigo_identificador << "\n";

    if (sello_disquero && strlen(sello_disquero) > 0) {
        std::cout << "Sello Disquero: " << obtenerSelloDisquero() << "\n";
    }

    // Mostrar fecha
    char* fecha = obtenerFechaFormateada();
    std::cout << "Fecha de Lanzamiento: " << fecha << "\n";
    delete[] fecha;

    // Mostrar duracion
    if (duracion_total_segundos > 0) {
        char* duracion = obtenerDuracionFormateada();
        std::cout << "Duracion Total: " << duracion << " (" << duracion_total_segundos << " segundos)\n";
        delete[] duracion;
    }

    // Mostrar puntuacion
    if (puntuacion > 0) {
        std::cout << "Puntuacion: " << puntuacion << "/10\n";
    }

    // Mostrar generos
    if (cantidad_generos > 0) {
        std::cout << "Generos: ";
        for (int i = 0; i < cantidad_generos; i++) {
            std::cout << generos[i];
            if (i < cantidad_generos - 1) std::cout << ", ";
        }
        std::cout << "\n";
    }

    // Mostrar ruta de portada
    if (ruta_portada && strlen(ruta_portada) > 0) {
        std::cout << "Portada: " << obtenerRutaPortada() << "\n";
    }

    // Mostrar canciones
    std::cout << "\nCanciones (" << cantidad_canciones << "):";
    if (cantidad_canciones > 0) {
        std::cout << "\n";
        for (int i = 0; i < cantidad_canciones; i++) {
            std::cout << "  " << (i + 1) << ". " << canciones[i]->obtenerTitulo();
            int duracion_seg = canciones[i]->obtenerDuracion();
            int min = duracion_seg / 60;
            int seg = duracion_seg % 60;
            std::cout << " [" << min << ":" << std::setfill('0') << std::setw(2) << seg << "]\n";
        }
    } else {
        std::cout << " (sin canciones)\n";
    }

    std::cout << std::string(60, '=') << "\n";
}

void Album::mostrarInformacionBasica() const {
    std::cout << "\n--- Album: " << obtenerNombre();

    if (anio_lanzamiento > 0) {
        std::cout << " (" << anio_lanzamiento << ")";
    }

    if (cantidad_canciones > 0) {
        std::cout << " - " << cantidad_canciones << " canciones";
    }

    if (puntuacion > 0) {
        std::cout << " - Puntuacion: " << puntuacion << "/10";
    }

    std::cout << "\n";
}

void Album::mostrarCanciones() const {
    std::cout << "\n=== CANCIONES DEL ALBUM: " << obtenerNombre() << " ===\n";

    if (cantidad_canciones == 0) {
        std::cout << "No hay canciones en este album.\n";
        return;
    }

    for (int i = 0; i < cantidad_canciones; i++) {
        std::cout << "  " << (i + 1) << ". ";
        std::cout << canciones[i]->obtenerTitulo();
        std::cout << " - " << canciones[i]->obtenerArtistaPrincipal();

        int duracion_seg = canciones[i]->obtenerDuracion();
        int min = duracion_seg / 60;
        int seg = duracion_seg % 60;
        std::cout << " [" << min << ":" << std::setfill('0') << std::setw(2) << seg << "]\n";
    }

    std::cout << "\nTotal: " << cantidad_canciones << " canciones\n";
}

char* Album::obtenerFechaFormateada() const {
    char* resultado = new char[11];  // DD/MM/YYYY\0

    resultado[0] = '0' + (dia_lanzamiento / 10);
    resultado[1] = '0' + (dia_lanzamiento % 10);
    resultado[2] = '/';
    resultado[3] = '0' + (mes_lanzamiento / 10);
    resultado[4] = '0' + (mes_lanzamiento % 10);
    resultado[5] = '/';

    int anio = anio_lanzamiento;
    resultado[9] = '0' + (anio % 10); anio /= 10;
    resultado[8] = '0' + (anio % 10); anio /= 10;
    resultado[7] = '0' + (anio % 10); anio /= 10;
    resultado[6] = '0' + (anio % 10);
    resultado[10] = '\0';

    return resultado;
}

char* Album::obtenerDuracionFormateada() const {
    int horas = duracion_total_segundos / 3600;
    int minutos = (duracion_total_segundos % 3600) / 60;
    int segundos = duracion_total_segundos % 60;

    char* resultado = new char[9];  // HH:MM:SS\0

    resultado[0] = '0' + (horas / 10);
    resultado[1] = '0' + (horas % 10);
    resultado[2] = ':';
    resultado[3] = '0' + (minutos / 10);
    resultado[4] = '0' + (minutos % 10);
    resultado[5] = ':';
    resultado[6] = '0' + (segundos / 10);
    resultado[7] = '0' + (segundos % 10);
    resultado[8] = '\0';

    return resultado;
}

// METODOS DE VALIDACION ESTATICOS

bool Album::validarCodigoIdentificador(int codigo) {
    return (codigo >= 0 && codigo <= 99);
}

bool Album::validarPuntuacion(int punt) {
    return (punt >= 1 && punt <= 10);
}

bool Album::validarFecha(int dia, int mes, int anio) {
    // Validar anio
    if (anio < 1900 || anio > 2025) {
        return false;
    }

    // Validar mes
    if (mes < 1 || mes > 12) {
        return false;
    }

    // Validar dia segun el mes
    int dias_por_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Verificar anio bisiesto
    if (mes == 2 && ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))) {
        dias_por_mes[1] = 29;
    }

    if (dia < 1 || dia > dias_por_mes[mes - 1]) {
        return false;
    }

    return true;
}

bool Album::validarGenero(const char* genero) {
    if (genero == nullptr || strlen(genero) == 0) {
        return false;
    }

    // Generos permitidos
    const char* generos_validos[] = {
        "Pop", "Rock", "Jazz", "Musica Clasica", "Electronica",
        "Hip Hop", "Reggae", "Blues", "Latina"
    };

    for (int i = 0; i < 9; i++) {
        if (strcmp(genero, generos_validos[i]) == 0) {
            return true;
        }
    }

    return false;
}

bool Album::validarRutaPortada(const char* ruta) {
    if (ruta == nullptr || strlen(ruta) == 0) {
        return false;
    }

    // Verificar que termine en .png
    int longitud = strlen(ruta);
    if (longitud < 4) {
        return false;
    }

    const char* extension = ruta + longitud - 4;
    return (strcmp(extension, ".png") == 0);
}

const char* Album::obtenerNombreGenero(GeneroMusical genero) {
    switch (genero) {
    case POP: return "Pop";
    case ROCK: return "Rock";
    case JAZZ: return "Jazz";
    case MUSICA_CLASICA: return "Musica Clasica";
    case ELECTRONICA: return "Electronica";
    case HIP_HOP: return "Hip Hop";
    case REGGAE: return "Reggae";
    case BLUES: return "Blues";
    case LATINA: return "Latina";
    default: return "Desconocido";
    }
}
