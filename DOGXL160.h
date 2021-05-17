/*
 * Autor Carlos Izquierdo Gómez
 *
 * Esta libreria se desarrollo como complemento al proyecto
 * TEO de la universidad Carlos 3 de Leganes
 *
 * Ultima revisión 17/05/2021
 */

#include "mbed.h"

void seleccionarColumna(int16_t columna);
/*
    FUNCTION: Posiciona el cursor en la columna seleccionada 
     
    INPUT:  columna     (numero de la columna en la que queremos posicionar el cursor).
    OUTPUT: 
    RETURN: No devuelve nada.
*/

void seleccionarPagina(int16_t pagina);
/*
    FUNCTION: Posiciona el cursor en la pagina seleccionada 
     
    INPUT:  pagina     (numero de la pagina en la que queremos posicionar el cursor).
    OUTPUT: 
    RETURN: No devuelve nada.
*/

void limpiarPantalla(void);
/*
    FUNCTION: Borra todo el contenido de la pantalla
    
        
    INPUT:  
    OUTPUT: 
    RETURN: No devuelve nada.
*/

void limpiarFilasNumeros(int16_t columnaI,int16_t columnaF,int16_t pagina);

/*
    FUNCTION: Elimina las 4 paginas que ocupan un numero 
     
    INPUT:  pagina     (numero de la pagina a partir de la cual quiero eliminar).
            columnaI     (numero de la columna en la que queremos empezar a eliminar los caracteres).
            columnaF     (numero de la columna en la que queremos empezar a eliminar los caracteres).
    OUTPUT: 
    RETURN: 
*/


void limpiarFilasLetras(int16_t columnaI,int16_t columnaF,int16_t pagina);
/*
   FUNCTION: Elimina las 5 paginas que ocupa una cadena de caracteres
     
    INPUT:  pagina     (numero de la pagina a partir de la cual quiero eliminar).
            columnaI     (numero de la columna en la que queremos empezar a eliminar los caracteres).
            columnaF     (numero de la columna en la que queremos empezar a eliminar los caracteres).
    OUTPUT: 
    RETURN: 
*/

void inicializacionPantalla(void);
/*
    FUNCTION: Inicializa los parametros de la pantalla 
        
    INPUT:  
    OUTPUT: 
    RETURN: No devuelve nada.
*/

int imprimirTexto(int16_t columna, int16_t pagina, char text[]);
/*
    FUNCTION: Imprime el texto a partir de la pagina y la columna seleccionada
        
    INPUT:  pagina     (numero de la pagina a partir de la cual quiero eliminar).
            columna     (numero de la columna en la que queremos posicionar el cursor).
    OUTPUT: 
    RETURN: entero con la ultima posicion 
*/

int imprimirNumero(int16_t columna, int16_t pagina, float valor, uint16_t decimales);
/*
    FUNCTION: Lee un entero y compara con el valor anterior para detectar 
    flancos de subida BIT a BIT. Ejemplo:
        *numant =   0b00000110 (6)
        num =       0b00001100 (12)
        return =    0b00001000 (10)
        
    INPUT:  num     (variable de la que detectar flanco)
    OUTPUT: numant  (puntero a la variable que almacena el valor ant de num)
    RETURN: Entero con los bits a uno correspondientes a las posiciones en las
    que se detecta un flanco de subida.
*/
