package com.example.practicamoviles.sqlite;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import androidx.annotation.Nullable;

import com.example.practicamoviles.objetos.Peliculas;
import com.example.practicamoviles.objetos.Plataformas;

import java.io.ByteArrayOutputStream;
import java.util.ArrayList;

public class SQLiteHelper extends SQLiteOpenHelper {

    //Nombre base de datos
    private static final String bd_nombre = "BDPractica";
    Context context;
    private static final int versionDB = 1;
    public static final String tabla_usuarios = "Usuarios";
    public static final String tablaplataformas = "plataformas";
    public static final String tablapeliculas = "peliculas";

    public SQLiteHelper(@Nullable Context context) {
        super(context, bd_nombre, null, versionDB);
    }

    //Crear las tablas
    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("CREATE TABLE " + tabla_usuarios + "(id integer primary key autoincrement, " +
                "nombre text, " +
                "apellidos text, " +
                "correo text not null, " +
                "password text not null, " +
                "fecha_nacimiento text, " +
                "id_pregunta_seguridad text, " +
                "respuesta_seguridad text, " +
                "tecnologia integer, " +
                "deportes integer, " +
                "redes_sociales integer, " +
                "cine integer, " +
                "otros integer, " +
                "respuesta_otros text, " +
                "factor_autentificacion integer)");

        db.execSQL(" CREATE TABLE " + tablaplataformas + "(" +
                "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                "idUsuario INTEGER," +
                "foto BLOB NOT NULL," +  //Almacenar la imagen como un binary large object
                "nombre TEXT NOT NULL," +
                "url TEXT," +
                "usuario TEXT," +
                "password TEXT," +
                "FOREIGN KEY(idUsuario) REFERENCES Usuarios(id) ON DELETE CASCADE" +
                ")");

