// BuscadorRutas.cpp
//
/////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "Abad.h"
#include "BuscadorRutas.h"
#include "FijarOrientacion.h"
#include "Guillermo.h"
#include "Juego.h"
#include "Logica.h"
#include "MotorGrafico.h"
#include "Objeto.h"
#include "PersonajeConIA.h"
#include "Puerta.h"
#include "RejillaPantalla.h"

using namespace Abadia;

/////////////////////////////////////////////////////////////////////////////
// mapa de las conexiones de las plantas de la abadía
/////////////////////////////////////////////////////////////////////////////

UINT8 BuscadorRutas::habitaciones[3][256] = {
	{
// planta baja
//
// X	00   01   02   03   04   05   06   07   08   09   0a   0b   0c   0d   0e  0f        Y
//		===============================================================================     ==
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0x08,0   ,0x08,0x08,0   ,0   ,0   ,0   , // 00
		0   ,0x08,0x08,0   ,0x08,0x08,0x08,0x09,0x07,0x0d,0x07,0x07,0x0c,0   ,0   ,0   , // 01
		0x01,0x1e,0x03,0x0d,0x06,0x0a,0x0a,0x0b,0x0c,0x02,0x08,0x08,0x03,0x04,0   ,0   , // 02
		0   ,0x03,0x04,0x0a,0x01,0x0e,0x0a,0x0a,0x02,0x08,0x0a,0x0a,0x01,0x04,0   ,0   , // 03
		0   ,0x01,0x05,0x0f,0x05,0x06,0x03,0x07,0x05,0x07,0x06,0x02,0x01,0x04,0   ,0   , // 04
		0   ,0x09,0x04,0x02,0x01,0x0c,0x07,0x05,0x05,0x05,0x04,0x08,0x09,0x04,0   ,0   , // 05
		0x01,0x1e,0x08,0x00,0x08,0x1b,0x05,0x05,0x05,0x05,0x04,0x08,0x09,0x04,0   ,0   , // 06
		0   ,0x02,0x03,0x0c,0x0a,0x0a,0x01,0x0d,0x05,0x0d,0x05,0x06,0x02,0   ,0   ,0   , // 07
		0   ,0   ,0   ,0x02,0x02,0x03,0x0c,0x0a,0x00,0x0a,0x09,0x06,0   ,0   ,0   ,0   , // 08
		0   ,0   ,0   ,0   ,0   ,0   ,0x02,0x03,0x05,0x06,0x02,0x02,0   ,0   ,0   ,0   , // 09
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0x01,0x0d,0x04,0   ,0   ,0   ,0   ,0   ,0   , // 0a
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0x02,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0b
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0c
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0d
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0e
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0     // 0f
	},
	{
// primera planta
//
// X	00   01   02   03   04   05   06   07   08   09   0a   0b   0c   0d   0e  0f        Y
//		===============================================================================     ==
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 00
		0   ,0x08,0x08,0   ,0x08,0x08,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 01
		0x01,0x2e,0x03,0x0d,0x06,0x1b,0x0d,0x06,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 02
		0   ,0x03,0x04,0x0a,0x01,0x0e,0x0a,0x08,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 03
		0   ,0x01,0x05,0x0f,0x05,0x06,0x03,0x07,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 04
		0   ,0x09,0x04,0x0a,0x01,0x0c,0x01,0x05,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 05
		0x01,0x2e,0x09,0x0f,0x0c,0x2b,0x05,0x05,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 06
		0   ,0x02,0x03,0x0c,0x0a,0x0a,0x01,0x0d,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 07
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 08
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 09
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0a
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0b
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0c
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0d
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0e
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0     // 0f
	},
	{
// segunda planta
//
// X	00   01   02   03   04   05   06   07   08   09   0a   0b   0c   0d   0e  0f        Y
//		===============================================================================     ==
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 00
		0   ,0x08,0x08,0   ,0x08,0x08,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 01
		0x01,0x0e,0x03,0x0d,0x06,0x2b,0x0d,0x06,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 02
		0   ,0x03,0x04,0x0a,0x01,0x0e,0x0a,0x08,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 03
		0   ,0x01,0x05,0x0f,0x05,0x06,0x03,0x07,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 04
		0   ,0x09,0x04,0x0a,0x01,0x0c,0x01,0x05,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 05
		0x01,0x0e,0x09,0x0f,0x0c,0x0b,0x05,0x05,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 06
		0   ,0x02,0x03,0x0c,0x0a,0x0a,0x01,0x0d,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 07
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 08
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 09
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0a
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0b
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0c
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0d
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   , // 0e
		0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0     // 0f
	}
};

/////////////////////////////////////////////////////////////////////////////
// posiciones alternativas para la búsqueda del camino
/////////////////////////////////////////////////////////////////////////////

PosicionJuego BuscadorRutas::alternativas[5];	

/////////////////////////////////////////////////////////////////////////////
// tabla con las puertas y las habitaciones que comunican 
/////////////////////////////////////////////////////////////////////////////

UINT8 BuscadorRutas::habitacionesPuerta[6][4] = {
	{ 0x35, 0x01, 0x36, 0x04 },	// puerta de la habitación del abad (entre la pantalla 0x3e y la 0x3d)
	{ 0x1b, 0x08, 0x2b, 0x02 },	// puerta de la habitación de los monjes (entre la pantalla 0 y la 0x38)
	{ 0x56, 0x08, 0x66, 0x02 },	// puerta de la habitación de severino (entre la pantalla 0x3d y la 0x3c)
	{ 0x29, 0x01, 0x2a, 0x04 },	// puerta de la salida de las habitaciones hacia la iglesia (entre la pantalla 0x29 y la 0x37)
	{ 0x27, 0x01, 0x28, 0x04 },	// puerta del pasadizo de detrás de la cocina (entre la pantalla 0x28 y la 0x26)
	{ 0x75, 0x01, 0x76, 0x04 }	// puertas que cierran el paso al ala izquierda de la abadía (entre la pantalla 0x11 y la 0x12)
};

