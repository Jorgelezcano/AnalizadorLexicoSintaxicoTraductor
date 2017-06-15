#include "lexer.h"

// Archivo de salida del proceso del lexer de json
FILE *salida;

char msj[5*TAMLEX];
char id[TAMLEX];
int numlinea = 1;
int cant_tokens_global= 0;

/*
 *Función que se utilizar para imprimir detalles de errores por línea
*/
void error_lexico(int numlinea,char* mensaje)
{
	printf("Lin: %d. Error Lexico: %s\n",numlinea,mensaje);
}
/*
 *Funcion para imprimir detalle lexico
*/
void detalle(int numlinea,char* compl,char* id)
{
    printf("linea: %d - componente lexico: %s - lexema: %s \n",numlinea,compl,id);
}

/*
 *Función que analizará cada token que posee el archivo que se pasa, atendiendo los tokens que pudiere
 *tener el lenguaje JSON.
*/
Lista *lexer(FILE* archivo){

	int i = 0;
	int estado,aceptado;
	char c = 0;
	salida = fopen("output_tokens.txt","w");

    Lista *lista;
    Elemento *actual;

    if ((lista = (Lista *) malloc (sizeof (Lista))) == NULL)
        return -1;

    actual = NULL;
    incializacion(lista);
    //==============================================================================
    //Empieza el ciclo while principal de la funcion lexer

	while((c=fgetc(archivo)) != EOF){
		//printf("linea actual: %d\n",numlinea);
		if ( c == '\t' || c==' '){
			fputc(' ',salida);
		}
        	else if(c == '\n'){
			fputc('\n',salida);
            		numlinea ++;
        	}
        //==============================================================================
        //comprobar si es uno de los caracteres [ ] { } : ; ,
		else if (c == '['){
            id[0] = c;
            id[1] = '\0';
			fputs("L_CORCHETE ",salida);
            detalle(numlinea,"L_CORCHETE",id);

            cant_tokens_global++;
            if(cant_tokens_global == 1)
                InsercionEnListaVacia(lista, L_CORCHETE, id, numlinea);
            else
                InsercionFinLista(lista, lista->fin, L_CORCHETE, id, numlinea);


		}
		else if(c == ']'){
            id[0] = c;
            id[1] = '\0';
			fputs("R_CORCHETE ",salida);
            detalle(numlinea,"R_CORCHETE",id);

            cant_tokens_global++;
            if(cant_tokens_global == 1)
                InsercionEnListaVacia(lista, R_CORCHETE, id, numlinea);
            else
                InsercionFinLista(lista, lista->fin, R_CORCHETE, id, numlinea);

		}
		else if(c == '{'){
            id[0] = c;
            id[1] = '\0';
			fputs("L_LLAVE ",salida);
            detalle(numlinea,"L_LLAVE",id);

            cant_tokens_global++;
            if(cant_tokens_global == 1)
                InsercionEnListaVacia(lista, L_LLAVE, id, numlinea);
            else
                InsercionFinLista(lista,lista->fin, L_LLAVE, id, numlinea);
		}
		else if(c == '}'){

            id[0] = c;
            id[1] = '\0';
			fputs("R_LLAVE ",salida);
            detalle(numlinea,"R_LLAVE",id);

            cant_tokens_global++;
            if(cant_tokens_global == 1)
                InsercionEnListaVacia(lista, R_LLAVE, id, numlinea);
            else
                InsercionFinLista(lista, lista->fin,R_LLAVE, id, numlinea);
		}
		else if(c == ','){

            id[0] = c;
            id[1] = '\0';
			fputs("COMA ",salida);
            detalle(numlinea,"COMA",id);

            cant_tokens_global++;
            if(cant_tokens_global == 1)
                InsercionEnListaVacia(lista, COMA, id, numlinea);
            else
                InsercionFinLista(lista, lista->fin,COMA, id, numlinea);
		}
		else if(c == ':'){

            id[0] = c;
            id[1] = '\0';
			fputs("DOS_PUNTOS ",salida);
            detalle(numlinea,"DOS_PUNTOS",id);

            cant_tokens_global++;
            if(cant_tokens_global == 1)
                InsercionEnListaVacia(lista, DOS_PUNTOS, id, numlinea);
            else
                InsercionFinLista(lista,lista->fin, DOS_PUNTOS, id, numlinea);
		}
        //==============================================================================
        //comprobar si es un String
		else if(c == '"'){
			ungetc(c,archivo);
			estado = 1;
			aceptado = 0;
            		i = 0;
			while(!aceptado){
				switch(estado){
					case 1:
						c = fgetc(archivo);
						if (c == '"'){
                            id[i++] = c;
							estado = 2;
						}
						break;
					case 2:
						c = fgetc(archivo);
						if (c == '"'){
                            id[i++] = c;
							estado = 3;
							//printf("cambio de estado 2 a 3\n");
						}
						else{
                            id[i++] = c;
							estado = 2;
						}
						break;
					case 3:
						aceptado = 1;
                        id[i] = '\0';
						break;
				}
			}
			if (aceptado){
                fputs("STRING ",salida);
                detalle(numlinea,"STRING",id);

                cant_tokens_global++;
            if(cant_tokens_global == 1)
                InsercionEnListaVacia(lista, STRING, id, numlinea);
            else
                InsercionFinLista(lista,lista->fin, STRING, id, numlinea);
            }

		}
        //==================================================
        //comprobar si es un true,TRUE,false,FALSE,null o NULL
        else if (isalpha(c))
		{
			i=0;
			do{
				id[i]=c;
				i++;
				c=fgetc(archivo);
				if (i>=TAMLEX)
					error_lexico(numlinea,"Longitud de Identificador excede tamaño de buffer");
			}while(isalpha(c) || isdigit(c));
			id[i]='\0';
			if (c!=EOF)
				ungetc(c,archivo);
			else
				c=0;
			if (strcmp(id,"true")==0 || strcmp(id,"TRUE")==0){
                fputs("PR_TRUE ",salida);
                detalle(numlinea,"PR_TRUE",id);

                cant_tokens_global++;
            if(cant_tokens_global == 1)
                InsercionEnListaVacia(lista, PR_TRUE, id, numlinea);
            else
                InsercionFinLista(lista,lista->fin, PR_TRUE, id, numlinea);
            }
            else if (strcmp(id,"false")==0 || strcmp(id,"FALSE")==0){
                fputs("PR_FALSE ",salida);
                detalle(numlinea,"PR_FALSE",id);

                cant_tokens_global++;
            if(cant_tokens_global == 1)
                InsercionEnListaVacia(lista, PR_FALSE, id, numlinea);
            else
                InsercionFinLista(lista,lista->fin, PR_FALSE, id, numlinea);
            }
            else if (strcmp(id,"null")==0 || strcmp(id,"NULL")==0){
                fputs("PR_NULL ",salida);
                detalle(numlinea,"PR_NULL",id);

                cant_tokens_global++;
            if(cant_tokens_global == 1)
                InsercionEnListaVacia(lista, PR_NULL, id, numlinea);
            else
                InsercionFinLista(lista,lista->fin, PR_NULL, id, numlinea);
            }
		}
        //==============================================================================
        //comprobar si es un numero
        else if (isdigit(c))
		{
				//es un numero
				i=0;
				estado=0;
				aceptado=0;
				id[i]=c;

				while(!aceptado)
				{
					switch(estado){
					case 0: //una secuencia netamente de digitos, puede ocurrir . o e
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=0;
						}
						else if(c=='.'){
							id[++i]=c;
							estado=1;
						}
						else if(tolower(c)=='e'){
							id[++i]=c;
							estado=3;
						}
						else{
							estado=6;
						}
						break;

					case 1://un punto, debe seguir un digito (caso especial de array, puede venir otro punto)
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=2;
						}
						else if(c=='.')
						{
							i--;
							fseek(archivo,-1,SEEK_CUR);
							estado=6;
						}
						else{
							sprintf("","No se esperaba '%c'",c);
							estado=-1;
						}
						break;
					case 2://la fraccion decimal, pueden seguir los digitos o e
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=2;
						}
						else if(tolower(c)=='e')
						{
							id[++i]=c;
							estado=3;
						}
						else
							estado=6;
						break;
					case 3://una e, puede seguir +, - o una secuencia de digitos
						c=fgetc(archivo);
						if (c=='+' || c=='-')
						{
							id[++i]=c;
							estado=4;
						}
						else if(isdigit(c))
						{
							id[++i]=c;
							estado=5;
						}
						else{
							sprintf("","No se esperaba '%c'",c);
							estado=-1;
						}
						break;
					case 4://necesariamente debe venir por lo menos un digito
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=5;
						}
						else{
							sprintf("","No se esperaba '%c'",c);
							estado=-1;
						}
						break;
					case 5://una secuencia de digitos correspondiente al exponente
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=5;
						}
						else{
							estado=6;
						}break;
					case 6://estado de aceptacion, devolver el caracter correspondiente a otro componente lexico
						if (c!=EOF)
							ungetc(c,archivo);
						else
							c=0;
                            id[++i]='\0';
                            aceptado=1;
                            fputs("NUMBER ",salida);
                            detalle(numlinea,"NUMBER",id);

                            cant_tokens_global++;
            if(cant_tokens_global == 1)
                InsercionEnListaVacia(lista, NUMBER, id, numlinea);
            else
                InsercionFinLista(lista,lista->fin, NUMBER, id, numlinea);
						break;
					case -1:
						if (c==EOF)
							error_lexico(numlinea,"No se esperaba el fin de archivo");
						else
							printf(" ");
						exit(1);
					}
				}
		}
	/************* Comprobar que no haya tokens No permitidos por el lenguaje JSON******************/
		else{
	 		error_lexico(numlinea,"Componente léxico no identificado");
			id[0] = c;
            id[1] = '\0';
			fputs("INVALID_TOKEN ",salida);
            detalle(numlinea,"INVALID_TOKEN",id);
		}
	}

    fclose(salida);
    return lista;
}

