package com.example.practicamoviles.objetos;

import android.graphics.Bitmap;

public class Peliculas {

    private int id;
    private int idUsuario;
    private int idPlataforma;
    private byte[] arrayCaratula;
    private Bitmap caratula;
    private String titulo;
    private int duracion;
    private int puntuacion;
    private String genero;

    // Constructor
    public Peliculas(int id, int idUsuario, int idPlataforma, Bitmap caratula, String titulo, int duracion, int puntuacion, String genero) {
        this.id = id;
        this.idUsuario = idUsuario;
        this.idPlataforma = idPlataforma;
        this.caratula = caratula;
        this.titulo = titulo;
        this.duracion = duracion;
        this.puntuacion = puntuacion;
        this.genero = genero;
    }

    // Getters y setters
    public int getId() {
        return id;
    }

    public int getIdUsuario() {
        return idUsuario;
    }

    public int getIdPlataforma() {
        return idPlataforma;
    }

    public Bitmap getCaratula() {
        return caratula;
    }

    public void setCaratula(Bitmap caratula) {
        this.caratula = caratula;
        arrayCaratula = ConversorBitmap.bitmapToArray(this.caratula);
    }

    public byte[] getArrayCaratula() {
        return arrayCaratula;
    }

    public void setArrayCaratula(byte[] arrayFoto) {
        this.arrayCaratula = arrayCaratula;
        this.caratula = ConversorBitmap.imageFromArray(this.arrayCaratula);
    }

    public String getTitulo() {
        return titulo;
    }

    public int getDuracion() {
        return duracion;
    }

    public int getPuntuacion() {
        return puntuacion;
    }

    public String getGenero() {
        return genero;
    }

}
