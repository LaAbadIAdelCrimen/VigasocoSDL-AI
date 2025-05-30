// VigasocoLibSDL.h
//
// Versión fake para montar la abadía como librería independiente
/////////////////////////////////////////////////////////////////////////////

#ifndef _VIGASOCO_LIBSDL_H_
#define _VIGASOCO_LIBSDL_H_

#include "../core/util/Singleton.h"
#include <string>
#include "Types.h"
//#include "SDL.h"
//#include "IPalette.h"
#include "SDLPalette.h"

#include "../core/abadia/Juego.h"
#include "../core/systems/cpc6128.h"

#include "../core/ICriticalSection.h"
#include <sys/time.h>
#include <cstring>

class IAudioPlugin {
private:
	bool sonidos[12]={0,0,0,0,0,0,0,0,0,0,0,0}; 
	bool sonidoslib[12]={0,0,0,0,0,0,0,0,0,0,0,0}; 
	// TODO, creo que se puede simplificar los sonidos
	// ahora que se devuelve dump en cada paso
// getters
public:
	virtual void Play(int sample, bool loop=false) { 
		// TODO: falta assert para comprobar rango
	                if ((sample>= 0) && (sample < 12)){ // TODO: no usar constante 12
		sonidos[sample]=true;
		sonidoslib[sample]=true;
			} 
//			else fprintf(stderr,"Play sample BAD INDEX %d\n",sample);
//fprintf(stderr,"Play sample %d arrayi %d\n",sample,sonidos[sample]);
	};
	virtual void Stop(int sample) {
	                if ((sample >= 0) && (sample < 12)){ // TODO: no usar constante 12
		sonidoslib[sample]=false;
			} 
//			else fprintf(stderr,"STOP sample BAD INDEX %d\n",sample);
	};
        virtual void setProperty(std::string prop, int data) {};
        virtual void setProperty(std::string prop, int index, int data) {
		if (prop == "sonidos"){
                	//if ((index >= 0) && (index < SONIDOS::END_OF_SOUNDS)){
	                if ((index >= 0) && (index < 12)){ // TODO: no usar constante 12
                        	sonidos[index]=data;
				sonidoslib[index]=data;
                	}
//			else fprintf(stderr,"setProperty sonidos sample BAD INDEX %d\n",index);
		}
//../core/abadia/Juego.cpp:       audio_plugin->Play(SONIDOS::Inicio,true);
//../core/abadia/Juego.cpp:       audio_plugin->Play(SONIDOS::Final,true);
//../core/abadia/Logica.cpp:              VigasocoMain->getAudioPlugin()->Play(SONIDOS::Fondo,true);
// en la version HTTP cuando se pedía explicitamente un dump se borraban los sonidos
// asi si sonaban varias cosas cuando se consultaba se tenia acumulado todo lo que había sonado
// en la lib se hace un dump al final de cada paso 
// no se puede poner todo a false al acabar porque hay sonidos que suena solo un momento
// mientras que 
		if (prop == "resetSonidosLib") {
			static const UINT8 Abrir = 0;
			static const UINT8 Aporrear = 1;
			static const UINT8 Campanas = 2;
			static const UINT8 Cerrar = 3;
			static const UINT8 Coger = 4;
			static const UINT8 Dejar = 5;
			static const UINT8 Espejo = 6;
			static const UINT8 Final = 7;
			static const UINT8 Fondo = 8;
			static const UINT8 Inicio = 9;
			static const UINT8 Pasos = 10;
			static const UINT8 Tintineo = 11;
			sonidoslib[Abrir]=false;
			sonidoslib[Aporrear]=false;
			sonidoslib[Campanas]=false;
			sonidoslib[Cerrar]=false;
			sonidoslib[Coger]=false;
			sonidoslib[Dejar]=false;
			sonidoslib[Espejo]=false;
			//sonidoslib[Final]=false;
			//sonidoslib[Fondo]=false;
			//sonidoslib[Inicio]=false;
			sonidoslib[Pasos]=false;
			sonidoslib[Tintineo]=false;
		} 
        };

	virtual int getProperty(std::string prop,int index) { 
		if (prop == "sonidos"){
			//if ((index >= 0) && (index < SONIDOS::END_OF_SOUNDS)){
			if ((index >= 0) && (index < 12)){ // TODO: no usar constante 1
				return sonidoslib[index];
//				return sonidos[index];
			}
//			else fprintf(stderr,"getProperty resetsonidoslib sample BAD INDEX %d\n",index);
		}
		return -1;
	};
};


// TODO: quitar los .o inncesarios del makefile
class InputHandler {
private:
	int _controles[END_OF_INPUTS];
// methods
public:
	void copyInputsState(int *dest) { memcpy(dest,_controles,sizeof(int)*END_OF_INPUTS); };  
	// getters
	void acquire() {};
        void unAcquire() {};

