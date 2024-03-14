/*3. Sacar la hipotenusa de un triangulo rectángulo,
pidiendo al usuario el valor de los 2 catetos*/

#include<stdio.h>
#include <math.h>
int main(){
	float hipotenusa, cateto1,cateto2;
	
	printf("digita el valor de los dos catetos: ");
	scanf("%f %f",&cateto1, &cateto2);
	
	hipotenusa = cateto1+cateto2;
	
	printf("la hipotenusa del triangulo: %.3f", hipotenusa);
	
	return 0;
}
