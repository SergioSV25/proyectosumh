#! /bin/bash

num1=20
num2=5

#Forma 1
echo "The addition is: $(( num1 + num2 ))"
echo "The substaction is: $(( num1 - num2 ))"
echo "The division is: $(( num1 / num2 ))"
echo "The multiplication is: $(( num1 * num2 ))"
echo "The mob is: $(( num1 % num2 ))"
echo
echo
#Forma 2
echo "The addition is: $(expr $num1 + $num2 )"
echo "The substaction is: $(expr $num1 - $num2 )"
echo "The division is: $(expr $num1 / $num2 )"
echo "The multiplication is: $(expr $num1 \* $num2 )"
echo "The mob is: $(expr $num1 % $num2 )"

#Si usamos expr en la multiplicacion se tiene que poner \* en lugar de *
#si no da error