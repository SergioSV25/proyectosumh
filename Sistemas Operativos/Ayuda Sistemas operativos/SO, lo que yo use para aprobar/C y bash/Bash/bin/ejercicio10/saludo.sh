#! /bin/bash
userHome=~ 


	
	
	Hora=$(date +%H%M)

	if (( Hora > 800 && Hora < 1359 ))
	then
		echo "Buenos dias "

	elif (( Hora > 1400 && Hora < 2059 )); 
	then
		echo "Buenas tardes "
	else
		echo "Buenas noches "		
	fi