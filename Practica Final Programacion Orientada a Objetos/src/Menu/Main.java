package Menu;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import Contacto.Contactos;
import Contacto.ContactoPersonal;
import Contacto.ContactoProfesional;
import Eventos.Evento;
import Eventos.CitaAniversario;
import Eventos.CitaCumpleanyos;
import Eventos.CitaMedico;
import Eventos.Reunion;
import Eventos.ReunionLlamadaTelefonica;
import Eventos.ReunionPresencial;
import Eventos.ReunionVideoconferencia;

//Main con todos las funciones, objetos, y lo que saldra por consola
public class Main {
	
//---------------------------------------------Funciones del programa-------------------------------------------------//
	
	/**
	 * TODO eliminar elemento que pidamos
	 * @param <L> Lista de objeto L, luego la funcion sabra de que objeto es la lista que le pasamos
	 * @param lista con elemento seleccionado, eliminado
	 * 
	 */
public static <L> void eliminarElementoArray(List<L> lista) {
		
		Scanner entrada = new Scanner(System.in);
		
		System.out.println("Indica si quieres eliminar un elemento de la lista (1) o no (2) ");
		int eliminar = Integer.parseInt(entrada.nextLine());
		
		if(eliminar == 1) {
			
			//Comprobar que la lista sea de la clase contacto
			if (lista.get(0) instanceof Contactos) {
				
				//Pido el nombre y el apellido del contacto que quiero eliminar
				System.out.println("Indica el nombre:");
				String nombreBuscado = entrada.nextLine();
				
				System.out.println("Indica el apellido: ");
				String apellidoBuscado = entrada.nextLine();
				
				//Recorro la lista
				for (int i = 0; i < lista.size(); i++) {
					
					L elemento = lista.get(i);
					
					//Cada elemento de la lista lo paso a objeto y compruebo que sea de la clase contactos
					if (elemento instanceof Contactos) {
					
						//Cambio objeto elemento a objeto contacto
						Contactos contacto = (Contactos) elemento;
	
				        //Obtener el nombre y el apellido del contacto y lo paso a minúsculas
				        String nombreContacto = contacto.getNombre().toLowerCase();
				        String apellidoContacto = contacto.getApellidos().toLowerCase();
				        
				        
				        //Verificar si los valores coinciden (ignorando mayúsculas y minúsculas)
				        if (nombreContacto.equalsIgnoreCase(nombreBuscado) && apellidoContacto.equalsIgnoreCase(apellidoBuscado)) {
				            
				        	//Eliminamos el objeto contacto
				            System.out.println("Contacto con nombre: " + nombreContacto + " eliminado.");
				            // Eliminamos el objeto contacto de la lista
	                        lista.remove(i);
				            
				        }
					} 
				}	
			}
			//Hago lo mismo con los elementos de la lista Reunion
			else if (lista.get(0) instanceof Evento) {
					
					//Pido el nombre y el apellido del contacto que quiero eliminar
					System.out.println("Indica el titulo:");
					String tituloBuscado = entrada.nextLine();
					
					//Recorro la lista
					for (int i = 0; i < lista.size(); i++) {
						
						L elemento = lista.get(i);
						
						//Cada elemento de la lista lo paso a objeto y compruebo que sea de la clase contactos
						if (elemento instanceof Evento) {
						
							//Cambio objeto elemento a objeto contacto
							Evento eventos = (Evento) elemento;
		
					        //Obtener el nombre y el apellido del contacto y lo paso a minúsculas
					        String tituloeliminar = eventos.getTitulo().toLowerCase();
					        
					        //Verificar si los valores coinciden (ignorando mayúsculas y minúsculas)
					        if (tituloeliminar.equalsIgnoreCase(tituloBuscado)) {
					            System.out.println("Evento con titulo: " + tituloeliminar + " eliminado.");
					            // Eliminamos el objeto evento de la lista
		                        lista.remove(i);        
					        }
						} 
					}
			}
		}	
}


/**
 * Modificacion de un contacto de la lista
 * @param lista contactos
 */
public static void modificarContacto(List<Contactos> lista) {
    Scanner entrada = new Scanner(System.in);

    // Pedir al usuario el nombre y el apellido del contacto a buscar
    System.out.print("Ingrese el nombre del contacto: ");
    String nombreBuscado = entrada.nextLine();
    System.out.print("Ingrese el apellido del contacto: ");
    String apellidoBuscado = entrada.nextLine();

    // Bucle para buscar el elemento en la lista
    for (Contactos contacto : lista) {
        if (contacto.getNombre().equalsIgnoreCase(nombreBuscado) &&
            contacto.getApellidos().equalsIgnoreCase(apellidoBuscado)) {

            System.out.println("Contacto encontrado:");

            // Verifica si es un objeto de la clase ContactoPersonal
            if (contacto instanceof ContactoPersonal) {
                ContactoPersonal contactoPersonalCambiar = (ContactoPersonal) contacto;

                // Muestra los atributos actuales del ContactoPersonal
                System.out.println(contactoPersonalCambiar);

             // Pide al usuario qué atributo desea modificar
                System.out.println("Seleccione el atributo que desea modificar:");
                System.out.println("1. Nombre");
                System.out.println("2. Apellidos");
                System.out.println("3. Teléfono");
                System.out.println("4. Movil");
                System.out.println("5. Fecha Cumpleanyos");
                System.out.println("6. Correo electronico");
                System.out.println("7. Alias");

                int opcionCambiar = Integer.parseInt(entrada.nextLine());

                // Modifica el atributo seleccionado
                switch (opcionCambiar) {
                    case 1:
                        System.out.print("Nuevo Nombre: ");
                        String nuevoNombre = entrada.nextLine();
                        contactoPersonalCambiar.setNombre(nuevoNombre);
                        break;
                    case 2:
                        System.out.print("Nuevo Apellido: ");
                        String nuevoApellido = entrada.nextLine();
                        contactoPersonalCambiar.setApellidos(nuevoApellido);
                        break;
                    case 3:
                    	System.out.print("Nuevo teléfono: ");
                        String nuevoTelefono = entrada.nextLine();
                        contactoPersonalCambiar.setTelefono(nuevoTelefono);
                        break;
                        
                    case 4:
                    	System.out.print("Nuevo Movil: ");
                        String nuevoMovil = entrada.nextLine();
                        contactoPersonalCambiar.setNum_movil(nuevoMovil);
                        break;
                        
                    case 5:
                    	System.out.print("Nueva Fecha de Cumpleanyos: ");
                        String nuevoCumple = entrada.nextLine();
                        contactoPersonalCambiar.setFechaCumpleanyos(nuevoCumple);
                        break;
                        
                    case 6:
                    	System.out.print("Nuevo correo: ");
                        String nuevoCorreo = entrada.nextLine();
                        contactoPersonalCambiar.setCorreo(nuevoCorreo);
                        break;
                        
                    case 7:
                    	System.out.print("Nuevo Alias: ");
                        String nuevoAlias = entrada.nextLine();
                        contactoPersonalCambiar.setAlias(nuevoAlias);
                        break;
                        
                        
                    default:
                        System.out.println("Opción no válida.");
                        System.out.println("Seleccione el atributo que desea modificar:");
                        System.out.println("1. Nombre");
                        System.out.println("2. Apellidos");
                        System.out.println("3. Teléfono");
                        System.out.println("4. Movil");
                        System.out.println("5. Fecha Cumpleanyos");
                        System.out.println("6. Correo electronico");
                        System.out.println("7. Alias");
                        
                        opcionCambiar = Integer.parseInt(entrada.nextLine());
                }
                
                System.out.println("Contacto modificado");
                System.out.println(" Nombre: " + contactoPersonalCambiar.getNombre());
                System.out.println(" Apellidos: " + contactoPersonalCambiar.getApellidos());
                System.out.println(" Teléfono: " + contactoPersonalCambiar.getTelefono());
                System.out.println(" Movil: " + contactoPersonalCambiar.getNum_movil());
                System.out.println(" Fecha Cumpleanyos: " + contactoPersonalCambiar.getFechaCumpleanyos());
                System.out.println(" Correo electronico: " + contactoPersonalCambiar.getCorreo());
                System.out.println(" Alias: " + contactoPersonalCambiar.getAlias());
                
            }
            // Verifica si es un objeto de la clase ContactoProfesional
            else if (contacto instanceof ContactoProfesional) {
                ContactoProfesional contactoProfesionalCambiar = (ContactoProfesional) contacto;

                // Muestra los atributos actuales del ContactoProfesional
                System.out.println(contactoProfesionalCambiar);

                // Pide al usuario qué atributo desea modificar
                System.out.println("Seleccione el atributo que desea modificar:");
                System.out.println("1. Nombre");
                System.out.println("2. Apellidos");
                System.out.println("3. Teléfono");
                System.out.println("4. Movil");
                System.out.println("5. Fecha Cumpleanyos");
                System.out.println("6. Correo electronico");
                System.out.println("7. Empresa");

                int opcionCambiar = Integer.parseInt(entrada.nextLine());

                // Modifica el atributo seleccionado
                switch (opcionCambiar) {
                    case 1:
                        System.out.print("Nuevo Nombre: ");
                        String nuevoNombre = entrada.nextLine();
                        contactoProfesionalCambiar.setNombre(nuevoNombre);
                        break;
                    case 2:
                        System.out.print("Nuevo Apellido: ");
                        String nuevoApellido = entrada.nextLine();
                        contactoProfesionalCambiar.setApellidos(nuevoApellido);
                        break;
                    case 3:
                    	System.out.print("Nuevo teléfono: ");
                        String nuevoTelefono = entrada.nextLine();
                        contactoProfesionalCambiar.setTelefono(nuevoTelefono);
                        break;
                        
                    case 4:
                    	System.out.print("Nuevo Movil: ");
                        String nuevoMovil = entrada.nextLine();
                        contactoProfesionalCambiar.setNum_movil(nuevoMovil);
                        break;
                        
                    case 5:
                    	System.out.print("Nueva Fecha de Cumpleanyos: ");
                        String nuevoCumple = entrada.nextLine();
                        contactoProfesionalCambiar.setFechaCumpleanyos(nuevoCumple);
                        break;
                        
                    case 6:
                    	System.out.print("Nuevo correo: ");
                        String nuevoCorreo = entrada.nextLine();
                        contactoProfesionalCambiar.setCorreo(nuevoCorreo);
                        break;
                        
                    case 7:
                    	System.out.print("Nueva empresa: ");
                        String nuevaEmpresa = entrada.nextLine();
                        contactoProfesionalCambiar.setEmpresa(nuevaEmpresa);
                        break;
                        
                        
                    default:
                        System.out.println("Opción no válida.");
                        System.out.println("Seleccione el atributo que desea modificar:");
                        System.out.println("1. Nombre");
                        System.out.println("2. Apellidos");
                        System.out.println("3. Teléfono");
                        System.out.println("4. Movil");
                        System.out.println("5. Fecha Cumpleanyos");
                        System.out.println("6. Correo electronico");
                        System.out.println("7. Empresa");
                        
                        opcionCambiar = Integer.parseInt(entrada.nextLine());
                }

                System.out.println("Contacto modificado");
                System.out.println(" Nombre: " + contactoProfesionalCambiar.getNombre());
                System.out.println(" Apellidos: " + contactoProfesionalCambiar.getApellidos());
                System.out.println(" Teléfono: " + contactoProfesionalCambiar.getTelefono());
                System.out.println(" Movil: " + contactoProfesionalCambiar.getNum_movil());
                System.out.println(" Fecha Cumpleanyos: " + contactoProfesionalCambiar.getFechaCumpleanyos());
                System.out.println(" Correo electronico: " + contactoProfesionalCambiar.getCorreo());
                System.out.println(" Empresa: " + contactoProfesionalCambiar.getEmpresa());
                
            }

            return; // Termina la función después de modificar el contacto
        }
        
        else {
        	System.out.println("Contacto no encontrado en la lista.");
        }
    } 
}


/**
 * Modificacion de un evento de la lista
 * @param lista eventos
 */
public static void modificarEvento(List<Evento> lista) {
    Scanner entrada = new Scanner(System.in);

    // Pedir al usuario el título del evento a buscar
    System.out.print("Ingrese el título del evento: ");
    String tituloBuscado = entrada.nextLine();

    // Bucle para buscar el evento en la lista
    for (Evento evento : lista) {
        if (evento.getTitulo().equalsIgnoreCase(tituloBuscado)) {
            System.out.println("Evento encontrado:");

            System.out.println("Seleccione el atributo que desea modificar:");
            System.out.println("1. Título: " + evento.getTitulo());
            System.out.println("2. Fecha y Hora de Inicio: " + evento.getFechaHoraInicio());
            System.out.println("3. Fecha y Hora de Fin: " + evento.getFechaHoraFin());
            System.out.println("4. Descripción: " + evento.getDescripcion());
            System.out.println("5. Notificar: " + evento.getNotificar());
            System.out.println("6. Tipo de Notificaciones: " + evento.getTipoNotificaciones());

            // Verifica el tipo de evento y permite al usuario modificar los atributos adecuados
            if (evento instanceof ReunionPresencial) {
            	
                ReunionPresencial reunionPresencial = (ReunionPresencial) evento;
                System.out.println("Tipo de Evento: Reunion Presencial");
                System.out.println("7. Localización X: " + reunionPresencial.getLocalizacionX());
                System.out.println("8. Localización Y: " + reunionPresencial.getLocalizacionY());
                System.out.println("9. Sala de Reuniones: " + reunionPresencial.getSalaReuniones());
            } 
            else if (evento instanceof ReunionLlamadaTelefonica) {
            	
                ReunionLlamadaTelefonica reunionLlamada = (ReunionLlamadaTelefonica) evento;
                System.out.println("Tipo de Evento: Reunion Llamada Telefónica");
                System.out.println("7. Teléfono Corto: " + reunionLlamada.getTelefonoCorto());
                System.out.println("8. Teléfono Largo: " + reunionLlamada.getTelefonoLargo());
                System.out.println("9. Clave: " + reunionLlamada.getClave());
            } 
            else if (evento instanceof ReunionVideoconferencia) {
            	
                ReunionVideoconferencia reunionVideoconferencia = (ReunionVideoconferencia) evento;
                System.out.println("Tipo de Evento: Reunion Videoconferencia");
                System.out.println("7. Tipo: " + reunionVideoconferencia.getTipo());
            } 
            else if (evento instanceof CitaAniversario) {
            	
                CitaAniversario citaAniversario = (CitaAniversario) evento;
                System.out.println("Tipo de Evento: Cita Aniversario");
                System.out.println("7. Contacto Personal: " + citaAniversario.getContactoPersonal());
                System.out.println("8. Fecha de Aniversario: " + citaAniversario.getFechaAniversario());
            } 
            else if (evento instanceof CitaCumpleanyos) {
            	
                CitaCumpleanyos citaCumpleanyos = (CitaCumpleanyos) evento;
                System.out.println("Tipo de Evento: Cita Cumpleaños");
                System.out.println("7. Nombre del Contacto: " + citaCumpleanyos.getNombreContacto());
            } 
            else if (evento instanceof CitaMedico) {
            	
                CitaMedico citaMedico = (CitaMedico) evento;
                System.out.println("Tipo de Evento: Cita Médico");
                System.out.println("7. Especialidad: " + citaMedico.getEspecialidad());
                System.out.println("8. Geolocalización X: " + citaMedico.getGeolocalizacionX());
                System.out.println("9. Geolocalización Y: " + citaMedico.getGeolocalizacionY());
            }

            System.out.print("Seleccione el número del atributo a modificar: ");
            int opcion = Integer.parseInt(entrada.nextLine());

            // Modificar el atributo seleccionado
            switch (opcion) {
                case 1:
                    System.out.print("Nuevo Título: ");
                    evento.setTitulo(entrada.nextLine());
                    break;
                case 2:
                    System.out.print("Nueva Fecha y Hora de Inicio: ");
                    evento.setFechaHoraInicio(entrada.nextLine());
                    break;
                case 3:
                    System.out.print("Nueva Fecha y Hora de Fin: ");
                    evento.setFechaHoraFin(entrada.nextLine());
                    break;
                case 4:
                    System.out.print("Nueva Descripción: ");
                    evento.setDescripcion(entrada.nextLine());
                    break;
                case 5:
                    System.out.print("Nuevo Notificar (true o false): ");
                    evento.setNotificar(entrada.nextLine());
                    break;
                case 6:
                    System.out.print("Nuevo Tipo de Notificaciones: ");
                    evento.setTipoNotificaciones(entrada.nextLine());
                    break;
                case 7:
                    // Modificar atributos específicos según el tipo de evento
                    if (evento instanceof ReunionPresencial) {
                        ReunionPresencial reunionPresencial = (ReunionPresencial) evento;
                        System.out.print("Nueva Localización X: ");
                        reunionPresencial.setLocalizacionX(entrada.nextLine());
                    } 
                    else if (evento instanceof ReunionLlamadaTelefonica) {
                        ReunionLlamadaTelefonica reunionLlamada = (ReunionLlamadaTelefonica) evento;
                        System.out.print("Nuevo Teléfono Corto: ");
                        reunionLlamada.setTelefonoCorto(Integer.parseInt(entrada.nextLine()));
                    } 
                    else if (evento instanceof ReunionVideoconferencia) {
                        ReunionVideoconferencia reunionVideoconferencia = (ReunionVideoconferencia) evento;
                        System.out.print("Nuevo Tipo: ");
                        reunionVideoconferencia.setTipo(entrada.nextLine());
                    } 
                    else if (evento instanceof CitaAniversario) {
                        CitaAniversario citaAniversario = (CitaAniversario) evento;
                        System.out.print("Nuevo Contacto Personal: ");
                        citaAniversario.setContactoPersonal(entrada.nextLine());
                    } 
                    else if (evento instanceof CitaCumpleanyos) {
                        CitaCumpleanyos citaCumpleanyos = (CitaCumpleanyos) evento;
                        System.out.print("Nuevo Nombre del Contacto: ");
                        citaCumpleanyos.setNombreContacto(entrada.nextLine());
                    } 
                    else if (evento instanceof CitaMedico) {
                        CitaMedico citaMedico = (CitaMedico) evento;
                        System.out.print("Nueva Especialidad: ");
                        citaMedico.setEspecialidad(entrada.nextLine());
                    }
                    break;
                
                case 8:
                    // Modificar atributos específicos según el tipo de evento
                    if (evento instanceof ReunionPresencial) {
                        ReunionPresencial reunionPresencial = (ReunionPresencial) evento;
                        System.out.print("Nueva Localización Y: ");
                        reunionPresencial.setLocalizacionY(entrada.nextLine());
                    } 
                    else if (evento instanceof ReunionLlamadaTelefonica) {
                        ReunionLlamadaTelefonica reunionLlamada = (ReunionLlamadaTelefonica) evento;
                        System.out.print("Nuevo Teléfono Largo: ");
                        reunionLlamada.setTelefonoLargo(Integer.parseInt(entrada.nextLine()));
                    } 
                    else if (evento instanceof CitaMedico) {
                        CitaMedico citaMedico = (CitaMedico) evento;
                        System.out.print("Nueva Geolocalización X: ");
                        citaMedico.setGeolocalizacionX(entrada.nextLine());
                    }
                    else if(evento instanceof CitaAniversario) {
                    	CitaAniversario citaAniversario = (CitaAniversario) evento;
                    	System.out.println("Nueva Fecha de Aniversario: ");
                    	citaAniversario.setFechaAniversario(entrada.nextLine());
                    }
                    break;
                case 9:
                    // Modificar atributos específicos según el tipo de evento
                    if (evento instanceof ReunionPresencial) {
                        ReunionPresencial reunionPresencial = (ReunionPresencial) evento;
                        System.out.print("Nueva Sala de Reuniones: ");
                        reunionPresencial.setSalaReuniones(entrada.nextLine());
                    } else if (evento instanceof ReunionLlamadaTelefonica) {
                        ReunionLlamadaTelefonica reunionLlamada = (ReunionLlamadaTelefonica) evento;
                        System.out.print("Nueva Clave: ");
                        reunionLlamada.setClave(entrada.nextLine());
                    } else if (evento instanceof CitaMedico) {
                        CitaMedico citaMedico = (CitaMedico) evento;
                        System.out.print("Nueva Geolocalización Y: ");
                        citaMedico.setGeolocalizacionY(entrada.nextLine());
                    }
                    
                    break;
                
                default:
                	
                    System.out.println("Opción no válida. Indica cual de las anteriores opciones quieres cambiar.");
                    opcion = Integer.parseInt(entrada.nextLine());
            
            }

            System.out.println("Evento modificado");
            return; // Termina la función después de modificar el evento
        }
        else {
        	System.out.println("Evento no encontrado en la lista.");
        }
    }

    
}


//-----------------------------------------EMPIEZA EL PROGRAMA-----------------------------------------------//
			
