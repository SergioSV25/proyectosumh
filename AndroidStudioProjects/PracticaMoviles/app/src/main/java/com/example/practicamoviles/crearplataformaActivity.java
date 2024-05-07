package com.example.practicamoviles;

import android.content.Intent;
import android.content.SharedPreferences;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.practicamoviles.sqlite.SQLiteHelper;

public class crearplataformaActivity extends AppCompatActivity {

    private TextView idUsuarioTextView;
    private EditText etNombrePlataforma, etURL, etUsuario, etPassword;
    private ImageView imageSubir;
    private ActivityResultLauncher<Intent> takePictureLauncher; //Lanzador para camara
    private ActivityResultLauncher<Intent> galleryLauncher; // Lanzador para la galería

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.crear_plataforma);

        // Referenciar el TextView
        idUsuarioTextView = findViewById(R.id.idUsuario);

        // Cargar preferencias
        cargarPreferencias();

        //Guardar en la base de datos
        Button botonGuardar = findViewById(R.id.button_guardar_plataforma);
        botonGuardar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                cargarPlataforma();
            }
        });

        Button btnCapturar = findViewById(R.id.button_camara);
        imageSubir = findViewById(R.id.imageView_plataforma);

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
        Button btnGaleria = findViewById(R.id.button_galeria);
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
        Button cancelar = findViewById(R.id.button_cancelar);
        cancelar.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                Intent intent = new Intent(crearplataformaActivity.this, plataformasActivity.class);
                startActivity(intent);
            }
        });
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

    //Anyadir cada plataforma a la base de datos
    public void cargarPlataforma() {
        // Crear una instancia de la base de datos helper
        SQLiteHelper dbHelper = new SQLiteHelper(this);
        SQLiteDatabase db = dbHelper.getWritableDatabase();

        etNombrePlataforma = findViewById(R.id.editText_nombreplataforma);
        etURL = findViewById(R.id.editText_url);
        etUsuario = findViewById(R.id.editText_usuario);
        etPassword = findViewById(R.id.editTextTextPasswordAcceso);
        imageSubir = findViewById(R.id.imageView_plataforma);

        //Metodo para obtener el bitmap de la imagen que cargue en el imageView desde cámara o galería
        Drawable drawable = imageSubir.getDrawable();
        Bitmap imagenPlataforma = drawable instanceof BitmapDrawable ? ((BitmapDrawable) drawable).getBitmap() : null;

        int idUsuario = Integer.parseInt(idUsuarioTextView.getText().toString());
        String usuario = etUsuario.getText().toString();
        String url = etURL.getText().toString();
        String password = etPassword.getText().toString();
        String nombrePlataforma = etNombrePlataforma.getText().toString();

        // Insertar usuario en la base de datos
        long id = dbHelper.anyadirPlataforma(idUsuario, imagenPlataforma, nombrePlataforma, url, usuario, password);

        if (id > 0){
            Toast.makeText(this, "Registro Completado.", Toast.LENGTH_SHORT).show();
            Intent intent = new Intent(crearplataformaActivity.this, plataformasActivity.class);
            startActivity(intent);
        }else{
            Toast.makeText(this, "Error al crear usuario.", Toast.LENGTH_SHORT).show();
        }

    }

}
