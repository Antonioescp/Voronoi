#ifndef _MSGS
#define _MSGS

/********************************************************
 * Esta biblioteca es para mostrar mensajes en pantalla
 * Como mensajes o menu de opciones
 * ******************************************************/

#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>

/* para mas facil uso de arreglo de cadenas */
typedef char string[50];

/* dibuja un mensaje con su titulo, toma x y y como posicion inicial a partir de la cual se calcula x2 y y2 usando el ancho y alto
se toma un titulo para mostrar en la parte de arriba del mensaje y un contenido para mostrar en la parte interior del mensaje, se toma
el color de texto, el color de los bordes y el color de relleno */
void newMensaje(int x, int y, int ancho, int alto, char *titulo, char *contenido, short texto, short borde, short relleno);

/* lo mismo que el de arriba pero mas apropiado para un menu */
void newMenu(int x, int y, int ancho, int alto, char *titulo, string opciones[], short texto, short borde, short relleno, short cantidadDeOpciones);

#include <voronoi\msgs.c>

#endif