#CXXFLAGS=-O3 -fPIC -I../core -I../VigasocoSDL/ `sdl-config --cflags` -D__abadIA__
CXXFLAGS=-march=native -mtune=generic -frecord-gcc-switches -Ofast -fopenmp -D_GLIBCXX_PARALLEL -fPIC -std=c++11 -I../core -I../VigasocoSDL/ `sdl-config --cflags` -D__abadIA__
LDFLAGS=-frecord-gcc-switches
#CXXFLAGS=-g -fPIC -I../core -I../VigasocoSDL/ `sdl-config --cflags`
VPATH=.:../core:../core/abadia:../core/util:../core/systems

OBJECTS = SDLAudioPlugin.o NULLAudioPlugin.o PluginMain.o

../VigasocoSDL/audio/libVigasocoSDLAudioPlugin.so: $(OBJECTS) 
	$(CXX) -fPIC -shared $(OBJECTS) -o $@
#	$(CXX) -g -fPIC -shared $(OBJECTS) -o $@

# para comprobar que no le faltan dependencias por resolver a la libreria
test: test.o
	$(CXX) -g test.o -o test -L ../VigasocoSDL/audio/ -l VigasocoSDLAudioPlugin `sdl-config --libs`

clean:
	rm -f $(OBJECTS) ../VigasocoSDL/audio/libVigasocoSDLAudioPlugin.so test test.o
