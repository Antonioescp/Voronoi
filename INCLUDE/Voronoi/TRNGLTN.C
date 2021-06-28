#include <voronoi\trngltn.h>

/* obtiene las cadenas del poligono */
void DeterminarCadenas(Vertices *v)
{
	int i;
	int ltl = LTL(v);
	int htl = HTL(v);

	v->elementos[ltl].cadena = ambas;
	v->elementos[htl].cadena = ambas;

	i = ltl + 1;
	while(i != htl && i < v->longitud)
		v->elementos[i++].cadena = derecha;

	i = htl + 1;
	while(i != ltl && i < v->longitud)
		v->elementos[i++].cadena = izquierda;
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
	int i; /* pa bucles */
	/* para poder ordenar en y despues sin perder esta informacion */
	bool esMonotono = EsMonotono(v);

	if(esMonotono)
	{
		/* tipos de datos abstractos para llevar a cabo el algoritmo */
		Vertices stack = newVertices(v->longitud);
		Vertices queue = newVertices(0);
		/* elementos pop de la queue */
		Vertice verticeActual;
		/* para guardar el vertice cuando 
			se mueva de una cadena a otra */
		Vertice top;

		/* determinando cadenas */
		DeterminarCadenas(v);

		/* ahora ordenamos en Y para llenar la cola */
		OrdenarPorCoordenadaDescendente(v, coordenadaY);

		/* guardando vertices de mayor a menor en Y */
		for(i = 0; i < v->longitud; i++)
			QueueVerticePush(&queue, &v->elementos[i]);

		/* primeros vertices del stack para empezar el proceso
			de triangulacion */
		verticeActual = QueueVerticePop(&queue);
		StackVerticePush(&stack, &verticeActual);

		verticeActual = QueueVerticePop(&queue);
		StackVerticePush(&stack, &verticeActual);

		/* este vertice se estara evaluando en la primera iteracion */
		verticeActual = QueueVerticePop(&queue);

		/* empezamos a triangular mientras aun haya elementos que evaluar */
		while(!queue.vacio)
		{
			getch();
			/* en la triangulacion hay 3 casos en 2 categorias A y B */
			/* la categoria A se da cuando ambos, el top del stack y el vertice actual
				pretenecen a la misma cadena */
			if(stack.elementos[stack.stackIndice].cadena == verticeActual.cadena || verticeActual.cadena == ambas)
			{
				/* el primer caso, caso A1, es cuando el verticeActual y 
				el tope del stack forman un angulo > 180 grados, en este caso solo 
				hacemos push */
				if(!EnLaIzquierda(&stack.elementos[stack.stackIndice - 1], &stack.elementos[stack.stackIndice], &verticeActual))
				{
					StackVerticePush(&stack, &verticeActual);
				}
				/* este es el segundo caso, caso A2, este caso se da cuando verticeActual
				y el tope del stack forman un angulo convexo en este caso hacemos un bucle
				 en el que conectamos el elemento despues del tope del stack con el 
				 vertice actual y hacemos un pop del stack hasta que el nuevo top del stack no forme un angulo convexo o el stack solo tenga 1 elemento que seria el punto final de la cadena */
				else if(EnLaIzquierda(&stack.elementos[stack.stackIndice - 1], &stack.elementos[stack.stackIndice], &verticeActual))
				{
					while(EnLaIzquierda(&stack.elementos[stack.stackIndice - 1], &stack.elementos[stack.stackIndice], &verticeActual) && stack.stackIndice > 0)
					{
						DibujarSegmentoApartirDeVertices(&stack.elementos[stack.stackIndice - 1], &verticeActual, VCOLOR_DIAGONAL);
						StackVerticePop(&stack);
					}
					StackVerticePush(&stack, &verticeActual);
				}
			}
			/* El 3er caso, el caso B, es cuando verticeActual esta en la cadena opuesta
				en este caso conectamos todos los vertices de la cadena opuesta con c pero
				antes tomamos el tope del stack puesto que eliminaremos todo los elementos
				del stack e iniciaremos uno nuevo con el que era el tope y el 
				verticeActual */
			else if(verticeActual.cadena != stack.elementos[stack.stackIndice].cadena)
			{
				top = stack.elementos[stack.stackIndice];
				/* conectamos todos los elementos del stack en bucle */
				while(stack.stackIndice > 0)
				{
					DibujarSegmentoApartirDeVertices(&stack.elementos[stack.stackIndice], &verticeActual, VCOLOR_DIAGONAL);
					StackVerticePop(&stack);
				}

				/* una vez nos quedamos con un solo elemento */
				StackVerticePop(&stack);
				StackVerticePush(&stack, &top);
				StackVerticePush(&stack, &verticeActual);
			}

			/* moviendonos al siguiente vertice */
			verticeActual = QueueVerticePop(&queue);
		}

		RemoverVertices(&queue);
		RemoverVertices(&stack);
	}
}
