#! /bin/bash

echo -e "Write youre age: \c"
read age

#FORMA 1 
if [ "$age" -eq 18 ] || [ "$age" -eq 30 ]
then
	echo "Valid age"
else
	echo "Invalid age"
fi	

#FORMA 2 
#En este caso la -o funciona como el or
if [ "$age" -eq 18 -o "$age" -eq 30 ]
then
	echo "Valid age"
else
	echo "Invalid age"
fi

#FORMA 3 
if [[ "$age" -eq 18 || "$age" -eq 30 ]]
then
	echo "Valid age"
else
	echo "Invalid age"
fi