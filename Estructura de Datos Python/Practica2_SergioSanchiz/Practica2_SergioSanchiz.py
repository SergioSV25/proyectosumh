#Practica 2 Sergio Sanchiz

from random import randint, choice
import time

#----------------------------------------------------------------------------
#-----------------------------CLASE CLIENTE----------------------------------
#----------------------------------------------------------------------------
class Cliente:
    def __init__(self, id, nombre, edad, sexo, entrada):
        self.id = id
        self.nombre = nombre
        self.edad = edad
        self.sexo = sexo
        self.entrada = entrada

    def __lt__(self, otro):
        if isinstance(otro, int):
            return self.id < otro
        else:
            return self.id < otro.id


    def __str__(self):
        return f"ID: {self.id}, Nombre: {self.nombre}, Edad: {self.edad}, Sexo: {self.sexo}, Entrada: {self.entrada}"

#----------------------------------------------------------------------------
#-------------------------------CLASE NODO-----------------------------------
#----------------------------------------------------------------------------
class Nodo:
    def __init__(self, valor):
        self.valor_objeto = valor
        self.id = valor.id
        self.izquierdo = None
        self.derecho = None

#----------------------------------------------------------------------------
#-------------------------------CLASE ARBOL----------------------------------
#----------------------------------------------------------------------------
class ArbolBinarioBusqueda:
    def __init__(self):
        self.raiz = None

    #Inserto los valoes en el arbol dependiendo del valor de los nodos, lo coloco como padre o hijo izquiero o derecho
    def insertar(self, id, valor):
        nuevo_nodo = Nodo(valor)

        if self.raiz is None:
            self.raiz = nuevo_nodo
        else:
            nodo_actual = self.raiz
            while True:
                if id == nodo_actual.id:
                    # Si ya existe un nodo con la misma id, se podría decidir si se
                    # reemplaza su valor o se lanza una excepción, dependiendo de la
                    # lógica específica de la aplicación
                    nodo_actual.valor_objeto = valor
                    return
                elif id < nodo_actual.id:
                    if nodo_actual.izquierdo is None:
                        nodo_actual.izquierdo = nuevo_nodo
                        return
                    else:
                        nodo_actual = nodo_actual.izquierdo
                else:
                    if nodo_actual.derecho is None:
                        nodo_actual.derecho = nuevo_nodo
                        return
                    else:
                        nodo_actual = nodo_actual.derecho

    #Desciendo por los nodos para buscar el valor que doy a la funcion
    def buscar(self, valor_buscar):
        nodo_actual = self.raiz

        while nodo_actual is not None:
            if nodo_actual.valor_objeto.id == valor_buscar:
                return nodo_actual.valor_objeto
            elif valor_buscar < nodo_actual.valor_objeto.id:
                nodo_actual = nodo_actual.izquierdo
            else:
                nodo_actual = nodo_actual.derecho

        return None

    
    #Funciones de la clase para hacer los recorridos y mostrar por pantalla los arboles
    # IN_ORDER
    def recorrido_inorden(self, nodo):
        if nodo is not None:
            self.recorrido_inorden(nodo.izquierdo)
            print(nodo.valor_objeto)
            self.recorrido_inorden(nodo.derecho)

    # PRE_ORDER
    def recorrido_preorden(self, nodo):
        if nodo is not None:
            print(nodo.valor_objeto)
            self.recorrido_preorden(nodo.izquierdo)
            self.recorrido_preorden(nodo.derecho)

    # POST_ORDER
    def recorrido_postorden(self, nodo):
        if nodo is not None:
            self.recorrido_postorden(nodo.izquierdo)
            self.recorrido_postorden(nodo.derecho)
            print(nodo.valor_objeto)

    # POR ANCHURA
    def recorrido_anchura(self, nodo):
        if nodo is None:
            return

        cola = [nodo]

        while cola:
            actual = cola.pop(0)
            print(actual.valor_objeto)

            if actual.izquierdo is not None:
                cola.append(actual.izquierdo)
            if actual.derecho is not None:
                cola.append(actual.derecho)

    #Eliminar un cliente y su nodo
    def eliminar(self, id):
        nodo_actual = self.raiz
        nodo_padre = None

        # Buscar el nodo a eliminar
        while nodo_actual is not None and nodo_actual.id != id:
            nodo_padre = nodo_actual
            if id < nodo_actual.id:
                nodo_actual = nodo_actual.izquierdo
            else:
                nodo_actual = nodo_actual.derecho

        if nodo_actual is None:
            # No se encontró el nodo a eliminar
            return

        # Caso 1: el nodo a eliminar no tiene hijos
        if nodo_actual.izquierdo is None and nodo_actual.derecho is None:
            if nodo_actual == self.raiz:
                self.raiz = None
            elif nodo_actual == nodo_padre.izquierdo:
                nodo_padre.izquierdo = None
            else:
                nodo_padre.derecho = None

            # Eliminar el cliente correspondiente
            eliminar_cliente_por_id(id, arbol1, arbol2, arbol3)

        # Caso 2: el nodo a eliminar tiene un solo hijo
        elif nodo_actual.izquierdo is None:
            hijo = nodo_actual.derecho
            nodo_actual.valor_objeto = hijo.valor_objeto
            nodo_actual.id = hijo.id
            nodo_actual.izquierdo = hijo.izquierdo
            nodo_actual.derecho = hijo.derecho

            # Eliminar el cliente correspondiente
            eliminar_cliente_por_id(id, arbol1, arbol2, arbol3)

        elif nodo_actual.derecho is None:
            hijo = nodo_actual.izquierdo
            nodo_actual.valor_objeto = hijo.valor_objeto
            nodo_actual.id = hijo.id
            nodo_actual.izquierdo = hijo.izquierdo
            nodo_actual.derecho = hijo.derecho

            # Eliminar el cliente correspondiente
            eliminar_cliente_por_id(id, arbol1, arbol2, arbol3)

        # Caso 3: el nodo a eliminar tiene dos hijos
        else:
            sucesor = nodo_actual.derecho
            while sucesor.izquierdo is not None:
                sucesor = sucesor.izquierdo

            self.eliminar(sucesor.id)
            nodo_actual.valor_objeto = sucesor.valor_objeto
            nodo_actual.id = sucesor.id

            # Eliminar el cliente correspondiente
            eliminar_cliente_por_id(id, arbol1, arbol2, arbol3)

    #Lo mismo que buscar, pero este devuelve el nodo alojado
    def buscar_nodo(self, id):
        nodo_actual = self.raiz

        while nodo_actual is not None:
            if nodo_actual.id == id:
                return nodo_actual
            elif id < nodo_actual.id:
                nodo_actual = nodo_actual.izquierdo
            else:
                nodo_actual = nodo_actual.derecho

        return None


    #Eliminar llama a este metodo para el nodo
    def eliminar_nodo(self, id):
        nodo_actual = self.raiz
        nodo_padre = None

        # Buscar el nodo a eliminar
        while nodo_actual is not None and nodo_actual.id != id:
            nodo_padre = nodo_actual
            if id < nodo_actual.id:
                nodo_actual = nodo_actual.izquierdo
            else:
                nodo_actual = nodo_actual.derecho

        if nodo_actual is None:
            # No se encontró el nodo a eliminar
            return

        # Caso 1: el nodo a eliminar es una hoja
        if nodo_actual.izquierdo is None and nodo_actual.derecho is None:
            if nodo_actual == self.raiz:
                self.raiz = None
            elif nodo_actual == nodo_padre.izquierdo:
                nodo_padre.izquierdo = None
            else:
                nodo_padre.derecho = None

        # Caso 2: el nodo a eliminar tiene un solo hijo
        elif nodo_actual.izquierdo is None:
            hijo = nodo_actual.derecho
            if nodo_actual.cliente == hijo.cliente:
                nodo_actual.derecho = None
            else:
                nodo_actual.valor_objeto = hijo.valor_objeto
                nodo_actual.id = hijo.id
                nodo_actual.izquierdo = hijo.izquierdo
                nodo_actual.derecho = hijo.derecho

        elif nodo_actual.derecho is None:
            hijo = nodo_actual.izquierdo
            if nodo_actual.cliente == hijo.cliente:
                nodo_actual.izquierdo = None
            else:
                nodo_actual.valor_objeto = hijo.valor_objeto
                nodo_actual.id = hijo.id
                nodo_actual.izquierdo = hijo.izquierdo
                nodo_actual.derecho = hijo.derecho

        # Caso 3: el nodo a eliminar tiene dos hijos
        else:
            sucesor = nodo_actual.derecho
            while sucesor.izquierdo is not None:
                sucesor = sucesor.izquierdo

            self.eliminar_nodo(sucesor.id)
            nodo_actual.valor_objeto = sucesor.valor_objeto
            nodo_actual.id = sucesor.id

