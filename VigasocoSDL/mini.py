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

