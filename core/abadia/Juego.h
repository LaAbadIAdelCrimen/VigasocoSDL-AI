// Juego.h
//
//		Clase principal del juego. Almacena el estado y las entidades del juego.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _ABADIA_JUEGO_H_
#define _ABADIA_JUEGO_H_


#include "../util/Singleton.h"
#include "../Types.h"

#ifdef __abadIA__
#include <stack>
#endif

class CPC6128;					// definido en CPC6128.h
class IAudioPlugin;				// definido en IAudioPlugin.h
class TimingHandler;			// definido en TimingHandler.h

namespace Abadia {

class Controles;				// definido en Controles.h
#ifndef __libabadIA__
class InfoJuego;				// definido en InfoJuego.h
#endif
class Logica;					// definido en Logica.h
class Marcador;					// definido en Marcador.h
class MotorGrafico;				// definido en MotorGrafico.h
class Objeto;					// definido en Objeto.h
class Paleta;					// definido en Paleta.h
class Pergamino;				// definido en Pergamino.h
class Personaje;				// definido en Personaje.h
class Puerta;					// definido en Puerta.h
class Sprite;					// definido en Sprite.h

#define elJuego Juego::getSingletonPtr()

class Juego : public Singleton<Juego>
{
// constantes
public:
	static const int numPersonajes = 8;
	static const int numPuertas = 7;
	static const int numObjetos = 8;

	static const int primerSpritePersonajes = 0;
	static const int primerSpritePuertas = primerSpritePersonajes + numPersonajes;
	static const int primerSpriteObjetos = primerSpritePuertas + numPuertas;
	static const int spritesReflejos = primerSpriteObjetos + numObjetos;
	static const int spriteLuz = spritesReflejos + 2;
	static const int numSprites = spriteLuz + 1;
	static const char *savefile[7];

// campos
private:
	bool mute;
	unsigned short slot;
	int _numInterruptsPerLogicUpdate=0x24;
public:
	int idioma;  // idioma de los textos TODO ponerlo como un enumerado
	// GraficosCPC estaba como privado
	// se pone como publico para que pueda acceder
	// el MotorGrafico.cpp y decidir si tiene que parchear las pantallas
	// o no
	// TODO: Poner metodos get para no dar acceso directo y que lo 
	// pueda cambiar por error desde otro lado
	bool GraficosCPC; // Indica si se usan los datos del archivo GraficosCPC
			  // o del GraficosVGA
			  // En ambos casos, son de 8 bits
	CPC6128 *cpc6128;						// objeto de ayuda para realizar operaciones gráficas del cpc6128
	IAudioPlugin *audio_plugin;	// puntero al plugin de audio
	Controles *controles;					// acceso a los controles del juego
	Paleta *paleta;							// paleta del juego
	TimingHandler *timer;					// manejador del temporizador
	UINT8 buffer[8192];						// buffer para mezclar los sprites y para buscar las rutas
	UINT8 *roms;							// puntero a las roms originales

	Logica *logica;							// objeto que se encarga de gestionar la lógica del juego
	Pergamino *pergamino;					// pergamino para la presentación y el final
	Marcador *marcador;						// marcador del juego
	MotorGrafico *motor;					// motor gráfico

	Sprite *sprites[numSprites];			// sprites del juego
	Puerta *puertas[numPuertas];			// puertas del juego
	Objeto *objetos[numObjetos];			// objetos del juego
	Personaje *personajes[numPersonajes];	// personajes del juego

	volatile int contadorInterrupcion;		// contador incrementado en la interrupción para sincronizar el juego

	bool pausa;								// indica si el juego está pausado
	bool modoInformacion;					// modo de información del juego
	bool cambioModoInformacion; // se ha cambiado el estado
#ifndef __libabadIA__
	InfoJuego *infoJuego;					// objeto para mostrar información interna del juego
#endif
#ifdef __abadIA__
	std::stack<int> frases; // una pila con todas las frases dichas desde el Ãltimo dump
#endif

// métodos
private:
	void reinicio();
	bool cargar(int slot);
	void save(int slot);
	// TODO sacar todo lo relativo a menus
	// a una clase para menu y no ensuciar la clase Juego
	void pintaMenuCargar(int seleccionado,bool efecto=false);
	bool menuCargar(void);
	void pintaMenuGrabar(int seleccionado,bool efecto=false);
	bool menuGrabar(void);
	//void pintaMenuIntroduccion(int seleccionado); //NO SE USA
	bool menuIntroduccion(void);
	void pintaMenuTeclado(int seleccionado);
	bool menuTeclado(void);
	void pintaMenuCamaras(int seleccionado);
	bool menuCamaras(void);
	void pintaMenuMejoras(int seleccionado);
	bool menuMejoras(void);
	void pintaMenuTutorial(int seleccionado,bool efecto=false);
	bool menuTutorial(void);
	void pintaMenuAyuda(int seleccionado,bool efecto=false);
	bool menuAyuda(void);
	void pintaMenuIdioma(int seleccionado,bool efecto=false);
	bool menuIdioma(void);
	void pintaMenuPrincipal(int seleccionado,bool efecto=false);
	bool menu(void);
	void cambioCPC_VGA(void);
	void compruebaCambioCPC_VGA(void);
	bool compruebaMenu(void);
	void ReiniciaPantalla(void);
#ifdef __abadIA__
	void compruebaEscenarioPrueba(void);
#endif
	int step(void);
public:
#ifdef __libabadIA__
	void init(void);
#endif
	void muestraFinal();
	void limpiaAreaJuego(int color);

	// bucle principal del juego
	void run();
#ifdef __libabadIA__
	//int step2(int controles[END_OF_INPUTS]);
	//int step2(void);
	int step(int *source); //TODO ¿const? ¿o usar references?
#endif

	// inicialización y limpieza
	Juego(UINT8 *romData, CPC6128 *cpc);
	~Juego();

protected:
	void muestraPresentacion();
	void muestraIntroduccion();
	bool muestraPantallaFinInvestigacion();

	void creaEntidadesJuego();
	
	void actualizaLuz();
	void generaGraficosFlipeados();
	void flipeaGraficos(UINT8 *tablaFlip, UINT8 *src, UINT8 *dest, int ancho, int bytes);
	void generaGraficosFlipeadosVGA();
	void flipeaGraficosVGA(UINT8 *src, UINT8 *dest, int ancho, int bytes);

	bool compruebaReinicio();
	void compruebaPausa();
	bool compruebaLoad();
	void compruebaSave();
};


}

#endif	// _ABADIA_JUEGO_H_
