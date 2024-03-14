#! /bin/bash

count=10
# Es tan simple como un if, se puede hacer de dos formas
#forma 1:
if [ $count -ne 9 ]
then
	echo "Condition is true"
fi	

#forma 2:
if (( $count >= 9 ))
then
	echo "Condition is true"
fi

word=a
#forma 1
if [[ $word == "a" ]]
then
	echo "Condition is true"
else
	echo "Condition is false"	
fi

#forma 2
if [[ $word > "b" ]]
then
	echo "Condition is true"
else
	echo "Condition is false"
fi

#Forma elif
if [[ $word == "b" ]]
then
	echo "Condition b is true"	
elif [[ $word == "a" ]] 
then	
	echo "Condition a is true"
else
	echo "Condition is false"	
fi