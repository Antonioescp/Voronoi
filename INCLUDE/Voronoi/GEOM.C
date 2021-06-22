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

	v.stackIndice = -1;
	v.vacio = true;

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

/* vertices stack ds, para tratar a la coleccion de vertice como stack */
/* agrega un elemento al stack */
void StackVerticePush(Vertices *v, Vertice *e)
{
	v->stackIndice++;
	v->vacio = false;

	if(v->stackIndice < v->longitud)
		v->elementos[v->stackIndice] = *e;
	else
		AgregarVertice(v, e);
}

/* elimina un elemento del stack */
Vertice* StackVerticePop(Vertices *v)
{
	Vertice* popped = NULL;

	if(v->stackIndice > -1)
		popped = &v->elementos[v->stackIndice];

	v->stackIndice--;

	if(v->stackIndice <= -1)
	{
		v->stackIndice = -1;
		v->vacio = true;
	}
	
	return popped;
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

/* Dibuja un poligono dado los vertices */
void DibujarPoligonoDeStack(Vertices *v)
{
	int i;
	for(i = 0;i <= v->stackIndice - 1; i++)
	{
		DibujarVertice(&v->elementos[i], VCOLOR_PUNTO_EXTREMO);
		DibujarSegmentoApartirDeVertices(&v->elementos[i], &v->elementos[i + 1], VCOLOR_LADO_EXTREMO);
	}

	DibujarVertice(&v->elementos[i], VCOLOR_PUNTO_EXTREMO);
	DibujarSegmentoApartirDeVertices(&v->elementos[i], &v->elementos[0], VCOLOR_LADO_EXTREMO);
}

/* dibuja los puntos de un stack */
void DibujarPuntosDeStack(Vertices *v, enum COLORS color)
{
	int i;
	for(i = 0; i <= v->stackIndice; i++)
		DibujarVertice(&v->elementos[i], color);
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
	return !(Area2(a, b, c) > 0);
}

/* determina si el punto d se encuentra dentro de el triangulo abc */
bool EnTriangulo(Vertice* a, Vertice* b, Vertice* c, Vertice* d)
{
	bool abIzquierda = EnLaIzquierda(a, b, d);
	bool bcIzquierda = EnLaIzquierda(b, c, d);
	bool caIzquierda = EnLaIzquierda(c, a, d);

	return abIzquierda == bcIzquierda && bcIzquierda == caIzquierda;
}

/* Revisa que el lado tenga puntos solo en un medio plano y no en el otro */
void RevisarLado(Vertices *v, int a, int b, Modo modo, int retraso)
{
	int i;

	bool izquierdaVacio = true, derechaVacio = true;

	if(modo == descriptivo)
	{
		DibujarSegmentoApartirDeVertices(&v->elementos[a], &v->elementos[b], VCOLOR_LADO_ACTUAL);
	}

	for(i = 0; i < v->longitud; i++)
	{
		if(i != a && i != b)
		{
			if(modo == descriptivo)
			{
				DibujarVertice(&v->elementos[i], VCOLOR_PUNTO_ACTUAL);
				delay(retraso);
			}

			if(EnLaIzquierda(&v->elementos[a], &v->elementos[b], &v->elementos[i]))
				izquierdaVacio = false;
			else
				derechaVacio = false;
		}
	}

	if(modo == descriptivo)
	{
		DibujarSegmentoApartirDeVertices(&v->elementos[a], &v->elementos[b], getbkcolor());

		DibujarPuntosExtremos(v, VCOLOR_PUNTO_EXTREMO, VCOLOR_PUNTO_DESCARTADO);
	}

	if(izquierdaVacio || derechaVacio)
	{
		v->elementos[a].extremo = true;
		v->elementos[b].extremo = true;

		DibujarSegmentoApartirDeVertices(&v->elementos[a], &v->elementos[b], VCOLOR_LADO_EXTREMO);
	}
}

/* Busca el punto mas bajo y el mas a la izquierda de haber dos puntos mas bajos en y */
/* lowest-then-leftmost */
int LTL(Vertices* v)
{
    /* el primer extremo, tomaremos el primero momentaneamente */
    int ltl = 0;

    /* probando todos los puntos */
    int k;
    for(k = 1; k < v->longitud; k++)
    {
        /* mas bajo then mas a la izquierda */
        if(  v->elementos[k].y < v->elementos[ltl].y || 
            (v->elementos[k].y == v->elementos[ltl].y && v->elementos[k].x < v->elementos[ltl].x))
        {
            ltl = k;
        }
    }

    return ltl;
}
