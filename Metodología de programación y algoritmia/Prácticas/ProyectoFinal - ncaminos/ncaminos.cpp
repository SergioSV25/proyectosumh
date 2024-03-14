/*Lucas Borges de Castro
  Sergio Sanchiz Villena
  Pablo Casimiro Beneitez
*/
#include <iostream>
#include <vector>

using namespace std;

// DECLARACION DE VARIABLES Y FUNCIONES
int decision = 0, n_filas = 0, n_columnas = 0, x1 = 0, y = 0, x2 = 0, y2 = 0;
int robot_recursivo(int x1, int y, int x2, int y2, int filas, int columnas) {
  if (x1 == x2 && y == y2) { // Caso base
    return 1;
  } else if (x1 >= filas ||
             y >= columnas) { // Limite de las dimensiones del plano
    return 0;
  } else {
    return robot_recursivo(x1 + 1, y + 1, x2, y2, filas, columnas) +
           robot_recursivo(x1 + 1, y, x2, y2, filas, columnas) +
           robot_recursivo(x1, y + 1, x2, y2, filas,
                           columnas); // Avanza una posicion en todos los rangos
                                      // de movimientos posibles
  }
}

int robot_iterativo(int x1, int y, int x2, int y2, int filas, int columnas) {
  // Declaración matriz bidimensional
  int **matriz = new int *[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
        // Inicializar todas las posiciones de la matriz con valor 0
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 0;
        }
    }

  matriz[x1][y] = 1; // Establece el punto inicial con valor 1 de movimientos

  // Inicio el proceso de cálculo de los caminos posibles desde el punto inicial
  // hacia el punto final.
  for (int x = x1; x <= x2; x++) {
    for (int i = y; i <= y2; i++) {
      if (x < filas - 1) {
        matriz[x + 1][i] += matriz[x][i]; // Mover hacia abajo
      }
      if (i < columnas - 1) {
        matriz[x][i + 1] += matriz[x][i]; // Mover hacia la derecha
      }
      if (x < filas - 1 && i < columnas - 1) {
        matriz[x + 1][i + 1] += matriz[x][i]; // Mover en diagonal
      }
    }
  }
  // En cuanto llega a la posición final, se guarda los movimientos que se han
  // hecho hasta ese punto.
  int num_caminos = matriz[x2][y2]; // Valor en el punto final

  // Liberar memoria asignada a la matriz
  for (int i = 0; i < filas; i++) {
    delete[] matriz[i];
  }
  delete[] matriz;

  return num_caminos;
}

int main() {
  cout << "  ***********************************" << endl;
  cout << "  ++++++++ NUMERO DE CAMINOS ++++++++" << endl;
  cout << "  ***********************************" << endl;

  // EJECUCION DEL PROGRAMA
  while (1) {
    cout << endl;
    cout << "Elige una de las siguientes opciones: " << endl;
    cout << "1.- Tamanyo del plano" << endl;
    cout << "2.- Puntos iniciales y finales" << endl;
    cout << "3.- Algoritmo recursivo " << endl;
    cout << "4.- Algoritmo iterativo " << endl;
    cout << "5.- Salir" << endl << endl;

    cout << "Opcion: ";
    cin >> decision;
    cout << endl;

    switch (decision) {
    case 1: // PEDIR LAS DIMENSIONES DEL PLANO
      cout << "Indica el numero de filas: " << endl;
      cin >> n_filas;
      cout << "Indica el numero de columnas: " << endl;
      cin >> n_columnas;

      /*CONTROL DE ERRORES*/
      if (n_filas == 0 && n_columnas == 0) {
        cout << "Has seleccionado un plano inexistente" << endl << endl;
        break;
        /*************************************/

      } else {
        cout << "Se ha definido un plano de: " << n_filas << " filas y "
             << n_columnas << " columnas." << endl
             << endl;
        break;
      }

    case 2: // PEDIR LOS PUNTOS DE PARTIDA Y DESTINO
      /*CONTROL DE ERRORES 1*/
      if (n_filas == 0 && n_columnas == 0) {
        cout << "Primero indica las dimensiones del plano" << endl << endl;
        break;
      }
      /*************************************/

      cout << "Indica la fila inicial: " << endl;
      cin >> x1;
      cout << "Indica la columna inicial: " << endl;
      cin >> y;
      cout << "Indica la fila final: " << endl;
      cin >> x2;
      cout << "Indica la columna final: " << endl;
      cin >> y2;

      /*CONTROL DE ERRORES 2*/
      if (x1 > n_filas || x2 > n_filas || y > n_columnas || y2 > n_columnas) {
        cout << "Estas intentando viajar desde/hacia un punto inexistente en "
                "el plano"
             << endl
             << endl;
        x1 = x2 = y = y2 = 0;
      } else if (x2 < x1 || y2 < y) {
        cout << "El punto final esta fuera del rango de movimientos del robot"
             << endl
             << endl;
        x1 = x2 = y = y2 = 0;
      }
      /*************************************/
      else {
        cout << "El algoritmo encontrara los N Caminos de (" << x1 << "," << y << ") a (" << x2 << "," << y2 << ")" << endl << endl;
      }
      break;
    case 3: // ALGORITMO RECURSIVO
      /*CONTROL DE ERRORES*/
      if (n_filas == 0 && n_columnas == 0) {
        cout << "Primero indica las dimensiones del plano" << endl << endl;
        break;
      }
      if (x1 == 0 && y == 0 && x2 == 0 && y2 == 0) {
        cout << "Indica los puntos iniciales y finales del plano antes" << endl;
        break;
      }
      /*************************************/

      // EJECUCION DEL ALGORITMO
      cout << "---------HAY " << robot_recursivo(x1, y, x2, y2, n_filas, n_columnas) << " CAMINOS POSIBLES---------" << endl;
      break;

    case 4: // ALGORITMO ITERATIVO
      /*CONTROL DE ERRORES*/
      if (n_filas == 0 && n_columnas == 0) {
        cout << "Primero indica las dimensiones del plano" << endl << endl;
        break;
      }
      if (x1 == 0 && y == 0 && x2 == 0 && y2 == 0) {
        cout << "Indica los puntos iniciales y finales del plano antes" << endl;
        break;
      }
      /*************************************/

      // EJECUCION DEL ALGORITMO
      int num_caminos = robot_iterativo(x1, y, x2, y2, n_filas, n_columnas);
      cout << "---------HAY " << num_caminos << " CAMINOS POSIBLES---------" << endl;
      break;
    }
    // FINALIZACION DE LA EJECUCION DEL PROGRAMA
    if (decision == 5) {
      cout << "  ***********************************" << endl;
      cout << "  +++++++++ FIN DE EJECUCION ++++++++" << endl;
      cout << "  ***********************************" << endl;
      break;
    }
  }
}