	//Empieza el main
	public static void main(String[] args) {
		
		Scanner entrada = new Scanner(System.in);
		
		List<Contactos> listaContactos = new ArrayList<>();
		List<Evento> listaEventos = new ArrayList<>();
		
		//------------------------------DECLARACION DE OBJETOS Y COLOCACION EN LAS LISTAS PARA COMPROBACIONES-------------------------------------------------//
		
		//Anyado 1 contacto de cada tipo al array para hacer mas facil las comprobaciones
		ContactoPersonal contactoPersonal = new ContactoPersonal("Santi", "Sempere", "669333221", "966221896", "24-3-2001", "micorreo@gmail.com", "NuevoAlias");
		listaContactos.add(contactoPersonal);
		
		ContactoProfesional contactoProfesional = new ContactoProfesional("Paco", "Buenafuente", "677890553", "988321245", "31-1-2000", "tucorreo@gmail.com", "MiEmpresa");
		listaContactos.add(contactoProfesional);
		
		//Anyado un evento de cada tipo al array para hacer mas facil las comprobaciones
		CitaAniversario aniversario = new CitaAniversario("13:46", "20:04", "Aniversario Paco", "Comida y cena en restaurante", "No", null, "Paco", "23-04");
		listaEventos.add(aniversario);
		
		CitaCumpleanyos cumple = new CitaCumpleanyos("12:00", "18:00", "Cumple Sergio", "27 cumpleanyos", "Si", "PopUp", "Sergio");
		listaEventos.add(cumple);
		
		CitaMedico medico = new CitaMedico("15:30", "16:30", "Cita Medico gastrointeritis", "Dolores de barriga y diarrea", "Si", "correo electronico", "Gastroenterologo", "29,58427", "21,43553249");
		listaEventos.add(medico);
		
		ReunionLlamadaTelefonica telefono = new ReunionLlamadaTelefonica("10:00", "10:15", "Llamada operador", "Llamar al operador de movil", "No", null, "Manuel Operador", 974322843, 655436273, "3288F");
		listaEventos.add(telefono);
		
		ReunionPresencial presencial = new ReunionPresencial("8:00", "9:00", "Reunion Trabajo", "Reunion Agentes de Seguridad", "No", null, null, "32,8888", "32", "Sala de trabajo");
		listaEventos.add(presencial);
		
		ReunionVideoconferencia conferencia = new ReunionVideoconferencia("13:00", "14:25", "Conferencia Xbox", "Conferencia de Xbox parte Starfield", "Si", "SMS", null, "Google Meet");
		listaEventos.add(conferencia);
		
				
		//---------------------------DECLARACION DE VARIABLES Y COMIENZO DEL FUNCIONAMIENTO DEL PROGRAMA--------------------------------------------------------//
		
		int menu = 0;
		int opcion;
		
		System.out.println("---- MENU AGENDA ---- Alumno: Sergio Sanchiz Villena ----  Correo: sergio.sanchiz@goumh.umh.es");
		
		do { //Siempre pondra el menu de distintas pantallas
			System.out.println("Selecciona la pantalla de Contactos(1), la de Eventos(2) o salir del programa(3)");
			
			menu = Integer.parseInt(entrada.nextLine());
			
			switch (menu) {
				
			//Pantalla de Contactos
			case 1:
					System.out.println("Selecciona si quieres dar de alta un contacto nuevo(1), modificar algun contacto guardado(2) o mostrar una lista de los contactos que tienes guardados(3).");
					opcion = Integer.parseInt(entrada.nextLine());
					
					if (opcion == 1) {//Dar de alta contacto
						
						System.out.println("¿Se trata de un contacto Personal(1) o de Empresa(2)?");
						int opcionContactos = Integer.parseInt(entrada.nextLine());
						
						if (opcionContactos == 1) {
							//Primero creo el objeto contacto, para evitar duplicidad de codigo, pido el alias y creo el objeto contactoProfesional
							Contactos contacto1 = Contactos.pedirInfoContacto();
							
							System.out.println("Alias: ");
							String alias = entrada.nextLine();
							
							//Objeto contacto personal
							ContactoPersonal personal = new ContactoPersonal(contacto1.getNombre(), contacto1.getApellidos(), contacto1.getTelefono(), contacto1.getNum_movil(), contacto1.getFechaCumpleanyos(), contacto1.getCorreo(), alias);
							
							//Nombre del contacto para comprobar que se ha anyadido
							System.out.println("Contacto con nombre: "+ personal.getNombre() +" y alias: " + personal.getAlias() + " dado de alta.");
							
							//Lo guardo en la lista general y la personal
							listaContactos.add(personal);							
						}
						else if (opcionContactos == 2) {
							//Primero creo el objeto contacto, para evitar duplicidad de codigo, pido la empresa y creo el objeto contactoProfesional
							Contactos contacto = Contactos.pedirInfoContacto();
							
							System.out.print("Empresa: ");
					        String empresa = entrada.nextLine();
							
					        //Objeto empresa
							ContactoProfesional profesional = new ContactoProfesional(contacto.getNombre(), contacto.getApellidos(), contacto.getTelefono(), contacto.getNum_movil(), contacto.getFechaCumpleanyos(), contacto.getCorreo(), empresa);
							
							//Nombre contacto para comprobar su creacion
							System.out.println("Contacto con nombre "+ profesional.getNombre() +" de Empresa: " + profesional.getEmpresa() + " dado de alta.");
							
							//Lo guardo en la lista general y en la lista profesional
							listaContactos.add(profesional);
						}
						else { //Control error de eleccion
							System.out.println("Opcion no valida. 1) para Contacto Personal, 2) para Contacto Profesional. ");
							opcionContactos = Integer.parseInt(entrada.nextLine());
						}
					}
					else if(opcion == 2) { //Opcion modificar contactos
						System.out.println("Cambiando informacion de contacto, indique los datos que se le asignan a continuacion. ");
						
						//La funcion se encarga de todo el proceso, solo tenemos que pasarle la lista contactos
						modificarContacto(listaContactos);
						
					}
					else if(opcion == 3) {//Opcion listado Contactos
						System.out.println("Selecciona si quieres ver una lista de todos los contactos(1), de los contactos personales(2) o de los contactos profesionales(3). ");
						opcion = Integer.parseInt(entrada.nextLine());
						
							if(opcion == 1) {//Lista de todos los contactos
								
								System.out.println("Mostrando lista de todos los contactos: ");
								
								//Recorriendo toda la lista para mostrar a cada contacto
								for(int i=0; i < listaContactos.size(); i++) {
								
								String nombre = listaContactos.get(i).getNombre();
								String apellido = listaContactos.get(i).getApellidos();
								
								System.out.println("Nombre: " + nombre);
					            System.out.println("Apellidos: " + apellido);
					            System.out.println(" ");
								}
								//Lamo a la funcion y le paso la lista	
								eliminarElementoArray(listaContactos);	
							}						
						else if(opcion == 2) { //Lista Contactos personales
					            
							System.out.println("Lista de Contactos Personales: ");
							
								//Recorriendo la lista
								for(int i=0; i < listaContactos.size(); i++) {
									
									//Instanceof para sacar todos los contactos personales
									if(listaContactos.get(i) instanceof ContactoPersonal) {
										
										String nombre = listaContactos.get(i).getNombre();
										String apellido = listaContactos.get(i).getApellidos();
										
										System.out.println("Nombre: " + nombre);
							            System.out.println("Apellidos: " + apellido);
							            System.out.println(" ");							            
									}
								}								
								//Lamo a la funcion y le paso la lista	
								eliminarElementoArray(listaContactos);
							}
						else if(opcion == 3) { //Lista Contactos Profesionales
							
							System.out.println("Lista de Contactos Profesionales: ");
								
								//Recorro la lista entera
								for(int i=0; i < listaContactos.size(); i++) {
									
									//Con instanceof, saco los elementos que pertenezcan a la clase contactoPersonal
									if(listaContactos.get(i) instanceof ContactoProfesional) {
										
										String nombre = listaContactos.get(i).getNombre();
										String apellido = listaContactos.get(i).getApellidos();
										
										System.out.println("Nombre: " + nombre);
							            System.out.println("Apellidos: " + apellido);
							            System.out.println(" ");
									
									}	            
							}	
							
							//Lamo a la funcion y le paso la lista	
							eliminarElementoArray(listaContactos);
						}							
						else {
							System.out.println("Error. Selecciona si quieres ver una lista de todos los contactos(1), de los contactos personales(2) o de los contactos profesionales(3).");
							opcion = Integer.parseInt(entrada.nextLine());
						}
				}		
					else {
						System.out.println("Opcion no valida. 1) para Alta de contacto, 2) para Modificar un contacto, 3) para ver el listado de contactos ");
						opcion = Integer.parseInt(entrada.nextLine());
						
						
					}
					
					break;
			case 2:
					//Pantalla de eventos
					System.out.println("Selecciona si quieres dar de alta un evento (1), modificarlo (2) o ver el listado de eventos (3)");
					opcion = Integer.parseInt(entrada.nextLine());
					
					if(opcion == 1) {
						
						System.out.println("Indica si es una cita (1) o una reunion (2): ");
						
						int crearEvento = Integer.parseInt(entrada.nextLine());
						
						//La parte de crear los objetos de eventos y meterlos en listas sera muy parecido a lo que hemos hecho con contactos
						
						if(crearEvento == 1) { //Opcion de que se trate de una cita
							
							System.out.println("Indica si se trata de una cumpleanyos (1), un anivarsario (2) o una cita de medico (3). ");
							int citaTipo = Integer.parseInt(entrada.nextLine());
							
							if(citaTipo == 1) { //Cumpleanyos
								Evento evento1 = Evento.pedirInfoEvento();
								
								System.out.println("Ingresa el nombre del Contacto cumpleanyero ");
								String nombreContacto = entrada.nextLine();
								
								CitaCumpleanyos citaCumple = new CitaCumpleanyos(evento1.getFechaHoraInicio(), evento1.getFechaHoraFin(), evento1.getTitulo(), evento1.getDescripcion(), evento1.getNotificar(), evento1.getTipoNotificaciones(), nombreContacto);
								
								System.out.println("Cita de Cumpleanyos con titulo: "+ citaCumple.getTitulo() + " creado");
								
								listaEventos.add(citaCumple);
								
							}
							else if(citaTipo == 2) { //Aniversario
								Evento evento2 = Evento.pedirInfoEvento();
								
								System.out.println("Ingresa la especialidad del medico: ");
								String especialidad = entrada.nextLine();
								
								System.out.println("Ingresa la localizacion de su consulta");
								System.out.println("En coordenadas X");
								String geolocalizacionX = entrada.nextLine();
								System.out.println("Y ahora en coordenadas Y");
								String geolocalizacionY = entrada.nextLine();
								
								CitaMedico citaMedico = new CitaMedico(evento2.getFechaHoraInicio(), evento2.getFechaHoraFin(), evento2.getTitulo(), evento2.getDescripcion(), evento2.getNotificar(), evento2.getTipoNotificaciones(), especialidad, geolocalizacionX, geolocalizacionY);
								
								System.out.println("Cita de Medico con titulo: "+ citaMedico.getTitulo() + " creado");
								
								listaEventos.add(citaMedico);
							}
							else if(citaTipo == 3) { //Aniversario
								Evento evento3 = Evento.pedirInfoEvento();
								
								System.out.println("Ingresa el nombre del Contacto del aniversario ");
								String nombreContacto = entrada.nextLine();
								
								System.out.println("Ingresa la fecha del aniversario ");
								String fechaAniversario = entrada.nextLine();
								
								CitaAniversario citaAniversario = new CitaAniversario(evento3.getFechaHoraInicio(), evento3.getFechaHoraFin(), evento3.getTitulo(), evento3.getDescripcion(), evento3.getNotificar(), evento3.getTipoNotificaciones(), nombreContacto, fechaAniversario);
								
								System.out.println("Cita de Aniversario con titulo: "+ citaAniversario.getTitulo() + " creado");
								
								listaEventos.add(citaAniversario);
								
							}
							else {//Control de error de elecciones
								System.out.println("Error. Indica si se trata de una cumpleanyos (1), un anivarsario (2) o una cita de medico (3).");
								citaTipo = Integer.parseInt(entrada.nextLine());
							}
							
						}
						else if(crearEvento == 2) { //Opcion de que se trate de una reunion
							System.out.println("Indica si se trata de una reunion Presencial (1), por Llamada Telefonica (2) o por Videollamada (3)");
							int tipoReunion = Integer.parseInt(entrada.nextLine());
							
							if(tipoReunion == 1) { //Reunion presencial
								Evento evento4 = Evento.pedirInfoEvento();
								
								System.out.println("Indica el nombre del contacto con quien ");
								String contacto = entrada.nextLine();
								
								Reunion reunion4 = new Reunion(evento4.getFechaHoraInicio(), evento4.getFechaHoraFin(), evento4.getTitulo(), evento4.getDescripcion(), evento4.getNotificar(), evento4.getTipoNotificaciones(), contacto);
								
								System.out.println("Indica la localizacion a continuacion");
								System.out.println("Localizacion X");
								String localizacionX = entrada.nextLine();
								System.out.println("Localizacion Y");
								String localizacionY = entrada.nextLine();
								
								System.out.println("Indica la sala de reuniones");
								String salaReuniones = entrada.nextLine();
								
								ReunionPresencial Rpresencial = new ReunionPresencial(reunion4.getFechaHoraInicio(), reunion4.getFechaHoraFin(), reunion4.getTitulo(), reunion4.getDescripcion(), reunion4.getNotificar(), reunion4.getTipoNotificaciones(), reunion4.getContactos(), localizacionX, localizacionY, salaReuniones);
								
								System.out.println("Reunion presencial con titulo: "+ Rpresencial.getTitulo() + " creado");
								
								listaEventos.add(Rpresencial);
								
							}
							else if (tipoReunion == 2) { //Llamada telefonica
								Evento evento5 = Evento.pedirInfoEvento();
								
								System.out.println("Indica el nombre del contacto con quien ");
								String contacto = entrada.nextLine();
								
								Reunion reunion5 = new Reunion(evento5.getFechaHoraInicio(), evento5.getFechaHoraFin(), evento5.getTitulo(), evento5.getDescripcion(), evento5.getNotificar(), evento5.getTipoNotificaciones(), contacto);
								
								System.out.println("Indica el telefono corto para llamar (movil)");
								int telefonoCorto = Integer.parseInt(entrada.nextLine());
								System.out.println("Y ahora el telefono largo (fijo)");
								int telefonoLargo = Integer.parseInt(entrada.nextLine());
								
								System.out.println("Indica su clave de llamada");
								String clave = entrada.nextLine();
								
								ReunionLlamadaTelefonica telefonica = new ReunionLlamadaTelefonica(reunion5.getFechaHoraInicio(), reunion5.getFechaHoraFin(), reunion5.getTitulo(), reunion5.getDescripcion(), reunion5.getNotificar(), reunion5.getTipoNotificaciones(), reunion5.getContactos(), telefonoCorto, telefonoLargo, clave);
								
								System.out.println("Reunion telefonica con titulo: "+ telefonica.getTitulo() + " creado");
								
								listaEventos.add(telefonica);
							}
							else if (tipoReunion == 3) { //VideoLlamada
								Evento evento6 = Evento.pedirInfoEvento();
								
								System.out.println("Indica el nombre del contacto con quien ");
								String contacto = entrada.nextLine();
								
								Reunion reunion6 = new Reunion(evento6.getFechaHoraInicio(), evento6.getFechaHoraFin(), evento6.getTitulo(), evento6.getDescripcion(), evento6.getNotificar(), evento6.getTipoNotificaciones(), contacto);
								
								System.out.println("Indica en que plataforma realizaras la videollamada");
								String tipo = entrada.nextLine();
								
								ReunionVideoconferencia videoLlamada = new ReunionVideoconferencia(reunion6.getFechaHoraInicio(), reunion6.getFechaHoraFin(), reunion6.getTitulo(), reunion6.getDescripcion(), reunion6.getNotificar(), reunion6.getTipoNotificaciones(), reunion6.getContactos(), tipo);
								
								System.out.println("Reunion por videollamada con titulo: "+ videoLlamada.getTitulo() + " creado");
								
								listaEventos.add(videoLlamada);
							}
							else {
								System.out.println("Error. Indica si se trata de una reunion Presencial (1), por Llamada Telefonica (2) o por Videollamada (3) ");
								tipoReunion = Integer.parseInt(entrada.nextLine());
							}
						
						}
						else {
							System.out.println("Error. Indica si es una cita (1) o una reunion (2)");
							crearEvento = Integer.parseInt(entrada.nextLine());
							
						}
						
					}
					else if(opcion == 2) { //Modificar evento
						
						//Misma funcion que en la parte de contacto, puesto que la funcion depende de la lista que le pase y los objetos que tenga en la lista
						modificarEvento(listaEventos);
						
					}
					else if(opcion == 3) { //Listado eventos
						
						//Cuando se haga cada muestreo por pantalla se preguntara si se quiere eliminar el evento 
					    System.out.println("Selecciona una opción:");
					    System.out.println("1. Mostrar todos los eventos");
					    System.out.println("2. Mostrar citas");
					    System.out.println("3. Mostrar reuniones");

					    int opcionLista = Integer.parseInt(entrada.nextLine());
					    
					    //Switch case para controlar la lista que queremos
					    switch (opcionLista) {
					        case 1: //Todos los eventos guardados
					            System.out.println("Mostrando todos los eventos:");
					            for (Evento evento : listaEventos) {
					                System.out.println("Título: " + evento.getTitulo());
					                System.out.println("Descripción: " + evento.getDescripcion());
					                System.out.println();
					            }
					            break;
					        case 2: //Si queremos ir a las citas, preguntamos que tipo de citas queremos que nos muestre
					            System.out.println("Selecciona el tipo de citas:");
					            System.out.println("1. Citas de Cumpleanyos");
					            System.out.println("2. Citas de Aniversario");
					            System.out.println("3. Citas Medicas");

					            int tipoCita = Integer.parseInt(entrada.nextLine());

					            System.out.println("Mostrando citas:");
					            
					            //Al seleccionar el tipo de cita, haremos un instanceof para mostrar la lista de la opcion elegida
					            for (Evento evento : listaEventos) {
					                if (evento instanceof CitaCumpleanyos && tipoCita == 1) { //Cumpleanyos
					                    System.out.println("Título: " + evento.getTitulo());
					                    System.out.println("Descripción: " + evento.getDescripcion());
					                    System.out.println();
					                } else if (evento instanceof CitaAniversario && tipoCita == 2) { //Aniversario
					                    System.out.println("Título: " + evento.getTitulo());
					                    System.out.println("Descripción: " + evento.getDescripcion());
					                    System.out.println();
					                } else if (evento instanceof CitaMedico && tipoCita == 3) { //Medico
					                    System.out.println("Título: " + evento.getTitulo());
					                    System.out.println("Descripción: " + evento.getDescripcion());
					                    System.out.println();
					                }
					                else {
					                	System.out.println("Error. Selecciona entre cita de cumpleanyos (1), de aniversario (2) o de medico (3)");
					                	tipoCita = Integer.parseInt(entrada.nextLine());
					                }
					            }
					            break;
					        case 3: //Si queremos mostrar las reuniones, pediremos que tipo de reunion quiere mostrar
					            System.out.println("Selecciona el tipo de reunión:");
					            System.out.println("1. Reuniones de Videollamada");
					            System.out.println("2. Reuniones de Llamada Telefónica");
					            System.out.println("3. Reuniones Presenciales");

					            int tipoReunion = Integer.parseInt(entrada.nextLine());

					            System.out.println("Mostrando reuniones:");

					            for (Evento evento : listaEventos) {
					            	//Seleccionamos la primera opcion, por lo que pasamos el filtro a los objetos de Videoconferencia
					                if (evento instanceof ReunionVideoconferencia && tipoReunion == 1) {
					                    System.out.println("Título: " + evento.getTitulo());
					                    System.out.println("Descripción: " + evento.getDescripcion());
					                    System.out.println();
					                } else if (evento instanceof ReunionLlamadaTelefonica && tipoReunion == 2) { //Segunda opcion de Llamada Telefonica
					                    System.out.println("Título: " + evento.getTitulo());
					                    System.out.println("Descripción: " + evento.getDescripcion());
					                    System.out.println();
					                } else if (evento instanceof ReunionPresencial && tipoReunion == 3) { //Tercera opcion de Reunion Presencial
					                    System.out.println("Título: " + evento.getTitulo());
					                    System.out.println("Descripción: " + evento.getDescripcion());
					                    System.out.println();
					                }
					                else {
					                	System.out.println("Error. Indica si quiere una reunion por videollamada (1), por llamada telefonica (2) o presencial (3)");
					                	tipoReunion = Integer.parseInt(entrada.nextLine());
					                }
					            }
					            break;
					        default:
					            System.out.println("Opción no válida. Indica si quiere listado de todos los eventos (1), de las Citas (2) o de las Reuniones (3)");
					            opcionLista = Integer.parseInt(entrada.nextLine());
					    }
					    
					    //Cuando muestre cada elemento del array, se le pregunta si quiere eliminar algun elemento, pasandole la lista como argumento
					    eliminarElementoArray(listaEventos);
					    
					}

					else {
						System.out.println("Opcion no valida. 1) para Alta de Eventos, 2) para Modificar un Evento, 3) para ver el listado de Eventos ");
						opcion = Integer.parseInt(entrada.nextLine());
					}
					
					break;
					
			case 3:
					System.out.println("Cerrando el programa. \n");
					break;
					
			default:
					System.out.println("Solo hay dos paginas, la de contactos y la de eventos");
					break;
			}
		
		}while (menu != 3);
		
		entrada.close();	
    }	
}
