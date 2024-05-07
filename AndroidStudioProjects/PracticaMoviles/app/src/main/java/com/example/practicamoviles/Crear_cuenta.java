package com.example.practicamoviles;

import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import com.example.practicamoviles.sqlite.SQLiteHelper;

public class Crear_cuenta extends AppCompatActivity {

    //Variables para los edits que hay en la pantalla crear cuenta
    private EditText etNombre, etApellidos, etCorreo, etFechaNac, etPassword, etRespuestaSeguridad, etRespuestaOtro;
    private Spinner spPregunta;
    private CheckBox cbCine, cbRedesSociales, cbTecnologia, cbDeportes, cbOtros, cbFactorAuentificacion;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.crear_cuenta);

        //Lista desblegable con las preguntas de seguridad
        Spinner spinnerSecurityQuestion = findViewById(R.id.preguntas_seguridad);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.security_questions_array, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinnerSecurityQuestion.setAdapter(adapter);

        //Cambiar un xml de invisible a visible
        CheckBox otros_mostrar = findViewById(R.id.checkBox_otros);
        EditText respuesta_otros = findViewById(R.id.respuesta_otro);

        otros_mostrar.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    respuesta_otros.setVisibility(View.VISIBLE);
                }else {
                    respuesta_otros.setVisibility(View.INVISIBLE);
                }
            }
        });

        //Guardar en la base de datos
        Button botonGuardar = findViewById(R.id.guardar_boton);
        botonGuardar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                guardarDatosEnLaBaseDeDatos();
            }
        });

    }

    public void showAlertDialog(View view) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage("¿Estas seguro de querer cancelar?")
                .setCancelable(false)
                .setPositiveButton("Sí", (dialog, id) -> {
                    finish();
                    Intent intent = new Intent(Crear_cuenta.this, MainActivity.class);
                    startActivity(intent);
                })
                .setNegativeButton("No", (dialog, id) -> dialog.cancel());
        AlertDialog alertDialog = builder.create();
        alertDialog.show();
    }

    public void guardarDatosEnLaBaseDeDatos() {

        // Crear una instancia de la base de datos helper
        SQLiteHelper dbHelper = new SQLiteHelper(this);
        SQLiteDatabase db = dbHelper.getWritableDatabase();

        // Recolectar los valores de los campos
        etNombre = findViewById(R.id.editNombre);
        etApellidos = findViewById(R.id.editApellidos);
        etCorreo = findViewById(R.id.editTextTextEmailAddress);
        etFechaNac = findViewById(R.id.editTextDate);
        etPassword = findViewById(R.id.editTextTextPassword);
        spPregunta = findViewById(R.id.preguntas_seguridad);
        etRespuestaSeguridad = findViewById(R.id.respuesta_seguridad);
        cbTecnologia = findViewById(R.id.checkBox_tecnologia);
        cbDeportes = findViewById(R.id.checkBox_deportes);
        cbCine = findViewById(R.id.checkBox_cine);
        cbRedesSociales = findViewById(R.id.checkBox_redessociales);
        cbOtros = findViewById(R.id.checkBox_otros);
        etRespuestaOtro = findViewById(R.id.respuesta_otro);
        cbFactorAuentificacion = findViewById(R.id.factor_autentificacion);

        //Metiendo los valores en las variables
        String nombre = etNombre.getText().toString();
        String apellido = etApellidos.getText().toString();
        String correo = etCorreo.getText().toString();
        String fecha_nacimiento = etFechaNac.getText().toString();
        String password = etPassword.getText().toString();
        String pregunta_seguridad = spPregunta.getSelectedItem().toString();
        String respuesta_seguridad = etRespuestaSeguridad.getText().toString();
        boolean tecnologia_checked = cbTecnologia.isChecked();
        boolean deportes_checked = cbDeportes.isChecked();
        boolean cine_checked = cbCine.isChecked();
        boolean redes_checked = cbRedesSociales.isChecked();
        boolean otros_checked = cbOtros.isChecked();
        String respuesta_otro = etRespuestaOtro.getText().toString();
        boolean aut_checked = cbFactorAuentificacion.isChecked();

        //Paso valores booleanos a enteros para poder meterlos a la base de datos
        int tecnologia = tecnologia_checked ? 1 : 0;
        int deportes = deportes_checked ? 1 : 0;
        int cine = cine_checked ? 1 : 0;
        int redes = redes_checked ? 1 : 0;
        int otros = otros_checked ? 1 : 0;
        int autentificar = aut_checked ? 1 : 0;

        // Insertar usuario en la base de datos
        long id = dbHelper.agregarUsuarios(correo, password, nombre, apellido, fecha_nacimiento, pregunta_seguridad, respuesta_seguridad, tecnologia, deportes, cine, redes, otros, respuesta_otro, autentificar);

        if (id > 0){
            Toast.makeText(this, "Registro Completado.", Toast.LENGTH_SHORT).show();
            Intent intent = new Intent(Crear_cuenta.this, HomeActivity.class);
            startActivity(intent);
        }else{
            Toast.makeText(this, "Error al crear usuario.", Toast.LENGTH_SHORT).show();
        }

    }
}
