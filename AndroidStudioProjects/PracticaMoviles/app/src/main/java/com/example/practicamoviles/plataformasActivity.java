package com.example.practicamoviles;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;
import android.app.AlertDialog;
import android.content.DialogInterface;

import androidx.appcompat.app.AppCompatActivity;

import com.example.practicamoviles.objetos.ConversorBitmap;
import com.example.practicamoviles.objetos.ElementoListaAdaptador;
import com.example.practicamoviles.objetos.Plataformas;
import com.example.practicamoviles.sqlite.SQLiteHelper;

import java.util.ArrayList;

public class plataformasActivity extends AppCompatActivity {

    private ListView listViewPlataformas;
    private ArrayList<Plataformas> listaDePlataformas;  // Lista para almacenar los datos de las plataformas
    private ElementoListaAdaptador adapter;  // Adaptador personalizado para el ListView

    private Context context;

    SQLiteHelper dbHelper = new SQLiteHelper(plataformasActivity.this);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.plataformas);

        context = this;

        listViewPlataformas = findViewById(R.id.listViewPlataformas);
        cargarPlataformasDesdeDB(); // Método para cargar plataformas de la base de datos
        Button crearPlataformas = findViewById(R.id.button_nueva_plataforma);
        Button atras = findViewById(R.id.button_atras);

        //Botón retroceder
        atras.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(plataformasActivity.this, HomeActivity.class);
                startActivity(intent);
            }
        });

        //Botón añadir nuevas plataformas
        crearPlataformas.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(plataformasActivity.this, crearplataformaActivity.class);
                startActivity(intent);
            }
        });

        //Click largo
        listViewPlataformas.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
                // Obtener la plataforma seleccionada
                Plataformas plataformaSeleccionada = listaDePlataformas.get(position);

                // Crear un diálogo para pedir confirmación
                AlertDialog.Builder builder = new AlertDialog.Builder(plataformasActivity.this);
                builder.setTitle("Eliminar Plataforma");
                builder.setMessage("¿Estás seguro de que quieres eliminar la plataforma " + plataformaSeleccionada.getNombre() + "?");

                // Acción para confirmar la eliminación
                builder.setPositiveButton("Eliminar", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // Eliminar la plataforma de la base de datos
                        SQLiteHelper dbHelper = new SQLiteHelper(plataformasActivity.this);
                        dbHelper.eliminarPlataforma(plataformaSeleccionada.getId());

                        // Eliminar la plataforma de la lista
                        listaDePlataformas.remove(position);

                        // Notificar al adaptador para actualizar el ListView
                        adapter.notifyDataSetChanged();

                        Toast.makeText(plataformasActivity.this, "Plataforma eliminada.", Toast.LENGTH_SHORT).show();
                    }
                });

                // Acción para cancelar la eliminación
                builder.setNegativeButton("Cancelar", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss(); // Cierra el diálogo sin hacer nada
                    }
                });

                // Mostrar el diálogo
                builder.show();

                return true; // Indica que el evento de pulsación prolongada ha sido manejado
            }
        });

        //Click corto
        listViewPlataformas.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long id) {
                // Verificar si la lista es válida y la posición está dentro de sus límites
                if (listaDePlataformas != null && !listaDePlataformas.isEmpty() && position < listaDePlataformas.size()) {
                    // Obtener la plataforma seleccionada
                    Plataformas plataformaSeleccionada = listaDePlataformas.get(position);

                    // Crear un nuevo Intent para iniciar la actividad de información
                    Intent intent = new Intent(plataformasActivity.this, informacionplataformaActivity.class);

                    // Usar un Bundle para agregar datos
                    Bundle bundle = new Bundle();
                    bundle.putString("NOMBRE_PLATAFORMA", plataformaSeleccionada.getNombre());
                    bundle.putString("URL_PLATAFORMA", plataformaSeleccionada.getUrl());
                    bundle.putByteArray("FOTO_PLATAFORMA", ConversorBitmap.bitmapToArray(plataformaSeleccionada.getFoto()));

                    // Agregar el Bundle al Intent
                    intent.putExtras(bundle);

                    // Iniciar la nueva actividad
                    startActivity(intent);
                } else if (listaDePlataformas == null){
                    // Manejo de errores si la lista está vacía o la posición es incorrecta
                    Toast.makeText(plataformasActivity.this, "listaDePlataformas == null", Toast.LENGTH_SHORT).show();
                }
                else if (listaDePlataformas.isEmpty()){
                    // Manejo de errores si la lista está vacía o la posición es incorrecta
                    Toast.makeText(plataformasActivity.this, "listaDePlataformas.isEmpty()", Toast.LENGTH_SHORT).show();
                }
                else if (position > listaDePlataformas.size()){
                    // Manejo de errores si la lista está vacía o la posición es incorrecta
                    Toast.makeText(plataformasActivity.this, "position > listaDePlataformas.size().", Toast.LENGTH_SHORT).show();
                }
            }
        });

    }

    private void cargarPlataformasDesdeDB() {
        listaDePlataformas = dbHelper.obtenerTodasPlataformas(plataformasActivity.this);

        adapter = new ElementoListaAdaptador(this, listaDePlataformas);  // Reinicia el adaptador con los nuevos datos
        listViewPlataformas.setAdapter(adapter);

        if (listaDePlataformas.isEmpty()) {
            Toast.makeText(this, "No hay plataformas.", Toast.LENGTH_SHORT).show();
        }
    }
}


