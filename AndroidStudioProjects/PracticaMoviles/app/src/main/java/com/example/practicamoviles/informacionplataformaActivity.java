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
import com.example.practicamoviles.objetos.Plataformas;
import com.example.practicamoviles.sqlite.SQLiteHelper;

public class informacionplataformaActivity extends AppCompatActivity {

    private ImageView imagenPlataforma;
    private TextView nombrePlataforma;
    private TextView urlPlataforma;
    private Button editarPlataforma;
    private Button botonSalir;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.infoplataforma);

        // Inicializar vistas
        imagenPlataforma = findViewById(R.id.imagenplataforma);
        nombrePlataforma = findViewById(R.id.nombreplataforma);
        urlPlataforma = findViewById(R.id.urlplataforma);
        editarPlataforma = findViewById(R.id.editarplataforma);
        botonSalir = findViewById(R.id.botonsalir);

        // Configurar el botón de salida
        botonSalir.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                Intent intent = new Intent(informacionplataformaActivity.this, plataformasActivity.class);
                startActivity(intent);
            }
        });

        // Obtener el Intent y el Bundle
        Intent intent = getIntent();
        Bundle bundle = intent.getExtras();

        if (bundle != null) {
            String nombre = bundle.getString("NOMBRE_PLATAFORMA", "Plataforma Desconocida");
            String url = bundle.getString("URL_PLATAFORMA", "URL Desconocida");
            byte[] fotoBytes = bundle.getByteArray("FOTO_PLATAFORMA");

             Bitmap fotoBitmap = ConversorBitmap.imageFromArray(fotoBytes);

            // Asignar los datos a las vistas
            nombrePlataforma.setText(nombre);
            urlPlataforma.setText(url);
            imagenPlataforma.setImageBitmap(fotoBitmap);
        } else {
            Toast.makeText(this, "No se pudieron cargar los datos de la plataforma", Toast.LENGTH_SHORT).show();
        }
    }
}