/////////////////////////////////////////////////////////////////////////////
// tablas según la orientación
/////////////////////////////////////////////////////////////////////////////

int BuscadorRutas::despOrientacion[4][2] = {
	{ +2,  0 },
	{  0, -2 },
	{ -2,  0 },
	{  0, +2 }
};

int BuscadorRutas::posDestinoOrientacion[4][2] = {
	{ 22, 12 },
	{ 12,  2 },
	{  2, 12 },
	{ 12, 22 }
};

/////////////////////////////////////////////////////////////////////////////
// inicialización y limpieza
/////////////////////////////////////////////////////////////////////////////

BuscadorRutas::BuscadorRutas(UINT8 *buf, int lgtud)
{
fprintf(stderr,"constructor BuscadorRutas\n");
	buffer = (INT32 *)buf;
	lgtudBuffer = lgtud/4;
	posPila = 0;

	rejilla = new RejillaPantalla(elMotorGrafico);

	// crea los objetos para indicar las posiciones a las que hay que ir según la orientación a coger
	fijaPosOri[0] = new FijaOrientacion0();
	fijaPosOri[1] = new FijaOrientacion1();
	fijaPosOri[2] = new FijaOrientacion2();
	fijaPosOri[3] = new FijaOrientacion3();
}

BuscadorRutas::~BuscadorRutas()
{
fprintf(stderr,"destructor BuscadorRutas\n");
	// borra los objetos para indicar las posiciones
	for (int i = 0; i < 4; i++){
		delete fijaPosOri[i];
	}

	delete rejilla;
	rejilla = 0;
}

/////////////////////////////////////////////////////////////////////////////
// métodos relacionados con las puertas
/////////////////////////////////////////////////////////////////////////////

// modifica las conexiones entre las habitaciones según las puertas a las que puede entrar el personaje
void BuscadorRutas::modificaPuertasRuta(int mascara)
{
	// combina la máscara con las puertas que pueden abrirse
	mascara = mascara & laLogica->mascaraPuertas;

	// recorre las puertas que comunican las habitaciones
	for (int i = 0; i < 6; i++){

		for (int j = 0; j < 2; j++){
			// dependiendo de si podríamos entrar por esa puerta o no, modifica las conexiones de la habitación
			if (mascara & 0x01){
				habitaciones[0][habitacionesPuerta[i][2*j]] = (~habitacionesPuerta[i][2*j + 1]) & habitaciones[0][habitacionesPuerta[i][2*j]];
			} else {
				habitaciones[0][habitacionesPuerta[i][2*j]] = (habitacionesPuerta[i][2*j + 1]) | habitaciones[0][habitacionesPuerta[i][2*j]];
			}
		}

		mascara = mascara >> 1;
	}
}

/////////////////////////////////////////////////////////////////////////////
// métodos de más alto nivel relacionados con la búsqueda y generación de rutas
/////////////////////////////////////////////////////////////////////////////

// genera las acciones de movimiento para ir a una posición determinada
void BuscadorRutas::generaAccionesMovimiento(PersonajeConIA *pers)
{
	// si hay que pensar un nuevo movimiento
	if (pers->pensarNuevoMovimiento){

		// si no hay que buscar ninguna ruta, sale
		if (!seBuscaRuta) return;

		numAlternativas = 0;
		alternativaActual = 0;
		int oriInicial = 0;
		int oldOri = 0;
		PosicionJuego *posDestino = 0;

		switch (pers->aDondeVa){
			case POS_GUILLERMO:
				posDestino = laLogica->guillermo;
				oriInicial = laLogica->guillermo->orientacion;
				break;
			case POS_ABAD:
				posDestino = laLogica->abad;
				oriInicial = laLogica->abad->orientacion;
				break;
			case POS_LIBRO:
				posDestino = elJuego->objetos[0];
				oriInicial = elJuego->objetos[0]->orientacion;
				break;
			case POS_PERGAMINO:
				posDestino = elJuego->objetos[3];
				oriInicial = elJuego->objetos[3]->orientacion;
				break;

			default:	// en otro caso se quiere ir a una de las posiciones predefinidas del personaje
				alternativas[0] = pers->posiciones[pers->aDondeVa];
				posDestino = &alternativas[0];
				oldOri = posDestino->orientacion;
				numAlternativas = 1;
				break;
		}

		// genera las alternativas a la posición de destino
		generaAlternativas(posDestino, oriInicial, oldOri);

		// trata de encontrar un camino para llegar a cualquiera de las alternativas que ha generado
		if (numAlternativas > 0){
			procesaAlternativas(pers, &alternativas[0]);
		}
	} else {
		// si ya tenía un nuevo movimiento pensado pero no hay movimiento, vuelve a pensarlo
		if (!laLogica->hayMovimiento){
			pers->descartarMovimientosPensados();
		}
	}
}

// trata de generar las posiciones alternativas cercanas a la que se le pasa
void BuscadorRutas::generaAlternativas(PosicionJuego *pos, int oriInicial, int oldOri)
{
	// genera una propuesta para llegar a una posición cercana a la de destino pero por diferentes orientaciones
	for (int i = 0; i < 4; i++){
		generaAlternativa(pos, (oriInicial + i) & 0x03, oldOri);
	}
}

