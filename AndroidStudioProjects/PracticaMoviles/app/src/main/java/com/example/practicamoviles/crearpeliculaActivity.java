package com.example.practicamoviles;

import android.content.Intent;
import android.content.SharedPreferences;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;

import com.example.practicamoviles.sqlite.SQLiteHelper;

public class crearpeliculaActivity extends AppCompatActivity {

    private TextView idUsuarioTextView;
    private EditText etTitulo, etGenero, etDuracion, etPuntuacion;
    private ImageView imageSubir;
    private ActivityResultLauncher<Intent> takePictureLauncher; //Lanzador para camara
    private ActivityResultLauncher<Intent> galleryLauncher; // Lanzador para la galería

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.crear_pelicula);

        // Referenciar el TextView
        idUsuarioTextView = findViewById(R.id.id_Usuario);

        //Muestro id del usuario
        cargarPreferencias();

        //Guardar en la base de datos
        Button botonGuardar = findViewById(R.id.button_crearpelicula);
        botonGuardar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                cargarPelicula();
            }
        });

        Button btnCapturar = findViewById(R.id.Foto);
        imageSubir = findViewById(R.id.imageView_pelicula);

        // Inicializar el ActivityResultLauncher
        takePictureLauncher = registerForActivityResult(
                new ActivityResultContracts.StartActivityForResult(),
                result -> {
                    if (result.getResultCode() == RESULT_OK && result.getData() != null) {
                        Bundle extras = result.getData().getExtras();
                        Bitmap imageBitmap = (Bitmap) extras.get("data");
                        imageSubir.setImageBitmap(imageBitmap);
                    } else if (result.getResultCode() == RESULT_CANCELED) {
                        Toast.makeText(this, "Captura cancelada", Toast.LENGTH_SHORT).show();
                    }
                });

        btnCapturar.setOnClickListener(v -> {
            Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
            takePictureLauncher.launch(intent);
        });

        // Inicializar el lanzador para la galería
        Button btnGaleria = findViewById(R.id.Galeria);
        galleryLauncher = registerForActivityResult(
                new ActivityResultContracts.StartActivityForResult(),
                result -> {
                    if (result.getResultCode() == RESULT_OK && result.getData() != null) {
                        Uri uri = result.getData().getData();
                        try {
                            Bitmap bitmap = MediaStore.Images.Media.getBitmap(getContentResolver(), uri);
                            imageSubir.setImageBitmap(bitmap);
                        } catch (Exception e) {
                            Toast.makeText(this, "Error al cargar la imagen", Toast.LENGTH_LONG).show();
                        }
                    } else if (result.getResultCode() == RESULT_CANCELED) {
                        Toast.makeText(this, "Selección de imagen cancelada", Toast.LENGTH_SHORT).show();
                    }
                });

        btnGaleria.setOnClickListener(v -> {
            Intent intent = new Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
            galleryLauncher.launch(intent);
        });

        //Cancelar e irnos a la pantalla de atrás
        Button cancelar = findViewById(R.id.button_cancelar_peli);
        cancelar.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                Intent intent = new Intent(crearpeliculaActivity.this, peliculasActivity.class);
                startActivity(intent);
            }
        });

    }

    //Anyadir cada plataforma a la base de datos
    public void cargarPelicula() {
        // Crear una instancia de la base de datos helper
        SQLiteHelper dbHelper = new SQLiteHelper(this);
        SQLiteDatabase db = dbHelper.getWritableDatabase();

        etTitulo = findViewById(R.id.editTituloPelicula);
        etGenero = findViewById(R.id.editGenero);
        etDuracion = findViewById(R.id.editDuracion);
        etPuntuacion = findViewById(R.id.editPuntuacion);
        imageSubir = findViewById(R.id.imageView_pelicula);

        //Metodo para obtener el bitmap de la imagen que cargue en el imageView desde cámara o galería
        Drawable drawable = imageSubir.getDrawable();
        Bitmap imagenPelicula = drawable instanceof BitmapDrawable ? ((BitmapDrawable) drawable).getBitmap() : null;

        int idUsuario = Integer.parseInt(idUsuarioTextView.getText().toString());
        String titulo = etTitulo.getText().toString();
        String genero = etGenero.getText().toString();
        int duracion = Integer.parseInt(etDuracion.getText().toString());
        int puntuacion = Integer.parseInt(etPuntuacion.getText().toString());

        // Insertar usuario en la base de datos
        long id = dbHelper.anyadirPeliculas(idUsuario, imagenPelicula, titulo, genero, duracion, puntuacion);

        //public long anyadirPeliculas(int idPlataforma, int idUsuario, Bitmap caratula, String titulo, String genero, int duracion, int puntuacion)
        if (id > 0){
            Toast.makeText(this, "Registro Completado.", Toast.LENGTH_SHORT).show();
            Intent intent = new Intent(crearpeliculaActivity.this, peliculasActivity.class);
            startActivity(intent);
        }else{
            Toast.makeText(this, "Error al crear usuario.", Toast.LENGTH_SHORT).show();
        }

    }

    private void cargarPreferencias() {
        SharedPreferences prefs = getSharedPreferences("UserData", MODE_PRIVATE);
        int userId = prefs.getInt("USER_ID", -1);

        // Mostrar userId en el TextView
        if (userId != -1) {
            idUsuarioTextView.setText(String.valueOf(userId));
        } else {
            idUsuarioTextView.setText("No ID Found");
        }
    }

}
