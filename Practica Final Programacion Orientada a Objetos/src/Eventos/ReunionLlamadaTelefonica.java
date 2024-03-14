package Eventos;

public class ReunionLlamadaTelefonica extends Reunion{
	
	int telefonoCorto, telefonoLargo;
	String clave;
	
	//Constructo de Llamada Telefonica Heredado de Reunion
	public ReunionLlamadaTelefonica(String fechaHoraInicio, String fechaHoraFin, String titulo, String descripcion,
			String notificar, String tipoNotificaciones, String contactos, int telefonoCorto, int telefonoLargo, String clave) {
		super(fechaHoraInicio, fechaHoraFin, titulo, descripcion, notificar, tipoNotificaciones, contactos);
		
		this.telefonoCorto = telefonoCorto;
		this.telefonoLargo = telefonoLargo;
		this.clave = clave;
	}

	//Getters y Setters
	public int getTelefonoCorto() {
		return telefonoCorto;
	}

	public void setTelefonoCorto(int telefonoCorto) {
		this.telefonoCorto = telefonoCorto;
	}

	public int getTelefonoLargo() {
		return telefonoLargo;
	}

	public void setTelefonoLargo(int telefonoLargo) {
		this.telefonoLargo = telefonoLargo;
	}

	public String getClave() {
		return clave;
	}

	public void setClave(String clave) {
		this.clave = clave;
	}
	
	

}
