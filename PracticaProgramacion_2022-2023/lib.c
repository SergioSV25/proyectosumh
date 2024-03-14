#include "lib.h"

void hola(){ 
    printf("Alumno: Sergio Sanchiz Villena\n");
    printf("Email: sergio.sanchiz@goumh.umh.es\n");
}

//Tokenizador
char* MiStrTok(char *cad1, char *sep, int corchetes){

    static char *pt1 = NULL;
    static char *pt2 = NULL;
    static char *ptFinal;

    if(cad1 != NULL){
        pt1 = cad1;
        ptFinal = pt1+strlen(cad1);
    }
    else{
        pt1 = pt2+1;
    }
    if(pt1>=ptFinal){
        pt1 = pt2 = ptFinal = NULL;
        return NULL;
    }
    if(corchetes == 1){ // corchetes activados
        
        while(pt1[0]!='\0' && pt1 < ptFinal && strchr(sep, pt1[0]) != NULL && pt1[0] != '['){
            pt1++;
        }

        if(pt1[0] == '['){
            pt1++;
            pt2 = pt1;
            while(pt2[0] != '\0' && pt2[0] != ']'){
                pt2++;
            }

            if(pt2[0] == '\0'){
                pt1 = pt2 = ptFinal = NULL;
                return NULL;
            }
            else{
                pt2[0] = '\0';
                return pt1; 
            }
        }

    }
    else{

        while(pt1[0]!='\0' && pt1 < ptFinal && strchr(sep, pt1[0]) != NULL){
            pt1++;
        }

    }
    
    if(pt1>=ptFinal){
        pt1 = pt2 = ptFinal = NULL;
        return NULL;
    }
    pt2 = pt1+1;

    while(pt2[0] != '\0' && strchr(sep, pt2[0]) == NULL){
        pt2++;
    }

    pt2[0] = '\0';
    return pt1;

}

//Valida que los corchetes esten bn escritos. BN 1, MAL 0
int validarCorchetes(char * cadena){

    int i=0;
    int contador=0;
    int primeravez = 0;
    int corchetesApertura=0;
    int corchetesCierre=0;
    int orden = 0;

    while(cadena[i] != '\0'){
        if(cadena[i] == '[' || cadena[i] == ']'){
            contador++;
        }
        i++;
    }

    if(contador == 0){
        return 1;
    }

    i = 0;
    contador = 0;

    while(cadena[i] != '\0'){
        if(cadena[i] == '[' && contador == 0){  
            contador++;
            primeravez=1;
        }
        else if(cadena[i] == ']' && contador == 1){
            contador--;
        }

        if(cadena[i] == '['){
            corchetesApertura++;
            if(orden == 1){ // si entra dentro MAL
                return 0;
            }
            orden = 1;
        }
        else if(cadena[i] == ']'){
            corchetesCierre++;
            if(orden == 0){ // si entra dentro MAL
                return 0;
            }
            orden = 0;
        }

        i++;
    }

    if(contador == 0 && primeravez == 1 && corchetesApertura == corchetesCierre){ // Si se mete aqui bn
        return 1;
    }
    else{ // si se mete aqui mal
        return 0;
    }

}

