#include <fstream>
#include "../core/Types.h"
#include "SDLCriticalSection.h"
#include "../core/systems/cpc6128.h"
#include "../core/abadia/Juego.h"
#include "VigasocoLibSDL.h"

using namespace Abadia;

//VigasocoLibSDL gVigasocoLibSDL;

//VigasocoLibSDL*VigasocoMain=&gVigasocoLibSDL;

// TODO: ¿este modo se puede eliminar?
bool gb_test(false);  // Âestamos en modo normal o ejecutando tests de pruebas?
std::string g_test("");  // Escenario de pruebas

int main(int argc, char **argv) {

	VigasocoLibSDL vigasocoTest;

	//std::ifstream kk("volcadorom",std::ofstream::binary);
	std::ifstream kk("volcadorom");
	const unsigned int size = 734451;
	UINT8 romData[size];
	Abadia::Juego *_abadiaGame=NULL;		// objeto principal del juego
	CPC6128 *cpc6128=NULL;				// clase de ayuda para realizar operaciones gráficas
	ICriticalSection *cs=NULL;			// sección crítica para sincronizar la escritura de gráficos
	kk.read((char *)romData,size);
fprintf(stderr,"m1 %p\n",VigasocoMain);
	// crea e inicia la sección crítica para la sincronización del dibujado de gráficos
	cs = VigasocoMain->createCriticalSection();
fprintf(stderr,"m2\n");
//	cs = new SDLCriticalSection();
	cs->init();
fprintf(stderr,"m3\n");

	//crea el objeto para tratar con gráficos del amstrad
	cpc6128 = new CPC6128(cs);
fprintf(stderr,"m4\n");
	_abadiaGame = new Abadia::Juego(romData, cpc6128);
fprintf(stderr,"m5\n");

	_abadiaGame->run();
fprintf(stderr,"m6\n");

	// destruye la sección crítica
	if (cs != 0){
		cs->destroy();
		delete cs;
	}

	// borra el objeto de ayuda para los gráficos
	if (cpc6128) delete cpc6128;

	// borra el objeto del juego
	if (_abadiaGame) delete _abadiaGame;

	return 0;
}

