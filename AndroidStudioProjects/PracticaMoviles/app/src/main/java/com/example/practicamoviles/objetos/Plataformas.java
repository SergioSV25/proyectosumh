package com.example.practicamoviles.objetos;

import android.graphics.Bitmap;

public class Plataformas {
    private int id; // Identificador de la plataforma
    private int idUsuario; // Relacionado con la tabla de usuarios
    private String nombre; // Nombre de la plataforma
    private String url; // URL de acceso a la plataforma
    private String usuario; // Usuario de acceso
    private String password; // Password de acceso

    private byte[] arrayFoto;
    private Bitmap foto;

    // Constructor
    public Plataformas(int id, int idUsuario, Bitmap foto, String nombre, String url, String usuario, String password) {
        this.id = id;
        this.idUsuario = idUsuario;
        this.foto = foto;
        this.nombre = nombre;
        this.url = url;
        this.usuario = usuario;
        this.password = password;
    }

    // Getters
    public int getId() {
        return id;
    }

    public int getIdUsuario() {
        return idUsuario;
    }

    public String getNombre() {
        return nombre;
    }

    public String getUrl() {
        return url;
    }

    public String getUsuario() {
        return usuario;
    }

    public String getPassword() {
        return password;
    }

    public Bitmap getFoto() {
        return foto;
    }

    public void setFoto(Bitmap foto) {
        this.foto = foto;
        arrayFoto = ConversorBitmap.bitmapToArray(this.foto);
    }

    public byte[] getArrayFoto() {
        return arrayFoto;
    }

    public void setArrayFoto(byte[] arrayFoto) {
        this.arrayFoto = arrayFoto;
        this.foto = ConversorBitmap.imageFromArray(this.arrayFoto);
    }

}

