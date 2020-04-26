from behave import *
import json
import requests
# todo, quitar sys
import sys
#from ctypes import cdll,c_int,c_char_p,byref
from ctypes import cdll,c_int,c_char_p,c_size_t,create_string_buffer,sizeof,POINTER

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


Controles = c_int * 70

class AbadIA(object):
	def __init__(self):
		print("AbadIA CONSTRUCTOR")
		self.lib = cdll.LoadLibrary('./LibAbadIA.so')
		self.lib.LibAbadIA_init()
		self.lib.LibAbadIA_step.restype = c_char_p
#falta revisar tipo de controles
		self.lib.LibAbadIA_step.argtypes = [POINTER(c_int),c_char_p,c_size_t]
		self.lib.LibAbadIA_save.restype = c_char_p
		self.lib.LibAbadIA_save.argtypes = [c_char_p,c_size_t]
		self.lib.LibAbadIA_load.argtypes = [c_char_p]
#		Controles = c_int * 70
		self.controles = Controles()
#		print("init dump 0%d\n",self.lib.LibAbadIA_step(self.controles))
#		print("init dump 1%d\n",self.lib.LibAbadIA_step(self.controles))
#		self.lib.LibAbadIA_step(controles)
		
##	def step(self,controles):
###		Controles = c_int * 70
#		controles = Controles()
#		tmp = self.lib.LibAbadIA_step(controles)
##		return self.lib.LibAbadIA_step(self.controles)
#		print ("step*%s*",self.status)
#		return tmp 

	def step(self):
		result = create_string_buffer(10000)
		tmp = self.lib.LibAbadIA_step(self.controles,result,sizeof(result)).decode()
# TODO vaya manera fea de poner todo a cero de nuevo
		self.controles = Controles()
		return tmp

	def load(self,input):
		return self.lib.LibAbadIA_load(input)
#igual el create_string_buffer puede ir aqui y no por todos lados			
#igual que en step
	def save(self,result,resultMaxLength):
		return self.lib.LibAbadIA_save(result,resultMaxLength)

#TODO: meter la direccion y puerto en una constante, en configuracion
# o que se inicialice al principio del escenario

# TODO: volver a activar cuando tengamos recurso status
@given('una conexion a la interfaz')
def step_impl(context):
    assert True

@given('una conexion existente a la interfaz')
def step_impl(context):
    context.execute_steps('''
	Given una conexion a la interfaz
    ''');

@when('reinicio el juego')
def step_impl(context):
##	controles = Controles()
#	Controles = c_int * 70
#	controles = Controles()
#	controles[KEYBOARD_E]=1
#	context.status=context.abadIA.step(controles).decode()
	context.abadIA.controles[KEYBOARD_E]=1
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()

#    r=requests.post(context.url,timeout=context.timeout)
#    assert r.status_code==200

@when('mando el comando "{comando}"')
def step_impl(context,comando):
#    r=requests.post(context.url+'/current/actions/'+comando,timeout=context.timeout)
#    assert r.status_code==200
	# en lib solo soportamos estos
	assert comando=="UP" or comando =="QR"
	if (comando=="UP"): 
		context.abadIA.controles[P1_UP]=1
#		context.status=context.abadIA.step().decode()
		context.status=context.abadIA.step()
	elif comando=="QR":
		context.abadIA.controles[KEYBOARD_Q]=1
		context.abadIA.controles[KEYBOARD_R]=1
#		context.status=context.abadIA.step().decode()
		context.status=context.abadIA.step()
	else:
		print("la version lib solo soporta ahora mismo comando UP y QR")
		assert False

#@when('no hago nada')
@step('no hago nada')
def step_impl(context):
#	Controles = c_int * 70
#	controles = Controles()
#	context.status=context.abadIA.step(controles).decode()
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()
#    r=requests.post(context.url+'/current/actions/NOP',timeout=context.timeout)
#    assert r.status_code==200


@step('duplico la velocidad')
def step_impl(context):
#    r=requests.post(context.url+'/current/actions/SPEEDUP',timeout=context.timeout)
#    assert r.status_code==200
	context.abadIA.controles[SERVICE_1]=1
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()

@step('reduzco la velocidad')
def step_impl(context):
#    r=requests.post(context.url+'/current/actions/SLOWDOWN',timeout=context.timeout)
#    assert r.status_code==200
	context.abadIA.controles[SERVICE_2]=1
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()

