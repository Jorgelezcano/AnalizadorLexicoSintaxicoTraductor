# Análisis Léxico- TRABAJO PRÁCTICO Nº 1 DE COMPILADORES
JORGE DANIEL LEZCANO CI 4696750 - JUNIO 2017
LEXER: Programa hecho en lenguaje C, el cual lee una fuente hecho en Json "fuente.txt",
detecta los tokens que hay por línea y va verificando a qué componente léxico pertenece cada token.
Guarda en un archivo "output_tokens.txt" a qué componente léxico pertenece e ir separado entre espacio.
Si hubiere algún token que no corresponde al leguaje JSON se guardará como un INVALID_TOKEN y
no se podrá continuar con el análisis Sintáctico.



PARA COMPILAR USAR: gcc main.c lexer.c lexer.h lista_enlazada.c -o jsonexe
PARA EJECUTAR USAR: ./jsonexe

OBS: al compilar aparecera un warning pero igual se ejecuta el proyecto.
