// VigasocoLibSDL.cpp
//
// Versión fake para montar la abadía como lib
/////////////////////////////////////////////////////////////////////////////

#include "VigasocoLibSDL.h"
#include <fstream>

unsigned char *abadiaROM;

extern "C" {
	void LibAbadIA_init() {
		VigasocoLibSDL *vigasocoTest=new VigasocoLibSDL();
		VigasocoLibSDL::getSingletonPtr()->init();
        // fprintf(stderr,"LibAbadIA_init() singleton %p\n", VigasocoLibSDL::getSingletonPtr());
	}

    char *LibAbadIA_step(int *controles, char *resultado, size_t resultadoMaxLength) {
		std::string tmp=VigasocoLibSDL::getSingletonPtr()->step(controles);
		strncpy(resultado,tmp.c_str(), resultadoMaxLength>=tmp.length()+1?tmp.length()+1:resultadoMaxLength-1);
		return resultado;
    }

    char *LibAbadIA_save(char *savedata, size_t saveMaxLength) {
		std::string tmp=VigasocoLibSDL::getSingletonPtr()->save();
		strncpy(savedata, tmp.c_str(), saveMaxLength>=tmp.length()+1?tmp.length()+1:saveMaxLength-1);
		return savedata;
	}

    bool LibAbadIA_load(const char * const input) {
		VigasocoLibSDL::getSingletonPtr()->reset();
		bool res=VigasocoLibSDL::getSingletonPtr()->load(input);
		// fprintf(stderr,"C load %d un bool true es %d y un false es %d\n",res,true,false);
		return res;
	}
}

// TODO: ¿este modo se puede eliminar?
bool gb_test(false);  // Âestamos en modo normal o ejecutando tests de pruebas?
std::string g_test("");  // Escenario de pruebas
VigasocoLibSDL::VigasocoLibSDL() {

    // fprintf(stderr,"constructor VigasocoLibSDL\n");
    // JT: aqui es donde cargo la ROM a cholon
    // fprintf(stderr,"Cargando la ROM\n");
    abadiaROM = new unsigned char[734451];
    std::ifstream fin("abadiaROM.bin");
    if(!fin)
          printf("failed to load abadiaROM.bin");
    fin.read((char *)abadiaROM, 734451);
    fin.close();
   //  fprintf(stderr,"Cargada\n");

	_palette=new SDLPalette();
	_palette->init(256);
	_audioPlugin=new IAudioPlugin;
	_inputHandler=new InputHandler;
	_timingHandler=new TimingHandler;

	//cs = new SDLCriticalSection();
	cs = new FakeCriticalSection();
	cs->init();

	cpc6128 = new CPC6128(cs);
 	_abadiaGame = new Abadia::Juego(abadiaROM, cpc6128);
}

VigasocoLibSDL::~VigasocoLibSDL()
{
// fprintf(stderr,"destructir VigasocoLibSDL\n");
	// destruye la sección crítica
	if (cs != 0){
		cs->destroy();
		delete cs;
	}

	// borra el objeto de ayuda para los gráficos
	if (cpc6128) delete cpc6128;

	// borra el objeto del juego
	if (_abadiaGame) delete _abadiaGame;
}
/*
ICriticalSection * VigasocoLibSDL::createCriticalSection()
{
	return new SDLCriticalSection();
}
*/
void VigasocoLibSDL::reset(void) {
// pruebas por bug primera misa en behave
if (_abadiaGame) delete _abadiaGame;
_abadiaGame = new Abadia::Juego(abadiaROM, cpc6128); init();
}
void VigasocoLibSDL::init(void) {
// fprintf(stderr," VigasocoLibSDL::init\n");
	_abadiaGame->init();
// fprintf(stderr,"FIN VigasocoLibSDL::init\n");
}

std::string VigasocoLibSDL::step(int *controles) {
    return	_abadiaGame->step(controles);
}

std::string VigasocoLibSDL::save(void) {
    return	_abadiaGame->save();
}

bool VigasocoLibSDL::load(std::string input) {
    return	_abadiaGame->cargar(input);
}