@when('digo que SI')
def step_impl(context):
#    r=requests.post(context.url+'/current/actions/SI',timeout=context.timeout)
#    assert r.status_code==200
	context.abadIA.controles[KEYBOARD_S]=1
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()

@when('digo que NO')
def step_impl(context):
#    r=requests.post(context.url+'/current/actions/NO',timeout=context.timeout)
#    assert r.status_code==200
	context.abadIA.controles[KEYBOARD_N]=1
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()

@when('giro a la izquierda')
def step_impl(context):
#    r=requests.post(context.url+'/current/actions/LEFT',timeout=context.timeout)
#    assert r.status_code==200
	context.abadIA.controles[P1_LEFT]=1
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()

@when('giro a la derecha')
def step_impl(context):
#    r=requests.post(context.url+'/current/actions/RIGHT',timeout=context.timeout)
#    assert r.status_code==200
	context.abadIA.controles[P1_RIGHT]=1
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()

@when('doy media vuelta')
def step_impl(context):
#    r=requests.post(context.url+'/current/actions/RIGHT',timeout=context.timeout)
#    assert r.status_code==200
#    r=requests.post(context.url+'/current/actions/RIGHT',timeout=context.timeout)
#    assert r.status_code==200
	context.abadIA.controles[P1_RIGHT]=1
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()
	context.abadIA.controles[P1_RIGHT]=1
	context.status=context.abadIA.step().decode()
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()

@when('avanzo')
def step_impl(context):
#    r=requests.post(context.url+'/current/actions/UP',timeout=context.timeout)
#    assert r.status_code==200
	context.abadIA.controles[P1_UP]=1
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()

@when('avanzo "{numeroPasos}" pasos')
def step_impl(context,numeroPasos):
#    i=0;
#    while i < int(numeroPasos):
#     r=requests.post(context.url+'/current/actions/UP',timeout=context.timeout)
#     assert r.status_code==200
# El segundo UP es porque el movimiento de avanzar necesita de 2 ciclos para completar la animacion de dar pasos
# Tambien vale con enviar un NOP
# Pero es mas realista enviar 2 UP, que es lo que haria un jugador humano, dejar pulsado UP hasta que ve ha terminado de avanzar
#     r=requests.post(context.url+'/current/actions/UP',timeout=context.timeout)
#     assert r.status_code==200
#     i+=1;

#     r=requests.post(context.url+'/current/actions/UP?repeat='+str(int(numeroPasos)*2),timeout=context.timeout)
#     assert r.status_code==200

	i=0;
	while i < int(numeroPasos):
		context.abadIA.controles[P1_UP]=1
#		context.status=context.abadIA.step().decode()
		context.status=context.abadIA.step()
		context.abadIA.controles[P1_UP]=1
#		context.status=context.abadIA.step().decode()
		context.status=context.abadIA.step()
		i+=1

@when('Adso avanza "{numeroPasos}" pasos')
def step_impl(context,numeroPasos):
#    i=0;
#    while i < int(numeroPasos):
#     r=requests.post(context.url+'/current/actions/DOWN',timeout=context.timeout)
#     assert r.status_code==200
#     i+=1;

#     r=requests.post(context.url+'/current/actions/DOWN?repeat='+numeroPasos,timeout=context.timeout)
#     assert r.status_code==200

	i=0;
	while i < int(numeroPasos):
		context.abadIA.controles[P1_DOWN]=1
#		context.status=context.abadIA.step().decode()
		context.status=context.abadIA.step()
		i+=1


@when('espero "{numeroIteraciones}" iteraciones')
def step_impl(context,numeroIteraciones):
#    i=0;
#    while i < int(numeroIteraciones):
#     r=requests.post(context.url+'/current/actions/NOP',timeout=context.timeout)
#     assert r.status_code==200
#     i+=1;

#     r=requests.post(context.url+'/current/actions/NOP?repeat='+numeroIteraciones,timeout=context.timeout)
#     assert r.status_code==200
	i=0;
	while i < int(numeroIteraciones):
#		context.status=context.abadIA.step().decode()
		print ("iteracion "+str(i)+" en espero iteraciones")
		context.status=context.abadIA.step()
		i+=1

@when('pulso espacio')
def step_impl(context):
#    r=requests.post(context.url+'/current/actions/SPACE',timeout=context.timeout)
#    assert r.status_code==200
#	context.abadIA.controles[KEYBOARD_SPACE]=1
	context.abadIA.controles[P1_BUTTON1]=1
