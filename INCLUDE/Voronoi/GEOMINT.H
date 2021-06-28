#ifndef _GEOMINT
#define _GEOMINT

/***************************************************************************
 * esta biblioteca contiene estrategias para la deteccion de intersecciones
 * geometricas
 * **************************************************************************/

/* biblioteca base de elementos geometricos y herramientas fundamentales */
#include <voronoi\geom.h>

/* detecta si los segmentos s1(a, b) y s2(c, d) intersectan */
bool Intersectan(Vertice *a, Vertice *b, Vertice *c, Vertice *d);
/* toma una coleccion de vertices, 
    calcula los segmentos y verifica si intersectan o no */
int BruteForceSID(Vertices *v);

#include <voronoi\geomint.c>

#endif
