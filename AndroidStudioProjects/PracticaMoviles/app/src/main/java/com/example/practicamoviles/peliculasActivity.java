package com.example.practicamoviles;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import com.example.practicamoviles.objetos.ConversorBitmap;
import com.example.practicamoviles.objetos.ElementoPeliculaAdaptador;
import com.example.practicamoviles.objetos.Peliculas;
import com.example.practicamoviles.sqlite.SQLiteHelper;

import java.util.ArrayList;

public class peliculasActivity extends AppCompatActivity {

    private ListView listViewPeliculas;
    private ArrayList<Peliculas> listaDePeliculas;  // Lista para almacenar los datos de las peliculas
    private ElementoPeliculaAdaptador adapter;  // Adaptador personalizado para el ListView

    private Context context;

    SQLiteHelper dbHelper = new SQLiteHelper(peliculasActivity.this);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.peliculas);

        context = this;

        listViewPeliculas = findViewById(R.id.arraypeliculas);
        cargarPeliculasDesdeDB(); // Método para cargar plataformas de la base de datos
        Button crearPeliculas= findViewById(R.id.button_nueva_peli);
        Button atras = findViewById(R.id.button_retroceder);

        //Botón retroceder
        atras.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(peliculasActivity.this, HomeActivity.class);
                startActivity(intent);
            }
        });

        //Botón añadir nuevas pelis
        crearPeliculas.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(peliculasActivity.this, crearpeliculaActivity.class);
                startActivity(intent);
            }
        });

        //-------------------------------------------------CLICKS CORTOS Y LARGOS PARA AÑADIR---------------------------------------------------------------------//
        //Click largo
        listViewPeliculas.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {

                // Obtener la plataforma seleccionada
                Peliculas peliculaSeleccionada = listaDePeliculas.get(position);

                // Crear un diálogo para pedir confirmación
                AlertDialog.Builder builder = new AlertDialog.Builder(peliculasActivity.this);
                builder.setTitle("Eliminar Plataforma");
                builder.setMessage("¿Estás seguro de que quieres eliminar la plataforma " + peliculaSeleccionada.getTitulo() + "?");

                // Acción para confirmar la eliminación
                builder.setPositiveButton("Eliminar", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // Eliminar la plataforma de la base de datos
                        SQLiteHelper dbHelper = new SQLiteHelper(peliculasActivity.this);
                        dbHelper.eliminarPeliculas(peliculaSeleccionada.getId());

                        // Eliminar la plataforma de la lista
                        listaDePeliculas.remove(position);

                        // Notificar al adaptador para actualizar el ListView
                        adapter.notifyDataSetChanged();

                        Toast.makeText(peliculasActivity.this, "Pelicula eliminada.", Toast.LENGTH_SHORT).show();

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
        listViewPeliculas.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long id) {
                // Verificar si la lista es válida y la posición está dentro de sus límites
                if (listaDePeliculas != null && !listaDePeliculas.isEmpty() && position < listaDePeliculas.size()) {
                    // Obtener la plataforma seleccionada
                    Peliculas peliculaSeleccionada = listaDePeliculas.get(position);

                    // Crear un nuevo Intent para iniciar la actividad de información
                    Intent intent = new Intent(peliculasActivity.this, informacionpeliculaActivity.class);

                    // Usar un Bundle para agregar datos
                    Bundle bundle = new Bundle();
                    bundle.putString("TITULO", peliculaSeleccionada.getTitulo());
                    bundle.putString("GENERO", peliculaSeleccionada.getGenero());
                    bundle.putByteArray("CARATULA", ConversorBitmap.bitmapToArray(peliculaSeleccionada.getCaratula()));
                    bundle.putInt("PUNTUACION", peliculaSeleccionada.getPuntuacion());
                    bundle.putInt("DURACION", peliculaSeleccionada.getDuracion());

                    // Agregar el Bundle al Intent
                    intent.putExtras(bundle);

                    // Iniciar la nueva actividad
                    startActivity(intent);
                } else if (listaDePeliculas == null){
                    // Manejo de errores si la lista está vacía o la posición es incorrecta
                    Toast.makeText(peliculasActivity.this, "listaDePlataformas == null", Toast.LENGTH_SHORT).show();
                }
                else if (listaDePeliculas.isEmpty()){
                    // Manejo de errores si la lista está vacía o la posición es incorrecta
                    Toast.makeText(peliculasActivity.this, "listaDePlataformas.isEmpty()", Toast.LENGTH_SHORT).show();
                }
                else if (position > listaDePeliculas.size()){
                    // Manejo de errores si la lista está vacía o la posición es incorrecta
                    Toast.makeText(peliculasActivity.this, "position > listaDePlataformas.size().", Toast.LENGTH_SHORT).show();
                }
            }
        });

    }

    private void cargarPeliculasDesdeDB() {
        listaDePeliculas = dbHelper.obtenerTodasPeliculas(peliculasActivity.this);

        adapter = new ElementoPeliculaAdaptador(this, listaDePeliculas);  // Reinicia el adaptador con los nuevos datos
        listViewPeliculas.setAdapter(adapter);

        if (listaDePeliculas.isEmpty()) {
            Toast.makeText(this, "No hay plataformas.", Toast.LENGTH_SHORT).show();
        }
    }
}
