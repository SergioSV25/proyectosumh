package Contacto;

public class ContactoPersonal extends Contactos{
	
	private String alias;
	
	//Constructor de la clase heredada donde anyado el alias
	public ContactoPersonal(String nombre, String apellidos, String telefono, String num_movil, String fechaCumpleanyos, String correo, String alias) {
		super(nombre, apellidos, telefono, num_movil, fechaCumpleanyos, correo);
		this.alias = alias;
	}

	//Getters y setters para acceder a los atributos
	public String getAlias() {
		return alias;
	}
	
	public void setAlias(String alias) {
		this.alias = alias;
	}
	
}
