#include "lexer.h"

FILE *archivo;

int main (int argc,char* args[]){
        Lista * l;

        /*********************** ANALIZADOR LEXICO ********************/

        if ((archivo=fopen("fuente.txt","rt"))){
            l = lexer(archivo);
        }
        else{
            printf("Error: no se pudo abrir el archivo\n");
        }
        fclose(archivo);

        if(is_invalid_token() == 1){ //1 es true
            printf("Error Lexico: Existe token no valido\n");

        }else{
        /*********************** ANALIZADOR SINTACTICO ********************/
        visualizacion(l);
        printf("No hubo errores lexicos.-> Se procedera a analizar la sintaxis\n");
        }

    return 0;
}
