#ifndef _DTSTRCT
#define _DTSTRCT

/* en esta biblioteca estan las estructuras de datos utilizadas para
	llevar a cabo los distintos algoritmos
	*/

/* es un stack de puntos
	funciona algo distinto al convencional
	solo sirve para cuando vamos a copiar puntos
	de otra coleccion, utiliza los indice en lugar de
	elementos, maneja su propio indice para iterar en orden
	en los indices agregados */
typedef struct StackPunto
{
	int longitud;
	int* indices;
	Vertice* elementos;
	bool vacio;
} StackPunto;

/* crea un stack listo para copiar cualquier indice de
	la collecion de vertice dada, solamente usa un arreglo de
	int, usa menos memoria que copiar cada elemento de v */
StackPunto newStackPunto(Vertices *v);
/*	Agrega un indice al stack */
void StackPuntoPush(StackPunto *sp, int indice);
/* retorna el indice del elemento eliminado del stack */
int StackPuntoPop(StackPunto *sp);

#include <voronoi/dtstrct.c>

#endif