// comprueba si la alternativa es viable y si es así la guarda
void BuscadorRutas::generaAlternativa(PosicionJuego *pos, int orientacion, int oldOri)
{
	// graba la posición y orientación de la alternativa
	alternativas[numAlternativas].posX = pos->posX + despOrientacion[orientacion][0];
	alternativas[numAlternativas].posY = pos->posY + despOrientacion[orientacion][1];
	alternativas[numAlternativas].altura = pos->altura;

	// invierte la orientación y la combina con la deseada
	alternativas[numAlternativas].orientacion = (orientacion ^ 0x02) | oldOri;

	int posXRejilla, posYRejilla;

	if (elMotorGrafico->rejilla->estaEnRejillaCentral(pos, posXRejilla, posYRejilla)){
		// obtiene la altura de la casilla
		int alturaDest = elMotorGrafico->rejilla->bufAlturas[posYRejilla][posXRejilla] & 0xef;
		int alturaRelativa = pos->altura - elMotorGrafico->obtenerAlturaBasePlanta(pos->altura);
		int difAltura = alturaRelativa - alturaDest + 1;

		// si la diferencia de altura es significativa, sale sin grabar esta alternativa
		if (!(difAltura >= 0) && (difAltura <= 5)) return;
	}

	numAlternativas++;
}

// comprueba si se puede obtener un camino para llegar a alguna de las posiciones calculadas
void BuscadorRutas::procesaAlternativas(PersonajeConIA *pers, PosicionJuego *destino)
{
	// comprueba si se ha llegado desde el origen a alguno de los destinos calculados y si no es así, genera
	// los comandos necesarios para que el personaje avance a la siguiente pantalla en la ruta buscada
	int rdo = buscaCamino(pers, destino);

	// si se ha llegado al sitio, lo indica
	if (rdo == -3){
		pers->aDondeHaLlegado = pers->aDondeVa;
	}
}

/////////////////////////////////////////////////////////////////////////////
// métodos de búsqueda y generación de rutas
/////////////////////////////////////////////////////////////////////////////

// comprueba si se ha llegado desde el origen al destino y si no es así, genera los comandos 
// necesarios para que el personaje avance a la siguiente pantalla en la ruta buscada
int BuscadorRutas::buscaCamino(PersonajeConIA *origen, PosicionJuego *destino)
{
	// si está en medio de una movimiento de guillermo, sale
	if ((contadorAnimGuillermo & 0x01) != 0) return -2;
	
	// si se ha generado algún camino en esta iteración del bucle principal, sale
	if (generadoCamino) return -2;

	// obtiene las alturas de las plantas para la posición de origen y de destino
	int alturaPlantaOri = elMotorGrafico->obtenerAlturaBasePlanta(origen->altura);
	int numPlanta = elMotorGrafico->obtenerPlanta(alturaPlantaOri);
	int alturaPlantaDest = elMotorGrafico->obtenerAlturaBasePlanta(destino->altura);

	// si las posiciones no están en la misma planta
	if (alturaPlantaOri != alturaPlantaDest){
		// obtiene una máscara para subir o bajar de planta dependiendo de la posición de destino
		int mascara = (alturaPlantaOri < alturaPlantaDest) ? 0x10 : 0x20;

		// obtiene las conexiones de la pantalla de origen
		int conexionesOri = habitaciones[numPlanta][(origen->posY & 0xf0) | ((origen->posX >> 4) & 0x0f)];

		// si desde la pantalla actual no se puede subir o bajar
		if ((conexionesOri & mascara) == 0){
			// busca en esta planta una pantalla con escaleras para subir o bajar
			posXIni = origen->posX >> 4;
			posYIni = origen->posY >> 4;
			bool encontrado = buscaPantalla(numPlanta, mascara);

			// limpia los resultados de la búsqueda
			limpiaBitsBusquedaPantalla(numPlanta);

			// si no se encontraron las escaleras, sale
			if (!encontrado){
				return 0;
			}

			// genera los comandos para ir desde la pantalla donde está el personaje a la siguiente pantalla camino de las escaleras
			posXIni = posXFinal;
			posYIni = posYFinal;
			return generaCaminoAPantalla(origen, numPlanta);
		} else {
			// si desde la pantalla actual se puede subir o bajar

			// rellena el buffer de alturas de la pantalla en la que está el personaje
			generaAlturasPantalla(origen);

			int valor = (alturaPlantaOri < alturaPlantaDest) ? 0x0d : 0x01;

			// modifica las posiciones del buffer de alturas de la pantalla actual que permiten subir
			// o bajar de planta, para que sean el destino del algoritmo de búsqueda de caminos
			for (int j = 0; j < 24; j++){
				for (int i = 0; i < 24; i++){
					if (rejilla->bufAlturas[j][i] == valor){
						rejilla->bufAlturas[j][i] |= 0x40;
					}
				}
			}

			// limita las opciones a probar a tan solo la opción actual
			numAlternativas = alternativaActual + 1;

			return generaCaminoAPosicion(origen, 0, 0);
		}
	} else {
		// si las 2 posiciones están en la misma planta

		bool mismaPantalla = false;

		// comprueba si las 2 posiciones están en la misma pantalla
		if (((destino->posX ^ origen->posX) & 0xf0) == 0){
			if (((destino->posY ^ origen->posY) & 0xf0) == 0){
				mismaPantalla = true;
			}
		}

		// si las 2 posiciones están en la misma pantalla
		if (mismaPantalla){
			// si la posición de origen y de destino es la misma
			if ((((destino->posX ^ origen->posX) & 0x0f) == 0) && (((destino->posY ^ origen->posY) & 0x0f) == 0)){
				// si la orientación del personaje no es la misma que la de destino
				if (origen->orientacion != destino->orientacion){
					// fija la primera posición del buffer de comandos
					origen->reiniciaPosicionBuffer();

					// escribe unos comandos para cambiar la orientación del personaje
					origen->modificaOrientacion(destino->orientacion);

					// escribe unos comandos para que esté un pequeño instante sin moverse
					origen->escribeComandos(0x1000, 12);

					// fija la primera posición del buffer de comandos
					origen->reiniciaPosicionBuffer();
				}

				return -3;
			} else {
				// si la posición de origen y de destino no es la misma

				// rellena el buffer de alturas de la pantalla en la que está el personaje
				generaAlturasPantalla(origen);

				int posXDest, posYDest;

				// ajusta la posición de destino a las coordenadas de rejilla
				bool noHayError = rejilla->ajustaAPosRejilla(destino->posX, destino->posY, posXDest, posYDest);
				assert(noHayError);

				return generaCaminoAPosicionSiAlcanzable(origen, posXDest, posYDest);
			}
		} else {
			// si las 2 posiciones no están en la misma pantalla

			// genera los comandos para ir desde la pantalla donde está el personaje a la siguiente pantalla camino de la pantalla destino
			posXIni = destino->posX >> 4;
			posYIni = destino->posY >> 4;
			return generaCaminoAPantalla(origen, numPlanta);
		}
	}
}


