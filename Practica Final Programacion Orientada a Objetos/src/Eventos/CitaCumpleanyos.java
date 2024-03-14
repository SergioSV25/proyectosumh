package Eventos;

public class CitaCumpleanyos extends Evento{
	
	private String nombreContacto;
	
	//Constructor con herencias de Evento
	public CitaCumpleanyos(String fechaHoraInicio, String fechaHoraFin, String titulo, String descripcion,
			String notificar, String tipoNotificaciones, String nombreContacto) {
		super(fechaHoraInicio, fechaHoraFin, titulo, descripcion, notificar, tipoNotificaciones);

		this.nombreContacto = nombreContacto;
		
	}

	//Getters y Setters
	public String getNombreContacto() {
		return nombreContacto;
	}
	
	public void setNombreContacto(String nombreContacto) {
		this.nombreContacto = nombreContacto;
	}
	
	

}
