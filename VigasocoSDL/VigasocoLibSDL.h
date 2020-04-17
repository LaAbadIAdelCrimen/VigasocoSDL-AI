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
	bool sonidos[12]; 
	// TODO, creo que se puede simplificar los sonidos
	// ahora que se devuelve dump en cada paso
// getters
public:
	virtual void Play(int sample, bool loop=false) { 
		// TODO: falta assert para comprobar rango
//fprintf(stderr,"IAudioPlugin::Play %d\n",sample);
		sonidos[sample]=true;
	};
	virtual void Stop(int sample) {};
        virtual void setProperty(std::string prop, int data) {};
        virtual void setProperty(std::string prop, int index, int data) {
//fprintf(stderr,"IAudioPlugin setproperty %s index %d data %d\n",prop.c_str(),index,data);
		if (prop == "sonidos"){
                	//if ((index >= 0) && (index < SONIDOS::END_OF_SOUNDS)){
	                if ((index >= 0) && (index < 12)){ // TODO: no usar constante 12
                        	sonidos[index]=data;
                	}
		}
        };

	virtual int getProperty(std::string prop,int index) { 
		if (prop == "sonidos"){
			//if ((index >= 0) && (index < SONIDOS::END_OF_SOUNDS)){
			if ((index >= 0) && (index < 12)){ // TODO: no usar constante 1
				return sonidos[index];
			}
		}
	};
};


// TODO: quitar los .o inncesarios del makefile
class InputHandler {
private:
	int _controles[END_OF_INPUTS];
// methods
public:
//	void copyInputsState(int *dest) { memcpy(dest,_controles,sizeof(int)*END_OF_INPUTS); dest[KEYBOARD_E]=1; };  // fprintf(stderr,"InputHandler::copyInputsState fake UP\n");};
	void copyInputsState(int *dest) { memcpy(dest,_controles,sizeof(int)*END_OF_INPUTS); };  // fprintf(stderr,"InputHandler::copyInputsState fake UP\n");};
	// getters
	void acquire() {};
        void unAcquire() {};

	void process(int controles[END_OF_INPUTS]) { memcpy(_controles,controles,sizeof(int)*END_OF_INPUTS); }; // fprintf(stderr,"InputHandler::process fake UP\n"); };
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
	//void sleep(UINT32 milliSeconds) { fprintf(stderr,"TimingHandler::sleep %d\n",milliSeconds); };
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