// Devuelve una TLISTA por referencia y ademas 0 BN, 1 MAL
int expansionCorchetes(char *separadores, char * comtok, TLISTA *listaaux){

    // Color Prompt
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char *comtok2[100];

    char aux[100] = "";

    strcpy(aux, comtok);

    int num_arg=0, signo;

    TNUM *numeroAux;

    if(strcmp(aux, "") == 0){ // caso en el que el comtok este vacio

        listaaux->n = 0;
        listaaux->primero=NULL;
        listaaux->ultimo=NULL;

        return 0;
    }

    // for(int i = 0; i<1; i++){
    //     printf("comtok[%d]: %s", i, comtok[i]);
    // }

    comtok2[num_arg] = strtok(comtok, separadores); // 1 : 10   
    num_arg++;

    while((comtok2[num_arg] = strtok(NULL, separadores)) != NULL){
        num_arg++;
    }

    if(comtok2[0] == NULL){ // [] -> Manejo de listas vacias

        listaaux->n = 0;
        listaaux->primero = NULL;
        listaaux->ultimo = NULL;
        return 0;
    }

    for(int i=0; i<num_arg; i++){
        if(decimalValidar(comtok2[i]) == 0){
            
            if(strcmp(comtok2[i], "*") != 0 && strcmp(comtok2[i], "$") != 0 && strcmp(comtok2[i], ":") != 0 ){
                return 1;
            }
        }
    }

    if(comtok2[1] == NULL){ //[9]
        double auxNumero = atof(comtok2[0]);

        TNUM *numero = crearListaNum(auxNumero, NumDecimales(comtok2[0]));

        listaaux->n=listaaux->n+1;
        listaaux->primero = numero;
        listaaux->ultimo = numero;

        return 0;
    }

    if(strcmp(comtok2[1], ":") == 0){

        if(num_arg == 3){

            if(decimalValidar(comtok2[0]) == 0 || decimalValidar(comtok2[2]) == 0){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                return 1;
            }

            char aux[20];
            double comtokP0 = atof(comtok2[0]);
            double comtokP2 = atof(comtok2[2]);

            if(comtokP0 < comtokP2){  // [2 : 9]

                TNUM *numero = crearListaNum(comtokP0, NumDecimales(comtok2[0]));
                listaaux->n = listaaux->n+1;
                listaaux->primero = numero;
                listaaux->ultimo = numero;

                for(double i=comtokP0+1; i<=comtokP2; i++){

                    sprintf(aux, "%.11g", i);
                    listaaux->n = listaaux->n+1;
                    numero = crearListaNum(i, NumDecimales(aux));
                    numeroAux = listaaux->ultimo;
                    numeroAux->siguiente = numero;
                    numero->anterior = numeroAux;
                    listaaux->ultimo = numero;
                }

            }
            else if(comtokP0 > comtokP2){ // [9 : 2]

                TNUM *numero = crearListaNum(comtokP0, NumDecimales(comtok2[0]));
                listaaux->n = listaaux->n+1;
                listaaux->primero = numero;
                listaaux->ultimo = numero;

                for(double i=comtokP0-1; i >= comtokP2; i--){

                    sprintf(aux, "%.11g", i);
                    listaaux->n = listaaux->n+1;
                    numero = crearListaNum(i, NumDecimales(aux));
                    numeroAux = listaaux->ultimo;
                    numeroAux->siguiente = numero;
                    numero->anterior = numeroAux;
                    listaaux->ultimo = numero;

                }
            }
            else{ // [1 : 1]

                TNUM *numero = crearListaNum(comtokP0, NumDecimales(comtok2[0]));

                listaaux->n = listaaux->n+1;
                listaaux->primero = numero;
                listaaux->ultimo = numero;
            }

        }
        else{
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);
            return 1;

        }
    }
    else if(strcmp(comtok2[1], "$") == 0 && strcmp(comtok2[3], ":") == 0){ // [1 $ 3 : 12]
        
        if(num_arg == 5){

            if(decimalValidar(comtok2[0]) == 0 || decimalValidar(comtok2[2]) == 0 || decimalValidar(comtok2[4]) == 0){

                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                return 1;
            }

            char aux[20];

            // convertimos el texto a numeros doubles
            double comtokP0 = atof(comtok2[0]);
            double comtokP2 = atof(comtok2[2]);
            double comtokP4 = atof(comtok2[4]);


            // Comprobamos el signo del incremento
            if(comtokP2 > 0){
                signo = 1;
            }
            else if(comtokP2 < 0){
                signo = -1;
            }
            else{

                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                return 1;

            }

            if(comtokP0 <= comtokP4){

                if(signo < 0){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("ERROR\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    return 1;
                }

                TNUM *numero = crearListaNum(comtokP0, NumDecimales(comtok2[0]));
                listaaux->n = listaaux->n+1;
                listaaux->primero = numero; 
                listaaux->ultimo = numero;

                for(double i=comtokP0+comtokP2; i<=comtokP4; i = i + comtokP2){   // [3 $ 5 : 20]

                    sprintf(aux, "%.11g", i);
                    listaaux->n = listaaux->n+1;
                    numero = crearListaNum(i, NumDecimales(aux));
                    numeroAux = listaaux->ultimo;
                    numeroAux->siguiente = numero;
                    numero->anterior = numeroAux;
                    listaaux->ultimo = numero;

                }

            }
            else if(comtokP0 > comtokP4){

                if(signo > 0){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("ERROR\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    return 1;
                }

                TNUM *numero = crearListaNum(comtokP0, NumDecimales(comtok2[0]));
                listaaux->n = listaaux->n+1;
                listaaux->primero = numero; 
                listaaux->ultimo = numero;

                for(double i=comtokP0+comtokP2; i >= comtokP4; i = i + comtokP2){   // [20 $ -5 : 3]

                    sprintf(aux, "%.11g", i);
                    listaaux->n = listaaux->n+1;
                    numero = crearListaNum(i, NumDecimales(aux));
                    numeroAux = listaaux->ultimo;
                    numeroAux->siguiente = numero;
                    numero->anterior = numeroAux;
                    listaaux->ultimo = numero;

                }
            }

        }
        else{

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);
            return 1;
        }
    }
    else if(strcmp(comtok2[1], "*") == 0){

        //Validamos que el segundo numero de la lista sea un entero
        if (enteroValidar(comtok2[2]) == 0 || atoi(comtok2[2]) < 1){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);
            return 1;
        }

        //Validamos que el primer numero de la lista sea un numero
        if(decimalValidar(comtok2[0]) == 0){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);
            return 1;
        }

        double primero = atof(comtok2[0]);
        int segundo = atoi(comtok2[2]);

        char aux[20];
        TNUM *numero = crearListaNum(primero, NumDecimales(comtok2[0]));
        listaaux->n = listaaux->n+1;
        listaaux->primero = numero;
        listaaux->ultimo = numero;

        for(int i=1; i < segundo; i++){   // [20 * 2]

            sprintf(aux, "%.11g", atof(comtok2[0]));
            listaaux->n=listaaux->n+1;
            numero = crearListaNum(atof(comtok2[0]), NumDecimales(aux));
            numeroAux = listaaux->ultimo;
            numeroAux->siguiente = numero; 
            numero->anterior = numeroAux;
            listaaux->ultimo = numero;

        }

        
    }
    else{  // [2 5 8 74 6]

        for(int i=0; i<num_arg; i++){
            if(decimalValidar(comtok2[i]) == 0){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                return 1;
            }
        }

        char aux[20];
        TNUM *numero = crearListaNum(atof(comtok2[0]), NumDecimales(comtok2[0]));
        listaaux->n = listaaux->n+1;
        listaaux->primero = numero;
        listaaux->ultimo = numero;

        for(int i=1; i < num_arg; i++){   // [20 $ -5 : 3]

            sprintf(aux, "%.11g", atof(comtok2[i]));
            listaaux->n=listaaux->n+1;
            numero = crearListaNum(atof(comtok2[i]), NumDecimales(aux));
            numeroAux = listaaux->ultimo;
            numeroAux->siguiente = numero; 
            numero->anterior = numeroAux;
            listaaux->ultimo = numero;

        }
            
    }

    return 0;
}

//Nos devuelve el numero de decimales que tiene la cadena
int NumDecimales(char *cad){ // 745.458

    int i, p=0, j=0;

    for(i=0; i<strlen(cad); i++){
        if(p==1){
            j++;
        }
        if(cad[i] == '.'){
            p=1;
        }
    }

    return j;
}

// Creamos una estructura para TNUM
TNUM *crearListaNum(double auxNumero, int decimales){

    TNUM *nuevoNodo = (TNUM *) malloc(sizeof(TNUM));

    if(nuevoNodo != NULL){

        nuevoNodo->valor = auxNumero;
        nuevoNodo->decimales = decimales;

        nuevoNodo->siguiente = NULL;
        nuevoNodo->anterior = NULL;
    }
    return nuevoNodo;

}

// Creamos la estructura para TLISTA
TLISTA *crearLista(){

    TLISTA *nuevoNodo = (TLISTA *) malloc(sizeof(TLISTA));

    if(nuevoNodo != NULL){
        nuevoNodo->n=0;
        nuevoNodo->primero = NULL;
        nuevoNodo->ultimo = NULL;
    }

    return nuevoNodo;

}