#------------------------------------------------------------------------
#-------------------------FUNCIONES GENERALES----------------------------
#------------------------------------------------------------------------
#número de 6 dígitos
def pedir_id(): 
    id = int(input("Ingresa la ID del cliente \n"))
    if len(str(id)) == 6:
        return id
    else:
        print("La ID tiene que ser un numero de 6 digitos. \n")
        return pedir_id()

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
    
#entrada booleano
def pedir_entrada():
    entrada_cliente = input("Introduce si ha entrado a la sala o no: \n")
    if entrada_cliente.lower() == "si":
            entrada_cliente = True
    elif entrada_cliente.lower() == "no":
            entrada_cliente = False
    else:
        print("Solo puedes contestar si o no")
        return pedir_entrada()


#-------------------------ESTAS FUNCIONES INTERACTUAN DIRECTAMENTE CON LA CLASE ARBOLBUSQUEDABINARIA()----------------------------------------

#Inserto cliente llamando a insertar de la clase Arbol Binario
def insertar_cliente(cliente, sala):
    sala.insertar(cliente.id, cliente)

#Busco el cliente por su id en los arboles
def buscar_cliente_por_id(cliente_id, arbol1, arbol2, arbol3):
    encontrado = False
    cliente_encontrado = None

    # Buscar en arbol1
    resultado = arbol1.buscar(cliente_id)
    if resultado:
        encontrado = True
        cliente_encontrado = resultado

    # Buscar en arbol2
    resultado = arbol2.buscar(cliente_id)
    if resultado:
        encontrado = True
        cliente_encontrado = resultado

    # Buscar en arbol3
    resultado = arbol3.buscar(cliente_id)
    if resultado:
        encontrado = True
        cliente_encontrado = resultado

    if encontrado:
        return cliente_encontrado
    else:
        return None

