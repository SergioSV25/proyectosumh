package Eventos;

public class Reunion extends Evento{

	private String contactos;
	
	//Constructor heredado de Evento
	public Reunion(String fechaHoraInicio, String fechaHoraFin, String titulo, String descripcion, String notificar, String tipoNotificaciones, String contactos) {
		super(fechaHoraInicio, fechaHoraFin, titulo, descripcion, notificar, tipoNotificaciones);
		
		this.contactos = contactos;
	}

	//Getters y Setters para los atributos de Reunion
	public String getContactos() {
		return contactos;
	}

	public void setContactos(String contactos) {
		this.contactos = contactos;
	}
	
	

}