int BuscadorRutas::generaCaminoAPantalla(PersonajeConIA *pers, int numPlanta)
{
	// busca un camino desde la posición que se le pasa a donde está el personaje
	bool encontrado = buscaPantalla(pers->posX >> 4, pers->posY >> 4, numPlanta);

	// limpia los resultados de la búsqueda
	limpiaBitsBusquedaPantalla(numPlanta);

	// si no se encontró el camino, sale
	if (!encontrado){
		return 0;
	}

	// rellena el buffer de alturas de la pantalla en la que está el personaje
	generaAlturasPantalla(pers);

	// marca las orientación que hay que coger como el destino de la búsqueda
	fijaPosOri[oriFinal]->fijaPos(rejilla);

	// limita las opciones a probar a tan solo la opción actual
	numAlternativas = alternativaActual + 1;

	return generaCaminoAPosicion(pers, posDestinoOrientacion[oriFinal][0], posDestinoOrientacion[oriFinal][1]);
}

int BuscadorRutas::generaCaminoAPosicion(PersonajeConIA *pers, int posXDest, int posYDest)
{
	// ajusta la posición del personaje a la rejilla
	bool noHayError = rejilla->ajustaAPosRejilla(pers->posX, pers->posY, posXIni, posYIni);
	assert(noHayError);

	// busca una ruta dentro de una pantalla desde la posición de origen a la de destino
	bool encontrado = buscaEnPantalla(posXDest, posYDest);
	
	// comprueba si se ha alcanzado la posición actual. Si es así sale. En otro caso, si se encontró
	// un camino para llegar al destino, programa las acciones para seguirlo en esta pantalla
	return compruebaFinCamino(pers, encontrado);
}

int BuscadorRutas::generaCaminoAPosicionSiAlcanzable(PersonajeConIA *pers, int posXDest, int posYDest)
{
	// ajusta la posición del personaje a la rejilla
	bool noHayError = rejilla->ajustaAPosRejilla(pers->posX, pers->posY, posXIni, posYIni);
	assert(noHayError);

	// busca una ruta dentro de una pantalla desde la posición de origen a la de destino
	bool encontrado = buscaEnPantallaSiAlcanzable(posXDest, posYDest);
	
	// comprueba si se ha alcanzado la posición actual. Si es así sale. En otro caso, si se encontró
	// un camino para llegar al destino, programa las acciones para seguirlo en esta pantalla
	return compruebaFinCamino(pers, encontrado);
}

// comprueba si se ha alcanzado la posición actual. Si es así sale. En otro caso, si se encontró
// un camino para llegar al destino, programa las acciones para seguirlo en esta pantalla
int BuscadorRutas::compruebaFinCamino(PersonajeConIA *pers, bool encontrado)
{
	// limpia los resultados de la búsqueda en el buffer de alturas
	limpiaBitsBusquedaEnPantalla();

	// si no se ha encontrado un camino
	if (!encontrado){
		alternativaActual++;

		// si se han terminado las alternativas, sale
		if (alternativaActual >= numAlternativas){
			return 0;
		}

		PosicionJuego *destino = &alternativas[alternativaActual];

		// si la posición de origen y de destino es la misma
		if (((destino->posX ^ pers->posX) == 0) && ((destino->posY ^ pers->posY) == 0)){
			// si la orientación del personaje no es la misma que la de destino
			if (pers->orientacion != destino->orientacion){
				// fija la primera posición del buffer de comandos
				pers->reiniciaPosicionBuffer();

				// escribe unos comandos para cambiar la orientación del personaje
				pers->modificaOrientacion(destino->orientacion);

				// escribe unos comandos para que esté un pequeño instante sin moverse
				pers->escribeComandos(0x1000, 12);

				// fija la primera posición del buffer de comandos
				pers->reiniciaPosicionBuffer();
			}

			return -3;
		} else {
			int posXDest = 0, posYDest = 0;

			// ajusta la posición de la siguiente alternativa a la rejilla
			bool noHayError = rejilla->ajustaAPosRejilla(destino->posX, destino->posY, posXDest, posYDest);
			assert(noHayError);

			// vuelve a probar a ver si encuentra el camino a esa posición
			return generaCaminoAPosicionSiAlcanzable(pers, posXDest, posYDest);
		}
	} else {
		// si se ha encontrado un camino
		generadoCamino = true;

		// genera todos los comandos para ir desde el origen al destino
		grabaComandosCamino(pers);

		return -1;
	}
}