#Junto a eliminar() para hacer la misma funcion
def eliminar_cliente_por_id(cliente_id, arbol1, arbol2, arbol3):
    cliente_encontrado = None
    arbol_encontrado = None

    # Buscar en arbol1
    resultado = arbol1.buscar(cliente_id)
    if resultado:
        cliente_encontrado = resultado
        arbol_encontrado = arbol1

    # Buscar en arbol2
    resultado = arbol2.buscar(cliente_id)
    if resultado:
        cliente_encontrado = resultado
        arbol_encontrado = arbol2

    # Buscar en arbol3
    resultado = arbol3.buscar(cliente_id)
    if resultado:
        cliente_encontrado = resultado
        arbol_encontrado = arbol3

    if cliente_encontrado:
        # Eliminar el cliente del árbol
        arbol_encontrado.eliminar(cliente_id)

        # Si el nodo donde estaba el cliente ya no tiene hijos, eliminar el nodo también
        if arbol_encontrado.buscar_nodo(cliente_id) is None:
            arbol_encontrado.eliminar_nodo(cliente_id)

        return cliente_encontrado
    else:
        return None



#----------------------------------------------------------------------------
#--------------------ESTO SERIA EL INICIO DEL PROGRAMA-----------------------
#----------------------------------------------------------------------------
arbol1 = ArbolBinarioBusqueda()
arbol2 = ArbolBinarioBusqueda()
arbol3 = ArbolBinarioBusqueda()

