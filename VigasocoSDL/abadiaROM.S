	.global abadiaROM
	.global abadiaROM_size
#	.section .rodata
# no puede ir en readonly porque
# Logica::iniciaHabitacionEspejo
# lo modifica en caliente
# y no quiero copiarlo en ram 
# al iniciar 
	.section .data
abadiaROM:
	.incbin "volcadorom"
1:
abadiaROM_size:
	.int 1b - abadiaROM
