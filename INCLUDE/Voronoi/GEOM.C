#include <Voronoi\geom.h>

/* inicializa un vertice */
Vertice newVertice(int x, int y)
{
	Vertice v;

	v.x = x;
	v.y = y;
	v.extremo = false;

	return v;
}

/* inicializa un segmento */
Segmento newSegmento(int ax, int ay, int bx, int by)
{
	Segmento s;

	s.a = newVertice(ax, ay);
	s.b = newVertice(bx, by);

	return s;
}

/* inicializa una coleccion de vertices de longitud elementos */
Vertices newVertices(int longitud)
{
	Vertices v;

	/* manteniendo longitud en el rango de numeros naturales */
	if(longitud > 0)
	{
		v.longitud = longitud;
		v.elementos = calloc(longitud, sizeof(Vertice));
	}
	else
	{
		v.longitud = 0;
		v.elementos = NULL;
	}

	return v;
}

/* Agrega un vertice a la coleccion de vertices */
void AgregarVertice(Vertices *vertices, Vertice *vertice)
{
	if(vertices->longitud <= 0)
	{
		vertices->longitud = 1;
		vertices->elementos = calloc(1, sizeof(Vertice));
	}
	else
	{
		vertices->longitud += 1;
		vertices->elementos = realloc(vertices->elementos, sizeof(Vertice) * vertices->longitud);
	}

	if(vertices->elementos == NULL)
		vertices->longitud = 0;
	else
		vertices->elementos[vertices->longitud - 1] = *vertice;
}

/* Elimina el ultimo vertice de la coleccion de vertices */
void RemoverUltimoVertice(Vertices *v)
{
	v->longitud -= 1;
	if(v->longitud == 0)
	{
		free(v->elementos);
		v->elementos = NULL;
	}
	else if(v->longitud > 0)
	{
		v->elementos = realloc(v->elementos, v->longitud * sizeof(Vertice));
	}
	else
	{
		v->longitud = 0;
		v->elementos = NULL;
	}
}

/* Borra una coleccion de vertices */
void RemoverVertices(Vertices *v)
{
	free(v->elementos);
	v->elementos = NULL;
	v->longitud = 0;
}

/* dibuja un vertice con su color */
void DibujarVertice(Vertice *v, enum COLORS color)
{
	setcolor(color);
	circle(v->x, v->y, RADIO_VERTICE);
	setfillstyle(SOLID_FILL, color);
	floodfill(v->x, v->y, color);
}

/* dibuja un segmento con su color */
void DibujarSegmento(Segmento *s, enum COLORS color)
{
	setcolor(color);
	line(s->a.x, s->a.y, s->b.x, s->b.y);
}

/* dibujar segmento dado un par de vertices */
void DibujarSegmentoApartirDeVertices(Vertice *v1, Vertice *v2, enum COLORS color)
{
	setcolor(color);
	line(v1->x, v1->y, v2->x, v2->y);
}

/* dibuja una coleccion de vertices con su color */
void DibujarVertices(Vertices *v, enum COLORS color)
{
	if(v->elementos != NULL)
	{
		int i;
		for(i = 0; i < v->longitud; i++)
		{
			DibujarVertice(&v->elementos[i], color);
		}
	}
}

/* Dibuja los puntos extremos una vez han sido definidos */
void DibujarPuntosExtremos(Vertices *v, enum COLORS color, enum COLORS colorNoExtremo)
{
	int i;
	for(i = 0; i < v->longitud; i++)
	{
		if(v->elementos[i].extremo)
			DibujarVertice(&v->elementos[i], color);
		else
			DibujarVertice(&v->elementos[i], colorNoExtremo);
	}
}

/* funciones geometricas */
/* calcula el doble del area de un triangulo utilizando la determinante */
float Area2(Vertice *a, Vertice *b, Vertice *c)
{
	float ax = a->x;
	float ay = a->y;
	float bx = b->x;
	float by = b->y;
	float cx = c->x;
	float cy = c->y;

	return 		ax * by - ay * bx
			+	bx * cy - by * cx
			+	cx * ay - cy * ax;
}

/* usa el signo de la determinante de un triangulo
para determinar si c esta a la izquierda del segmento ab */
bool EnLaIzquierda(Vertice *a, Vertice* b, Vertice *c)
{
	return (Area2(a, b, c) > 0);
}

/* determina si el punto d se encuentra dentro de el triangulo abc */
bool EnTriangulo(Vertice* a, Vertice* b, Vertice* c, Vertice* d)
{
	bool abIzquierda = EnLaIzquierda(a, b, d);
	bool bcIzquierda = EnLaIzquierda(b, c, d);
	bool caIzquierda = EnLaIzquierda(c, a, d);

	return abIzquierda == bcIzquierda && bcIzquierda == caIzquierda;
}

/*  determina los puntos extremos y dibuja la envolvente convexa,
    este algoritmo es muy lento, tiene una complejidad de O(n^4) */
void EnvolventeConvexaLento(Vertices *v, Modo modo)
{
	int a, b, c, d;

	/* en buena fe marcamos todos los puntos como extremos */
	for(a = 0; a < v->longitud; a++)
		v->elementos[a].extremo = true;
	
	/* ahora empezamos a iterar en los posibles triangulos */
	for(a = 0; a < v->longitud; a++)
	{
		for(b = a + 1; b < v->longitud; b++)
		{
			for(c = b + 1; c < v->longitud; c++)
			{
				for(d = 0; d < v->longitud; d++)
				{
					/* evitamos revisar los puntos que forman el triangulo actual o los
						puntos extremos */
					if(d == a || d == b || d == c || !v->elementos[d].extremo)
						continue;

					if(modo == descriptivo)
					{
						cleardevice();
						DibujarSegmentoApartirDeVertices(&v->elementos[a], &v->elementos[b], VCOLOR_TRIANGULO_ACTUAL);
						DibujarSegmentoApartirDeVertices(&v->elementos[b], &v->elementos[c], VCOLOR_TRIANGULO_ACTUAL);
						DibujarSegmentoApartirDeVertices(&v->elementos[c], &v->elementos[a], VCOLOR_TRIANGULO_ACTUAL);

						DibujarPuntosExtremos(v, VCOLOR_PUNTO_EXTREMO, VCOLOR_PUNTO_DESCARTADO);
					}

					/* revisamos si el punto d se encuentra en el triangulo abc, si lo esta, entonces
						no es extremo */
					if( EnTriangulo(&v->elementos[a], &v->elementos[b], &v->elementos[c], &v->elementos[d]) )
					{
						v->elementos[d].extremo = false;
					}
				}
			}
		}
	}
}
