#ifndef USUARIO_H
#define USUARIO_H

#include "playlist.h"

class Usuario {
public:
    // Enum para tipo de membresia
    enum TipoMembresia {
        ESTANDAR,
        PREMIUM
    };

private:
    // Informacion basica
    char* nickname;  // Nombre de usuario unico
    char* password;  // Contrasena (opcional para esta version)
    char* ciudad;
    char* pais;
    char* fecha_inscripcion;  // Formato: DD/MM/YYYY
    TipoMembresia tipo_membresia;

    // Lista de favoritos (solo Premium)
    Playlist* lista_favoritos;

    // Usuario seguido (solo Premium)
    Usuario* usuario_seguido;

    // Contador para publicidad (solo Estandar)
    int contador_reproducciones;

    // Metodos auxiliares
    void copiarCadena(char*& destino, const char* origen);
    void liberarCadena(char*& cadena);
    void inicializarAtributos();
    void liberarMemoria();

public:
    // Constructores y destructor
    Usuario();
    Usuario(const char* nickname, const char* password = nullptr,
            TipoMembresia tipo = ESTANDAR);
    Usuario(const Usuario& otro);
    ~Usuario();

    // Operador de asignacion
    Usuario& operator=(const Usuario& otro);

    // Setters
    bool establecerNickname(const char* nickname);
    bool establecerPassword(const char* password);
    bool establecerCiudad(const char* ciudad);
    bool establecerPais(const char* pais);
    bool establecerFechaInscripcion(const char* fecha);
    bool establecerTipoMembresia(TipoMembresia tipo);

    // Getters
    const char* obtenerNickname() const;
    const char* obtenerPassword() const;
    const char* obtenerCiudad() const;
    const char* obtenerPais() const;
    const char* obtenerFechaInscripcion() const;
    TipoMembresia obtenerTipoMembresia() const;
    const char* obtenerNombreTipoMembresia() const;

    // Metodos de validacion de membresia
    bool esPremium() const;
    bool esEstandar() const;

    // Calidad de audio segun membresia
    int obtenerCalidadAudio() const;  // Devuelve 128 o 320

    // Gestion de contador de reproducciones (para publicidad)
    void incrementarContadorReproducciones();
    int obtenerContadorReproducciones() const;
    void reiniciarContadorReproducciones();
    bool debeVerPublicidad() const;  // True cada 2 canciones

    // Gestion de lista de favoritos (solo Premium)
    bool crearListaFavoritos(const char* nombre = "Mis Favoritos");
    Playlist* obtenerListaFavoritos();
    const Playlist* obtenerListaFavoritos() const;
    bool tieneListaFavoritos() const;

    // Seguir a otro usuario (solo Premium)
    bool seguirUsuario(Usuario* otro_usuario);
    Usuario* obtenerUsuarioSeguido();
    const Usuario* obtenerUsuarioSeguido() const;
    bool estaSiguiendoUsuario() const;

    // Capacidades segun membresia
    bool puedeRetrocederCanciones(int num_canciones) const;
    int obtenerMaximoRetroceso() const;  // 0 para Estandar, 4 o 6 segun contexto

    // Mostrar informacion
    void mostrarPerfil() const;
    void mostrarInformacionCompleta() const;

    // Validaciones estaticas
    static bool validarNickname(const char* nickname);
    static bool validarFecha(const char* fecha);
};

#endif
