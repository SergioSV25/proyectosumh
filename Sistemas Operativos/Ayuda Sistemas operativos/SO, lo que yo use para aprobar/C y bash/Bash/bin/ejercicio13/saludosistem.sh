#! /bin/bash
userHome=~ 
	
	cd /home/alu30/bin/ejercicio10
	sal=$(saludo.sh)
	cd /home/alu30/bin/ejercicio11
	sem=$(Diasemana.sh)
	cd /home/alu30/bin/ejercicio12
	numus=$(cuentausuarios.sh)

	echo "$sal alu30"
	echo "Hoy es $sem"
	if (( $numus>0 && $numus <=10))
	 then
		echo "Número de usuarios: $numus (Servidor ocioso ...)"

	elif (( $numus>10 && $numus <=20))
	then

		echo "Número de usuarios: $numus (Servidor atareado ...)"

	elif (( $numus>20))
	then

		echo "Número de usuarios: $numus (Servidor saturado ...)"
	fi	
	
	 