//Valida que sea un numero real || 0 MAL, 1 BN
int decimalValidar(char *cad){

    int i, ini, p=0, j;

    if(cad[0] == '+' || cad[0] == '-'){
        ini=1;
    }
    else{
        ini=0;
    }

    for(i=ini; i<strlen(cad); i++){
        if(cad[i]<'0' || cad[i]> '9'){
            if(cad[i] == '.'){
                p++;
            }
            else{
                return 0;
            }
        }
        if(p==2){
            return 0;
        }
    }

    if(ini==1 && strlen(cad) == 1){
        return 0;
    }
    if(strlen(cad) == 0){
        return 0;
    }

    if(ini==1 && strlen(cad) == 2 && cad[1] == '.'){ //+.
        return 0;
    }

    if(ini == 0 && strlen(cad) == 1 && cad[0] == '.'){ // .
        return 0;
    }

    return 1;
}

// Imprime los elementos de la lista
void verLista(TLISTA *lista){

    // Color Prompt
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if(lista->primero == NULL){
        SetConsoleTextAttribute(hConsole, 2);
        printf("[]\n");
        SetConsoleTextAttribute(hConsole, 7);
        return;
    }

    TNUM *aux = lista->primero;
    SetConsoleTextAttribute(hConsole, 2);
    printf("\n[");
    for(int i = 0; i < lista->n; i++){

        if(i == lista->n-1){
            printf("%.11g", aux->valor);
        }
        else{
            printf("%.11g ", aux->valor);
        }

        aux = aux->siguiente;
    }
    printf("]\n");
    SetConsoleTextAttribute(hConsole, 7);
    
}

// 0 si es variable, 1 si es error, 2 si es numero
int listaOvariable(char *cad){
    
    if(cad[0] >= 'a' && cad[0] <= 'z'){
        return 0;
    }
    else if(cad[0] >= 'A' && cad[0] <= 'Z'){
        return 0;
    }
    else if(cad[0] == '+' || cad[0] == '-'){ 

        if(cad[1] >= '0' || cad[1] <= '9'){
            return 2;
        }
        if(cad[1] == '.'){
            if(cad[2] >= '0' && cad[2] <= '9'){
                return 2;
            }
            return 1;
        }

    }
    else if(cad[0] == '.'){
        if(cad[1] >= '0' && cad[1] <= '9'){
            return 2;
        }
        return 1;
    }
    else if(cad[0] >= '0' || cad[0] <= '9'){
        return 2;
    }

    return 1;
}

//Nos devuelve en formato lista lo que le pasemos
TLISTA *charToList(char *cadena, TVAR *laGranVariable, char *separadores){

    // Color Prompt
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    TLISTA *lista = crearLista();

    if(listaOvariable(cadena) == 1){ // caso ERROR

        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR\n");
        SetConsoleTextAttribute(hConsole, 7);
        return NULL;

    }
    else if(listaOvariable(cadena) == 0){ //Caso variable   a = [16 3]

        TVAR *aux = buscarVariable(laGranVariable, cadena);
        if(aux == NULL){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL;
        }
        lista = aux->valor;
    }
    else if(expansionCorchetes(separadores, cadena, lista) == 1){

        free(lista);

        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR\n");
        SetConsoleTextAttribute(hConsole, 7);

        return NULL;
    }
    return lista;
}

// Reservvamos memoria para una variable
TVAR *crearVariable(char *nombreVariable, TLISTA *lista){

    TVAR *nuevoNodo = (TVAR *)malloc(sizeof(TVAR));

    if(nuevoNodo != NULL){

        strcpy(nuevoNodo->nombre, nombreVariable);
        nuevoNodo->valor = lista;

        nuevoNodo->siguiente = NULL;
        nuevoNodo->anterior = NULL;
    }

    return nuevoNodo;
}

// Buscamos a partir de un nombre una variable
TVAR *buscarVariable(TVAR *laGranVariable, char *nombreVariable){

    TVAR *auxiliar = laGranVariable;

    while(auxiliar != NULL){

        if(strcmp(auxiliar->nombre, nombreVariable) == 0){
            return auxiliar;
        }
        auxiliar = auxiliar->siguiente;
    }

    return NULL;
}