	void process(int controles[END_OF_INPUTS]) { 
		memcpy(_controles,controles,sizeof(int)*END_OF_INPUTS); 
		// equivalencias por si al agente le da por usar las otras
		// alternativas de las instrucciones originales
		if (_controles[KEYBOARD_A]) _controles[P1_UP]=1;
		if (_controles[KEYBOARD_K]) _controles[P1_RIGHT]=1;
		if (_controles[KEYBOARD_L]) _controles[P1_LEFT]=1;
		if (_controles[KEYBOARD_Z]) _controles[P1_DOWN]=1;
		// en realidad Vigasoco emula mal porque el P1_BUTTON1 lo equivale al espacio
		// pero en realidad debería ser igual a P1_DOWN:
	}; 
};

class TimingHandler {
// methods
public:
	// timer functions
        //INT64 getTime(){ return SDL_GetTicks(); }
	// en abadIA solo se usa para el numero aleatorio del laberinto
        INT64 getTime(){ 
		struct timeval tmp;
		gettimeofday(&tmp, NULL);
		return tmp.tv_sec*1000+tmp.tv_usec/1000;
	}
	void sleep(UINT32 milliSeconds) { };
	
};

class FakeCriticalSection: public ICriticalSection {
public:
	FakeCriticalSection() {};
	void init() {};
	void enter() {};
	void leave() {};
	void destroy() {};
};

class IPalette;

#define VigasocoMain VigasocoLibSDL::getSingletonPtr()

//#include "Vigasoco.h"
//class ICriticalSection;	// defined in ICriticalSection.h
//class VigasocoLibSDL : public Vigasoco
class VigasocoLibSDL:  public Singleton<VigasocoLibSDL> 
{
// private
	Abadia::Juego *_abadiaGame=NULL;
	CPC6128 *cpc6128=NULL;
	ICriticalSection *cs=NULL;	

// fields
protected:
	IAudioPlugin *_audioPlugin=NULL;
	InputHandler *_inputHandler=NULL;
	TimingHandler *_timingHandler=NULL;
	IPalette *_palette=NULL;
// methods
public:
	// initialization and cleanup
	VigasocoLibSDL();
	virtual ~VigasocoLibSDL();
	void init(void);
void reset(void);
	// platform services
	//virtual ICriticalSection *createCriticalSection();

	// getters
	IPalette *getPalette() const { return _palette; }
	IAudioPlugin *getAudioPlugin() const { return _audioPlugin; }
	InputHandler *getInputHandler() const { return _inputHandler; }
        TimingHandler *getTimingHandler() const { return _timingHandler; }

	//
	//void step(int *controles);
	std::string step(int *controles);
	std::string save(void);
	bool load(std::string input);
};

#endif	// _VIGASOCO_LIBSDL_H_

/*

// VigasocoSDL.h
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _VIGASOCO_SDL_H_
#define _VIGASOCO_SDL_H_


#include "Vigasoco.h"
#include "PluginHandler.h"
#include "ILoader.h"
#include <string>
#include <vector>

class VigasocoSDL : public Vigasoco
{
// types
public:
	typedef std::vector<std::string> Strings;

// constants
protected:
	static int g_currentVideoPluginVersion;
	static int g_currentInputPluginVersion;
	static int g_currentLoaderPluginVersion;
	static int g_currentAudioPluginVersion;

	static std::string g_videoPluginPath;
	static std::string g_inputPluginPath;
	static std::string g_loaderPluginPath;
	static std::string g_audioPluginPath;

// types
protected:
	typedef std::vector<DLLEntry> DLLEntries;

// fields
protected:
	// port options
	std::string _sDrawPluginsDLL;
	std::string _sDrawPlugin;
	Strings _sInputPluginsDLLs;
	Strings _sInputPlugins;
	std::string _sAudioPluginsDLL;
	std::string _sAudioPlugin;
	Strings _sPaths;

	// DLL stuff
	PluginHandler *_pluginHandler;
	DLLEntry _drawPluginInfo;
	DLLEntries _inputPluginsInfo;
	DLLEntry _audioPluginInfo;
	DLLEntries _loaderPluginsInfo;

// methods
public:
	// initialization and cleanup
	VigasocoSDL(std::string game,
			std::string drawPluginsDLL, std::string drawPlugin,
			Strings inputPluginsDLLs, Strings inputPlugins,
			std::string audioPluginsDLL, std::string audioPlugin,
			Strings paths);
	virtual ~VigasocoSDL();

	// platform services
	virtual ICriticalSection *createCriticalSection();

protected:
	// template methods overrides

	// construction
	virtual bool platformSpecificInit();
	virtual void createPalette();
	virtual void addCustomLoaders(FileLoader *fl);
	virtual void createDrawPlugin();
	virtual void createAudioPlugin();
	virtual void addCustomInputPlugins();
	virtual void createTimer();
	virtual void createAsyncThread();
	virtual void initCompleted();

	// destruction
	virtual void destroyAsyncThread();
	virtual void destroyTimer();
	virtual void removeCustomInputPlugins();
	virtual void destroyDrawPlugin();
	virtual void destroyAudioPlugin();
	virtual void removeCustomLoaders(FileLoader *fl);
	virtual void destroyPalette();
	virtual void platformSpecificEnd();

	virtual bool processEvents();

private:
};

#endif	// _VIGASOCO_SDL_H_

*/
