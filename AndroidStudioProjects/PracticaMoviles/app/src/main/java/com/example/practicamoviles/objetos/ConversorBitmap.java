package com.example.practicamoviles.objetos;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;

import java.io.ByteArrayOutputStream;

public class ConversorBitmap {
    // convert from bitmap to byte array
    public static byte[] bitmapToArray(Bitmap bitmap) {
        ByteArrayOutputStream stream = new ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.PNG, 0, stream);
        return stream.toByteArray();
    }

    // convert from byte array to bitmap
    public static Bitmap imageFromArray(byte[] image) {
        return BitmapFactory.decodeByteArray(image, 0, image.length);
    }
}
