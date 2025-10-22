#ifndef ARTISTA_H
#define ARTISTA_H

class Album;

class Artista {
private:
    // Informacion basica
    char* nombre;
    int codigo_identificador;  // 5 digitos (00000-99999)
    int edad;
    char* pais_origen;

    // Estadisticas
    int cantidad_seguidores;
    int posicion_tendencias_global;

    // Catalogo de albumes (arreglo dinamico)
    Album** albumes;
    int cantidad_albumes;
    int capacidad_albumes;

    // Metodos auxiliares
    void copiarCadena(char*& destino, const char* origen);
    void liberarCadena(char*& cadena);
    void redimensionarAlbumes();
    void inicializarAtributos();
    void liberarMemoria();

public:
    // Constructores y destructor
    Artista();
    Artista(const char* nombre, int codigo, int edad = 0,
            const char* pais = nullptr);
    Artista(const Artista& otro);
    ~Artista();

    // Operador de asignacion
    Artista& operator=(const Artista& otro);

    // Setters
    bool establecerNombre(const char* nombre);
    bool establecerCodigoIdentificador(int codigo);
    bool establecerEdad(int edad);
    bool establecerPaisOrigen(const char* pais);
    bool establecerCantidadSeguidores(int seguidores);
    bool establecerPosicionTendencias(int posicion);

    // Getters
    const char* obtenerNombre() const;
    int obtenerCodigoIdentificador() const;
    int obtenerEdad() const;
    const char* obtenerPaisOrigen() const;
    int obtenerCantidadSeguidores() const;
    int obtenerPosicionTendencias() const;

    // Gestion de seguidores
    void incrementarSeguidores(int cantidad = 1);
    void decrementarSeguidores(int cantidad = 1);

    // Gestion de albumes
    bool agregarAlbum(Album* album);
    int obtenerCantidadAlbumes() const;
    Album* obtenerAlbum(int indice) const;
    bool tieneAlbum(const Album* album) const;

    // Mostrar informacion
    void mostrarInformacion() const;
    void mostrarInformacionCompleta() const;
    void mostrarAlbumes() const;

    // Validaciones estaticas
    static bool validarCodigo(int codigo);
    static bool validarEdad(int edad);
};

#endif