// devuelve true si la parte más significativa de 2 coordenadas es -1, 0 o 1
bool BuscadorRutas::estaCerca(int coord1, int coord2, int &distancia)
{
	distancia = (coord1 >> 4) - (coord2 >> 4);
	if (distancia < 0) distancia = -distancia;
	return distancia <= 1;
}

// rellena el buffer de alturas con los datos de la pantalla actual en la que está el personaje
// y marca las casillas que ocupan del resto de los personajes y las puertas
void BuscadorRutas::generaAlturasPantalla(PersonajeConIA *pers)
{
	// rellena el buffer de alturas con los datos de altura de la pantalla actual
	rejilla->rellenaAlturasPantalla(pers);

	bool guillermoCerca = false;

	int distX, distY;

	// comprueba si guillermo está cerca del personaje
	if (estaCerca(laLogica->guillermo->posX, pers->posX, distX)){
		if (estaCerca(laLogica->guillermo->posY, pers->posY, distY)){
			if (elMotorGrafico->obtenerAlturaBasePlanta(laLogica->guillermo->altura) == elMotorGrafico->obtenerAlturaBasePlanta(pers->altura)){
				guillermoCerca = true;
			}
		}
	}

	// si guillermo no está cerca, comprueba si el personaje al que sigue la cámara está cerca
	if (!guillermoCerca){
		if (!estaCerca(elMotorGrafico->posXPantalla, pers->posX, distX)) return;
		if (!estaCerca(elMotorGrafico->posYPantalla, pers->posY, distY)) return;
		if (elMotorGrafico->alturaBasePantalla != elMotorGrafico->obtenerAlturaBasePlanta(pers->altura)) return;
	}

	// aquí llega si guillermo o el personaje al que sigue la cámara están cerca
	int primerPersonaje = 1;

	// si el personaje está en la misma habitación que guillermo o del personaje al que sigue la cámara
	if ((distX == 0) && (distY ==0)){
		primerPersonaje = 0;
	}

	// marca la posición de los personajes
	for (int i = primerPersonaje; i < Juego::numPersonajes; i++){
		Personaje *personaje = elJuego->personajes[i];

		if (personaje != pers){
			personaje->marcaPosicion(rejilla, 0x10);
		}
	}

	// marca la posición de las puertas
	for (int i = 0; i < Juego::numPuertas; i++){
		Puerta *puerta = elJuego->puertas[i];

		if (puerta->estaAbierta){
			puerta->marcaPosiciones(rejilla, 0x0f);
		}
	}

	pers->marcaPosicion(rejilla, 0);
}

/////////////////////////////////////////////////////////////////////////////
// métodos relacionados con la búsqueda de caminos en una pantalla
/////////////////////////////////////////////////////////////////////////////

// busca una ruta dentro de una pantalla desde la posición de origen a la que esté marcada como objetivo de la búsqueda
bool BuscadorRutas::buscaEnPantalla()
{
	// realiza la búsqueda
	return buscaEnPantallaComun();
}

// busca una ruta dentro de una pantalla desde la posición de origen a la de destino
bool BuscadorRutas::buscaEnPantalla(int posXDest, int posYDest)
{
	// marca la posición de destino como el objetivo de la búsqueda
	rejilla->bufAlturas[posYDest][posXDest] |= 0x40;

	// realiza la búsqueda
	bool encontrado = buscaEnPantallaComun();

	posXFinal = posXDest;
	posYFinal = posYDest;

	return encontrado;
}

// busca una ruta dentro de una pantalla desde la posición de origen a la de destino si la posición de destino es alcanzable
bool BuscadorRutas::buscaEnPantallaSiAlcanzable(int posXDest, int posYDest)
{
	int alturaBase = rejilla->bufAlturas[posYDest][posXDest] & 0x0f;

	// si la posición es muy alta, indica que no es alcanzable
	if (alturaBase >= 0x0e){
		return false;
	}

	// si en la posición de destino no puede situarse un personaje, sale
	if (!esPosicionAlcanzable(posXDest, posYDest, alturaBase)){
		return false;
	}

	// si la posición era alcanzable fija la posición de destino como el objetivo de la búsqueda
	rejilla->bufAlturas[posYDest][posXDest] &= 0x7f;
	rejilla->bufAlturas[posYDest][posXDest] |= 0x40;

	// realiza la búsqueda
	bool encontrado = buscaEnPantallaComun();

	posXFinal = posXDest;
	posYFinal = posYDest;

	return encontrado;
}

