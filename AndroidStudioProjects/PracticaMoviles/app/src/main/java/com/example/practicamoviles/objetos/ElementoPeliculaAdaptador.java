package com.example.practicamoviles.objetos;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.practicamoviles.R;

import java.util.ArrayList;

public class ElementoPeliculaAdaptador extends BaseAdapter {

    private Context mContext;
    private ArrayList<Peliculas> listaPeliculas;

    // Constructor
    public ElementoPeliculaAdaptador(Context context, ArrayList<Peliculas> peliculas) {
        super();
        this.mContext = context;
        this.listaPeliculas = peliculas;
    }

    @Override
    public int getCount() {
        return listaPeliculas.size();
    }

    @Override
    public Object getItem(int position) {
        return listaPeliculas.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        convertView = inflater.inflate(R.layout.itemlista, null);

        ImageView imageView = convertView.findViewById(R.id.imageView_plataforma);
        TextView nombreTextView = convertView.findViewById(R.id.textView_plataforma);

        nombreTextView.setText(listaPeliculas.get(position).getTitulo());
        imageView.setImageBitmap(listaPeliculas.get(position).getCaratula());

        return convertView;
    }

}
