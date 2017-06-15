/*
 *  Analizador Léxico	
 *  Analizador léxico que se utilizará junto al analizador sintaxico y el traductor.
 *	
 *  Reconoce los componentes lexicos válidos para el lenguaje JSON
 *	
 */

/*********** Inclusión de cabecera **************/
#include "lexer.h"


/************* Variables globales **************/

token t;				// token global para recibir componentes del Analizador Lexico

// variables para el analizador lexico

FILE *archivo;			// Fuente pascal
char buff[2*TAMBUFF];	// Buffer para lectura de archivo fuente
char id[TAMLEX];		// Utilizado por el analizador lexico
int numLinea=1;			// Numero de Linea

/**************** Funciones **********************/


// Rutinas del analizador lexico

void error(const char* mensaje)
{
    printf("Lin %d: Error Lexico. %s. ",numLinea,mensaje);	
}


void sigLex()
{
    int i=0;
    char c=0;
    int acepto=0;
    int estado=0;
    char msg[41];

    while((c=fgetc(archivo))!=EOF)
    {
        if (c==' ' || c=='\t'){

            continue;	//eliminar espacios en blanco
        }
        else if(c=='\t')
        {
            //incrementar el numero de linea
            continue;
        }
        else if(c=='\n')
        {
            //incrementar el numero de linea
            numLinea++;
            continue;
        }
        else if (c==':')
        {
            t.compLex=DOS_PUNTOS;
            t.comp="DOS_PUNTOS";
			t.lexema=":";
            break;
        }
        else if (c=='{')
        {
            t.compLex=L_LLAVE;
            t.comp="L_LLAVE";
			t.lexema="{";
            break;
        }
        else if (c=='}')
        {
            t.compLex=R_LLAVE;
            t.comp="R_LLAVE";
			t.lexema="}";
            break;
        }
        else if (c=='[')
        {
            t.compLex=L_CORCHETE;
            t.comp="L_CORCHETE";
			t.lexema="[";
            break;
        }
        else if (c==']')
        {
            t.compLex=R_CORCHETE;
            t.comp="R_CORCHETE";
			t.lexema="]";
            break;
        }
        else if (c==',')
        {
            t.compLex=COMA;
            t.comp="COMA";
			t.lexema=",";
            break;
        }
        else if (c == '"')
        {
            //es un STRING /*VERIFICA QUE SE INGRESA UN STRING VALIDO*/
            c=fgetc(archivo);
			i = 0;
			id[i]= c; 
            while(c!=EOF){
                if(c == '"'){
					id[i] = '\0';
                    t.compLex=STRING;
					t.comp="STRING";
					t.lexema = id;
                    break;
                }else if(i>=TAMLEX){
					ungetc(c, archivo);
				}
				else{
                    c=fgetc(archivo);
					id[++i] = c;
                }
            }
            if (c==EOF)
                error("Se llego al fin sin cerrar el String");
			else if(i>=TAMLEX){
				error("Longitud de Identificador excede tamaño de buffer");
			}
            break;
        }
        else if (isdigit(c))
        {
            //es un numero

            i=0;
            estado=0;
            acepto=0;
            id[i]=c;

            while(!acepto)
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
                            sprintf(msg,"No se esperaba '%c'",c);
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
                            sprintf(msg,"No se esperaba '%c'",c);
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
                            sprintf(msg,"No se esperaba '%c'",c);
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
							acepto=1;
							t.compLex=NUMBER;
							t.comp="NUMBER";
							t.lexema = id;
                        break;
                    case -1:
                        if (c==EOF)
                            error("No se esperaba el fin de archivo");
                        else
                            error(msg);
                    }
                }
            break;
        }
        else if (isalpha(c)) {
            i = 0;
            do{
                id[i] = c;
                i++;
                c = fgetc(archivo);
            }while (isalpha(c));
            id[i]='\0';
            if (c!=EOF)
                ungetc(c,archivo);
            if(strcmp(id, "true") == 0 || strcmp(id, "TRUE") == 0){
                t.compLex=PR_TRUE;
                t.comp="PR_TRUE";
				t.lexema = "true";
                break;
            }
            else if (strcmp(id, "false") == 0 || strcmp(id, "FALSE") == 0){
                t.compLex=PR_FALSE;
                t.comp="PR_FALSE";
				t.lexema = "false";
                break;
            }
            else if(strcmp(id, "null") == 0 || strcmp(id, "NULL") == 0){
                t.compLex=PR_NULL;
                t.comp="PR_NULL";
				t.lexema = "null";
                break;
            }
            else{
                sprintf(msg,"No se esperaba '%s'",id);
                error(msg);				
            }
        }
        else {
            sprintf(msg,"No se esperaba '%c'",c);
            error(msg);
        }
    }
    if (c==EOF)
    {
        t.compLex=EOF;
        t.comp="EOF";
    }
}

/*int main(int argc,char* args[])
{
    // inicializar analizador lexico

    if(argc > 1)
    {
        if (!(archivo=fopen(args[1],"rt")))
        {
            printf("Archivo no encontrado.\n");
            exit(1);
        }
        while (t.comp!="EOF"){
            sigLex();
            printf("%s ",t.comp); 
        }
        fclose(archivo);
    }else{
        printf("Debe pasar como parametro el path al archivo fuente.\n");
        exit(1);
    }

    printf("\n");

    return 0;
}*/
