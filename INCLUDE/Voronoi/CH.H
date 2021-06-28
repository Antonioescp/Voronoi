#ifndef _CONVEXHULL
#define _CONVEXHULL

/*********************************************************************
 * esta biblioteca sirve para encontrar los puntos extremos 
 * y tambien para dibujar la envolvente convexa a traves de distintos
 * metodos
 * *******************************************************************  */

/* biblioteca base de elementos geometricos y herramientas fundamentales */
#include <voronoi\geom.h>

/*  determina los puntos extremos con pruebas in-triangle
    este algoritmo es muy lento, tiene una complejidad de O(n^4) */
void PuntosExtremosLento(Vertices *v, Modo modo, int retraso);
/* determina la envolvente convexa buscando los lados extremos, en lugar de puntos,
este algoritmo es O(n^3) */
void LadosExtremos(Vertices *v, Modo modo, int retraso);
/* utiliza el algoritmo de la marcha de jarvis O(n^2) o envoltura de regalo */
void JarvisMarch(Vertices *v, Modo modo, int retraso);
/* utiliza el algoritmo de graham para dibujar la envolvente convexa O(n^2) */
void GrahamScan(Vertices *v, Modo modo, int retraso);

#include <voronoi\ch.c>

#endif
