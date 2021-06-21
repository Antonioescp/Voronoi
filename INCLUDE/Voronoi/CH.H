#ifndef _CONVEXHULL
#define _CONVEXHULL

#include <voronoi\geom.h>

/* ordena los vertices por angulo polar apartir del punto
menor con respecto a Y y con respecto a X de haber n puntos iguales
menores en Y (LTL), se utiliza en el escaneo de Graham */
void OrdenarPorAnguloPolar(Vertices *v);

/*  determina los puntos extremos con pruebas in-triangle
    este algoritmo es muy lento, tiene una complejidad de O(n^4) */
void PuntosExtremosLento(Vertices *v, Modo modo, int retraso);
/* determina la envolvente convexa buscando los lados extremos, en lugar de puntos,
este algoritmo es O(n^3) */
void LadosExtremos(Vertices *v, Modo modo, int retraso);
/* utiliza el algoritmo de la marcha de jarvis O(n^2) o envoltura de regalo */
void Jarvis(Vertices *v, Modo modo, int retraso);
/* utiliza el algoritmo de graham para dibujar la envolvente convexa O(n log n) */
void Graham(Vertices *v);

#include <voronoi\ch.c>

#endif
