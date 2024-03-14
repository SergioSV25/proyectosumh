package Eventos;

public class CitaAniversario extends Evento{

	private String contactoPersonal;
	private String fechaAniversario;
	
	//Constructor heredado de Evento
	public CitaAniversario(String fechaHoraInicio, String fechaHoraFin, String titulo, String descripcion,
			String notificar, String tipoNotificaciones, String contactoPersonal, String fechaAniversario) {
		super(fechaHoraInicio, fechaHoraFin, titulo, descripcion, notificar, tipoNotificaciones);
		
		this.contactoPersonal = contactoPersonal;
		this.fechaAniversario = fechaAniversario;

	}
	
	//Getters y Setters para acceder a los atributos
	public String getContactoPersonal() {
		return contactoPersonal;
	}

	public void setContactoPersonal(String contactoPersonal) {
		this.contactoPersonal = contactoPersonal;
	}

	public String getFechaAniversario() {
		return fechaAniversario;
	}

	public void setFechaAniversario(String fechaAniversario) {
		this.fechaAniversario = fechaAniversario;
	}
	
	
	
	

}
