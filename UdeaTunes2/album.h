#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>

class Cancion;  // Forward declaration

class Album {
private:
    // Informacion basica del album
    char* nombre;
    int codigo_identificador;  // 2 digitos (00-99)
    char* sello_disquero;
    char* ruta_portada;  // Ruta a imagen .png
    int puntuacion;  // 1-10 (otorgada por usuarios)

    // Fecha de lanzamiento
    int dia_lanzamiento;
    int mes_lanzamiento;
    int anio_lanzamiento;

    // Generos musicales (hasta 4)
    char** generos;  // Array de generos
    int cantidad_generos;
    int capacidad_generos;  // Siempre 4 (maximo)

    // Canciones del album (arreglo dinamico)
    Cancion** canciones;
    int cantidad_canciones;
    int capacidad_canciones;

    // Duracion total (calculada automaticamente de las canciones)
    int duracion_total_segundos;

    // Metodos auxiliares privados
    void copiarCadena(char*& destino, const char* origen);
    void liberarCadena(char*& cadena);
    void inicializarAtributos();
    void liberarMemoria();
    void redimensionarCanciones();
    void recalcularDuracionTotal();

public:
    // Generos musicales permitidos (validacion)
    enum GeneroMusical {
        POP,
        ROCK,
        JAZZ,
        MUSICA_CLASICA,
        ELECTRONICA,
        HIP_HOP,
        REGGAE,
        BLUES,
        LATINA
    };

    // Constructores y destructor
    Album();
    Album(const char* nombre, int codigo_identificador,
          const char* sello_disquero = nullptr,
          const char* ruta_portada = nullptr,
          int dia = 1, int mes = 1, int anio = 2000);
    Album(const Album& otro);
    ~Album();

    // Operadores esenciales
    Album& operator=(const Album& otro);

    // Metodos para establecer informacion basica
    bool establecerNombre(const char* nuevo_nombre);
    bool establecerCodigoIdentificador(int codigo);
    bool establecerSelloDisquero(const char* sello);
    bool establecerRutaPortada(const char* ruta);
    bool establecerPuntuacion(int puntuacion);
    bool establecerFechaLanzamiento(int dia, int mes, int anio);

    // Metodos para obtener informacion basica
    const char* obtenerNombre() const;
    int obtenerCodigoIdentificador() const;
    const char* obtenerSelloDisquero() const;
    const char* obtenerRutaPortada() const;
    int obtenerPuntuacion() const;
    int obtenerDiaLanzamiento() const;
    int obtenerMesLanzamiento() const;
    int obtenerAnioLanzamiento() const;
    int obtenerDuracionTotal() const;

    // Metodos para gestionar generos (hasta 4, SOLO agregar)
    bool agregarGenero(const char* genero);
    int obtenerCantidadGeneros() const;
    const char* obtenerGenero(int indice) const;
    bool tieneGenero(const char* genero) const;

    // Metodos para gestionar canciones (SOLO agregar, sin eliminacion)
    bool agregarCancion(Cancion* cancion);
    int obtenerCantidadCanciones() const;
    Cancion* obtenerCancion(int indice) const;
    bool contieneCancion(Cancion* cancion) const;

    // Metodos de utilidad
    void mostrarInformacionCompleta() const;
    void mostrarInformacionBasica() const;
    void mostrarCanciones() const;
    char* obtenerFechaFormateada() const;  // Formato: DD/MM/YYYY
    char* obtenerDuracionFormateada() const;  // Formato: HH:MM:SS

    // Metodos de validacion estaticos
    static bool validarCodigoIdentificador(int codigo);
    static bool validarPuntuacion(int puntuacion);
    static bool validarFecha(int dia, int mes, int anio);
    static bool validarGenero(const char* genero);
    static bool validarRutaPortada(const char* ruta);

    // Metodo helper para convertir string de genero a enum
    static const char* obtenerNombreGenero(GeneroMusical genero);
};

#endif
