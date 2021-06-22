#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>

#include <voronoi\geom.h>
#include <voronoi\dtstrct.h>

/*********************************************************
 * Este programa desea implementar un stack que esta destinado
 * a copiar los elementos de una coleccion de Vertices,
 * implementarlo de esta manera usa menos memoria y es mas rapido
 * ya que solo utiliza los indices de la coleccion de vertices 
 * original, en lugar de copiar una estructura completa de cada Vertice
 * */

Vertice PuntoAleatorio(void)
{
	return newVertice(rand() % 100 + 1, rand() % 100 + 1);
}

void AV(Vertices *v, Vertice v1)
{
	AgregarVertice(v, &v1);
}

void ImprimirVertices(Vertices *v)
{
	int i;
	for(i = 0; i < v->longitud; i++)
		printf("X: %d Y: %d\n", v->elementos[i].x, v->elementos[i].y);
}

void ImprimirStack(StackPunto *sp)
{
	int i;
	for(i = 0; i < sp->longitud; i++)
		printf("X: %d Y: %d\n", sp->elementos[sp->indices[i]].x, sp->elementos[sp->indices[i]].y);
}

int main()
{
	int i;
	int indice;
	StackPunto nuevo;
	Vertices vertices = newVertices(0);

	for(i = 0; i < 10; i++)
		AV(&vertices, PuntoAleatorio());

	clrscr();
	ImprimirVertices(&vertices);

	nuevo = newStackPunto(&vertices);

	StackPuntoPush(&nuevo, 1);
	StackPuntoPush(&nuevo, 3);
	StackPuntoPush(&nuevo, 9);


	if(nuevo.vacio)
		printf("Infiltrado papa");

	printf("\n");

	ImprimirStack(&nuevo);

	indice = StackPuntoPop(&nuevo);
	printf("\nIndice\nX: %d Y:%d\n\n", vertices.elementos[indice]);

	printf("Stack: \n");
	ImprimirStack(&nuevo);

	indice = StackPuntoPop(&nuevo);
	printf("\nIndice\nX: %d Y:%d\n\n", vertices.elementos[indice]);

	printf("Stack: \n");
	ImprimirStack(&nuevo);

	indice = StackPuntoPop(&nuevo);
	printf("\nIndice\nX: %d Y:%d\n\n", vertices.elementos[indice]);

	printf("Stack: \n");
	ImprimirStack(&nuevo);

	getch();
	return 0;
}
