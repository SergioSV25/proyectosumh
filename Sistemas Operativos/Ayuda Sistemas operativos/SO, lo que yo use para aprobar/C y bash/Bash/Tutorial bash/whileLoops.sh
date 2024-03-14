#! /bin/bash


n=1

#Forma 1
while [[ $n -le 10 ]]; 
do
	echo "$n"
	((n++))
done

#Froma 2
echo
n=1
echo
while (( $n <= 10 )); 
do
	echo "$n"
	((n++))
done