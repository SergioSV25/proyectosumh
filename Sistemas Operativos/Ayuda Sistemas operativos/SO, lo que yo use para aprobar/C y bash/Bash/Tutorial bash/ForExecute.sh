#! /bin/bash

for command in ls pwd date 
do
	echo "----------------------$command--------------------------"
	$command
done

echo 
echo 


#El * significa que quiero iterar este bucle for tantas
#veces como direcorotios haya en este propio directorio
for item in *
do
	if [ -d $item ]
	then
		echo $item
		
	fi
done