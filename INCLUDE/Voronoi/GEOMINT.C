#include <voronoi\geomint.h>

/* crea un segmento */
Segmento newVSegmento(Vertice *a, Vertice *b)
{
	Segmento s;

	s.a = *a;
	s.b = *b;

	return s;
}

/* inicializa una coleccion de segmentos */
Segmentos newSegmentos(int longitud)
{
	Segmentos s;

	/* manteniendo longitud en el rango de numeros naturales */
	if(longitud > 0)
	{
		s.longitud = longitud;
		s.elementos = calloc(longitud, sizeof(Segmento));
	}
	else
	{
		s.longitud = 0;
		s.elementos = NULL;
	}

	return s;
}

/* Agrega un segmento a la coleccion de segmentos */
void AgregarSegmento(Segmentos* segmentos, Segmento* segmento)
{
	if(segmentos->longitud <= 0)
	{
		segmentos->longitud = 1;
		segmentos->elementos = calloc(1, sizeof(Segmento));
	}
	else
	{
		segmentos->longitud += 1;
		segmentos->elementos = realloc(segmentos->elementos, sizeof(Segmento) * segmentos->longitud);
	}

	if(segmentos->elementos == NULL)
		segmentos->longitud = 0;
	else
		segmentos->elementos[segmentos->longitud - 1] = *segmento;
}

/* Elimina un segmento de la coleccion de segmentos */
void RemoverUltimoSegmento(Segmentos* s)
{
	s->longitud -= 1;
	if(s->longitud == 0)
	{
		free(s->elementos);
		s->elementos = NULL;
	}
	else if(s->longitud > 0)
	{
		s->elementos = realloc(s->elementos, s->longitud * sizeof(Segmento));
	}
	else
	{
		s->longitud = 0;
		s->elementos = NULL;
	}
}

/* Borra una coleccion de segmentos */
void RemoverSegmentos(Segmentos* s)
{
	free(s->elementos);
	s->elementos = NULL;
	s->longitud = 0;
}

/* herramientas de deteccion */

/* detecta si los segmentos s1(a, b) y s2(c, d) intersectan */
bool Intersectan(Vertice *a, Vertice *b, Vertice *c, Vertice *d)
{
	/* haremos 4 pruebas to-left, una por cada vertice 
		estos bools nos sirven para determinar si los segmentos 
		intersectan, esta funcion analisa dos segmentos dados por
		4 puntos, toma dos puntos osea s1 y prueba los dos puntos del s2,
		si los dos estan a la izquierda o los estan a la derecha se le
		llama patron LL o RR respectivamente, al existir un patron LL o RR
		se dice que no hay una interseccion, para que haya una interseccion
		debe habre un patron LR */
	bool LLRR = false;
	bool LLRR2 = false;

	/* haciendo pruebas to-left de s1 con respecto a s2.a y s2.b */
	if( 
		( EnLaIzquierda(a, b, c) && EnLaIzquierda(a, b, d) )
			||
		( !EnLaIzquierda(a, b, c) && !EnLaIzquierda(a, b, d) )
	  )
		{
			LLRR = true;
		}

	/* haciendo pruebas to-left de s2 con respecto a s1.a y s1.b */
	if(
		( EnLaIzquierda(c, d, a) && EnLaIzquierda(c, d, b) )
			|| 
		( !EnLaIzquierda(c, d, a) && !EnLaIzquierda(c, d, b) )
	  )
		{
			LLRR2 = true;
		}

	/* si ninguno tiene patron LL o RR entonces hay interseccion */
	return (!LLRR && !LLRR2);
}

/* detecta si dos segmentos dados intersectan, usa fuerza bruta, dos for por lo tanto O(n^2) */
int BruteForceSID(Vertices *v)
{
	int i, j;
	int intersecciones = 0;
	/* revisamos si hay suficientes puntos para hacer segmentos separados */
	int longitud = (v->longitud % 2 == 0) ? v->longitud : v->longitud - 1;

	/* fuerza bruta */
	for(i = 0; i < longitud; i += 2) /* O(n)*/
	{
		DibujarSegmentoApartirDeVertices(&v->elementos[i], &v->elementos[i + 1], VCOLOR_LADO_EXTREMO);

		for(j = i + 2; j < longitud; j += 2) /* O(n^2)*/
		{
			if(Intersectan(&v->elementos[i], &v->elementos[i + 1], &v->elementos[j], &v->elementos[j + 1]))
				intersecciones++;
		}
	}

	return intersecciones;
}

