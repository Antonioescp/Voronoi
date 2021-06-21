#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

/*********************************
 * este programa prueba las estructuras
 * stack
 * *********************************/

#include <voronoi\ch.h>

void ImprimirVertices(Vertices *v)
{
	int i;
	printf("Vertices: %d\n", v->longitud);
	printf("stackIndice: %d\n\n", v->stackIndice);

	for(i = 0; i < v->longitud; i++)
		printf("X: %d Y: %d\n", v->elementos[i].x, v->elementos[i].y);

	printf("\n");
}

void MostrarStack(Vertices *v)
{
	int i;
	printf("\n");

	printf("longitud: %d\nStackIndex: %d\n\n", v->longitud, v->stackIndice);
	for(i = 0; i <= v->stackIndice; i++)
		printf("X: %d Y: %d\n", v->elementos[i].x, v->elementos[i].y);

	printf("\n");
}

Vertice PuntoAleatorio(void)
{
	return newVertice(rand() % 51 + 50, rand() % 51 + 50);
}

int main()
{
	Vertices vertices = newVertices(0);
	Vertice nuevo;

	Vertices s;
	Vertices t;

	int i;

	srand(time(NULL));

	for(i = 0; i < 10; i++)
	{
		nuevo = newVertice(i, i);
		AgregarVertice(&vertices, &nuevo);
	}

	clrscr();
	ImprimirVertices(&vertices);

	getch();
	clrscr();
	s = newVertices(vertices.longitud);

	StackVerticePush(&s, &vertices.elementos[0]);
	StackVerticePush(&s, &vertices.elementos[1]);

	MostrarStack(&s);

	getch();
	clrscr();
	t = newVertices(vertices.longitud - 2);

	for(i = vertices.longitud - 1; i > 2; i--)
		StackVerticePush(&t, &vertices.elementos[i]);

	MostrarStack(&t);

	getch();
	clrscr();

	while(t.stackIndice > -1)
	{
		StackVerticePop(&t);
		MostrarStack(&t);

		getch();
	}
	
	return 0;
}
