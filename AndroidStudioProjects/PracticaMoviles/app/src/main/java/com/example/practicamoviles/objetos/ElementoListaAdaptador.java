package com.example.practicamoviles.objetos;

import android.annotation.SuppressLint;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.practicamoviles.R;

import java.util.ArrayList;

public class ElementoListaAdaptador  extends BaseAdapter {

    private Context mContext;
    private ArrayList<Plataformas> listaPlataformas;

    // Constructor
    public ElementoListaAdaptador(Context context, ArrayList<Plataformas> plataformas) {
        super();
        this.mContext = context;
        this.listaPlataformas = plataformas;
    }

    @Override
    public int getCount() {
        return listaPlataformas.size();
    }

    @Override
    public Object getItem(int position) {
        return listaPlataformas.get(position);
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

        nombreTextView.setText(listaPlataformas.get(position).getNombre());
        imageView.setImageBitmap(listaPlataformas.get(position).getFoto());

        return convertView;
    }
}