// método común para la búsqueda de rutas dentro de la pantalla
bool BuscadorRutas::buscaEnPantallaComun()
{
	// marca como exploradas todas las posiciones del borde
	for (int i = 0; i < 24; i++){
		rejilla->bufAlturas[i][0] |= 0x80;
		rejilla->bufAlturas[i][23] |= 0x80;
		rejilla->bufAlturas[0][i] |= 0x80;
		rejilla->bufAlturas[23][i] |= 0x80;
	}

	nivelRecursion = 1;
	posPila = 0;

	// guarda en la pila la posición inicial
	push(posXIni, posYIni);

	// marca la posición inicial como explorada
	rejilla->bufAlturas[posYIni][posXIni] |= 0x80;

	// guarda el marcador de fín de nivel de profundidad
	push(-1, -1);

	posProcesadoPila = 0;
	int posX, posY;

	while (true){
		// obtiene el elemento a procesar
		elem(posProcesadoPila, posX, posY);
		posProcesadoPila++;

		// si ha terminado una iteración del bucle
		if ((posX == -1) && (posY == -1)){
			// si se ha terminado de procesar la pila, sale
			if (posProcesadoPila == posPila){
				return false;
			} else {
				// en otro caso, marca el fín del nivel de recursión y continúa procesando
				push(-1, -1);
				nivelRecursion++;
			}
		} else {
			// lee la altura de la posición actual
			int altura = rejilla->bufAlturas[posY][posX] & 0x0f;

			if (esPosicionDestino(posX + 1, posY, altura)){
				posXFinal = posX + 1; 
				posYFinal = posY;
				oriFinal = IZQUIERDA;

				return true;
			}
			if (esPosicionDestino(posX, posY - 1, altura)){
				posXFinal = posX; 
				posYFinal = posY - 1;
				oriFinal = ARRIBA;

				return true;
			}
			if (esPosicionDestino(posX - 1, posY, altura)){
				posXFinal = posX - 1; 
				posYFinal = posY;
				oriFinal = DERECHA;

				return true;
			}
			if (esPosicionDestino(posX, posY + 1, altura)){
				posXFinal = posX; 
				posYFinal = posY + 1;
				oriFinal = ABAJO;

				return true;
			}
		}
	}

	return false;
}

// comprueba si la posición que se le pasa es alcanzable
bool BuscadorRutas::esPosicionAlcanzable(int posX, int posY, int altura)
{
	return esPosicionDestino(posX, posY, altura, altura, false);
}

// comprueba si la posición que se le pasa es un objetivo de búsqueda
bool BuscadorRutas::esPosicionDestino(int posX, int posY, int alturaBase)
{
	// obtiene la altura de esta posición
	int altura = rejilla->bufAlturas[posY][posX];

	// si la posición ya había sido explorada, sale
	if ((altura & 0x80) != 0){
		return false;
	}

	// en otro caso comprueba los vecinos
	return esPosicionDestino(posX, posY, altura, alturaBase, true);
}


// comprueba si la posición que se le pasa es un objetivo de búsqueda
bool BuscadorRutas::esPosicionDestino(int posX, int posY, int altura, int alturaBase, bool buscandoSolucion)
{
	// elimina los resultados de la búsqueda
	altura &= 0x3f;

	// si hay mucha diferencia de altura entre esta posición y la posición base, sale
	int difAltura = alturaBase - altura + 1;
	if ((difAltura < 0) || (difAltura >= 3)){
		return false;
	}

	// si no coincide la altura de la posición (x, y) con la posición (x - 1, y)
	if (altura != (rejilla->bufAlturas[posY][posX - 1] & 0x3f)){
		// si hay mucha diferencia de altura, sale
		difAltura = (rejilla->bufAlturas[posY][posX - 1] & 0x3f) - altura + 1;
		if ((difAltura < 0) || (difAltura >= 3)){
			return false;
		}

		// si no coincide la altura de la posición (x, y) con la posición (x, y - 1), sale
		if (altura != (rejilla->bufAlturas[posY - 1][posX] & 0x3f)){
			return false;
		}

		// si la diferencia de altura de (x - 1, y) no coincide con la de (x - 1, y - 1), sale
		int difAltura2 = (rejilla->bufAlturas[posY - 1][posX - 1] & 0x3f) - altura + 1;
		if (difAltura  != difAltura2){
			return false;
		}
	} else {
		// aquí llega si coincide la altura de la posición (x, y) con la posición (x - 1, y)

		// si hay mucha diferencia de altura entre la posición (x, y) y la posición (x, y - 1), sale
		difAltura = (rejilla->bufAlturas[posY - 1][posX] & 0x3f) - altura + 1;
		if ((difAltura < 0) || (difAltura >= 3)){
			return false;
		}

		// si la diferencia de altura de (x - 1, y - 1) no coincide con la de (x, y - 1), sale
		int difAltura2 = (rejilla->bufAlturas[posY - 1][posX - 1] & 0x3f) - altura + 1;
		if (difAltura  != difAltura2){
			return false;
		}
	}

	// aqui llega si la diferencia entre las 4 posiciones es considerada salvable

	// marca la posición como explorada
	rejilla->bufAlturas[posY][posX] |= 0x80;

	// si sólo se quería comprobar si la posición era accesible, sale indicando que si lo era
	if (!buscandoSolucion){
		return true;
	}

	// si ha encontrado la solución
	if ((rejilla->bufAlturas[posY][posX] & 0x40) != 0){
		// quita la marca de posición explorada
		rejilla->bufAlturas[posY][posX] &= 0x7f;

		// indica que ha encontrado la posición de destino
		return true;
	}

	// mete en la pila la posición actual para explorarla proximamente
	push(posX, posY);

	return false;
}

