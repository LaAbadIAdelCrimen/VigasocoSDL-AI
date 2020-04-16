Pruebas abadia compilada como lib

git checkout libabadia
make -f Makefile.libtest  libtest  LibAbadIA.so
ver test.py testpython.py libtest.cpp extra/tests/features/environment.py y /extra/tests/features/steps/lib_steps/lib_steps.py* para ejemplos de uso

probar en extra/tests/features/ haciendo un enlace a LibAbadia.so
ln -s ../../../VigasocoSDL/LibAbadIA.so . 
behave -D interfaz=libtest XXX.feature -n "NoMBRE ESCENARIO"

para comparar comportamiento con 
behave -D interfaz=http XXX.feature -n "NoMBRE ESCENARIO"
(hay que tener un abadia-HEADLESS antiguo arrancado)

da core dump si se prueba

behave -D interfaz=libtest ResolverAbadIA.feature

sin embardo no da core con
behave -D interfaz=libtest ResolverAbadIA.feature abadIA.feature