        db.execSQL(" CREATE TABLE " + tablapeliculas + "(" +
                "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                "idUsuario INTEGER," +
                "idPlataforma INTEGER," +
                "caratula BLOB NOT NULL," +  //Almacenar la caratula como un binary large object
                "titulo TEXT NOT NULL," +
                "duracion INTEGER," +
                "puntuacion INTEGER," +
                "genero TEXT," +
                "FOREIGN KEY(idUsuario) REFERENCES Usuarios(id) ON DELETE CASCADE," +
                "FOREIGN KEY(idPlataforma) REFERENCES plataformas(id) ON DELETE CASCADE" +
                ")");
    }

    //Upgrade tablas
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS tabla_usuarios");
        db.execSQL("DROP TABLE IF EXISTS tablaplataformas");
        db.execSQL("DROP TABLE IF EXISTS tablapeliculas");
        onCreate(db);
    }

    //----------------------------------------------------------------METODOS USUARIOS------------------------------------------------------------------------------------------------
    //Agregar usuarios
    public long agregarUsuarios(String correo, String password, String nombre, String apellidos, String fecha_nacimiento, String pregunta_seguridad, String respuesta_seguridad, int tecnologia, int deportes, int redes_sociales, int cine, int otros, String respuesta_otros, int aut) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();

        //No es necesario poner el 'id' ya que es automático y se autoincrementa
        values.put("correo", correo);
        values.put("password", password);
        values.put("nombre", nombre);
        values.put("apellidos", apellidos);
        values.put("fecha_nacimiento", fecha_nacimiento);
        values.put("id_pregunta_seguridad", pregunta_seguridad);
        values.put("respuesta_seguridad", respuesta_seguridad);
        values.put("tecnologia", tecnologia);
        values.put("deportes", deportes);
        values.put("redes_sociales", redes_sociales);
        values.put("cine", cine);
        values.put("otros", otros);
        values.put("respuesta_otros", respuesta_otros);
        values.put("factor_autentificacion", aut);

        // Intentar insertar en la base de datos
        long id = db.insert("Usuarios", null, values);

        // Cerrar la base de datos
        db.close();
        // Devuelve el ID del usuario insertado o -1 si hubo un error
        return id;
    }

    //Validacion del login
    public int validarUsuario(String email, String password) {
        SQLiteDatabase db = this.getReadableDatabase();
        int userId = -1;  // valor por defecto si la autenticación falla
        Cursor cursor = db.query("Usuarios", // Nombre de la tabla
                new String[] { "id" }, // Columnas a retornar
                "correo = ? AND password = ?", // Condición WHERE
                new String[] { email, password }, // Valores para la condición WHERE
                null, // groupBy
                null, // having
                null); // orderBy

        if (cursor.moveToFirst()) {
            userId = cursor.getInt(0);  // Obtener el ID del usuario
        }
        cursor.close();
        db.close();
        return userId;
    }

    //----------------------------------------------------------------TABLA PLATAFORMAS--------------------------------------------------------------------------------
    //Paso el bitmap a array de bits  VALIDO PARA PELICULAS
    private byte[] getBitmapAsByteArray(Bitmap bitmap) {
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.PNG, 0, outputStream);
        return outputStream.toByteArray();
    }

    // Insertar plataforma con la imagen
    public long anyadirPlataforma(int idUsuario, Bitmap foto, String nombre, String url, String usuario, String password) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();

        // Convertir Bitmap a byte array
        byte[] fotoBytes = getBitmapAsByteArray(foto);

        values.put("idUsuario", idUsuario);
        values.put("foto", fotoBytes);
        values.put("nombre", nombre);
        values.put("url", url);
        values.put("usuario", usuario);
        values.put("password", password);

        long id = db.insert("plataformas", null, values);

        db.close();

        return id;
    }

    public ArrayList<Plataformas> obtenerTodasPlataformas(Context context) {
        ArrayList<Plataformas> listaPlataformas = new ArrayList<>();

        SQLiteHelper dbPlataformas = new SQLiteHelper(context);

        Cursor cursor = dbPlataformas.getReadableDatabase().rawQuery("SELECT * FROM " + tablaplataformas, null);

        while (cursor.moveToNext()) {
            int id = cursor.getInt(cursor.getColumnIndexOrThrow("id"));
            int idUsuario = cursor.getInt(cursor.getColumnIndexOrThrow("idUsuario"));
            byte[] foto = cursor.getBlob(cursor.getColumnIndexOrThrow("foto"));
            String nombre = cursor.getString(cursor.getColumnIndexOrThrow("nombre"));
            String url = cursor.getString(cursor.getColumnIndexOrThrow("url"));
            String usuario = cursor.getString(cursor.getColumnIndexOrThrow("usuario"));
            String password = cursor.getString(cursor.getColumnIndexOrThrow("password"));

            Bitmap fotoBitmap = BitmapFactory.decodeByteArray(foto, 0, foto.length);

            Plataformas plataforma = new Plataformas(id, idUsuario, fotoBitmap, nombre, url, usuario, password);
            plataforma.setFoto(fotoBitmap);
            listaPlataformas.add(plataforma);
        }
        cursor.close();
        dbPlataformas.close();
        return listaPlataformas;
    }

    public void eliminarPlataforma(int plataformaId) {
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete("plataformas", "id = ?", new String[]{String.valueOf(plataformaId)});
        db.close();
    }

    //----------------------------------------------------------------TABLA PELICULAS--------------------------------------------------------------------------------

    // Insertar plataforma con la imagen
    public long anyadirPeliculas(int idUsuario, Bitmap caratula, String titulo, String genero, int duracion, int puntuacion) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();

        // Convertir Bitmap a byte array
        byte[] caratulaBytes = getBitmapAsByteArray(caratula);

        values.put("idUsuario", idUsuario);
        values.put("caratula", caratulaBytes);
        values.put("titulo", titulo);
        values.put("genero", genero);
        values.put("duracion", duracion);
        values.put("puntuacion", puntuacion);

        long id = db.insert("peliculas", null, values);

        db.close();

        return id;
    }

    public void eliminarPelicula(int idPelicula) {
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete("peliculas", "id = ?", new String[]{String.valueOf(idPelicula)});
        db.close();
    }

    public ArrayList<Peliculas> obtenerTodasPeliculas(Context context) {
        ArrayList<Peliculas> listaPeliculas = new ArrayList<>();

        SQLiteHelper dbPeliculas = new SQLiteHelper(context);

        Cursor cursor = dbPeliculas.getReadableDatabase().rawQuery("SELECT * FROM " + tablapeliculas, null);

        while (cursor.moveToNext()) {
            int id = cursor.getInt(cursor.getColumnIndexOrThrow("id"));
            int idUsuario = cursor.getInt(cursor.getColumnIndexOrThrow("idUsuario"));
            int idPlataforma = cursor.getInt(cursor.getColumnIndexOrThrow("idPlataforma"));
            byte[] caratula = cursor.getBlob(cursor.getColumnIndexOrThrow("caratula"));
            String titulo = cursor.getString(cursor.getColumnIndexOrThrow("titulo"));
            String genero = cursor.getString(cursor.getColumnIndexOrThrow("genero"));
            int duracion = cursor.getInt(cursor.getColumnIndexOrThrow("duracion"));
            int puntuacion = cursor.getInt(cursor.getColumnIndexOrThrow("puntuacion"));

            Bitmap caratulaBitmap = BitmapFactory.decodeByteArray(caratula, 0, caratula.length);

            Peliculas pelicula = new Peliculas(id, idUsuario, idPlataforma, caratulaBitmap, titulo, duracion, puntuacion, genero);
            pelicula.setCaratula(caratulaBitmap);
            listaPeliculas.add(pelicula);
        }
        cursor.close();
        dbPeliculas.close();
        return listaPeliculas;
    }

    public void eliminarPeliculas(int peliculasId) {
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete("peliculas", "id = ?", new String[]{String.valueOf(peliculasId)});
        db.close();
    }

}

