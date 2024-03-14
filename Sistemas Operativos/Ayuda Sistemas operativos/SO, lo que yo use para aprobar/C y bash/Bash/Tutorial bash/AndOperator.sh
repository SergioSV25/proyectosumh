#! /bin/bash

echo -e "Write youre age: \c"
read age

#FORMA 1 
if [ "$age" -gt 18 ] && [ "$age" -lt 30 ]
then
	echo "Valid age"
else
	echo "Invalid age"
fi	

#FORMA 2 
#En este caso la -a funciona como el and
if [ "$age" -gt 18 -a "$age" -lt 30 ]
then
	echo "Valid age"
else
	echo "Invalid age"
fi

#FORMA 3 
if [[ "$age" -gt 18 && "$age" -lt 30 ]]
then
	echo "Valid age"
else
	echo "Invalid age"
fi	
