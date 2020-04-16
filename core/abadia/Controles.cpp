// Controles.cip
//
/////////////////////////////////////////////////////////////////////////////

#include "Controles.h"

// para memset
#include <string.h>

using namespace Abadia;

/////////////////////////////////////////////////////////////////////////////
// inicialización y limpieza
/////////////////////////////////////////////////////////////////////////////

Controles::Controles()
{
	ih = 0;
}

Controles::~Controles()
{
}

/////////////////////////////////////////////////////////////////////////////
// métodos
/////////////////////////////////////////////////////////////////////////////

// inicia los controles para el juego
void Controles::init(InputHandler *input)
{
	ih = input;
	memset(_oldControles, 0, END_OF_INPUTS);
}

// actualiza el estado de los controles
void Controles::actualizaEstado()
{
//#ifndef __libabadIA__
	// obtiene el estado de los controles
	ih->copyInputsState(_controles);
//fprintf(stderr,"Controles::actualizaEstado llamo a copyInputsState\n");


//#else
//_controles[P1_UP]=1;
//#endif
//fprintf(stderr,"Controles::actualizaEstado _oldControles UP %d controles UP %d\n",_oldControles[P1_UP],_controles[P1_UP]);
//fprintf(stderr,"Controles::actualizaEstado _oldControles RESET %d controles RESET %d\n",_oldControles[P1_UP],_controles[P1_UP]);

	// combina el estado actual de los controles con el anterior para poder detectar pulsaciones
	for (int i = 0; i < END_OF_INPUTS; i++){
		_oldControles[i] = (_oldControles[i] << 1) & 0x03;
		if (_controles[i] > 0){
			_oldControles[i] |= 1;
		}
	}
//fprintf(stderr,"Controles::actualizaEstado _oldControles UP %d\n",_oldControles[P1_UP]);
}

// comprueba si se acaba de pulsar una tecla
bool Controles::seHaPulsado(Inputs input)
{
//fprintf(stderr,"Controles::seHaPulsado\n");
//_oldControles[P1_UP]=0x01; // 666 
	// detecta transiciones de 0 a 1
	return _oldControles[input] == 0x01;
}

#ifdef __libabadIA__
//void Controles::libabadIAInput(int controles[END_OF_INPUTS]) {
void Controles::libabadIAInput(int *controles) {
	ih->process(controles);
//fprintf(stderr,"Controles::libabadIAInput UP %d\n", controles[P1_UP]);
}
#endif