//Operador -> + - head tail...
TLISTA * operar(char **cadena, TVAR *laGranVariable, int num_arg, char *separadores){ // a = [1 2 3] + [254 9]
    // Color Prompt
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    TLISTA *lista1 = crearLista();
    TLISTA *lista2 = crearLista();

    if(contarCaracteres(cadena, "+") == 1){

        lista1 = charToList(cadena[0], laGranVariable, separadores);

        if(lista1 == NULL){
            return NULL;
        }

        lista2 = charToList(cadena[2], laGranVariable, separadores);

        if(lista2 == NULL){
            return NULL;
        }

        return CombinacionListas(lista1, lista2);
    }
    else if(contarCaracteres(cadena, "-") == 1){

        lista1 = charToList(cadena[0], laGranVariable, separadores);

        if(lista1 == NULL){
            return NULL;
        }

        lista2 = charToList(cadena[2], laGranVariable, separadores);

        if(lista2 == NULL){
            return NULL;
        }

        return restaLista(lista1, lista2);

    }
    else if(strcmp(cadena[0], "head") == 0){

        if(num_arg != 3){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        if(enteroValidar(cadena[1]) == 0){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        if(atoi(cadena[1]) <= 0){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TLISTA *listaAux = charToList(cadena[2], laGranVariable, separadores);

        if(listaAux == NULL){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;

        }

        return copiarNlistaPrimeras(listaAux, atoi(cadena[1]));

    }
    else if(strcmp(cadena[0], "tail") == 0){

        if(num_arg != 3){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        if(enteroValidar(cadena[1]) == 0){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        if(atoi(cadena[1]) <= 0){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TLISTA *listaAux = charToList(cadena[2], laGranVariable, separadores);

        if(listaAux == NULL){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;

        }

        return copiarNlistaUltimas(listaAux, atoi(cadena[1]));
    }
    else if(strcmp(cadena[0], "turn") == 0 ){

        if(num_arg != 2){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TLISTA *listaAux = charToList(cadena[1], laGranVariable, separadores);

        //verLista(listaAux);

        if(listaAux == NULL){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;

        }

        return copiarListaInversa(listaAux);

    }
    else if(strcmp(cadena[0], "order") == 0){

        TLISTA *listaAux;

        if(num_arg !=2 && num_arg != 3){

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;

        }

        if(num_arg == 2){
            
            listaAux = charToList(cadena[1], laGranVariable, separadores);
            
            if(listaAux == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);

                return NULL;
            }
            return ordenarListaAscendente(listaAux);
            
            
        }
        else{
            listaAux = charToList(cadena[2], laGranVariable, separadores);
        }
        

        if(listaAux == NULL){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        if(strcmp(cadena[1], "asc") == 0){

            return ordenarListaAscendente(listaAux);
        }
        else if(strcmp(cadena[1], "des") == 0){
            
            return ordenarListaDescendente(listaAux);
        }
        else{
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }
        

    }
    else if(strcmp(cadena[0], "map") == 0){

        if(num_arg != 3){

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }


        //Validar que n sea un numero real
        if(decimalValidar(cadena[1]) == 0){

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        
        TLISTA *listaAux = charToList(cadena[2], laGranVariable, separadores);

        if(listaAux == NULL){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;

        }

        double n = atof(cadena[1]);

        return mapLista(listaAux, n);

    }
    if(contarCaracteres(cadena, "?") == 1){

        if(num_arg != 3){

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        //Validar que n sea un numero real
        if(decimalValidar(cadena[2]) == 0){

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TLISTA *listaAux = charToList(cadena[0], laGranVariable, separadores);
        
        if(listaAux == NULL){

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TVAR* variableAsignar = buscarVariable(laGranVariable, cadena[0]);

        if(variableAsignar == NULL){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        double n = atof(cadena[2]);

        TLISTA * Temp = funcionInterrogacion(listaAux, n);

        TLISTA *Temp2 = crearDuplicadoLista(Temp);

        return Temp2;
       
    }
    else{

        return charToList(cadena[0], laGranVariable, separadores);
    }



    
}

// Inserta la nueva variable en la ultima posicion de laGranVariable
TVAR *insertaUltimaVariable(TVAR *LagranVariable, TVAR *variableAsignar){

    TVAR *auxiliar = LagranVariable;

    if(auxiliar == NULL){

        // printf("Primer nodo\n");

        LagranVariable = variableAsignar;

        LagranVariable->siguiente = NULL;
        LagranVariable->anterior = NULL;
    }
    else{

        while(auxiliar->siguiente != NULL){
            auxiliar = auxiliar->siguiente;
        }

        auxiliar->siguiente = variableAsignar;
        variableAsignar->anterior = auxiliar;
        variableAsignar->siguiente = NULL;
    }

    return LagranVariable;

}

//imprime todas las variables que cuelgan de laGranVariable
void imprimirTVAR(TVAR *LaGranLista){
    TVAR *aux = LaGranLista;
    while(aux != NULL){
        printf("%s\n", aux->nombre);
        verLista(aux->valor);
        aux = aux->siguiente;
    }
}

// nos devuelve el numero de veces que ha encontrado un caracter en concreto dentro de una cadena
int contarCaracteres(char **cadena, char *caracter){

    int contador = 0;
    int i=0;

    while(cadena[i] != NULL){ //'\0'
        if(strcmp(cadena[i], caracter) == 0){
            contador++;
        }
        i++;
    }

    return contador;
}

// Crear una nueva lista con la concatenacion de las 2 listas que le pasamos por parametros
TLISTA *CombinacionListas(TLISTA *lista1, TLISTA *lista2){

    TLISTA *lista = crearLista();

    char aux[20];
    TNUM *numAux, *numTemp, *numLista;

    lista->n = lista1->n + lista2->n;

    if(lista1->primero != NULL){ 

        numAux = lista1->primero;
        numTemp = crearListaNum(numAux->valor, numAux->decimales);
        lista->primero = numTemp;
        lista->ultimo = numTemp;
        numAux = numAux->siguiente;

        for(int i=1; i<lista1->n; i++){

            numTemp = crearListaNum(numAux->valor, numAux->decimales);
            numLista = lista->ultimo;
            numLista->siguiente = numTemp;
            numTemp->anterior = numLista;

            lista->ultimo = numTemp;
            numAux = numAux->siguiente;

        }

    }

    if(lista1->primero != NULL){

        if(lista2->primero != NULL){ 

            numAux = lista2->primero; // pasamos a la siguiente lista

            for(int i=0; i<lista2->n; i++){
                numTemp = crearListaNum(numAux->valor, numAux->decimales);
                numLista = lista->ultimo;
                numLista->siguiente = numTemp;
                numTemp->anterior = numLista;

                lista->ultimo = numTemp;
                numAux = numAux->siguiente;
            }
        }
    }
    else{

        numAux = lista2->primero;
        numTemp = crearListaNum(numAux->valor, numAux->decimales);
        lista->primero = numTemp;
        lista->ultimo = numTemp;
        numAux = numAux->siguiente;

        for(int i=0; i<lista2->n; i++){
            numTemp = crearListaNum(numAux->valor, numAux->decimales);
            numLista = lista->ultimo;
            numLista->siguiente = numTemp;
            numTemp->anterior = numLista;

            lista->ultimo = numTemp;
            numAux = numAux->siguiente;
        }

    }

    
    return lista;
}

//Paso 2 listas y me devuelve la diferencia de las 2
TLISTA *restaLista(TLISTA *lista1, TLISTA *lista2){

    // casos donde una de las listas este vacia
    if(lista1->primero == NULL){
        return NULL;
    }
    if(lista2->primero == NULL){
        return lista1;
    }

    TLISTA *lista = crearLista();

    char aux[20];
    TNUM *numAux, *numTemp, *numLista, *numAux2, *numcontador;
    int cortafuegos = 0;

    // Creamos un duplicado de las listas 1 y 2
    TLISTA *listaDuplicada = crearDuplicadoLista(lista1);
    TLISTA *listaDuplicada2 = crearDuplicadoLista(lista2);

    numAux2 = listaDuplicada2->primero;

    while(numAux2 != NULL){

        numAux = listaDuplicada->primero;

        while(numAux != NULL){

            if(numAux->valor == numAux2->valor){

                //Borramos de las listas el numero coincidente
                eliminarElementoLista(listaDuplicada, numAux->valor);
                eliminarElementoLista(listaDuplicada2, numAux2->valor);

                cortafuegos = 1;

                break;
            }

            numAux = numAux->siguiente;
        }

        if(cortafuegos == 0){ 
            numAux2 = numAux2->siguiente;
        }
        else{
            numAux2 = listaDuplicada2->primero;
        }

        cortafuegos = 0;

        
    }
    
    lista = crearDuplicadoLista(listaDuplicada);

    return lista;
}

//Para trabajar con una lista duplicada y asi no tener problemas con la lista principal
TLISTA *crearDuplicadoLista(TLISTA *lista){

    TLISTA *listaDuplicada = crearLista();

    TNUM *numAux = lista->primero;
    TNUM *numPrev = NULL;

    while(numAux != NULL){

        TNUM *numTemp = crearListaNum(numAux->valor, numAux->decimales);

        if(numPrev == NULL){
            listaDuplicada->primero = numTemp;
            numTemp->anterior = NULL;
        }
        else{
            numPrev->siguiente = numTemp;
            numTemp->anterior = numPrev;
        }

        listaDuplicada->ultimo = numTemp;
        listaDuplicada->n++;

        numPrev = numTemp;
        numAux = numAux->siguiente;
    }

    return listaDuplicada;
}

// Esta funcion se encarga de borrar el elemento de la lista que encuentre con el valor que le pasamos
void eliminarElementoLista(TLISTA *listaDuplicada, double valor){

    TNUM *numAux, *numAnterior, *numSiguiente;

    numAux = listaDuplicada->primero; 

    verLista(listaDuplicada);

    while(numAux != NULL){

        if(valor == numAux->valor){

            //Encontramos cual es el numero de antes y despues
            numAnterior = numAux->anterior;
            numSiguiente = numAux->siguiente;

            //Recolocamos los nodos
            if(numAnterior == NULL && numSiguiente == NULL){ // Ser el unico de la lista

                listaDuplicada->primero = NULL;
                listaDuplicada->ultimo = NULL;

            }
            else if(numAnterior == NULL){ // Ser el primero de la lista

                listaDuplicada->primero = numSiguiente;
                numSiguiente->anterior = NULL;
                numAux->siguiente = NULL;

            }
            else if(numSiguiente == NULL){ // Ser el ultimo de la lista

                listaDuplicada->ultimo = numAnterior;
                numAnterior->siguiente = NULL;
            }
            else{ //Ser el elemento de enmedio

                numAnterior->siguiente = numSiguiente;
                numSiguiente->anterior = numAnterior;
            }
            
            listaDuplicada->n = listaDuplicada->n-1;

            numAux->anterior = NULL;
            numAux->siguiente = NULL;

            free(numAux);

            return;

        }

        numAux = numAux->siguiente;
    }

    return ;

}

// Devuelve 1 si L1 esta contenido en L2 y 0 si no
// Primero introduce la lista mas grande (L2) y luego la mas pequeña (L1) sabemos que es mas pequeña porque tiene menos elementos y por eso TRUE
int  contenidaLista(TLISTA *L2, TLISTA *L1){ 

    if(L2 == NULL){
        // printf("RestaListas: L2 es null\n");
        return 1;
    }
    if(L1 == NULL){
        // printf("RestaListas: L1 es null\n");
        return 0;
    }

    TLISTA *lista = crearLista();

    char aux[20];
    TNUM *numAux, *numAux2, *numTemp, *numLista, *numcontador;

    int bucle2 = 0, bucle1;

    // printf("DENTRO COMBI LISTA 1[");
    // verLista(L2);
    // printf("]\n");

    // printf("DENTRO COMBI LISTA 2[");
    // verLista(L1);
    // printf("]\n");

    //Creamos duplicado de listux2
    TLISTA *listaDuplicada = crearDuplicadoLista(L2);
    TLISTA *listaDuplicada2 = crearDuplicadoLista(L1);

    numAux = listaDuplicada->primero;
    numAux2 = listaDuplicada2->primero;

    numcontador = listaDuplicada->primero;

    bucle2 = 0;
    bucle1 = 0;

    int cortafuegos = 0;
    
    while(numAux2 != NULL){

        while(numAux != NULL){

            // printf("NUMERO A COMPARAR: %.11g\n", numAux2->valor);
            // printf("NUMERO A COMPARAR: %.11g\n", numAux->valor);

            if(numAux2 == NULL || numAux == NULL){

                break;

            }

            if(numAux->valor == numAux2->valor){

                //Borramos de las listas el numero coincidente
                eliminarElementoLista(listaDuplicada, numAux->valor);
                eliminarElementoLista(listaDuplicada2, numAux2->valor);

                // verLista(listaDuplicada);
                // verLista(listaDuplicada2);

                numAux = listaDuplicada->primero;
                numAux2 = listaDuplicada2->primero;

                cortafuegos = 1;

            }
            else{

                // if(numAux == NULL){
                //     printf("NUMERO NULL\n");
                // }
                // else{
                //     printf("NUMERO : %.11g\n", numAux->valor);
                // }

                numAux = numAux->siguiente; //Avanzamos el puntero de L1

                //printf("NUMERO : %.11g\n", numAux->valor);

            }

            bucle1++;
           
        }

        if(numAux2 != NULL){

            eliminarElementoLista(listaDuplicada2, numAux2->valor);

            numAux = listaDuplicada->primero;
            numAux2 = listaDuplicada2->primero;
        }

        bucle2++;
        
    }

    lista = crearDuplicadoLista(listaDuplicada);

    // verLista(lista);
    // verLista(L2);

    int numeroelementos = L2->n - L1->n;

    if(lista->n == numeroelementos){
        return 1;
    }
    else{
        return 0;
    } 
}

// validamos numeros enteros. 1 BN, 0 MAL
int enteroValidar(char *cad){
    int i, ini;

    if(cad[0] == '+' || cad[0] == '-'){
        ini=1;
    }
    else{
        ini = 0;
    }

    for(int i=ini; i<strlen(cad); i++){
        if(cad[i]<'0' || cad[i]>'9'){
            return 0;
        }
    }

    if(ini==1 && strlen(cad) == 1){
        return 0;
    }
    
    return 1;

}

// Nos devuelve una lista con las N primeras posiciones -> HEAD
TLISTA *copiarNlistaPrimeras(TLISTA *lista, int n){

    TLISTA *listaAux = crearLista();

    TNUM *numAux, *numTemp, *numLista;

    if(lista->primero == NULL){
        return NULL;
    }

    if(n>lista->n){
        n = lista->n;
    }

    listaAux->n = n;

    numAux=lista->primero;
    numTemp = crearListaNum(numAux->valor, numAux->decimales);

    listaAux->primero = numTemp;
    listaAux->ultimo = numTemp;

    numAux=numAux->siguiente;

    for(int i=1; i<n; i++){
        numTemp = crearListaNum(numAux->valor, numAux->decimales);
        numLista=listaAux->ultimo;
        numLista->siguiente = numTemp;
        numTemp->anterior = numLista;

        listaAux->ultimo = numTemp;
        numAux = numAux->siguiente;
    }

    return listaAux;
}

// Nos devuelve una lista con las N ultimas posiciones -> TAIL
TLISTA *copiarNlistaUltimas(TLISTA *lista, int n){ 

    TLISTA *listaAux = crearLista();
    TNUM *numAux, *numTemp, *numLista;

    if(lista->primero == NULL){
        return NULL;
    }

    if(n>lista->n){
        n = lista->n;
    }

    listaAux->n = n;

    numAux = lista->ultimo;
    numTemp = crearListaNum(numAux->valor, numAux->decimales);

    listaAux->primero = numTemp;
    listaAux->ultimo = numTemp;

    numAux = numAux->anterior;
    for(int i=1; i<n; i++){
        numTemp = crearListaNum(numAux->valor, numAux->decimales);
        numLista = listaAux->primero;
        numLista->anterior = numTemp;
        numTemp->siguiente = numLista;

        listaAux->primero = numTemp;
        numAux = numAux->anterior;
    }

    return listaAux;

}

//Invierte los elementos de una lista -> TURN
TLISTA *copiarListaInversa(TLISTA *lista){

    TLISTA *listaAux = crearLista();
    TNUM *numAux, *numTemp, *numLista;
    int i;

    if(lista->primero == NULL){
        return NULL;
    }

    // verLista(lista);

    
 
    numAux = lista->ultimo;

    // printf("%.11g\n", numAux->valor);

    numTemp = crearListaNum(numAux->valor, numAux->decimales);

    // printf("%.11g\n", numTemp->valor);

    listaAux->primero = numTemp;
    listaAux->ultimo = numTemp;


    // printf("%.11g\n", listaAux->primero->valor);


    numAux = numAux->anterior;

    for(i=1; i<lista->n; i++){
        numTemp = crearListaNum(numAux->valor, numAux->decimales);
      
        numLista=listaAux->ultimo;
        numLista->siguiente = numTemp;
        numTemp->anterior = numLista;

        listaAux->ultimo = numTemp;

        // printf("%.11g\n", listaAux->ultimo->valor);
        // printf("Bucle 2: %.11g\n", numTemp->valor);

        numAux = numAux->anterior; 
       
    }
    // printf("Fuera %.11g\n", listaAux->primero->valor);
    // printf("Fuera %.11g\n", listaAux->ultimo->valor);

    // TLISTA *A = listaAux;
    // TNUM *B = A->primero;
    // while(B != NULL){
        
    //     printf("%.11g\n", B->valor);
    //     B = B->siguiente;

    // }
    TLISTA *AYUDA = crearDuplicadoLista(listaAux);
    // verLista(A);
    // verLista(listaAux);
    // verLista(AYUDA);
    
    return AYUDA;
    
}

//
void laGranVista(TVAR *laGranVariable){

    // Color Prompt
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if(laGranVariable == NULL){
        SetConsoleTextAttribute(hConsole, 2);
        printf("No hay variables cargadas\n");
        SetConsoleTextAttribute(hConsole, 7);
    }

    TVAR *auxiliar = laGranVariable;
    TLISTA *listaux = NULL;

    SetConsoleTextAttribute(hConsole, 2);

    while(auxiliar != NULL){
        
        listaux = auxiliar->valor;
        if(listaux->n == 0){
           
           printf("%s: [vacia!]\n", auxiliar->nombre);

        }
        else{
            
            double sumatorio = Sum(listaux);
            double promedio = Sum(listaux) / listaux->n;
            printf("NomVariable: %s -> Numero de elementos: %d, Sumatorio: %.11g y Promedio: %.11g\n", auxiliar->nombre, listaux->n, sumatorio, promedio);   
            
        }

        auxiliar = auxiliar->siguiente;

    }

    SetConsoleTextAttribute(hConsole, 7);

}

//Creacion del espacio de
TVARS *crearWorkspace(TVARS *workspace){

    workspace = (TVARS *) malloc(sizeof(TVARS));

    workspace->n = 0;
    workspace->var1 = NULL;

    return workspace;
}

//
int contadorVariables(TVAR *LaGranVariable){

    TVAR *aux = LaGranVariable;
    int i = 0;

    while(aux != NULL){

        i++;
        aux = aux->siguiente;
    }

    return i;

}

//Guardamos en txt
void save(char *nombre, TVARS *workspace){

    //Si al final acabamos poniendole filtros al nombre descomentar esto
    /*
    int i = validarNombre(nombre);
    if(i == 0){
        printf("ERROR FATAL\n");
        return 0;
    }
    */

   char aux[50]="./";
   int numeroElementos = 0;

    strcat(aux, nombre);

    if(strchr(nombre, '.') == NULL){ //Entramos en el caso de que no tenga .txt
        strcat(aux, ".txt");
    }

    FILE *fichero;
    fichero = fopen(aux, "w");
    if(fichero != NULL){

        fprintf(fichero, "LIST WORKSPACE\n");
        fprintf(fichero, "---------------\n");   

        TVAR *auxiliar = workspace->var1; 

        for(int i = 0; i<workspace->n; i++){
            
            //Imprimimos el nombre de la variable
            fprintf(fichero, "%s\n", auxiliar->nombre);

            TLISTA *auxLista = auxiliar->valor;
            TNUM *numAux = auxLista->primero;

            if(numAux == NULL){
                fprintf(fichero, "\n");
            }

            for(int j = 0; j<auxLista->n; j++){

                if(j == auxLista->n-1){
                    fprintf(fichero, "%.11g\n", numAux->valor);
                }
                else{
                    fprintf(fichero, "%.11g ", numAux->valor);
                }

                numAux = numAux->siguiente;

            }

            if(i < workspace->n-1){
                fprintf(fichero, "---------------\n");
            }

            auxiliar = auxiliar->siguiente;
        }

        fclose(fichero);
    }
    else{
        printf("ERROR\n");
    }

}

// Validamos que este bn escrito todo, 0 MAL, 1 BN
int validarNombre(char *nombre){

    int i = 0;

    while(nombre[i] != '\0'){
        if(nombre[i] >= '0' && nombre[i] <= '9'){
            i++;
            continue;
        }
        if(nombre[i]>= 'a' && nombre[i] <= 'z'){
            i++;
            continue;
        }
        if(nombre[i] >= 'A' && nombre[i] <= 'Z'){
            i++;
            continue;
        }
        return 0;
    }

    if(strcmp(nombre, "head") == 0){
        return 0;
    }
    else if(strcmp(nombre, "tail") == 0){
        return 0;
    }
    else if(strcmp(nombre, "isIn") == 0){
        return 0;
    }
    else if(strcmp(nombre, "vars") == 0){
        return 0;
    }
    else if(strcmp(nombre, "save") == 0){
        return 0;
    }
    else if(strcmp(nombre, "load") == 0){
        return 0;
    }
    else if(strcmp(nombre,"sum")== 0){
        return 0;
    }
    else if(strcmp(nombre,"turn")== 0){
        return 0;
    }
    else if(strcmp(nombre,"order")== 0){
        return 0;
    }
    else if(strcmp(nombre,"map")== 0){
        return 0;
    }
    
    return 1;

}

//Cargar desde el fichero
TVARS *load(char *nombre){

    FILE *fichero;
    char aux[50] = "./";
    char linea[100], val[100];
    int c=0, n = 0, numeroVariables;
    TVARS *workspace = NULL;
    TVAR *laGranVariable = NULL;

    strcat(aux, nombre);

    if(strchr(nombre, '.') == NULL){ //Entramos en el caso de que no tenga .txt
        strcat(aux, ".txt");
    }

    // printf("La ruta del load es: %s\n", aux);

    fichero = fopen(aux, "r"); //abrimos fichero en modo lectura

    if(fichero == NULL){
        return NULL;
    }

    fgets(linea, 100, fichero);  // Aqui cogemos LIST WORKSPACE 
    fgets(linea, 100, fichero);  // Aqui cogemos ---------------
    
    while((c = fgetc(fichero)) != EOF){  // Aqui contamos las lineas del documento
        if( c == '\n')
            n++;
        putchar(c);
    } 
    n++; // Incrementamos una linea extra por el tema de los guiones

    workspace = crearWorkspace(workspace);

    numeroVariables = n/3;
    workspace->n = numeroVariables;

    //printf("El numero de variables es: %d\n", workspace->n);

    //Caso en el que LIST WORKSPACE este vacio
    if(numeroVariables == 0){  
        workspace->var1 = laGranVariable;
        return workspace;
    }

    fseek(fichero,0,SEEK_SET); // Movemos el cursor al principio del documento otra vez

    fgets(linea, 100, fichero);  // Aqui cogemos LIST WORKSPACE 
    fgets(linea, 100, fichero);  // Aqui cogemos ---------------

    for(int i=0; i<numeroVariables; i++){

        char nombreVariable[20]="";

        fgets(linea, 100, fichero);
        strcpy(nombreVariable, linea);
        Trim(nombreVariable);

        fgets(linea, 100, fichero);
        TLISTA *auxiliarLista = charToList(linea, NULL, " \n");

        // printf("Nombre de la Variable: %s\n", nombreVariable);
        // verLista(auxiliarLista);
        // printf("El numero de elementos de la lista es: %d\n", auxiliarLista->n);

        fgets(linea, 100, fichero);

        TVAR *auxiliarVariable = crearVariable(nombreVariable, auxiliarLista);

        laGranVariable =  insertaUltimaVariable(laGranVariable, auxiliarVariable);

    }

    workspace->var1 = laGranVariable;

    //imprimirTVAR(laGranVariable);

    return workspace;
}

//Quita los espacios en blanco de las cadenas por delante y por detras
void Trim(char *cad){
    int c, i=0, j, n = strlen(cad);

    if(cad == NULL || n < 1){
        return;
    }
    
    n--;

    while(n>0 && ((c=cad[n]) == ' ' || c=='\n')){ 
        n--;
    }

    cad[n+1] = '\0';

    while(i<=n && ((c=cad[i]) == ' ' || c == '\n')){ 
        i++;
    }

    for(j=0; j<=n-i+1; j++){
        cad[j] = cad[j+i];
    }
    
}

//Liberar listas
TLISTA *liberarListas(TLISTA *lista){ //le pasamos la lista que queremos eliminar

    //como lo que vamos a hacer es liberar TNUMS y TLISTAS necesitare dos auxiliares *
    TLISTA *auxiliarLista = lista;

    if(lista->n == 0){ //significa que dentro no hay ningun tnum
        
        free(lista);
        return NULL;
    }

    //caso de que la lista no esté vacia
    for(int i=0; i<auxiliarLista->n; i++){

        //aqui dentro es donde vamos a tener que liberar los tnums
        TNUM * auxiliarNUM = auxiliarLista->primero; //auxiliarNUM es lo que vamos a borrar
        auxiliarLista->primero = auxiliarNUM->siguiente;

    
        // Recolocamos los punteros
        auxiliarNUM->anterior = NULL;
        auxiliarNUM->siguiente = NULL; 

        // Actualizamos el puntero de auxiliarLista->primero
        if(i != auxiliarLista->n-1 ){ //caso de que no sea el ultimo
            auxiliarLista->primero->anterior = NULL;
        }
        

        free(auxiliarNUM);

    }

    auxiliarLista->primero = NULL;
    auxiliarLista->ultimo = NULL;

    free(lista);

    return NULL;
}

//le pasamos la gran variable
TVAR *liberarVariables(TVAR *laGranVariable){


    if(laGranVariable == NULL){ //caso de que este vacio
        free(laGranVariable);
        return NULL;
    }

    while(laGranVariable != NULL){ 

        TVAR *auxiliarVariable = laGranVariable;
        
        laGranVariable = laGranVariable->siguiente; //ahora la gran variable apunta a la segunda posicion

        // limpiamos la TLISTA de la variable (TVAR)
        auxiliarVariable->valor = liberarListas(auxiliarVariable->valor);

        //Recolocamos los punteros
        auxiliarVariable->anterior = NULL;
        auxiliarVariable->siguiente = NULL;

        if(laGranVariable != NULL){
            laGranVariable->anterior = NULL; //la que estaba en segunda posicion
        }

        free(auxiliarVariable);

        auxiliarVariable = laGranVariable;

   }

    free(laGranVariable);

    return NULL;
}

//Sumar elementos lista
double Sum(TLISTA *lista){

    TNUM *numeros= lista->primero;
    double valor= 0;

    for(int i=0; i<lista->n; i++){

        valor = valor + numeros->valor;

        numeros = numeros->siguiente;
    }

    return valor;
}

//Funcion order
TLISTA *ordenarListaAscendente(TLISTA *lista){

    TLISTA *listaAux = crearLista();
    TNUM *numAux, *numAux2, *numTemp, *numLista;
    double valor;
    int decimales;

    if(lista->primero == NULL){
        return NULL;
    }

    TLISTA *AYUDA = crearDuplicadoLista(lista);

    while(AYUDA->primero != NULL){

        numAux = AYUDA->primero;
        valor = 9999;
        
        for(int i = 0; i<AYUDA->n; i++){

            if(numAux->valor < valor){

                valor = numAux->valor;
                decimales = numAux->decimales;

            }

            numAux = numAux->siguiente;

        }

        numTemp = crearListaNum(valor, decimales);

        if(listaAux->primero != NULL){

            numLista = listaAux->ultimo;
            numLista->siguiente = numTemp;
            numTemp->anterior = numLista;
            listaAux->ultimo = numTemp;
        
        }
        else{
            listaAux->primero = numTemp;
            listaAux->ultimo = numTemp;
        }

        listaAux->n = listaAux->n+1;

        eliminarElementoLista(AYUDA, valor);

    }
    
    return listaAux;

}

//Funcion order des
TLISTA *ordenarListaDescendente(TLISTA *lista){
    TLISTA *listaAux = crearLista();
    TNUM *numAux, *numAux2, *numTemp, *numLista;
    double valor;
    int decimales;

    if(lista->ultimo == NULL){
        return NULL;
    }

    TLISTA *AYUDA = crearDuplicadoLista(lista);

    while(AYUDA->ultimo != NULL){

        numAux = AYUDA->primero;
        valor = -9999;
        
        for(int i = 0; i<AYUDA->n; i++){

            if(numAux->valor > valor){

                valor = numAux->valor;
                decimales = numAux->decimales;

            }

            numAux = numAux->siguiente;

        }

        numTemp = crearListaNum(valor, decimales);

        if(listaAux->primero != NULL){

            numLista = listaAux->ultimo;
            numLista->siguiente = numTemp;
            numTemp->anterior = numLista;
            listaAux->ultimo = numTemp;
        
        }
        else{
            listaAux->primero = numTemp;
            listaAux->ultimo = numTemp;
        }

        listaAux->n = listaAux->n+1;

        eliminarElementoLista(AYUDA, valor);

    }
    
    return listaAux;
}

//
TLISTA *mapLista(TLISTA *lista, double n){ // 4 8 2 7

    TLISTA *listaAux = crearDuplicadoLista(lista);

    TNUM *numAux = listaAux->primero; 

    for(int i=0; i<listaAux->n; i++){ // i = i + 1

        numAux->valor = numAux->valor + n;
        numAux = numAux->siguiente;
    }

    return listaAux;

}

// x1 ? x2
TLISTA *funcionInterrogacion(TLISTA *lista, double n){

    TLISTA *auxiliar = lista;
    TNUM *numAux = auxiliar->primero;

    for(int i=0; i<auxiliar->n; i++){

        if( numAux->valor == n){
            //printf("Estamos dentro\n");
            eliminarElementoLista(auxiliar, n);
            return auxiliar; 
        }

        numAux = numAux->siguiente ;
    }

    auxiliar = anyadirElemntoLista(auxiliar, n);
    
    return auxiliar;

}

// Anyadir elementos
TLISTA *anyadirElemntoLista(TLISTA *lista, double n){
    
    TLISTA *auxiliar = lista;
    TNUM *numAux = auxiliar->ultimo;
    TNUM *numTemp = NULL;
    char aux[20];

    sprintf(aux, "%.11g", n);
    numTemp = crearListaNum(n, NumDecimales(aux)); //ya tenemos el juguete

    numAux->siguiente = numTemp;
    numTemp->anterior=numAux;
    
    auxiliar->ultimo=numTemp;

    TLISTA * duplicado = crearDuplicadoLista(auxiliar);

    // verLista(duplicado);

    return duplicado;
}

//Devuelvve PAR o IMPAR segun el nº de elementos de la lista
void parOImpar(TLISTA *lista){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    TLISTA *auxiliar = lista;

    if(lista->n % 2 == 0){
        SetConsoleTextAttribute(hConsole, 2);
        printf("PAR\n");
        SetConsoleTextAttribute(hConsole, 7);
    }
    else{
        SetConsoleTextAttribute(hConsole, 2);
        printf("IMPAR\n");
        SetConsoleTextAttribute(hConsole, 7);
    } 

}

TVAR *eliminarVariable(TVAR *laGranVariable, char *cad){

    TVAR *variableEliminar = laGranVariable;

    TVAR *auxiliarVariableSig, *auxiliarVariableAnt;

    while(variableEliminar != NULL){
        
        if(strcmp(cad, variableEliminar->nombre) == 0){

            
            auxiliarVariableSig = variableEliminar->siguiente; 
            auxiliarVariableAnt = variableEliminar->anterior;


            if(auxiliarVariableSig == NULL && auxiliarVariableAnt == NULL){ //UNICO ELEMENTO
                laGranVariable = NULL;
            }
            else if(auxiliarVariableSig != NULL && auxiliarVariableAnt == NULL){ //Es el PRIMERO
                laGranVariable = auxiliarVariableSig;
                auxiliarVariableSig->anterior = NULL;
            }
            else if(auxiliarVariableSig == NULL && auxiliarVariableAnt != NULL){ //Es el ULTIMO
                auxiliarVariableAnt->siguiente = NULL;
            }
            else{ //ESTA EN MEDIO
                auxiliarVariableSig->anterior = auxiliarVariableAnt;
                auxiliarVariableAnt->siguiente = auxiliarVariableSig;
            }

            //Recolocamos los punteros
            variableEliminar->anterior = NULL;
            variableEliminar->siguiente = NULL;

            liberarListas(variableEliminar->valor);

            free(variableEliminar);
            return laGranVariable;

        }
        variableEliminar = variableEliminar->siguiente;
    }
    return laGranVariable;
}

//Comprueba que exista en la carpeta un fichero con este nombre, 0 MAL, 1 BN.
int comprobarFichero(char *cadena){

    DIR *d; 
    struct dirent *f;
    int j = 0;
    char aux[100];

    d = opendir(".");
    if(d == NULL){
        printf("error\n");
        return 0;
    }

    strcpy(aux, cadena);
    strcat(aux, ".txt");
    
    while((f = readdir(d)) != NULL){

        printf("%s\n", f->d_name);
        if(strcmp(f->d_name, aux) == 0){
            printf("archivo ya existente\n");
            return 0;
        }

    }
    closedir(d);
    return 1;
}

