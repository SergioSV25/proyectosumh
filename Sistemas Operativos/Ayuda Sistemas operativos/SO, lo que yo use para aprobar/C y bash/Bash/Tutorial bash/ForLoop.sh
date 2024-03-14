#! /bin/bash


#Forma 1
for i in 1 2 3 4 5
do
	echo $i
done

echo
echo
i=1
#Forma 2
#El rango es de 1 a 10 y se incrementa en 2
for i in {1..10..2}
do
	echo $i
done

echo
echo
i=1
#Forma 3

for (( i = 0; i < 10; i++ )) 
	do
		echo $i	
	done		