// limpia los bits usados por la rutina de búsqueda
void BuscadorRutas::limpiaBitsBusquedaEnPantalla()
{
	for (int j = 0; j < 24; j++){
		for (int i = 0; i < 24; i++){
			rejilla->bufAlturas[j][i] &= 0x3f;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// métodos relacionados con la búsqueda de caminos entre pantallas
/////////////////////////////////////////////////////////////////////////////

// busca una ruta desde una pantalla de origen a una de destino
bool BuscadorRutas::buscaPantalla(int posXDest, int posYDest, int numPlanta)
{
	// marca la posición de destino como el objetivo de la búsqueda
	habitaciones[numPlanta][(posYDest << 4) | posXDest] |= 0x40;

	// busca el camino entre la posición inicial y la final
	return buscaPantalla(numPlanta, 0x40);
}

// busca (partiendo de la posición inicial) una ruta a una pantalla que cumpla la máscara que se le pasa
bool BuscadorRutas::buscaPantalla(int numPlanta, int mascara)
{
	posPila = 0;

	// guarda en la pila la posición inicial
	push(posXIni, posYIni);

	// marca la posición inicial como explorada
	habitaciones[numPlanta][(posYIni << 4) | posXIni] |= 0x80;

	// guarda el marcador de fín de nivel de profundidad
	push(-1, -1);

	posProcesadoPila = 0;
	int posX, posY;

	while (true){
		// obtiene el elemento a procesar
		elem(posProcesadoPila, posX, posY);
		posProcesadoPila++;

		// si ha terminado una iteración del bucle
		if ((posX == -1) && (posY == -1)){
			// si se ha terminado de procesar la pila, sale
			if (posProcesadoPila == posPila){
				return false;
			} else {
				// en otro caso, marca el fín del nivel y continúa procesando
				push(-1, -1);
			}
		} else {
			// en otro caso, explora las posiciones vecinas
			if (esPantallaDestino(posX + 1, posY, numPlanta, mascara, 0x04)){
				posXFinal = posX + 1; 
				posYFinal = posY;
				oriFinal = IZQUIERDA;

				return true;
			}
			if (esPantallaDestino(posX, posY - 1, numPlanta, mascara, 0x08)){
				posXFinal = posX; 
				posYFinal = posY - 1;
				oriFinal = ARRIBA;

				return true;
			}
			if (esPantallaDestino(posX - 1, posY, numPlanta, mascara, 0x01)){
				posXFinal = posX - 1; 
				posYFinal = posY;
				oriFinal = DERECHA;

				return true;
			}
			if (esPantallaDestino(posX, posY + 1, numPlanta, mascara, 0x02)){
				posXFinal = posX; 
				posYFinal = posY + 1;
				oriFinal = ABAJO;

				return true;
			}
		}
	}

	return false;
}

// comprueba si la posición que se le pasa es un objetivo de búsqueda
bool BuscadorRutas::esPantallaDestino(int posX, int posY, int numPlanta, int mascara, int mascaraDestino)
{
	// si está fuera de la tabla, sale
	if ((posX < 0) || (posX > 0x10) || (posY < 0) || (posY > 0x10)) return false;

	// si se puede entrar a la habitación de destino por la orientación
	if ((habitaciones[numPlanta][(posY << 4) | posX] & mascaraDestino) == 0){
		// si se ha encontrado el destino, sale
		if ((habitaciones[numPlanta][(posY << 4) | posX] & mascara) != 0){
			return true;
		}

		// si la habitación no había sido explorada, guarda la posición en la pila y la marca como explorada
		if (((habitaciones[numPlanta][(posY << 4) | posX]) & 0x80) == 0){
			push(posX, posY);

			habitaciones[numPlanta][(posY << 4) | posX] |= 0x80;
		}
	}

	return false;
}

// limpia los bits usados por la rutina de búsqueda
void BuscadorRutas::limpiaBitsBusquedaPantalla(int numPlanta)
{
	for (int i = 0; i < 0x100; i++){
		habitaciones[numPlanta][i] = habitaciones[numPlanta][i] & 0x3f;
	}
}

/////////////////////////////////////////////////////////////////////////////
// generación de comandos a partir de una ruta calculada
/////////////////////////////////////////////////////////////////////////////

void BuscadorRutas::grabaComandosCamino(PersonajeConIA *pers)
{
	int oldPosX = pers->posX;
	int oldPosY = pers->posY;
	int oldAltura = pers->altura;
	int oldOri = pers->orientacion;
	bool oldEnDesnivel = pers->enDesnivel;
	bool oldGiradoEnDesnivel = pers->giradoEnDesnivel;
	bool oldBajando = pers->bajando;

	pers->reiniciaPosicionBuffer();

	reconstruyeCamino(pers);

	pers->escribeComandos(0x1000, 12);
	pers->reiniciaPosicionBuffer();

	pers->bajando = oldBajando;
	pers->giradoEnDesnivel = oldGiradoEnDesnivel;
	pers->enDesnivel = oldEnDesnivel;
	pers->orientacion = oldOri;
	pers->altura = oldAltura;
	pers->posY = oldPosY;
	pers->posX = oldPosX;
}

void BuscadorRutas::reconstruyeCamino(PersonajeConIA *pers)
{
	// coloca el tope de la pila en la posición desde la que se encontró el camino
	posPila = posProcesadoPila;

	int posXDest, posYDest;

	// obtiene el elemento del tope de la pila
	pop(posXDest, posYDest);

	int posPila2 = lgtudBuffer - 1;

	// marca el final de los movimientos
	pushInv(posPila2, -1);

	// guarda la posición de destino
	pushInv(posPila2, posXFinal);
	pushInv(posPila2, posYFinal);

	// guarda la orientación final invertida
	pushInv(posPila2, oriFinal ^ 2);

	if (nivelRecursion != 1){
		int posX, posY, difAlturaX, difAlturaY, ori;

		while (true){
			// obtiene elementos de la pila hasta encontrar el marcador de otra iteración
			do {
				pop(posX, posY);
			} while (!((posX == -1) && (posY == -1)));

			// guarda el movimiento anterior
			pushInv(posPila2, posXDest);
			pushInv(posPila2, posYDest);

			while (true){
				// obtiene el siguiente valor de la pila
				pop(posX, posY);

				// calcula la distancia en y
				difAlturaY = posY - posYDest + 1;

				// si la distancia es muy grande, sigue sacando valores
				if ((difAlturaY < 0) || (difAlturaY >= 3)){
					continue;
				}

				// calcula la distancia en x
				difAlturaX = posX - posXDest + 1;

				// si la distancia es muy grande, sigue sacando valores
				if ((difAlturaX < 0) || (difAlturaX >= 3)){
					continue;
				}

				// dependiendo de las distancias
				switch (4*difAlturaX + difAlturaY){
					case 1:	// si es el elemento (x - 1, y)
						ori = DERECHA;
						break;
					case 6:	// si es el elemento (x, y + 1)
						ori = ABAJO;
						break;
					case 9:	// si es el elemento (x + 1, y)
						ori = IZQUIERDA;
						break;
					case 4:	// si es el elemento (x, y - 1)
						ori = ARRIBA;
						break;
					default:
						// si no es ninguno de estos casos, sigue sacando valores
						continue;
				}

				// si se llega hasta aquí se ha encontrado la posición anterior
				break;
			}

			// guarda el movimiento anterior
			posXDest = posX;
			posYDest = posY;

			// guarda la orientación anterior
			pushInv(posPila2, ori);

			// si se ha llegado a la posición inicial, sale
			if ((posXIni == posX) && (posYIni == posY)){
				break;
			}
		}
	}

	// aquí llega cuando ya ha encontrado el camino completo del destino al origen

	int oriDest, difAltura1, difAltura2, avanceX, avanceY, posXRejilla, posYRejilla;
	bool llegoADestino = true;

	do {
		if (llegoADestino){
			// lee la orientación que debe tomar el personaje
			popInv(posPila2, oriDest);

			// si el personaje está en un desnivel
			if (pers->enDesnivel){
				// si el personaje va a girar noventa grados estando en desnivel, cambia su estado de girado
				if (((pers->orientacion ^ oriDest) & 0x01) != 0){
					pers->giradoEnDesnivel = !pers->giradoEnDesnivel;
				}
			}

			// si ha cambiado la orientación, escribe unos comandos para girar
			if (pers->orientacion != oriDest){
				pers->modificaOrientacion(oriDest);
				pers->orientacion = oriDest;
			}

			// obtiene la altura de las posiciones hacia las que se va a mover
			rejilla->obtenerAlturaPosicionesAvance(pers, difAltura1, difAltura2, avanceX, avanceY);

			// escribe un comando dependiendo de si sube, baja o se mantiene
			pers->avanzaPosicion(difAltura1, difAltura2, avanceX, avanceY);
		} else {
			posPila2++;
		}

		// si ya ha sacado todo el camino de la pila, sale
		if (((INT16)(buffer[posPila2 + 3] & 0xffff)) == -1){
			return;
		}

		// saca de la pila la posición a la que se mueve el personaje
		popInv(posPila2, posYDest);
		popInv(posPila2, posXDest);

		// obtiene la posición del personaje con respecto a las 20x20 posiciones centrales de la rejilla
		bool noHayError = rejilla->ajustaAPosRejilla(pers->posX, pers->posY, posXRejilla, posYRejilla);
		assert(noHayError);

		// comprueba si ha llegado a la posición de destino antes de sacar más valores de la pila
		llegoADestino = ((posXRejilla == posXDest) && (posYRejilla == posYDest));
	} while (true);
}

/////////////////////////////////////////////////////////////////////////////
// operaciones sobre la pila
/////////////////////////////////////////////////////////////////////////////

// mete un dato en la pila
void BuscadorRutas::push(INT32 val1, INT32 val2)
{
	assert(posPila < lgtudBuffer);

	buffer[posPila] = ((val2 & 0xffff) << 16) | (val1 & 0xffff);
	posPila++;
}

// saca un dato de la pila
void BuscadorRutas::pop(INT32 &val1, INT32 &val2)
{
	assert(posPila > 0);

	posPila--;
	int rdo = buffer[posPila];
	val1 = ((INT16)(rdo & 0xffff));
	val2 = ((INT16)((rdo >> 16) & 0xffff));
}

// obtiene el elemento de la posición seleccionada
void BuscadorRutas::elem(int posicion, INT32 &val1, INT32 &val2)
{
	assert(posicion >= 0);
	assert(posPila >= posicion);

	int rdo = buffer[posicion];
	val1 = ((INT16)(rdo & 0xffff));
	val2 = ((INT16)((rdo >> 16) & 0xffff));
}

// mete un dato en la pila, en la posición especificada y en sentido inverso
void BuscadorRutas::pushInv(int &posicion, INT32 val1, INT32 val2)
{
	assert((posicion >= 0) && (posicion < lgtudBuffer));

	buffer[posicion] = ((val2 & 0xffff) << 16) | (val1 & 0xffff);
	posicion--;
}

// mete un dato en la pila, en la posición especificada y en sentido inverso
void BuscadorRutas::pushInv(int &posicion, INT32 val1)
{
	assert((posicion >= 0) && (posicion < lgtudBuffer));

	buffer[posicion] = val1 & 0xffff;
	posicion--;
}

// saca un dato en la posición especificada de la pila en sentido inverso
void BuscadorRutas::popInv(int &posicion, INT32 &val1)
{
	assert(posicion < lgtudBuffer);

	posicion++;
	int rdo = buffer[posicion];
	val1 = ((INT16)(rdo & 0xffff));
}

// saca un dato en la posición especificada de la pila en sentido inverso
void BuscadorRutas::popInv(int &posicion, INT32 &val1, INT32 &val2)
{
	assert(posicion < lgtudBuffer);

	posicion++;
	int rdo = buffer[posicion];
	val1 = ((INT16)(rdo & 0xffff));
	val2 = ((INT16)((rdo >> 16) & 0xffff));
}
