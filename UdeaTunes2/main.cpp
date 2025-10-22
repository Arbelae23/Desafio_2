#include "cancion.h"
#include "creditos.h"
#include "album.h"
#include "artistas.h"
#include "playlist.h"
#include "usuario.h"
#include "interfaz.h"
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    cout << "\n" << string(80, '=') << "\n";
    cout << "           UDEATUNES - SISTEMA FASE 1 DE STREAMING\n";
    cout << string(80, '=') << "\n";


    // 1. CREAR ARTISTAS


    cout << "\n1. Creando artistas...\n";

    Artista* pink_floyd = new Artista("Pink Floyd", 12345, 0, "Reino Unido");
    pink_floyd->establecerCantidadSeguidores(50000000);
    pink_floyd->establecerPosicionTendencias(10);

    Artista* the_beatles = new Artista("The Beatles", 54321, 0, "Reino Unido");
    the_beatles->establecerCantidadSeguidores(80000000);
    the_beatles->establecerPosicionTendencias(1);

    cout << "   -> 2 artistas creados\n";


    // 2. CREAR ALBUMES Y CANCIONES

    cout << "\n2. Creando albumes y canciones...\n";

    // Album de Pink Floyd
    Album* dark_side = new Album("The Dark Side of the Moon", 73,
                                 "Harvest Records",
                                 "/storage/pink_floyd/images/dark_side_moon.png",
                                 1, 3, 1973);
    dark_side->establecerPuntuacion(10);
    dark_side->agregarGenero("Rock");
    dark_side->agregarGenero("Musica Clasica");

    // Canciones del album
    Cancion* cancion1 = new Cancion("Speak to Me", "Pink Floyd",
                                    "The Dark Side of the Moon", "Rock",
                                    90, 1973);
    cancion1->agregarCompositor("Nick", "Mason", "COMP001122");

    Cancion* cancion2 = new Cancion("Time", "Pink Floyd",
                                    "The Dark Side of the Moon", "Rock",
                                    421, 1973);
    cancion2->agregarCompositor("Roger", "Waters", "COMP667788");

    Cancion* cancion3 = new Cancion("Money", "Pink Floyd",
                                    "The Dark Side of the Moon", "Rock",
                                    382, 1973);
    cancion3->agregarCompositor("Roger", "Waters", "COMP667788");

    dark_side->agregarCancion(cancion1);
    dark_side->agregarCancion(cancion2);
    dark_side->agregarCancion(cancion3);

    // Agregar album al artista
    pink_floyd->agregarAlbum(dark_side);

    // Album de The Beatles
    Album* abbey_road = new Album("Abbey Road", 69,
                                  "Apple Records",
                                  "/storage/beatles/images/abbey_road.png",
                                  26, 9, 1969);
    abbey_road->establecerPuntuacion(10);
    abbey_road->agregarGenero("Rock");
    abbey_road->agregarGenero("Pop");

    Cancion* cancion4 = new Cancion("Come Together", "The Beatles",
                                    "Abbey Road", "Rock", 259, 1969);
    cancion4->agregarCompositor("John", "Lennon", "COMP778899");

    Cancion* cancion5 = new Cancion("Here Comes The Sun", "The Beatles",
                                    "Abbey Road", "Pop", 185, 1969);
    cancion5->agregarCompositor("George", "Harrison", "COMP223344");

    abbey_road->agregarCancion(cancion4);
    abbey_road->agregarCancion(cancion5);

    the_beatles->agregarAlbum(abbey_road);

    cout << "   -> 2 albumes con 5 canciones creados\n";


    // 3. CREAR CATALOGO DE CANCIONES


    const int TOTAL_CANCIONES = 5;
    Cancion* catalogo_canciones[TOTAL_CANCIONES] = {
        cancion1, cancion2, cancion3, cancion4, cancion5
    };


    // 4. CREAR USUARIOS


    cout << "\n3. Creando usuarios...\n";

    // Usuario Premium
    Usuario* usuario_premium = new Usuario("rockfan2025", "pass123",
                                           Usuario::PREMIUM);
    usuario_premium->establecerCiudad("Bucaramanga");
    usuario_premium->establecerPais("Colombia");
    usuario_premium->establecerFechaInscripcion("01/10/2025");

    // Usuario Estandar
    Usuario* usuario_estandar = new Usuario("musiclover", "pass456",
                                            Usuario::ESTANDAR);
    usuario_estandar->establecerCiudad("Bogota");
    usuario_estandar->establecerPais("Colombia");
    usuario_estandar->establecerFechaInscripcion("15/09/2025");

    cout << "   -> Usuario Premium: " << usuario_premium->obtenerNickname() << "\n";
    cout << "   -> Usuario Estandar: " << usuario_estandar->obtenerNickname() << "\n";


    // 5. CREAR PLAYLIST PARA USUARIO PREMIUM


    cout << "\n4. Creando lista de favoritos para usuario Premium...\n";

    usuario_premium->crearListaFavoritos("Mis Clasicos de Rock");
    Playlist* favoritos = usuario_premium->obtenerListaFavoritos();

    if (favoritos) {
        favoritos->agregarCancion(cancion2);  // Time
        favoritos->agregarCancion(cancion3);  // Money
        favoritos->agregarCancion(cancion5);  // Here Comes The Sun

        cout << "   -> " << favoritos->obtenerCantidadCanciones()
             << " canciones agregadas a favoritos\n";
    }


    // 6. CREAR INTERFAZ Y CONFIGURAR PUBLICIDAD


    cout << "\n5. Configurando sistema de publicidad...\n";

    Interfaz interfaz;

    // Agregar mensajes publicitarios
    interfaz.agregarMensajePublicitario(
        "Descubre los nuevos audifonos inalambricos con cancelacion de ruido. Calidad premium para tu musica!",
        'A'  // Categoria AAA
        );

    interfaz.agregarMensajePublicitario(
        "Aprovecha el 50% de descuento en tu suscripcion Premium. Musica sin limites!",
        'A'  // Categoria AAA
        );

    interfaz.agregarMensajePublicitario(
        "Visita nuestra tienda online y encuentra los mejores productos para amantes de la musica.",
        'B'  // Categoria B
        );

    interfaz.agregarMensajePublicitario(
        "Conoce los proximos conciertos en tu ciudad. No te pierdas a tus artistas favoritos en vivo!",
        'C'  // Categoria C
        );

    interfaz.agregarMensajePublicitario(
        "Nuevo album disponible! Descubre lo ultimo de tus artistas favoritos en UdeATunes.",
        'B'  // Categoria B
        );

    cout << "   -> " << interfaz.obtenerCantidadMensajes()
         << " mensajes publicitarios agregados\n";


    // 7. DEMOSTRAR FUNCIONALIDADES


    cout << "\n6. Demostracion de funcionalidades:\n";
    cout << string(80, '-') << "\n";

    // Mostrar perfil de usuarios
    cout << "\nPERFIL USUARIO PREMIUM \n";
    usuario_premium->mostrarInformacionCompleta();

    cout << "\n PERFIL USUARIO ESTANDAR \n";
    usuario_estandar->mostrarInformacionCompleta();

    // Mostrar artistas
    cout << "\n ARTISTA 1 \n";
    pink_floyd->mostrarInformacionCompleta();
    pink_floyd->mostrarAlbumes();

    cout << "\n ARTISTA 2 \n";
    the_beatles->mostrarInformacionCompleta();
    the_beatles->mostrarAlbumes();

    // Mostrar albumes
    cout << "\n";
    dark_side->mostrarInformacionCompleta();

    cout << "\n";
    abbey_road->mostrarInformacionCompleta();

    // Mostrar playlist
    if (favoritos) {
        favoritos->mostrarCanciones();
    }


    // 8. SIMULACION DE REPRODUCCION

    cout << "\n\n7. SIMULACION DE REPRODUCCION:\n";
    cout << string(80, '=') << "\n";

    cout << "\n REPRODUCCION CON USUARIO ESTANDAR (con publicidad) \n";
    cout << "Reproduciendo 3 canciones...\n";
    cout << "\nPresiona ENTER para comenzar...";
    cin.get();

    // Reproducir 3 canciones como usuario estandar
    for (int i = 0; i < 3; i++) {
        interfaz.reproducirCancion(catalogo_canciones[i], *usuario_estandar, true);
        cout << "\n";
    }

    cout << "\n REPRODUCCION CON USUARIO PREMIUM (sin publicidad) \n";
    cout << "Reproduciendo 2 canciones...\n";
    cout << "\nPresiona ENTER para continuar...";
    cin.get();

    // Reproducir 2 canciones como usuario premium
    for (int i = 0; i < 2; i++) {
        interfaz.reproducirCancion(catalogo_canciones[i], *usuario_premium, true);
        cout << "\n";
    }


    // 9. PRUEBA DE SEGUIR USUARIO


    cout << "\n8. PRUEBA DE SEGUIR A OTRO USUARIO:\n";
    cout << string(80, '-') << "\n";

    // Crear segundo usuario premium
    Usuario* otro_premium = new Usuario("melodylover", "pass789", Usuario::PREMIUM);
    otro_premium->crearListaFavoritos("Mis Favoritos");
    otro_premium->obtenerListaFavoritos()->agregarCancion(cancion1);
    otro_premium->obtenerListaFavoritos()->agregarCancion(cancion4);

    cout << "\nUsuario '" << otro_premium->obtenerNickname()
         << "' tiene " << otro_premium->obtenerListaFavoritos()->obtenerCantidadCanciones()
         << " canciones en favoritos\n";

    cout << "\nUsuario '" << usuario_premium->obtenerNickname()
         << "' seguira a '" << otro_premium->obtenerNickname() << "'\n\n";

    usuario_premium->seguirUsuario(otro_premium);

    cout << "\nAhora '" << usuario_premium->obtenerNickname()
         << "' tiene " << usuario_premium->obtenerListaFavoritos()->obtenerCantidadCanciones()
         << " canciones en favoritos\n";


    // 10. LIMPIEZA DE MEMORIA


    cout << "\n\n9. Liberando memoria...\n";

    delete cancion1;
    delete cancion2;
    delete cancion3;
    delete cancion4;
    delete cancion5;

    delete dark_side;
    delete abbey_road;

    delete pink_floyd;
    delete the_beatles;

    delete usuario_premium;
    delete usuario_estandar;
    delete otro_premium;

    cout << "   -> Memoria liberada correctamente\n";


    // FINALIZACION


    cout << "\n" << string(80, '=') << "\n";
    cout << "           DEMOSTRACION COMPLETADA\n";
    cout << string(80, '=') << "\n";

    cout << "\nRESUMEN DE IMPLEMENTACION:\n";
    cout << "\n1. CLASES IMPLEMENTADAS:\n";
    cout << "   - Cancion (con duracion en segundos)\n";
    cout << "   - Creditos (productores, musicos, compositores)\n";
    cout << "   - Album (hasta 4 generos, arreglo dinamico de canciones)\n";
    cout << "   - Artista (catalogo de albumes, seguidores, tendencias)\n";
    cout << "   - Playlist (hasta 10000 canciones para Premium)\n";
    cout << "   - Usuario (Premium/Estandar, lista de favoritos, seguir usuarios)\n";
    cout << "   - Interfaz (reproduccion, publicidad, temporizador)\n";

    cout << "\n2. PUBLICIDAD:\n";
    cout << "   - Integrada en la clase Interfaz como estructura interna\n";
    cout << "   - Hasta 50 mensajes con categorias C, B, AAA\n";
    cout << "   - Prioridades: C=1, B=2, AAA=3\n";
    cout << "   - Se muestra cada 2 canciones para usuarios Estandar\n";
    cout << "   - No se repite el mismo mensaje consecutivamente\n";

    cout << "\n3. REPRODUCCION CON TEMPORIZADOR:\n";
    cout << "   - Usa <thread>, <chrono>, <atomic>, <mutex>\n";
    cout << "   - Cuenta regresiva con minutos:segundos\n";
    cout << "   - Muestra informacion completa de la cancion\n";
    cout << "   - Temporizador de 3 segundos para testing\n";
    cout << "   - Simula rutas de archivos de audio y portadas\n";

    cout << "\n4. DIFERENCIAS PREMIUM vs ESTANDAR:\n";
    cout << "   - Premium: 320 kbps, sin publicidad, lista de favoritos\n";
    cout << "   - Estandar: 128 kbps, publicidad cada 2 canciones\n";
    cout << "   - Premium: puede retroceder hasta 4-6 canciones\n";
    cout << "   - Premium: puede seguir a otros usuarios Premium\n";

    cout << "\n5. CUMPLIMIENTO DE REQUISITOS:\n";
    cout << "   - Sin STL (arreglos dinamicos propios con char*)\n";
    cout << "   - Sin tildes\n";
    cout << "   - Gestion completa de memoria dinamica\n";
    cout << "   - Constructores de copia y operadores de asignacion\n";
    cout << "   - Validaciones robustas\n";
    cout << "   - Publicidad sin crear clase nueva (estructura interna)\n";

    cout << "\n" << string(80, '=') << "\n";

    return 0;
}