#	context.status=context.abadIA.step().decode()
	context.status=context.abadIA.step()

#falta no tener que pasar el json
#y que behave lo construya en base a los comandos listados
#TODO falta verificar que el resultado de cada comando individual es OK
#TODO falta hacer uno equivalente para probar el endpoint de grabaciones si al final se mantiene
@when('mando los comandos')
def step_impl(context):
  r=requests.post(context.url+'/current/actions',context.text,timeout=context.timeout);
  print("multicommand status code "+str(r.status_code));
#  assert r.status_code>0
  assert r.status_code==200

@when('cargo una partida')
def step_impl(context):
#    r=requests.put(context.url+'/current',context.text,timeout=context.timeout)
#    assert r.status_code==200
#	print("cargo una partida cuyo texto es: *"+context.text+"*")
	assert context.abadIA.load(context.text.encode())
	

@step('grabo la partida')
def step_impl(context):
#    r=requests.get(context.url+'/current', headers={"accept":"text/x.abadIA+plain"},timeout=context.timeout)
#    print("***partida recibida***");
#    print(r.text);
#    assert r.status_code==200
## TODO: no se por que en el body hay una línea en blanco al final
#    assert r.text.count('\n')==431
## TODO: si está en la pantalla que indica el porcentaje completado
## y se de a grabar, se devuelven sólo 430 líneas ¿por qué?
# da fallos el decode a veces
#	res=context.abadIA.save().decode()
	result = create_string_buffer(10000)
	res=context.abadIA.save(result,sizeof(result)).decode()
	print("grabo la partida *"+res+"*")
	assert res.count('\n')==431

@step('grabo la partida y comparo el volcado')
def step_impl(context):
#    print("lineas partida esperada: "+context.text.count('\n')+1);
#    assert context.text.count('\n')+1==431;
#    r=requests.get(context.url+'/current', headers={"accept":"text/x.abadIA+plain"},timeout=context.timeout)
#    print("***partida recibida***");
#    print(r.text);
#    print("***partida esperada***");
#    print(context.text);
#    assert r.status_code==200
# TODO: no se por que en el body hay una línea en blanco al final
#    assert r.text.count('\n')==431
#    assert context.text==r.text
	print("lineas partida esperada: "+context.text.count('\n')+1);
	assert context.text.count('\n')+1==431;
	res=context.abadIA.save()
	print("***partida recibida***");
	print(res);
	print("***partida esperada***");
	print(context.text);
	assert res.count('\n')==431
	assert context.text==res
	

# TODO: comparar contra tabla para poder ampliar lo que se comprueba
@then('el resultado es "{resultado}" con descripcion "{descripcion}"')
def step_impl(context,resultado,descripcion):
	assert context.dump["resultado"]==resultado
	assert context.dump["descripcion"]==descripcion

@then('el resultado es "{resultado}"')
def step_impl(context,resultado):
	print("mmmm *"+context.dump+"**"+resultado+"**");
	assert context.dump==resultado

#@then('los valores iniciales son correctos')
@step('los valores iniciales son correctos')
def step_impl(context):
#    r=requests.get(context.url+'/current', headers={"accept":"application/json"},timeout=context.timeout)
#    assert r.status_code==200
#    print("resultDUMPtext**"+context.status.text);
# no me gusta tener que mandar el dump, pero tal y como se
# refrescan las frases es necesario
    context.abadIA.controles[KEYBOARD_D]=1
#    context.status=context.abadIA.step().decode()
    context.status=context.abadIA.step()
    print("resultDUMPtext**"+context.status);
    valid_json=False;
    try:
#      json_object = json.loads(context.status.text)
      json_object = json.loads(context.status)
    except ValueError:
      print("El dump no devuelve un  JSON\n");
      valid_json = False;
#      assert False 
    else:
      valid_json = True;
      dump = json.loads(context.status)
      print("resultDUMP**"+str(dump));

    assert valid_json;

    context.dump=dump;
    for head in context.table[0].headings:
      print("***"+head+"***"+type(dump[head]).__name__+"***valor recibido***"+str(dump[head])+"***valor esperado***"+str(context.table[0][head])+"***"); 
      if (type(dump[head]).__name__=="bool"):
       #assert dump[head]==bool(context.table[0][head])
       assert str(dump[head])==(context.table[0][head])
      else:
       if (type(dump[head]).__name__=="int"):
        assert dump[head]==int(context.table[0][head])
       else:
        assert False 
