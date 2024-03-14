#Practica 1 Estructura de Datos / Sergio Sanchiz

import random
import time

#------------------------------------------------------------------------
#---------------------OPERACIONES DE LAS COLAS---------------------------
#------------------------------------------------------------------------

class Cola:
    #Creando las colas vacias, con capacidad maxima que le pase por pantalla
    def __init__(self):
        self.item = []
            
    #Agrega el elemento x como último de la cola.
    def encolar(self, cliente):
        self.item.append(cliente)

    #Funcion para saber la longitud de la cola
    def longitud(self):
        return len(self.item)

    #Elimina el primer elemento de la cola y devuelve su valor.
    #Si la cola está vacía, levanta ValueError.
    def desencolar(self):
        try:
            return self.item.pop(0)
        except:
            raise ValueError("La cola está vacía")

    #Devuelve True si la cola esta vacía, False si no.
    def es_vacia(self):
        return self.item == []
    
    #Para poder imprimir el contenido de las listas
    def __str__(self):
        return str(self.item)
    
    #Vaciamos la cola entera
    def vaciar(self):
        while not self.es_vacia():
            self.desencolar()

#------------------------------------------------------------------------
#-------------------------FUNCIONES GENERALES----------------------------
#------------------------------------------------------------------------

#número de 6 dígitos
def pedir_dni(): 
    dni = int(input("Ingresa el dni del cliente \n"))
    dni_igual = unico_dni(dni)
    
    if dni_igual == True:
        print("Este DNI esta repetido, ingresa uno distinto: \n")
        pedir_dni()
    else:
        if len(str(dni)) == 6:
            return dni
        else:
            print("El dni tiene que ser un numero de 6 digitos. \n")
            return pedir_dni()

#el dni que pase lo va a buscar en cada cliente de la lista donde guardo todos los clientes
def unico_dni(dni_buscar):
    dni_igual = False
    for i in range(cola_general.longitud()):
        cliente = cola_general.desencolar()       
        #Recorro la lista del cliente sacado hasta dar con el dni
        if cliente[0] == dni_buscar:
            dni_igual = True
    return dni_igual


#string de 10 letras
def pedir_nombre(): 
    nombre = input("Ingresa el nombre del cliente \n")
    if(len(nombre)) <= 10:
        return nombre
    else:
        print("El nombre debe ser maximo de 10 letras \n")
        return pedir_nombre()

#número entre 0 y 99
def pedir_edad(): 
    edad = int(input("Ingresa la edad del cliente \n"))
    if edad >= 0 and edad <= 100:
        return edad
    else:
        print("La edad solo puede ser entre 0 y 100 anyos \n")
        return pedir_edad()

#femenino, masculino u otro
def pedir_sexo(): 
    sexo = input("Introduce el sexo: (masculino, femenino u otro) \n")
    if sexo.lower() in ["masculino", "femenino", "otro"]:
        return sexo.lower()
    else:
        print("El sexo solo puede ser 'masculino', 'femenino' o 'otro'.\n")
        return pedir_sexo()

#comedia, terror, fantasía
def pedir_genero(): 
    genero = input("Introduce el genero: (comedia, terror o fantasia) \n")
    if genero.lower() in ["comedia", "terror", "fantasia"]:
        return genero.lower()
    else:
        print("El genero de pelicula solo puede ser 'comedia', 'terror' o 'fantasia'.\n")
        return pedir_genero()


#----------------------------------------------------------------------------
#--------------------ESTO SERIA EL INICIO DEL PROGRAMA-----------------------
#----------------------------------------------------------------------------

clientes_comedia = Cola()
clientes_terror = Cola()
clientes_fantasia = Cola()
cola_general = Cola()
numero_aleatorio2 = random.randint(1, 3)
numero_aleatorio3 = random.randint(1, 3)

