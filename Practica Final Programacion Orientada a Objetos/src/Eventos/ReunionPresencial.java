package Eventos;

public class ReunionPresencial extends Reunion{

	String localizacionX, localizacionY, salaReuniones;
		
	//Constructo Reunion Presencial con atributos heredados y los suyos propios 
	public ReunionPresencial(String fechaHoraInicio, String fechaHoraFin, String titulo, String descripcion,
			String notificar, String tipoNotificaciones, String contactos, String localizacionX, String localizacionY, String salaReuniones) {
		super(fechaHoraInicio, fechaHoraFin, titulo, descripcion, notificar, tipoNotificaciones, contactos);
		
		this.localizacionX = localizacionX;
		this.localizacionY = localizacionY;
		this.salaReuniones = salaReuniones;
		
	}

	//Getters y Setters
	public String getLocalizacionX() {
		return localizacionX;
	}

	public void setLocalizacionX(String localizacionX) {
		this.localizacionX = localizacionX;
	}

	public String getLocalizacionY() {
		return localizacionY;
	}

	public void setLocalizacionY(String localizacionY) {
		this.localizacionY = localizacionY;
	}

	public String getSalaReuniones() {
		return salaReuniones;
	}

	public void setSalaReuniones(String salaReuniones) {
		this.salaReuniones = salaReuniones;
	}
	
	

}
