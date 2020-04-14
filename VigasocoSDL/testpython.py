import sys
from ctypes import cdll,c_int,c_char_p
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

lib.LibAbadIA_step.restype = c_char_p

class AbadIA(object):
	def init(self):
		lib.LibAbadIA_init()
	def step(self,controles):
#		Controles = c_int * 70
#		controles = Controles()
		kk = lib.LibAbadIA_step(controles)
		print ("step*%s*",kk)
		return kk

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


#prueba avanzar
(P1_UP ,
P1_LEFT,
P1_DOWN,
P1_RIGHT,
P1_BUTTON1,
P1_BUTTON2,
P2_UP,
P2_LEFT,
P2_DOWN,
P2_RIGHT,
P2_BUTTON1,
P2_BUTTON2,
START_1,
START_2,
COIN_1,
COIN_2,
SERVICE_1,
SERVICE_2,
KEYBOARD_A,
KEYBOARD_B,
KEYBOARD_C,
KEYBOARD_D,
KEYBOARD_E,
KEYBOARD_F,
KEYBOARD_G,
KEYBOARD_H,
KEYBOARD_I,
KEYBOARD_J,
KEYBOARD_K,
KEYBOARD_L,
KEYBOARD_M,
KEYBOARD_N,
KEYBOARD_O,
KEYBOARD_P,
KEYBOARD_Q,
KEYBOARD_R,
KEYBOARD_S,
KEYBOARD_T,
KEYBOARD_U,
KEYBOARD_V,
KEYBOARD_W,
KEYBOARD_X,
KEYBOARD_Y,
KEYBOARD_Z,
KEYBOARD_0,
KEYBOARD_1,
KEYBOARD_2,
KEYBOARD_3,
KEYBOARD_4,
KEYBOARD_5,
KEYBOARD_6,
KEYBOARD_7,
KEYBOARD_8,
KEYBOARD_9,
KEYBOARD_SPACE,
KEYBOARD_INTRO,
KEYBOARD_SUPR,
FUNCTION_1,
FUNCTION_2,
FUNCTION_3,
FUNCTION_4,
FUNCTION_5,
FUNCTION_6,
FUNCTION_7,
FUNCTION_8,
FUNCTION_9,
FUNCTION_10,
FUNCTION_11,
FUNCTION_12) = range(69)
#FUNCTION_12) = map(c_int, range(69))

print("sin enviar nada", file=sys.stderr)
sys.stderr.write('sin enviar nada')
test.step(controles)
test.step(controles)
print("fin sin enviar nada", file=sys.stderr)
sys.stderr.write('fin sin enviar nada')
controles[P1_UP]=1
test.step(controles)
controles[P1_UP]=0
test.step(controles)
test.step(controles)
test.step(controles)
test.step(controles)
test.step(controles)
print("Hello, world!", file=sys.stderr)
sys.stderr.write('hello world')
#prueba reiniciar
controles[KEYBOARD_E]=1;
test.step(controles)
controles[KEYBOARD_E]=0;
test.step(controles)
test.step(controles)
test.step(controles)
test.step(controles)
print("Bye, world!", file=sys.stderr)
sys.stderr.write('bye world')
controles[KEYBOARD_D]=1;
print("kk*%s*", "a");
tmp=test.step(controles)
print("dump*%s*", tmp);
#print("dump*%s*", test.step(controles));
controles[KEYBOARD_D]=0;








