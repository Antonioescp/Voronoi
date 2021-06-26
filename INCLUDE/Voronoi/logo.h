#ifndef _logo
#define _logo

typedef enum{
	negro,
	azul,
	verde,
	cian,
	rojo,
	magenta,
	marron,
	gris,
	gris2,
	azul2,
	verde2,
	cian2,
	rojo2,
	magenta2,
	amarillo,
	blanco
}colores;

void presentacion(void);
void circulo(void);
void poligono(void);
void relleno(void);
void internos(void);
void barraDeCarga(void);

#include "voronoi\logo.c"

#endif