#CREO UNOS CLIENTES PARA NO TENER SIEMPRE QUE ANYADIR
cliente = Cliente(100000, "Juan", 25, "Masculino", False)
insertar_cliente(cliente, arbol1)
cliente = Cliente(121212, "Sergio", 43, "Masculino", True)
insertar_cliente(cliente, arbol1)

cliente = Cliente(454545, "Maria", 88, "femenino", True)
insertar_cliente(cliente, arbol2)
cliente = Cliente(676767, "Mario", 8, "masculino", True)
insertar_cliente(cliente, arbol2)

cliente = Cliente(343434, "Lucas", 44, "Otro", False)
insertar_cliente(cliente, arbol3)
cliente = Cliente(898989, "Nuria", 23, "Femenino", False)
insertar_cliente(cliente, arbol3)

while True:
    print("---------------------------------------------------------------------------------------------------------------------------------------")
    print("Menú:")
    print("1. Insertar un miembro en un ABB")
    print("2. Buscar cualquier espectador en un ABB")
    print("3. Imprimir lista de espectadores en cualquier ABB indicando recorridos de cualquier forma: anchura, profundidad (PRE, IN, POST ORDEN)")
    print("4. Borrar un espectador, cuya tarjeta haya sido introducida por teclado, si existe en el correspondiente ABB")
    print("5. Introducir un numero y crear dicha cantidad de espectadores al alzar guardandolos en el correspondiente ABB")
    print("6. Introducir un numero y generar al azar dicha cantidad de espectadores, que se borraran, si existen, en los correspondientes ABB")
    print("7. Iniciar la simulacion")
    print("8. Salir del programa")
    
    opcion = input("Seleccione una opción: ")

    if opcion == "1":
        id_cliente = pedir_id()
        nombre_cliente = pedir_nombre()
        edad_cliente = pedir_edad()
        sexo_cliente = pedir_sexo()
        entrada_cliente = pedir_entrada()

        cliente = Cliente(id_cliente, nombre_cliente, edad_cliente, sexo_cliente, entrada_cliente)

        arbol_elegido = int(input("¿En qué árbol quieres insertar al cliente? (1/2/3): "))

        if arbol_elegido == 1:
            insertar_cliente(cliente, arbol1)
            print("Cliente con DNI: ", id_cliente, " insertado correctamente en el arbol 1.")
        elif arbol_elegido == 2:
            insertar_cliente(cliente, arbol2)
            print("Cliente con DNI: ", id_cliente, " insertado correctamente en el arbol 2.")
        elif arbol_elegido == 3:
            insertar_cliente(cliente, arbol3)
            print("Cliente con DNI: ", id_cliente, " insertado correctamente en el arbol 3.")

    elif opcion == "2":
        # Pregunto al usuario el ID del cliente que desea buscar
        cliente_id = int(input("Ingrese el ID del cliente que desea buscar: "))

        # Busco el cliente en los tres árboles binarios de búsqueda
        cliente_encontrado = buscar_cliente_por_id(cliente_id, arbol1, arbol2, arbol3)

        if cliente_encontrado:
            print("Cliente encontrado:")
            print(cliente_encontrado)
        else:
            print("El cliente con el id ",cliente_id," no fue encontrado.")

    elif opcion == "3":
        sala_num = int(input("Ingrese el número de sala (1, 2 o 3): "))

        #Muestro por pantalla el contenido de los arboles por los metodos indicados
        if sala_num == 1:
            print("Recorrido por profundidad: ")
            print("IN_ORDER")
            arbol1.recorrido_inorden(arbol1.raiz)
            print("PRE_ORDER")
            arbol1.recorrido_preorden(arbol1.raiz)
            print("POST_ORDER")
            arbol1.recorrido_postorden(arbol1.raiz)

            print("Recorrido por anchura")
            arbol1.recorrido_anchura(arbol1.raiz)

        elif sala_num == 2:
            print("Recorrido por profundidad: ")
            print("IN_ORDER")
            arbol2.recorrido_inorden(arbol2.raiz)
            print("PRE_ORDER")
            arbol2.recorrido_preorden(arbol2.raiz)
            print("POST_ORDER")
            arbol2.recorrido_postorden(arbol2.raiz)

            print("Recorrido por anchura")
            arbol2.recorrido_anchura(arbol2.raiz)

        elif sala_num == 3:
            print("Recorrido por profundidad: ")
            print("IN_ORDER")
            arbol3.recorrido_inorden(arbol3.raiz)
            print("PRE_ORDER")
            arbol3.recorrido_preorden(arbol3.raiz)
            print("POST_ORDER")
            arbol3.recorrido_postorden(arbol3.raiz)

            print("Recorrido por anchura")
            arbol3.recorrido_anchura(arbol3.raiz)
        else:
            print("Número de sala inválido")

    elif opcion == "4":
        
        #Introduzco el id para eliminar el cliente con ese id
        id_a_eliminar = int(input("Introduce el ID del cliente que quieres eliminar: "))

        # Busco el cliente en los tres árboles binarios de búsqueda
        cliente_eliminado = eliminar_cliente_por_id(id_a_eliminar, arbol1, arbol2, arbol3)

        # Verifica si el cliente fue eliminado correctamente y muestra un mensaje en consecuencia
        if cliente_eliminado is not None:
            print(f"El cliente con ID {id_a_eliminar} ha sido eliminado correctamente.")
        else:
            print(f"No se encontró ningún cliente con ID {id_a_eliminar}.")

    elif opcion == "5":
        num_espectadores = int(input("Ingrese la cantidad de espectadores que deseas crear: "))
        
        #Tengo pensado crear unos clientes aleatorios, entonces crearé una lista de nombres, sexo y entrada
        lista_nombres = ["Paula", "Isabel", "Nuria", "Sergio", "Juan", "Pedro", "María", "Sofía", "Lucía", "Miguel", "Lucas", "Carlos"]
        lista_sexo = ["Hombre", "Mujer", "Otro"]
        lista_entrada = [True, False]

        #Creo clientes hasta llegar al final del numero de espectadores
        for i in range(num_espectadores):
            #Ahora con la lista de nombres, empiezo a crear los clientes
            id = randint(100000, 999999) #ID aleatorio
            nombre = choice(lista_nombres) #Nombre aleatorio
            edad = randint(1, 99) #Edad aleatoria
            sexo = choice(lista_sexo) #Sexo aleatorio
            entrada = choice(lista_entrada) #Entrada aleatoria
            
            #Creo el objeto cliente con sus datos
            cliente = Cliente(id, nombre, edad, sexo, entrada)

            #Cambio cada elemento de la lista cliente en un nodo para poder hacer las comparaciones y asi agregarlo al arbol
            nodo_cliente = Nodo(cliente) #Creo el primer nodo con el valor de id
            actual = nodo_cliente  #Establezco el nodo actual como el primer nodo

            #Asigno el valor del atributo "id" del cliente al atributo "id" del nodo
            nodo_cliente.id = cliente.id
                
            if i % 3 == 0:
                insertar_cliente(cliente, arbol1)
                print("Cliente con ID: ", id, "metido en el ABB1")
                
            elif i % 3 == 1:
                insertar_cliente(cliente, arbol2)
                print("Cliente con ID: ", id, "metido en el ABB2")
            else:
                insertar_cliente(cliente, arbol3)
                print("Cliente con ID: ", id, "metido en el ABB3")

    elif opcion == "6":
        #Este paso es parecido al 4 solo que de manera aleatoria genera los IDs
        cantidad_IDs = int(input("Escribe la cantidad de IDs que quieres generar de manera aleatoria: \n"))

        print("Generando IDs aleatorios...")

        #Empiezo el bucle for para hacer 
        for i in range(cantidad_IDs):
            #Para ello genero el ID aleatorio
            id_aleatorios_a_eliminar = randint(100000, 999999)

            # Busco el cliente en los tres árboles binarios de búsqueda
            cliente_eliminado = eliminar_cliente_por_id(id_aleatorios_a_eliminar, arbol1, arbol2, arbol3)

            # Verifica si el cliente fue eliminado correctamente y muestra un mensaje en consecuencia
            if cliente_eliminado is not None:
                print(f"El cliente con ID {id_aleatorios_a_eliminar} ha sido eliminado correctamente.")
            else:
                print(f"No se encontró ningún cliente con ID {id_aleatorios_a_eliminar}.")

    elif opcion == "7": 
        #Comienza la simulacion
        print("Comienza la simulacion, el programa tendra autonomia a partir de este mensaje")

        conteo_segundos = 0

        while conteo_segundos < 6:
            time.sleep(1)
            
            lista_nombres = ["Paula", "Isabel", "Nuria", "Sergio", "Juan", "Pedro", "María", "Sofía", "Lucía", "Miguel", "Lucas", "Carlos", "Valentina", "Jose", "Manuel"]
            lista_sexo = ["Hombre", "Mujer", "Otro"]
            lista_entrada = [True, False]
            lista_arboles = [arbol1, arbol2, arbol3]

            #Genero los clientes
            id_aleatorio = randint(100000, 999999)
            nombre_aleatorio = choice(lista_nombres)
            edad_aleatorio = randint(1, 99) 
            sexo_aleatorio = choice(lista_sexo) 
            entrada_aleatorio = choice(lista_entrada) 
            
            cliente = Cliente(id_aleatorio, nombre_aleatorio, edad_aleatorio, sexo_aleatorio, entrada_aleatorio)

            if entrada_aleatorio == True:
                arbol_aleatorio = choice(lista_arboles)
                insertar_cliente(cliente, arbol_aleatorio)

                print("ABB1:")
                arbol1.recorrido_inorden(arbol1.raiz)
                print("\n")

                print("ABB2:")
                arbol2.recorrido_inorden(arbol2.raiz)
                print("\n")

                print("ABB3:")
                arbol3.recorrido_inorden(arbol3.raiz)
                print("\n")

                if arbol_aleatorio == arbol1:
                    print(f"EVENTO: Se introduce espectador {id_aleatorio} en el ABB1\n")
                elif arbol_aleatorio == arbol2:
                    print(f"EVENTO: Se introduce espectador {id_aleatorio} en el ABB2\n")
                elif arbol_aleatorio == arbol3:
                    print(f"EVENTO: Se introduce espectador {id_aleatorio} en el ABB3\n")
            else:
                arbol_aleatorio = choice(lista_arboles)
                print("ABB1:")
                arbol1.recorrido_inorden(arbol1.raiz)
                print("\n")

                print("ABB2:")
                arbol2.recorrido_inorden(arbol2.raiz)
                print("\n")

                print("ABB3:")
                arbol3.recorrido_inorden(arbol3.raiz)
                print("\n")

                if arbol_aleatorio == arbol1:
                    print(f"EVENTO: Se borra espectador {id_aleatorio} del ABB1\n")
                elif arbol_aleatorio == arbol2:
                    print(f"EVENTO: Se borra espectador {id_aleatorio} del ABB2\n")
                elif arbol_aleatorio == arbol3:
                    print(f"EVENTO: Se borra espectador {id_aleatorio} del ABB3\n")
        
            conteo_segundos += 1


    elif opcion == "8":
        print("Saliendo del programa")
        break