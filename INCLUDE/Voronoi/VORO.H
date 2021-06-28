#ifndef _VORO
#define _VORO

/*******************************************************************
 * Esta biblioteca tiene todo lo desarrollado con respecto a voronoi
 * Work in progress
 * *****************************************************************/

/* biblioteca base de elementos geometricos y herramientas fundamentales */
#include <voronoi\geom.h>
#include <math.h>

/* dibuja el diagrama de voronoi con fuerza bruta */
/* muy malo, ademas de impreciso */
void BruteVoronoi(Vertices *v);

#include <voronoi\voro.c>

#endif
