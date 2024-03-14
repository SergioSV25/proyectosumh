#! /bin/bash

#Introducir texto en variables
echo "Enter full name: " 
read name1 name2 name3
echo "Enterd full name: $name1, $name2, $name3"

#Lo mismo pero todo es en la misma linea
#El comando -p es para que se lea tofo lo de la linea
#El -sp es lo mismo pero silencioso, es decir, no salen caracteres
echo
echo
read -p 'Username : ' user_var
read -sp 'Password : ' password_var
#Echo solo es para poner un espacio
echo
echo "Username: $user_var"
echo "Password: $password_var"


#Para gaurdar varios valores juntos en un array se hace asi:
echo
echo
echo "Enter names: "
read -a names
echo "Names: ${names[0]}, ${names[1]}, ${names[2]}"

#Aqui vemos que si no ponemos ninguna variable donde guardar los datos,
#se almacena en una variable predefinida que es $REPLY
#esta variable almacena tanto caracter como strings
echo
echo
echo "Enter name: "
read 
echo "Names: $REPLY"