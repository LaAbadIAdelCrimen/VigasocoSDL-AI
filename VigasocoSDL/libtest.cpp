#include <fstream>
#include "VigasocoLibSDL.h"

// TODO: ¿este modo se puede eliminar?
//bool gb_test(false);  // Âestamos en modo normal o ejecutando tests de pruebas?
//std::string g_test("");  // Escenario de pruebas
/*
int old_main(int argc, char **argv) {

	VigasocoLibSDL vigasocoTest;

fprintf(stderr,"1\n");
	vigasocoTest.init();
fprintf(stderr,"2\n");

	int controles[END_OF_INPUTS];
	memset(controles,0,sizeof(int)*END_OF_INPUTS);

	// ¿tiene sentido todo el rato pasar controles
	// o pasarlo al inicio en el init??
//controles[P1_UP]=1;
fprintf(stderr,"3\n");
	vigasocoTest.step(controles);
fprintf(stderr,"4\n");
//controles[P1_UP]=1;
	vigasocoTest.step(controles);
fprintf(stderr,"5\n");
//controles[P1_UP]=1;
//controles[P1_UP]=1;
	vigasocoTest.step(controles);
fprintf(stderr,"6\n");
//controles[P1_UP]=1;
//controles[P1_UP]=1;
	vigasocoTest.step(controles);
fprintf(stderr,"7\n");
//controles[P1_UP]=1;
	vigasocoTest.step(controles);
fprintf(stderr,"8\n");
//controles[P1_UP]=1;
	vigasocoTest.step(controles);
fprintf(stderr,"9\n");
//controles[P1_UP]=1;
	vigasocoTest.step(controles);
fprintf(stderr,"10\n");
//controles[P1_UP]=1;
	vigasocoTest.step(controles);
fprintf(stderr,"11\n");
//controles[P1_UP]=1;
	vigasocoTest.step(controles);
fprintf(stderr,"12\n");
//controles[P1_UP]=1;
	vigasocoTest.step(controles);
fprintf(stderr,"12+1\n");
//controles[P1_UP]=1;
	vigasocoTest.step(controles);
fprintf(stderr,"14\n");
//controles[P1_UP]=1;

	return 0;
} */

int main(int argc, char **argv) {

fprintf(stderr,"END_OF_INPUTS %d\n",END_OF_INPUTS);
fprintf(stderr,"1\n");
	VigasocoMain->init();
fprintf(stderr,"2\n");

	int controles[END_OF_INPUTS];
	memset(controles,0,sizeof(int)*END_OF_INPUTS);
//	fprintf(stderr,"dump0 %s\n",VigasocoMain->step(controles).c_str());
controles[KEYBOARD_E]=1;
	fprintf(stderr,"dump0 %s\n",VigasocoMain->step(controles).c_str());
controles[KEYBOARD_E]=0;
controles[P1_LEFT]=0;
	fprintf(stderr,"dump1 %s\n",VigasocoMain->step(controles).c_str());
	fprintf(stderr,"dump2 %s\n",VigasocoMain->step(controles).c_str());
/*
	// ¿tiene sentido todo el rato pasar controles
	// o pasarlo al inicio en el init??
controles[P1_UP]=1;
fprintf(stderr,"3 %d\n",controles[P1_UP]);
	VigasocoMain->step(controles);
fprintf(stderr,"4 %d\n",controles[P1_UP]);
//controles[P1_UP]=1;
	VigasocoMain->step(controles);
fprintf(stderr,"5 %d\n",controles[P1_UP]);
//controles[P1_UP]=1;
	VigasocoMain->step(controles);
//controles[P1_UP]=1;
fprintf(stderr,"6 %d\n",controles[P1_UP]);
	VigasocoMain->step(controles);
fprintf(stderr,"7 %d\n",controles[P1_UP]);
fprintf(stderr,"8 %d %s\n",controles[P1_UP],VigasocoMain->step(controles).c_str());
*/
	return 0;
}

