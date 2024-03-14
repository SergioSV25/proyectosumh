package Contacto;

import java.util.Scanner;

public class Contactos {
	
	protected String nombre;
	protected String apellidos;
	protected String telefono;
	protected String num_movil;
	protected String fechaCumpleanyos;
	protected String correo;

	//Constructor de clase
	public Contactos(String nombre, String apellidos, String telefono, String num_movil, String fechaCumpleanyos, String correo) {
    this.nombre = nombre;
    this.apellidos = apellidos;
    this.telefono = telefono;
    this.num_movil = num_movil;
    this.fechaCumpleanyos = fechaCumpleanyos;
    this.correo = correo;
	}

	//Getters y setters para acceder a los atributos
	public String getNombre() {
		return nombre;
	}

	public void setNombre(String nombre) {
		this.nombre = nombre;
	}

	public String getApellidos() {
		return apellidos;
	}

	public void setApellidos(String apellidos) {
		this.apellidos = apellidos;
	}

	public String getTelefono() {
		return telefono;
	}

	public void setTelefono(String telefono) {
		this.telefono = telefono;
	}

	public String getNum_movil() {
		return num_movil;
	}

	public void setNum_movil(String num_movil) {
		this.num_movil = num_movil;
	}

	public String getFechaCumpleanyos() {
		return fechaCumpleanyos;
	}

	public void setFechaCumpleanyos(String fechaCumpleanyos) {
		this.fechaCumpleanyos = fechaCumpleanyos;
	}

	public String getCorreo() {
		return correo;
	}

	public void setCorreo(String correo) {
		this.correo = correo;
	}
	
	/**
	 * Pido informacion que es de la clase general para pasarla a los objetos de las clases heredadas
	 * @return objeto Contacto
	 */
	public static Contactos pedirInfoContacto() {
		Scanner entrada = new Scanner(System.in);
		
		System.out.println("Ingresa los datos del contacto");
		
		System.out.print("Nombre: ");
        String nombre = entrada.nextLine();
        
        System.out.print("Apellidos: ");
        String apellidos = entrada.nextLine();
        
        System.out.print("Teléfono: ");
        String telefono = entrada.nextLine();
        
        System.out.print("Movil: ");
        String num_movil = entrada.nextLine();
        
        System.out.print("Fecha de cumpleaños (dd - MM - yyyy): ");
        //Lo guardo como String
        String fechaCumpleanyos = entrada.nextLine();
        
        System.out.print("Correo electrónico: ");
        String correo = entrada.nextLine();
        
        return new Contactos(nombre, apellidos, telefono, num_movil, fechaCumpleanyos, correo);
        
	}
	
}