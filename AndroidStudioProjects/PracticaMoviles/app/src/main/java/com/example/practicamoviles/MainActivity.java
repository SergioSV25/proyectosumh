package com.example.practicamoviles;

import androidx.appcompat.app.AppCompatActivity;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.example.practicamoviles.sqlite.SQLiteHelper;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.iniciar_sesion);

        Button CrearCuenta = findViewById(R.id.buttonCrearCuenta);
        EditText campoEmail = findViewById(R.id.campo_email);
        EditText campoPassword = findViewById(R.id.campo_password);
        Button buttonIniciarSesion = findViewById(R.id.button_iniciarSesion);

        //Caso que quiera irme a la pantalla de crear cuenta
        CrearCuenta.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Crear_cuenta.class);
                startActivity(intent);
            }
        });


        //Caso que quiera hacer las validaciones de campos
        buttonIniciarSesion.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                //Obtengo los valores de los editTexts
                String email = campoEmail.getText().toString(); //sergio@gmail.com
                String password = campoPassword.getText().toString(); //12345

                // Validar si el usuario existe en la base de datos
                SQLiteHelper dbHelper = new SQLiteHelper(MainActivity.this);

                int userId = dbHelper.validarUsuario(email, password);

                if (userId != -1) {
                    // Usuario válido
                    Toast.makeText(MainActivity.this, "Inicio de sesión exitoso.", Toast.LENGTH_SHORT).show();

                    // Guardar los datos del usuario
                    guardarPreferencias(userId);

                    // Navegar a HomeActivity
                    Intent intent = new Intent(MainActivity.this, HomeActivity.class);
                    startActivity(intent);
                }else {
                    // Usuario no encontrado o contraseña incorrecta
                    Toast.makeText(MainActivity.this, "Correo electrónico o contraseña incorrectos.", Toast.LENGTH_SHORT).show();
                }
            }

            //En caso de ir bien el login, guardo el id del login
            private void guardarPreferencias(int userId) {
                SharedPreferences prefs = getSharedPreferences("UserData", MODE_PRIVATE);
                SharedPreferences.Editor editor = prefs.edit();
                editor.putInt("USER_ID", userId);
                editor.apply();
            }
        });
    }
}