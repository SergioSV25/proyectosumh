package com.example.practicamoviles.objetos;

public class Usuarios {
    private int id;
    private String nombre;
    private String apellidos;
    private String correo;
    private String password;
    private String fechaNacimiento;
    private int idPreguntaSeguridad;
    private String respuestaSeguridad;

    //Constructor
    public Usuarios(int id, String nombre, String apellidos, String correo, String password, String fechaNacimiento, int idPreguntaSeguridad, String respuestaSeguridad, boolean tecnologia, boolean deportes, boolean redesSociales, boolean cine, boolean otros, boolean factorAutentificacion) {
        this.id = id;
        this.nombre = nombre;
        this.apellidos = apellidos;
        this.correo = correo;
        this.password = password;
        this.fechaNacimiento = fechaNacimiento;
        this.idPreguntaSeguridad = idPreguntaSeguridad;
        this.respuestaSeguridad = respuestaSeguridad;
        this.tecnologia = tecnologia;
        this.deportes = deportes;
        this.redesSociales = redesSociales;
        this.cine = cine;
        this.otros = otros;
        this.factorAutentificacion = factorAutentificacion;
    }

    // Se almacenan como entero en la base de datos, pero se maneja como boolean en la aplicación
    private boolean tecnologia;
    private boolean deportes;
    private boolean redesSociales;
    private boolean cine;
    private boolean otros;
    private boolean factorAutentificacion;

    // Constructor
    public Usuarios() {

    }

    // Getters y Setters
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

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

    public String getCorreo() {
        return correo;
    }

    public void setCorreo(String correo) {
        this.correo = correo;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getFechaNacimiento() {
        return fechaNacimiento;
    }

    public void setFechaNacimiento(String fechaNacimiento) {
        this.fechaNacimiento = fechaNacimiento;
    }

    public int getIdPreguntaSeguridad() {
        return idPreguntaSeguridad;
    }

    public void setIdPreguntaSeguridad(int idPreguntaSeguridad) {
        this.idPreguntaSeguridad = idPreguntaSeguridad;
    }

    public String getRespuestaSeguridad() {
        return respuestaSeguridad;
    }

    public void setRespuestaSeguridad(String respuestaSeguridad) {
        this.respuestaSeguridad = respuestaSeguridad;
    }

    public boolean isTecnologia() {
        return tecnologia;
    }

    public void setTecnologia(boolean tecnologia) {
        this.tecnologia = tecnologia;
    }

    public boolean isDeportes() {
        return deportes;
    }

    public void setDeportes(boolean deportes) {
        this.deportes = deportes;
    }

    public boolean isRedesSociales() {
        return redesSociales;
    }

    public void setRedesSociales(boolean redesSociales) {
        this.redesSociales = redesSociales;
    }

    public boolean isCine() {
        return cine;
    }

    public void setCine(boolean cine) {
        this.cine = cine;
    }

    public boolean isOtros() {
        return otros;
    }

    public void setOtros(boolean otros) {
        this.otros = otros;
    }

    public boolean getFactorAutentificacion() {
        return factorAutentificacion;
    }

    public void setFactorAutentificacion(boolean factorAutentificacion) {
        this.factorAutentificacion = factorAutentificacion;
    }

}
