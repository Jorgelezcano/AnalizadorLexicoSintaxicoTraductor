#include "lexer.h"

 //Una lista enlazada sin ningun elemento se llama lista vacía.
//Su puntero inicial tiene el valor NULL
//Si un la lista es de 1 solo elemento, el campo siguiente apunta a NULL


/*Inicializar una lista*/
void incializacion(Lista *lista){
    lista->inicio = NULL;
    lista->fin= NULL;
    lista->tamano = 0;
}

/*Inserción en una lista vacía */
int InsercionEnListaVacia(Lista *lista, int comp_lexico, char lexema[TAMLEX], int num_linea){
    Elemento *nuevo_elemento;
    if((nuevo_elemento = (Elemento *)malloc(sizeof(Elemento)))==NULL)
        return -1;

    nuevo_elemento->comp_lexico= comp_lexico;
    strcpy(nuevo_elemento->lexema, lexema);
    nuevo_elemento->num_linea = num_linea;
    nuevo_elemento->siguiente = NULL;
    lista->inicio = nuevo_elemento;
    lista->fin = nuevo_elemento;
    lista->tamano++;
    return 0;
}

/*Insercion al inicio de una lista*/
int InsercionInicioLista(Lista *lista, int comp_lexico, char lexema[TAMLEX], int num_linea){
    Elemento *nuevo_elemento;
    if((nuevo_elemento = (Elemento *)malloc(sizeof(Elemento)))==NULL)
        return -1;

    nuevo_elemento->comp_lexico= comp_lexico;
    strcpy(nuevo_elemento->lexema, lexema);
    nuevo_elemento->num_linea = num_linea;

    nuevo_elemento->siguiente = lista->inicio;
    lista->inicio=nuevo_elemento;
    lista->tamano++;
    return 0;
}

//Insercion al final de la lista
int InsercionFinLista(Lista *lista, Elemento *actual, int comp_lexico, char lexema[TAMLEX], int num_linea){
    Elemento *nuevo_elemento;
    if((nuevo_elemento = (Elemento *)malloc(sizeof(Elemento)))==NULL)
        return -1;

    nuevo_elemento->comp_lexico= comp_lexico;
    strcpy(nuevo_elemento->lexema, lexema);
    nuevo_elemento->num_linea = num_linea;

    actual->siguiente = nuevo_elemento;
    nuevo_elemento->siguiente = NULL;

    lista->fin = nuevo_elemento;
    lista->tamano++;
    return 0;
}
/*
//Insercion en otra parte (X) de la lista
int InsercionLista(Lista *lista, char *dato, int pos){
    if(lista->tamano <2)
        return -1;
    if(pos<1 || pos >=1)
        return -1;
    Elemento *actual;
    Elemento *nuevo_elemento;
    int i;

    if((nuevo_elemento=(Elemento *)malloc(sizeof(Elemento)))==NULL)
            return -1;
    if((nuevo_elemento->dato=(char *)malloc(50*sizeof(char)))==NULL)
            return -1;

    actual = actual->siguiente;
    for(i = 1; i<pos; ++i )
            actual=actual->siguiente;
    if(actual->siguiente == NULL)
            return -1;
    strcpy(nuevo_elemento->dato, dato);

    nuevo_elemento->siguiente=actual->siguiente;
    actual->siguiente = nuevo_elemento;
    lista->tamano++;
    return 0;
}

//Eliminar en el inicio de la lista
int EliminarInicio(Lista *lista){
    if(lista->tamano == 0)
        return -1;
    Elemento *sup_elemento;
    sup_elemento = lista->inicio;
    lista->inicio=lista->inicio->siguiente;
    if(lista->tamano==1)
        lista->fin = NULL;
    free(sup_elemento->dato);
    free(sup_elemento);
    lista->tamano--;
    return 0;
}

//Eliminar en X posicion de la lista
int EliminarEnLista(Lista *lista, int pos){
    if(lista->tamano <= 1 ||  pos < 1 || pos >= lista->tamano)
        return -1;
    int i;
    Elemento *actual;
    Elemento *sup_elemento;
    actual = lista->inicio;
    for(i=1;i<pos;++i)
        actual = actual ->siguiente;
    sup_elemento = actual->siguiente;
    actual->siguiente = actual->siguiente->siguiente;
    if(actual->siguiente==NULL)
        lista->fin = actual;
    free(sup_elemento->dato);
    free(sup_elemento);
    lista->tamano--;
    return 0;
}
*/
//visualizar lista entera

void visualizacion(Lista *lista){
    Elemento *actual;
    actual = lista->inicio;
    while(actual != NULL){
            printf("Comp_lexico:%d - Lexema:%s - Linea:%d\n",actual->comp_lexico, actual->lexema, actual->num_linea);
            actual = actual->siguiente;
        }
}
/*
//destruir la lista
void destruir (Lista * lista){
  while (lista->tamano > 0)
    EliminarInicio (lista);
}*/

 /*
int menu (Lista *lista,int *k){
  int eleccion;
  printf("********** MENU **********\n");
  if (lista ->tamano == 0){
    printf ("1. agregar el primer elemento\n");
    printf ("2. Quitar\n");
  }else if(lista ->tamano == 1 || *k == 1){
    printf ("1. agregar al inicio de la lista\n");
    printf ("2. agregar al final de la lista\n");
    printf ("4. agregar al inicio de la lista\n");
    printf ("6. Destruir la lista\n");
    printf ("7. Quitar\n");
  }else {
    printf ("1. Agregar elemento al inicio de la lista\n");
    printf ("2. Agregar elemento al final de la lista\n");
    printf ("3. Agregar elemento después de la posición indicada\n");
    printf ("4. Eliminar el elemento del inicio de la lista\n");
    printf ("5. Eliminar el elemento después de la posición indicada\n");
    printf ("6. Destruir la lista\n");
    printf ("7. Quitar\n");
  }
  printf ("\n\nElegir: ");
  scanf ("%d", &eleccion);
  getchar();
  if(lista->tamano == 0 && eleccion == 2)
    eleccion = 7;
  return eleccion;
}*/
