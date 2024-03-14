#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include "lib.h"


//gcc lib.c main.c -o main.exe


int main(int argc, char *argv[])
{

    // Color Prompt
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Variables globales
    char prompt[100] = "*";
    char command[100];
    char separadores[8] = " \t\n";
    char *comtok[100];

    int num_arg;

    TVARS *workspace = NULL;
    TVAR *LaGranVariable = NULL;
    TLISTA *lista = NULL;
    TNUM *elemento = NULL;

    hola();

    workspace = crearWorkspace(workspace);

    //Empieza el programa
    while(1){

        printf("<%s>:", prompt);
        gets(command); // recogemos lo que el usuario escriba por pantalla

        //validar que lo que nos han escrito sea correcto
        if(validarCorchetes(command) == 0){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);
            continue;
        }

        //tokenizar (trocear command) segun los separadores
        //Esta parte mete en comtok las palabras sueltas
        num_arg = 0;
        comtok[num_arg] = MiStrTok(command, separadores, 1);
        
        // printf("comtok[%d]: %s\n", num_arg, comtok[num_arg]);

        num_arg++;
        while((comtok[num_arg] = MiStrTok(NULL, separadores, 1)) != NULL){
            // printf("comtok[%d]: %s\n", num_arg, comtok[num_arg]);
            num_arg++;
        }
        if(comtok[0] == NULL){
            continue;
        }

        if(strcmp(comtok[0], "exit") == 0 && num_arg == 1){
            
            //Liberamos la memoria de laGranVariable
            //las variables globales que estamos usando aqui son el workspace (que contiene a la granvariable) y laGranVariable, asi que hay que borrar esas dos cosas

            //imprimirTVAR(LaGranVariable);
            
            LaGranVariable = liberarVariables(LaGranVariable);


            if(workspace->n != 0){

                workspace->var1 = liberarVariables(workspace->var1);

            }
            
            //Liberamos la memoria del workspace
            free(workspace);
            workspace = NULL;
           
            SetConsoleTextAttribute(hConsole, 2);
            printf("Bye, Bye\n");
            SetConsoleTextAttribute(hConsole, 7);
            return 0;
        }
        else if(strcmp(comtok[0], "isIn") == 0){ // isIn 2 [2 3 4] TRUE
            if (num_arg != 3){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            //printf("%s\n", comtok[1]);
           
            if ((enteroValidar(comtok[1]) == 0) ){
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error el segundo token no es valido\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TLISTA *listaAux = charToList(comtok[1],LaGranVariable,separadores);

            if(listaAux == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TLISTA *listaAux2 = charToList(comtok[2],LaGranVariable,separadores);

            if(listaAux2 == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            // Realizamos la misma operación que en el caso de #
            if(contenidaLista(listaAux2,listaAux) == 1){
                SetConsoleTextAttribute(hConsole, 2);
                printf("TRUE\n");
                SetConsoleTextAttribute(hConsole, 7);
            } else {
                SetConsoleTextAttribute(hConsole, 2);
                printf("FALSE\n");
                SetConsoleTextAttribute(hConsole, 7);
            }


        }
        else if(strcmp(comtok[0], "vars") == 0){

            if(num_arg != 1){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            laGranVista(LaGranVariable);

        }
        else if(strcmp(comtok[0], "save") == 0){

            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            workspace->n = contadorVariables(LaGranVariable);
            //printf("Numero de variables en el workspace: %d\n", workspace->n);
            workspace->var1 = LaGranVariable;
            //imprimirTVAR(workspace->var1);

            save(comtok[1], workspace);

        }
        else if(strcmp(comtok[0], "load") == 0){

            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            // if(validarNombre(comtok[1]) == 0){
            //     SetConsoleTextAttribute(hConsole, 4);
            //     printf("ERROR\n");
            //     SetConsoleTextAttribute(hConsole, 7);
            //     continue;
            // }

            workspace = load(comtok[1]);

            if(workspace == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            LaGranVariable = workspace->var1;
        }

        else if(strcmp(comtok[0], "sum") == 0){

            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TLISTA *auxiliarSuma;
            auxiliarSuma = charToList(comtok[1], LaGranVariable, separadores);

            if (auxiliarSuma == NULL){
                continue;
            }
            
            double valorSum;
            valorSum=Sum(auxiliarSuma);
            SetConsoleTextAttribute(hConsole, 2);
            printf("%.11g\n", valorSum);
            SetConsoleTextAttribute(hConsole, 7);

        }

        else if(num_arg>1 && strcmp(comtok[1], "=") == 0){ // a = [1 2 3]    a = b     a = [1] + [2]

            if(listaOvariable(comtok[0]) != 0){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            if(validarNombre(comtok[0]) == 0){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TVAR* variableAsignar = buscarVariable(LaGranVariable, comtok[0]);

            int cortafuegos = 0;

            if(variableAsignar == NULL){
               variableAsignar = crearVariable(comtok[0], NULL);
               cortafuegos = 2;
            }

            // for(int i = 2; i < num_arg; i++){
            //     printf("comtok[2]: %s\n", comtok[i]);
            // }

            
            TLISTA *listaValor = operar(&comtok[2], LaGranVariable, num_arg-2, separadores);

            verLista(listaValor);

            if(listaValor == NULL){
                continue;
            }

            variableAsignar->valor = listaValor;

            // verLista(variableAsignar->valor);

            if(cortafuegos == 2){
                LaGranVariable = insertaUltimaVariable(LaGranVariable, variableAsignar);
            }
        
            // imprimirTVAR(LaGranVariable);      
            
        }
        else if(num_arg>1 && strcmp(comtok[1], "#") == 0 && num_arg == 3){ // [1 2 3] # [1 2 3 4] --> TRUE    a # [1 2 3]

            TLISTA *lista1 = crearLista();
            TLISTA *lista2 = crearLista();

            lista1 = charToList(comtok[0], LaGranVariable, separadores);

            if(lista1 == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            lista2 = charToList(comtok[2], LaGranVariable, separadores);

            if(lista2 == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            if(contenidaLista(lista2, lista1) == 1){
                SetConsoleTextAttribute(hConsole, 2);
                printf("TRUE\n");
                SetConsoleTextAttribute(hConsole, 7);
            }
            else{
                SetConsoleTextAttribute(hConsole, 2);
                printf("FALSE\n");
                SetConsoleTextAttribute(hConsole, 7);
            }
        }
        else if(strcmp(comtok[0], "parOimpar") == 0){

            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            if(listaOvariable(comtok[1]) == 1){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TLISTA *listaAux = charToList(comtok[1],LaGranVariable,separadores);
            parOImpar(listaAux);

        }

        else if (strcmp(comtok[0], "delete") == 0){

            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TVAR *variableAsignar = buscarVariable(LaGranVariable,comtok[1]);
            if(variableAsignar == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            LaGranVariable = eliminarVariable(LaGranVariable, variableAsignar->nombre);
        }
        else if (strcmp(comtok[0], "update")==0){ 
              
              if(num_arg != 3){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            TVAR *variableAsignar = buscarVariable(LaGranVariable,comtok[1]);
            if(variableAsignar == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            strcpy(variableAsignar->nombre, comtok[2]);
        }

        else if(strcmp(comtok[0], "vaciar") == 0){
            
            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TVAR *variableAsignar = buscarVariable(LaGranVariable,comtok[1]);

            if(variableAsignar == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            // limpiamos la TLISTA de la variable (TVAR)
            variableAsignar->valor = liberarListas(variableAsignar->valor);

            variableAsignar->valor = crearLista();

        }

        else if(strcmp(comtok[0], "import") == 0){
            if(num_arg != 4){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TVARS *workspaceAuxiliar;
            TVARS *nuevoWorkspace;
            TVARS *tercerWorkspace;

            nuevoWorkspace = load(comtok[1]);
            
            tercerWorkspace = nuevoWorkspace;

            if(nuevoWorkspace == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            // imprimirTVAR(nuevoWorkspace->var1);

            workspaceAuxiliar = load(comtok[2]);

            if(workspaceAuxiliar == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            //imprimirTVAR(workspaceAuxiliar->var1);

            TVAR *variableSiguiente = nuevoWorkspace->var1;
            TVAR *variableAnterior = workspaceAuxiliar->var1;

            for(int i=0; i<nuevoWorkspace->n-1; i++){
                variableSiguiente = variableSiguiente->siguiente;
            }

            variableSiguiente->siguiente = variableAnterior;
            variableAnterior->anterior = variableSiguiente;

            tercerWorkspace->n = nuevoWorkspace->n + workspaceAuxiliar->n;

            imprimirTVAR(tercerWorkspace->var1);

            if(comprobarFichero(comtok[3]) == 1){
              save(comtok[3], tercerWorkspace);
            }
        }
        else{
            TLISTA *listaToPrint = operar(comtok, LaGranVariable, num_arg, separadores); //[1 : 6] - [1 5 9]     [1 2 3 4 5 6 1 5 9 ]
            if(listaToPrint != NULL){
                verLista(listaToPrint);
            }

        }

    }

    return 0;
}












