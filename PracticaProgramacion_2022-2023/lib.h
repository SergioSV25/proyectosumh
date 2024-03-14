#ifndef lib_H
#define lib_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
//--------------------Definicion de estructuras del enunciado------------------------//
typedef struct Numero
{
    double valor;
    int decimales;
    struct Numero *siguiente, *anterior;
}TNUM;

typedef struct 
{
    int n;
    TNUM *primero, *ultimo;
}TLISTA;

typedef struct Var
{
    char nombre[20];
    TLISTA *valor;
    struct Var *siguiente, *anterior;
}TVAR;

typedef struct
{
    int n;
    TVAR *var1;
}TVARS;


//-------------------------Funciones de la practica----------------------------------//
void hola();
char* MiStrTok(char *cad1, char *sep, int corchetes);
int validarCorchetes(char * cadena);
int expansionCorchetes(char *separadores, char * comtok, TLISTA *listaaux);
int NumDecimales(char *cad);
TNUM *crearListaNum(double auxNumero, int decimales);
TLISTA *crearLista();
int decimalValidar(char *cad);
void verLista(TLISTA *lista);
int listaOvariable(char *cad);
TLISTA *charToList(char *cadena, TVAR *laGranVariable, char *separadores);
TVAR *crearVariable(char *nombreVariable, TLISTA *lista);
TVAR *buscarVariable(TVAR *laGranVariable, char *nombreVariable);
TLISTA * operar(char **cadena, TVAR *laGranVariable, int num_arg, char *separadores);
TVAR *insertaUltimaVariable(TVAR *LagranVariable, TVAR *variableAsignar);
void imprimirTVAR(TVAR *LaGranLista);
int contarCaracteres(char **cadena, char *caracter);
TLISTA *CombinacionListas(TLISTA *lista1, TLISTA *lista2);
TLISTA *restaLista(TLISTA *lista1, TLISTA *lista2);
TLISTA *crearDuplicadoLista(TLISTA *lista);
void eliminarElementoLista(TLISTA *listaDuplicada, double valor);
int contenidaLista(TLISTA *L2, TLISTA *L1);
int enteroValidar(char *cad);
TLISTA *copiarNlistaPrimeras(TLISTA *lista, int n);
TLISTA *copiarNlistaUltimas(TLISTA *lista, int n);
TLISTA *copiarListaInversa(TLISTA *lista);
void laGranVista(TVAR *laGranVariable);
TVARS *crearWorkspace(TVARS *workspace);
int contadorVariables(TVAR *LaGranVariable);
void save(char *nombre, TVARS *workspace);
int validarNombre(char *nombre);
TVARS *load(char *nombre);
void Trim(char *cad);
TLISTA *liberarListas(TLISTA *lista);
TVAR *liberarVariables(TVAR *laGranVariable);
double Sum(TLISTA *lista);
TLISTA *ordenarListaAscendente(TLISTA *lista);
TLISTA *ordenarListaDescendente(TLISTA *lista);
TLISTA *mapLista(TLISTA *lista, double n);
TLISTA *funcionInterrogacion(TLISTA *lista, double n);
TLISTA *anyadirElemntoLista(TLISTA *lista, double n);

//Empiezan mis propias funciones
void parOImpar(TLISTA *lista);
TVAR *eliminarVariable(TVAR *laGranVariable, char *cad);
int comprobarFichero(char *cadena);
#endif