while True:
    print("-------------------------")
    print("Venta de entradas de cine")
    print("--------- Menu ----------")
    print("1.Insertar un miembro en una cola")
    print("2.Sacar el primer cliente de cualquier cola")
    print("3.Imprimir cualquier cola")
    print("4.Consultar que clientes estan esperando en cualquier cola")
    print("5.Ver informacion sobre un cliente por su DNI")
    print("6.Iniciar la simulacion (datos generados aleatoriamente)")
    print("7. Salir")

    opcion = input("Ingresa una opcion: ")

    #Añadiendo clientes a la lista de espera y a la cola por genero (se considera sala)
    if opcion == "1":
        print("Insertando miembros en la cola")

        #Pido los datos al cliente llamando a las demas funciones
        dni = pedir_dni()
        nombre = pedir_nombre()
        edad = pedir_edad()
        sexo = pedir_sexo()
        genero = pedir_genero()
        sala = input("Indica si le ha gustado la peli: \n")
        
        #Instancio la lista cliente con el valor de los atributos dados
        cliente = [dni, nombre, edad, sexo, genero, sala]

        #Lo meto en la cola general por si luego tengo que consultarla
        cola_general.encolar(cliente)

        #Ahora lo meto en la cola del genero que haya puesto
        if cliente[4] == "terror":
            clientes_terror.encolar(cliente)
            print("Cliente metido en la lista Terror, quedaria tal que asi:")
            print(clientes_terror)

        elif cliente[4] == "comedia":
            clientes_comedia.encolar(cliente)
            print("Cliente metido en la lista Comedia, quedaria tal que asi:")
            print(clientes_comedia)

        elif cliente[4] == "fantasia":
            clientes_fantasia.encolar(cliente)
            print("Cliente metido en la lista Fantasia, quedaria tal que asi:")
            print(clientes_fantasia)

        print("Operacion realizada con exito, tanto en lista de espera como en cola por genero de cine \n")


    #Eliminando el primer cliente de la cola por genero aleatoriamente
    elif opcion == "2":
        print("Sacando cliente...\n")

        if numero_aleatorio2 == 1:
            clientes_terror.desencolar()
            print("Cliente sacado de la lista Terror, quedaria tal que asi:")
            print(clientes_terror)

        elif numero_aleatorio2 == 2:
            clientes_fantasia.desencolar()
            print("Cliente sacado de la lista Fantasia, quedaria tal que asi:")
            print(clientes_fantasia)

        elif numero_aleatorio2 == 3:
            clientes_comedia.desencolar()
            print("Cliente sacado de la lista Comedia, quedaria tal que asi:")
            print(clientes_comedia)


    #Imprimo una cola aleatoria
    elif opcion == "3":
        print("Imprimiendo cualquier cola. \n")
        
        if numero_aleatorio3 == 1:
            print(clientes_terror)
        elif numero_aleatorio3 == 2:
            print(clientes_fantasia)
        elif numero_aleatorio3 == 3:
            print(clientes_comedia)

        
    #Consulto e imprimo todos 
    elif opcion == "4":
        print("Consultando todos los clientes")
        print(cola_general)


    elif opcion == "5":
        #Primero comprobamos que la lista no esté vacia
        if cola_general.es_vacia():
            print("No hay clientes en la cola")
        else:
            dni_buscar = int(input("Ingrese el DNI del cliente que desea buscar: "))
            encontrado = False
            for i in range(cola_general.longitud()):
                cliente = cola_general.desencolar()       
            #Recorro la lista hasta dar con el dni 
                if cliente[0] == dni_buscar:
                    encontrado = True
                    #Imprimo la información del cliente encontrado
                    print("Información del cliente con DNI", dni_buscar)
                    print("Nombre:", cliente[1])
                    print("Edad:", cliente[2])
                    print("Sexo:", cliente[3])
                    print("Género de cine:", cliente[4])
                    print("Le ha gustado la película:", cliente[5])
                    cola_general.encolar(cliente)
                else:
                    print("No se encontró ningún cliente con el DNI", dni_buscar)


    elif opcion == "6":
        print("Iniciando simulacion")
        
        #Creo nuevas listas
        lista_dnis_comedia = []
        lista_dnis_terror = []
        lista_dnis_fantasia = []
        lista_dnis_general = []

        #Verificadores de las salas que están llenas
        salas_llenas = 0
        sala_comedia = 0
        sala_terror = 0
        sala_fantasia = 0
        
        i = 1
        
        print("Generando clientes aleatorios...\n")

        while salas_llenas < 3:

            cola_general.vaciar()
            salas_llenas = sala_comedia + sala_fantasia + sala_terror
            generos_disponibles = ["comedia", "terror", "fantasia"]
            
            #Creo cada cliente de manera aleatoria
            time.sleep(5) 
            dni = random.randint(100000, 999999)
            nombre = "Cliente " + str(i)
            i += 1
            edad = random.randint(0, 100)
            sexo = random.choice(["masculino", "femenino", "otro"])
            genero = random.choice(generos_disponibles)
            legusta = random.randint(0, 100)
            if (legusta >= 6):
                sala = "Si"
                cliente = [dni, nombre, edad, sexo, genero, sala]
                print(cliente)
            else:
                sala = "No"
                print("Error de venta al cliente con dni: ", dni)
            
            dni_cliente = cliente[0]
            cola_general.encolar(cliente)

            #Hago un bucle while que termina cuando se llenan las 3 salas
            while not cola_general.es_vacia() and salas_llenas < 3:
                cliente = cola_general.desencolar()
                genero = cliente[4]
                
                #Para meter un usuario en la lista de genero COMEDIA
                if genero == "comedia" and sala == "Si" and len(lista_dnis_comedia) <= 9:
                    lista_dnis_comedia.append(dni_cliente)
                    print ("Comedia: ", lista_dnis_comedia)

                elif len(lista_dnis_comedia) > 9:                      
                    if "comedia" in generos_disponibles:
                            generos_disponibles.remove("comedia")
                    lista_dnis_general.append(dni_cliente)
                    sala_comedia = 1
                
                #Para meter un usuario en la lista de genero TERROR
                if genero == "terror" and sala == "Si" and len(lista_dnis_terror) <= 9:
                    lista_dnis_terror.append(dni_cliente)
                    print("Terror: ", lista_dnis_terror)    
                
                elif len(lista_dnis_terror) > 9:        
                        if "terror" in generos_disponibles:
                            generos_disponibles.remove("terror")
                        lista_dnis_general.append(dni_cliente)
                        sala_terror = 1
                
                #Para meter un usuario en la lista de genero FANTASIA
                if genero == "fantasia" and sala == "Si" and len(lista_dnis_fantasia) <= 9:
                    lista_dnis_fantasia.append(dni_cliente)
                    print ("Fantasia: ", lista_dnis_fantasia)

                elif len(lista_dnis_fantasia) > 9:
                        if "fantasia" in generos_disponibles:
                            generos_disponibles.remove("fantasia")
                        lista_dnis_general.append(dni_cliente)
                        sala_fantasia = 1 
        
        #Cuando se llenen las 3 listas, entonces se mostraran todos los datos y se cierra la simulacion
        else:
            print("Se han llenado todas las salas.")
            print("Clientes por DNI en la sala comedia: ", lista_dnis_comedia)
            print("Clientes por DNI en la sala terror: ", lista_dnis_terror)
            print("Clientes por DNI en la sala fantasia: ", lista_dnis_fantasia)
            print("Clientes por DNI esperando a entrar en alguna sala: ", lista_dnis_general)
            print("Cine cerrado, termina la simulación. \n")
            cola_general.vaciar()

    

    elif opcion == "7":
        print("Saliendo del programa...")
        break

    else:
        print("Opción inválida. Por favor ingrese una opción válida.")
        