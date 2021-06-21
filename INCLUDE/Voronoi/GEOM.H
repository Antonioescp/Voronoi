#ifndef _GEOM
#define _GEOM

#include <stdlib.h>
#include <graphics.h>
#include <dos.h>

/************************************************************************************
 * Esta biblioteca contiene los tipos de datos geometricos utilizados en el programa,
 * estos tipos representan ciertos elementos geometricos necesarios para
 * el diagrama de voronoi, tambien contiene funciones para el manejo de
 * las mismas estructuras.
 * ***********************************************************************************/

#define RADIO_VERTICE 2

#define VCOLOR_TRIANGULO_ACTUAL LIGHTBLUE
#define VCOLOR_PUNTO_DESCARTADO RED
#define VCOLOR_PUNTO_EXTREMO GREEN
#define VCOLOR_PUNTO_ACTUAL CYAN
#define VCOLOR_LADO_ACTUAL BROWN
#define VCOLOR_LADO_EXTREMO BROWN

#define true 1
#define false 0

/* en lugar de un enum para consumir menos memoria */
typedef unsigned char bool;

/* distintos modos de los algoritmos */
typedef enum Modo
{
    descriptivo,
    rapido
} Modo;

/* representa un vertice / punto / vector en el plano 
 * utiliza double para mayor presicion en calculos matematicos */
typedef struct Vertice{
	int x, y;
    bool extremo;
    int sucesor;
} Vertice;

/* Un segmento en el plano, con sus puntos / vertices a y b */
typedef struct Segmento{
	Vertice a, b;
} Segmento;

/* una coleccion de vertices */
typedef struct Vertices
{
    int longitud;
    Vertice *elementos;

    /* soporte para stack */
    int stackIndice;
    bool vacio;
} Vertices;

/* inicializa un vertice */
Vertice newVertice(int x, int y);
/* inicializa un segmento */
Segmento newSegmento(int ax, int ay, int bx, int by);
/* inicializa una coleccion de vertices */
Vertices newVertices(int longitud);
/* Agrega un vertice a la coleccion de vertices */
void AgregarVertice(Vertices *vertices, Vertice *vertice);
/* Elimina un vertice de la coleccion de vertices */
void RemoverUltimoVertice(Vertices *v);
/* Borra una coleccion de vertices */
void RemoverVertices(Vertices *v);

/* vertices stack ds, para tratar a la coleccion de vertice como stack */
/* agrega un elemento al stack */
void StackVerticePush(Vertices *v, Vertice *e);
/* elimina un elemento del stack */
Vertice* StackVerticePop(Vertices *v);

/* dibuja un vertice con su color */
void DibujarVertice(Vertice *v, enum COLORS color);
/* dibuja un segmento con su color */
void DibujarSegmento(Segmento *s, enum COLORS color);
/* dibujar segmento dado un par de vertices */
void DibujarSegmentoApartirDeVertices(Vertice *v1, Vertice *v2, enum COLORS color);
/* dibuja una coleccion de vertices con su color */
void DibujarVertices(Vertices *v, enum COLORS color);
/* Dibuja los puntos extremos una vez han sido definidos */
void DibujarPuntosExtremos(Vertices *v, enum COLORS color, enum COLORS colorNoExtremo);
/* Dibuja un poligono dado los vertices */
void DibujarPoligonoDeStack(Vertices *v);
/* dibuja los puntos de un stack */
void DibujarPuntosDeStack(Vertices *v, enum COLORS color);

/* funciones geometricas */
/* calcula el doble del area de un triangulo utilizando la determinante */
float Area2(Vertice *a, Vertice *b, Vertice *c);

/* usa el signo de la determinante de un triangulo
para determinar si c esta a la izquierda del segmento ab */
bool EnLaIzquierda(Vertice *a, Vertice* b, Vertice *c);
/* determina si el punto d se encuentra dentro de el triangulo abc */
bool EnTriangulo(Vertice* a, Vertice* b, Vertice* c, Vertice* d);
/* Revisa que el lado tenga puntos solo en un medio plano y no en el otro */
void RevisarLado(Vertices *v, int a, int b, Modo modo, int retraso);
/* Busca el punto mas bajo y el mas a la izquierda de haber dos puntos mas bajos en y */
/* lowest-then-leftmost */
int LTL(Vertices* v);

#include <Voronoi\geom.c>

#endif
