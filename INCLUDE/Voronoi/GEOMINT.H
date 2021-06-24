#ifndef _GEOMINT
#define _GEOMINT

/* esta biblioteca contiene estrategias para la deteccion de intersecciones
	geometricas */

/* incluimos todo lo anterior */
#include <voronoi\ch.h>

/* una coleccion de Segmentos */
typedef struct Segmentos
{
    int longitud;
    Segmento* elementos;
} Segmentos;

/* crea un segmento */
Segmento newVSegmento(Vertice *a, Vertice *b);
/* inicializa una coleccion de segmentos */
Segmentos newSegmentos(int longitud);
/* Agrega un segmento a la coleccion de segmentos */
void AgregarSegmento(Segmentos* segmentos, Segmento* segmento);
/* Elimina un segmento de la coleccion de segmentos */
void RemoverUltimoSegmento(Segmentos* s);
/* Borra una coleccion de segmentos */
void RemoverSegmentos(Segmentos* s);

/* herramientas de deteccion */

/* detecta si los segmentos s1(a, b) y s2(c, d) intersectan */
bool Intersectan(Vertice *a, Vertice *b, Vertice *c, Vertice *d);

/* detecta si hay segmentos intersectandose */
int BruteForceSID(Vertices *v);


#include <voronoi\geomint.c>

#endif
