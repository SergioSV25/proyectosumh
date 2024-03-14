package Eventos;

import java.util.Scanner;

public class Evento {
    private String fechaHoraInicio;
    private String fechaHoraFin;
    private String titulo;
    private String descripcion;
    private String notificar;
    private String tipoNotificaciones;

    public Evento(String fechaHoraInicio, String fechaHoraFin, String titulo, String descripcion, String notificar, String tipoNotificaciones) {
        this.fechaHoraInicio = fechaHoraInicio;
        this.fechaHoraFin = fechaHoraFin;
        this.titulo = titulo;
        this.descripcion = descripcion;
        this.notificar = notificar;
        this.tipoNotificaciones = tipoNotificaciones;
    }

    //Getters y setters para acceder a los atributos
    public String getFechaHoraInicio() {
        return fechaHoraInicio;
    }

    public void setFechaHoraInicio(String fechaHoraInicio) {
        this.fechaHoraInicio = fechaHoraInicio;
    }

    public String getFechaHoraFin() {
        return fechaHoraFin;
    }

    public void setFechaHoraFin(String fechaHoraFin) {
        this.fechaHoraFin = fechaHoraFin;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public String getDescripcion() {
        return descripcion;
    }

    public void setDescripcion(String descripcion) {
        this.descripcion = descripcion;
    }

    public String getNotificar() {
        return notificar;
    }

    public void setNotificar(String notificar) {
        this.notificar = notificar;
    }

    public String getTipoNotificaciones() {
        return tipoNotificaciones;
    }
    
    public void setTipoNotificaciones(String tipoNotificaciones) {
    	this.tipoNotificaciones = tipoNotificaciones;
    }
    
    /**
     * Creamos un metodo que pide la informacion general de eventos, las clases heredadas pediran informacion concreta y crearan sus propios objetos
     * @return objeto clase evento
     */
    public static Evento pedirInfoEvento() {
    	
    	String tipoNotificacion = "POPUP";
    	
    	Scanner entrada = new Scanner(System.in);
		
		System.out.println("Ingresa los datos generales del evento");
		
		System.out.print("A que hora empieza: ");
        String fechaHoraInicio = entrada.nextLine();
        
        System.out.print("A que hora termina: ");
        String fechaHoraFin = entrada.nextLine();
        
        System.out.print("Titulo del evento: ");
        String titulo = entrada.nextLine();
        
        System.out.print("Descripcion del evento: ");
        String descripcion = entrada.nextLine();
        
        System.out.print("¿Quieres que se te notifique este evento? (si o no)");
        String notificar = entrada.nextLine();
        
        if(notificar.equalsIgnoreCase("si") || notificar.equalsIgnoreCase("no")) {
        	System.out.println("Error. Indica si quieres ser notificado o no");
        	notificar = entrada.nextLine();
        }
        else {
        	System.out.println("Indica que tipo de datos quieres recibir: PopUp, SMS o correo.");
        	tipoNotificacion = entrada.nextLine();
        	if(tipoNotificacion.equalsIgnoreCase("popup") || tipoNotificacion.equalsIgnoreCase("SMS") || tipoNotificacion.equalsIgnoreCase("correo")) {
        		System.out.println("Recibira una notificacion tipo " + tipoNotificacion);
        	}
        	else {
        		System.out.println("Error. Indica que tipo de datos quieres recibir: PopUp, SMS o correo.");
        		tipoNotificacion = entrada.nextLine();
        	}
        }
        	
        String tipoNotificaciones = tipoNotificacion;

        return new Evento(fechaHoraInicio, fechaHoraFin, titulo, descripcion, notificar, tipoNotificaciones);
    }
    
}
