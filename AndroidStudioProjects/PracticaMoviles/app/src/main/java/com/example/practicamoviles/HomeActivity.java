package com.example.practicamoviles;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import androidx.appcompat.app.AppCompatActivity;

public class HomeActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.plataformas_pelis);

        ImageButton plataformas = findViewById(R.id.boton_plataformas);
        ImageButton peliculas = findViewById(R.id.boton_peliculas);
        Button ir_atras = findViewById(R.id.button_volver_iniciar_sesion);

        //Caso que quiera irme a la pantalla de plataformas
        plataformas.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(HomeActivity.this, plataformasActivity.class);
                startActivity(intent);
            }
        });

        //Caso que quiera irme a la pantalla de plataformas
        peliculas.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(HomeActivity.this, peliculasActivity.class);
                startActivity(intent);
            }
        });

        ir_atras.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(HomeActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });
    }

}
