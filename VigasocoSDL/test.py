import sys
from ctypes import cdll,c_int,c_char_p

Controles = c_int * 70


class AbadIA(object):
	def __init__(self):
		self.lib = cdll.LoadLibrary('./LibAbadIA.so')
		self.lib.LibAbadIA_step.restype = c_char_p
		self.lib.LibAbadIA_init()
	def step(self,controles):
		return self.lib.LibAbadIA_step(controles)

test = AbadIA()

controles = Controles()

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

i=0
print("dump0 %s",test.step(controles))
print("dump1 %s",test.step(controles))
print("dump2 %s",test.step(controles))
print("dump3 %s",test.step(controles))

#test.step(controles)
#controles[P1_UP]=1
#test.step(controles)
#controles[P1_UP]=0
#test.step(controles)
#test.step(controles)
#test.step(controles)
#test.step(controles)
#test.step(controles)
#print("Hello, world!", file=sys.stderr)
#sys.stderr.write('hello world')
#prueba reiniciar
#controles[KEYBOARD_E]=1;
#test.step(controles)
#controles[KEYBOARD_E]=0;
#test.step(controles)
#test.step(controles)
#test.step(controles)
#test.step(controles)
#print("Bye, world!", file=sys.stderr)
#sys.stderr.write('bye world')
controles[KEYBOARD_D]=1;
print("kk*%s*", "a");
tmp=test.step(controles)
print("dump1*%s*", tmp);
print("dump2*%s*", test.step(controles));
controles[KEYBOARD_D]=0;








