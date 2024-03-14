
#Definimnos el target o el ejecutable 
#que en este caso es myporg
#UNa vez tengamos eso hay que poner el.o de 
#cada archivo .c que es para compilar el objeto

TARGET = myprog
OBJS = main.o diag.o com.o init.o
CFLAGS = -Wall #Esto es para mostrara warnings
CC = gcc

$(TARGET) : $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(TARGET)
#para que no salga la linea de arriba se pone @

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@


.PHONY : clean 
clean:
	rm -f *.o $(TARGET)
#Esto sirve para eliminar todos los archivos .o y el myprog
#cuando llamemos a clean
#El phony es para asegurarnos de que coge el clean de forma correcta	