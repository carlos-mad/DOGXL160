/*
 * Autor Carlos Izquierdo Gómez
 *
 * Esta libreria se desarrolló como complemento al proyecto
 * TEO de la universidad Carlos 3 de Leganés
 * Ultima revisión 17/05/2021
 */
 


int16_t  columnaActual=0;
char Mensaje[20];

int main(){

 inicializacionPantalla();

sprintf(Mensaje, "Hello"); //text to be printed on screen

columnaActual=imprimirTexto(2,10,Mensaje);  //We position ourselves in column 2 page 10 and print the string stored in the variable message

}
