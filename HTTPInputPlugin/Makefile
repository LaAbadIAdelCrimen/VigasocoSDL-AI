#CXXFLAGS=-O3 -fPIC -I../core -I../VigasocoSDL/ `sdl-config --cflags` -std=c++11 -D__abadIA__ 
#CXXFLAGS=-march=native -Ofast -fopenmp -fPIC -I../core -I../core/util  -I../VigasocoSDL/ `sdl-config --cflags` -std=c++11 -D__abadIA__ 
#TODO: falta ver si se puede hacer profiling en ejecución de una librería dinámica y recompilar optimizando
CXXFLAGS=-march=native -mtune=generic -frecord-gcc-switches -Ofast -fopenmp -std=c++17 -D__abadIA__ -fPIC -I../core -I../core/util -I../VigasocoSDL -I/usr/include/boost/ `sdl-config --cflags`  
LDFLAGS=-frecord-gcc-switches
VPATH=.:../core:../core/abadia:../core/util:../core/systems

all: ../VigasocoSDL/input/libVigasocoHTTPInputPlugin.so 

OBJECTS = HTTPInputPlugin.o PluginMain.o

OBJECTS_profile=$(OBJECTS:.o=.profile.o)

$(OBJECTS_profile): CXXFLAGS+=-D__abadIA_PROFILE__

%.profile.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# all 
all: ../VigasocoSDL/input/libVigasocoHTTPInputPlugin.so ../VigasocoSDL/input/libVigasocoHTTPInputPlugin-profile.so

../VigasocoSDL/input/libVigasocoHTTPInputPlugin.so: $(OBJECTS)
	$(CXX) -fPIC -shared $(OBJECTS) -I/usr/include/boost/ -lboost_thread -lboost_system -o $@

../VigasocoSDL/input/libVigasocoHTTPInputPlugin-profile.so: $(OBJECTS_profile)
	$(CXX) -fPIC -shared $(OBJECTS_profile)  -Ii/usr/include/boost/ -lboost_thread -lboost_system -o $@

clean:
	rm -f $(OBJECTS) $(OBJECTS_profile) ../VigasocoSDL/input/libVigasocoHTTPInputPlugin.so 

# end of file