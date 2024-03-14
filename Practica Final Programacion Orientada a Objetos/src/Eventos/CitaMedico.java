package Eventos;

public class CitaMedico extends Evento{
	
	private String especialidad;
	private String geolocalizacionX;
	private String geolocalizacionY;

	//Constructor con herencia de Evento, anyado ademas la especialidad y la localizacion X e Y
	public CitaMedico(String fechaHoraInicio, String fechaHoraFin, String titulo, String descripcion, String notificar,
			String tipoNotificaciones, String especialidad, String geolocalizacionX, String geolocalizacionY) {
		super(fechaHoraInicio, fechaHoraFin, titulo, descripcion, notificar, tipoNotificaciones);
		
		this.especialidad = especialidad;
		this.geolocalizacionX = geolocalizacionX;
		this.geolocalizacionY = geolocalizacionY;
	}
	
	//Getters y Setters creados
	public String getEspecialidad() {
		return especialidad;
	}
	
	public void setEspecialidad(String especialidad) {
		this.especialidad = especialidad;
	}

	public void setNombreContacto(String nombreContacto) {
		this.especialidad = nombreContacto;
	}

	public String getGeolocalizacionX() {
		return geolocalizacionX;
	}

	public void setGeolocalizacionX(String geolocalizacionX) {
		this.geolocalizacionX = geolocalizacionX;
	}

	public String getGeolocalizacionY() {
		return geolocalizacionY;
	}

	public void setGeolocalizacionY(String geolocalizacionY) {
		this.geolocalizacionY = geolocalizacionY;
	}
	
}
