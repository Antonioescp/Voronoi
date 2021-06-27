#include <stdio.h>
#include <conio.h>

/* herramientas geometricas */
#include <voronoi\geom.h>

/* agregar vertice sin usar puntero para vertice */
void QueuePush(Vertices* col, Vertice e)
{
	QueueVerticePush(col, &e);
}

void QueuePop(Vertices* col)
{
	Vertice popped = QueueVerticePop(col);

	printf("Popped: X: %d, Y: %d\n", popped.x, popped.y);
}

/* imprime la cola de vertices */
void Imprimir(Vertices* col)
{
	int i;

	for(i = 0; i < col->longitud; i++)
	{
		printf("X: %d, Y: %d\n", col->elementos[i].x, col->elementos[i].y);
	}
	printf("\n");
}

int main()
{
	Vertices col = newVertices(0);

	QueuePush(&col, newVertice(1, 1));
	clrscr();
	Imprimir(&col);

	QueuePush(&col, newVertice(2, 2));
	Imprimir(&col);

	QueuePush(&col, newVertice(3, 3));
	Imprimir(&col);

	QueuePush(&col, newVertice(4, 4));
	Imprimir(&col);

	QueuePop(&col);
	Imprimir(&col);
	getch();
	/*
	QueuePop(&col);
	Imprimir(&col);
	getch();*/

	QueuePop(&col);
	Imprimir(&col);
	getch();

	QueuePop(&col);
	Imprimir(&col);
	getch();

	if(col.vacio)
		printf("La cola esta vacia: %d\n", col.longitud);
	else
		printf("La cola no esta vacia: %d\n", col.longitud);

	getch();
	return 0;
}

