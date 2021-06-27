#include <voronoi\trngltn.h>

/* obtiene las cadenas del poligono */
void Cadenas(Vertices *v)
{
	int i;
	int ltl = LTL(v);
	int htl = HTL(v);

	i = ltl + 1;
	while(i != htl && i < v->longitud)
		v->elementos[i++].opuesto = false;

	i = htl + 1;
	while(i != ltl && i < v->longitud)
		v->elementos[i++].opuesto = true;
}

/* prueba si un poligono es monotono */
bool EsMonotono(Vertices *v)
{
	/* estado monotono de cadenas */
	bool cadena1 = false;
	bool cadena2 = false;

	/* tomanto el extremo inferior y superior */
	int ltl = LTL(v);
	int htl = HTL(v);

	/* empezando desde el extremo inferior */
	int i = ltl + 1;
	int y = v->elementos[ltl].y;

	/* si solo estan htl y ltl en la cadena */
	while(i != htl && i < v->longitud)
	{
		/* si el valor siguiente en la cadena es menor a la posicion
				en y del vertice anterior, entonces, la cadena es monotona */
		if(y <= v->elementos[i].y )
		{
			y = v->elementos[i].y;
			cadena1 = true;
		}
		else
		{
			cadena1 = false;
			break;
		}

		i++;
	}
	
	/* empezando desde el extremo superior hacia extremo inferior */
	i = htl + 1;
	y = v->elementos[htl].y;
	while(i != ltl && i < v->longitud)
	{
		/* si el valor en Y del punto actual es menor al valor 
			en Y del punto anterior entonces es monotona; */
		if(y >= v->elementos[i].y )
		{
			y = v->elementos[i].y;
			cadena2 = true;
		}
		else
		{
			cadena2 = false;
			break;
		}

			i++;
	}

	return (cadena1 && cadena2);
}

/* triangula un poligono monotono */
void TriangulacionMonotona(Vertices *v)
{
	
}
