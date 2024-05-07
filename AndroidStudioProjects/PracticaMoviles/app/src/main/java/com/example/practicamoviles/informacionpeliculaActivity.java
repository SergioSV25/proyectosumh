package com.example.practicamoviles;

import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.example.practicamoviles.objetos.ConversorBitmap;

public class informacionpeliculaActivity extends AppCompatActivity {

    private ImageView caratulaImageView;
    private TextView titulo_pelicula;
    private TextView genero_pelicula;
    private TextView puntuacion_pelicula;
    private TextView duracion_pelicula;
    private Button editar;
    private Button botonSalir;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.infopeliculas);

        // Inicializar vistas
        titulo_pelicula = findViewById(R.id.Titulo_peli);
        caratulaImageView = findViewById(R.id.imageView_caratula);
        genero_pelicula = findViewById(R.id.genero_respuesta);
        puntuacion_pelicula = findViewById(R.id.puntuacion_respuesta);
        duracion_pelicula = findViewById(R.id.duracion_respuesta);
        editar = findViewById(R.id.button_editar_peli);
        botonSalir = findViewById(R.id.button_ir_a_pelis);

        // Configurar el botón de salida
        botonSalir.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                Intent intent = new Intent(informacionpeliculaActivity.this, peliculasActivity.class);
                startActivity(intent);
            }
        });

        // Obtener el Intent y el Bundle
        Intent intent = getIntent();
        Bundle bundle = intent.getExtras();

        if (bundle != null) {
            String titulo_peli = bundle.getString("TITULO", "Sin titulo");
            String genero_peli = bundle.getString("GENERO", "URL Desconocida");
            byte[] caratulaBytes = bundle.getByteArray("CARATULA");
            int puntuacion_peli = bundle.getInt("PUNTUACION", 00000);
            int duracion_peli = bundle.getInt("DURACION", 00000);

            Bitmap portada_peliculas = ConversorBitmap.imageFromArray(caratulaBytes);

            // Asignar los datos a las vistas
            titulo_pelicula.setText(titulo_peli);
            caratulaImageView.setImageBitmap(portada_peliculas);
            genero_pelicula.setText(genero_peli);
            puntuacion_pelicula.setText(String.valueOf(puntuacion_peli));
            duracion_pelicula.setText(String.valueOf(duracion_peli));


        } else {
            Toast.makeText(this, "No se pudieron cargar los datos de la plataforma", Toast.LENGTH_SHORT).show();
        }
    }

}
