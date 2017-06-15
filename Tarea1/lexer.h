/*********** Librerias utilizadas **************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

/*********** Componentes lexicos del JSON ********/
#define L_CORCHETE 256
#define R_CORCHETE 257
#define L_LLAVE 258
#define R_LLAVE 259
#define COMA 260
#define DOS_PUNTOS 261
#define STRING 262
#define NUMBER 263
#define PR_TRUE 264
#define PR_FALSE 265
#define PR_NULL 266

/********** Constantes ******************************/
#define EPSILON 267
#define TAMLEX 60
#define TAMBUFF 30
#define INVALID_TOKEN 268
#define CANT_TOKENS 11

/************* Estructuras ********************/

typedef struct ElementoLista{
    int comp_lexico;
    char lexema[TAMLEX];
    int num_linea;
    struct ElementoLista *siguiente;
}Elemento;

typedef struct ListaIdentificar{
    Elemento *inicio;
    Elemento *fin;
    int tamano;
}Lista;


/************* Prototipos ********************/
Lista *lexer(FILE*);
void error_lexico(int,char*);
int is_invalid_token ();
int get_cant_tokens();


/*inicializa la lista*/
void incializacion(Lista *lista);
/*En caso de error devuelve -1 sino 0*/
int InsercionEnListaVacia(Lista *lista, int comp_lexico, char lexema[TAMLEX], int num_linea);
/*insertar en inicio de la lista*/
int InsercionInicioLista(Lista *lista, int comp_lexico, char lexema[TAMLEX], int num_linea);
/*insertar en fin de la lista*/
int InsercionFinLista(Lista *lista, Elemento *actual, int comp_lexico, char lexema[TAMLEX], int num_linea);
/*insertar en X posicion de la lista*/
int InsercionLista (Lista *lista, int dato, int pos);
/*elimina un elemento al inicio de una lista*/
int EliminarInicio(Lista *lista);
/*suprimir un elemento de una X posicion*/
int EliminarEnLista(Lista *lista, int pos);
 /*muestra la lista entera*/
void visualizacion(Lista *lista);
/* destruir la lista */
void destruir(Lista * lista);
