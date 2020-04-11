from ctypes import cdll,c_int
lib = cdll.LoadLibrary('./LibAbadIA.so')

# ok con class
# falta step 
#class AbadIA(object):
#	def __init__(self):
#		self.obj = lib.LibAbadIA_new()

#	def init(self):
#		lib.LibAbadIA_init(self.obj)

#a = AbadIA()
#a.init()

# pruebas sin class
#error, piensa que el singleton devuelve un int
#lib.LibAbadIA_singleton().init()
#a = lib.LibAbadIA_singleton()
#a.init()

# con class pero si guardar nada, ya que es un singleton
# la lib tiene que instanciar el objeto, ya que no lo hacemos aquí
Controles = c_int * 70

class AbadIA(object):
	def init(self):
		lib.LibAbadIA_init()
	def step(self,controles):
#		Controles = c_int * 70
#		controles = Controles()
		lib.LibAbadIA_step(controles)

test = AbadIA()
test.init()

controles = Controles()
#print(controles)
#for i in controles: print(i, end=" ")
test.step(controles)
test.step(controles)
test.step(controles)
test.step(controles)
test.step(controles)
#test.step()
#lib.LibAbadIA_step(controles)