int get_cant_tokens(){
    return cant_tokens_global;
}


int is_invalid_token (){
    int val = 0; //0 es falso
    char c;
    char comp_lex[TAMLEX];
    int e=0; //cantidad de caracteres del token
    FILE *arch = fopen("output_tokens.txt","rt");

    if (arch != NULL){
        while((c=fgetc(arch)) != EOF){

            if (c == '\t' || c==' ' || c == '\n'){
                comp_lex[e] = '\0';
                //printf("Componente lexico: %s\n",comp_lex);
                if(strcmp(comp_lex, "INVALID_TOKEN") == 0){
                    val = 1; // 1 es verdadero
                }
                e = 0; //inicializa la cant de caracteres para otro token
        	}else{
                comp_lex[e] = c;
                e++;
        	}

        }
    }else{
        printf("Error en el Analizador Lexico: no se pudo abrir el archivo\n");
        val = 1;// 1 es verdadero
    }

    fclose(arch);

    return val;
}
//==============================================================================
/*
 *Funcion main principal que abre el archivo que se debe indicar al ejecutar el programa
 *Directamente se ejecuta la función LEXER() si existe el archivo.
*/
/*FILE *archivo;

int main(int argc, char* args[]){

	if ((archivo=fopen(args[1],"rt"))){
        lexer(archivo);
	}
	else{
		printf("Error no se pudo abrir el archivo\n");
	}
	fclose(archivo);
    return 0;
}*/
