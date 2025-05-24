// VigasocoLibSDL.cpp
//
// Versión fake para montar la abadía como lib
/////////////////////////////////////////////////////////////////////////////

#include "VigasocoLibSDL.h"
#include <fstream>

extern unsigned char _binary_abadiaROM_bin_start[];
extern unsigned char _binary_abadiaROM_bin_end[];

extern "C" {
	void LibAbadIA_init() { 
		// TODO: que solo se ejecute una vez
		VigasocoLibSDL *vigasocoTest=new VigasocoLibSDL();
		VigasocoLibSDL::getSingletonPtr()->init(); 
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
		return res;
	}
}

// TODO Revisar si se mantiene esto
bool gb_test(false);  // ¿Bestamos en modo normal o ejecutando tests de pruebas?
std::string g_test("");  // Escenario de pruebas


VigasocoLibSDL::VigasocoLibSDL() {
	// para no copiar todo el código que interpretaba la ROM
	// la reordenaba y añadia los gráficos VGA y CPC
	// aquí tenemos embebido directamente un volcado de esa
	// información
	assert((_binary_abadiaROM_bin_end-_binary_abadiaROM_bin_start)==734451);

	_palette=new SDLPalette();
	_palette->init(256);
	_audioPlugin=new IAudioPlugin;
	_inputHandler=new InputHandler;
	_timingHandler=new TimingHandler;

	cs = new FakeCriticalSection();
	cs->init();

	cpc6128 = new CPC6128(cs);
/*
std::ifstream kk("abadiaROM.bin");
const unsigned int size = 734451;
UINT8 romData[size];
kk.read((char *)romData,size);
fprintf(stderr,"romData %d*%d\n", romData[0],romData[734451]); 	
fprintf(stderr,"abadiaROM %d*%d\n", abadiaROM[0],abadiaROM[734451]); 	
fprintf(stderr,"romData %d*%d\n", romData[1],romData[734450]); 	
fprintf(stderr,"abadiaROM %d*%d\n", abadiaROM[1],abadiaROM[734450]); 	
fprintf(stderr,"size abadiaROM %d\n", abadiaROM_size);
bool ok=true;
for (int i=0; i< size; i++) {
	if (romData[i]!=abadiaROM[i]) { ok=false; fprintf(stderr,"diff en %d\n",i); }
}
fprintf(stderr,"ok %d\n", ok);
*/

	_abadiaGame = new Abadia::Juego(_binary_abadiaROM_bin_start, cpc6128);
}

VigasocoLibSDL::~VigasocoLibSDL()
{
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

void VigasocoLibSDL::reset(void) {
	// pruebas por bug primera misa en behave
	if (_abadiaGame) delete _abadiaGame;
	_abadiaGame = new Abadia::Juego(_binary_abadiaROM_bin_start, cpc6128);
	init();
}
void VigasocoLibSDL::init(void) {
	_abadiaGame->init();
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
