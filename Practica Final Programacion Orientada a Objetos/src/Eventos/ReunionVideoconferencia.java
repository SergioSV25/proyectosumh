package Eventos;

public class ReunionVideoconferencia extends Reunion{

	String tipo;
	
	//Constructor con herencias y atributos propios
	public ReunionVideoconferencia(String fechaHoraInicio, String fechaHoraFin, String titulo, String descripcion,
			String notificar, String tipoNotificaciones, String contactos, String tipo) {
		super(fechaHoraInicio, fechaHoraFin, titulo, descripcion, notificar, tipoNotificaciones, contactos);
		
		this.tipo = tipo;
	}

	//Getters y Setters
	public String getTipo() {
		return tipo;
	}

	public void setTipo(String tipo) {
		this.tipo = tipo;
	}
	
	

}
