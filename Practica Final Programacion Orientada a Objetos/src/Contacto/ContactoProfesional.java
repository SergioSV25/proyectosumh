package Contacto;

public class ContactoProfesional extends Contactos{
	
	private String empresa;
	
	//Constructor de la clase heredada donde anyado la empresa
	public ContactoProfesional(String nombre, String apellidos, String telefono, String num_movil, String fechaCumpleanyos, String correo, String empresa) {
		super(nombre, apellidos, telefono, num_movil, fechaCumpleanyos, correo);
		this.empresa = empresa;
	}

	//Getters y setters para acceder a los atributos
	public String getEmpresa() {
		return empresa;
	}
	
	public void setEmpresa(String empresa) {
		this.empresa = empresa;
	}
	
}
