#ifndef _TRNGLTN
#define _TRNGLTN

/* esta biblioteca contiene funciones para triangular */
/* biblioteca base de elementos geometricos */
#include <voronoi\geom.h>


/* obtiene las cadenas del poligono */
void DeterminarCadenas(Vertices *v);
/* prueba si un poligono es monotono */
bool EsMonotono(Vertices *v);
/* triangula un poligono monotono */
void TriangulacionMonotona(Vertices *v);

#include <voronoi\trngltn.c>

#endif
