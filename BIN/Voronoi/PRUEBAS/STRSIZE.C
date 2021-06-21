#include <stdio.h>
#include <conio.h>

#include <voronoi\ch.h>

/******************************************************
 * este programa tiene como objetivo probar si es mejor copiar una coleccion de estructuras
 * o crear un arreglo de punteros para apuntar a elementos de esa coleccion
 * ******************************************************/

int main()
{
	int colSize = sizeof(Vertice) * 10;
	int ptrColSize = sizeof(Vertice *) * 10;
	clrscr();

	printf("Uso de memoria copiando coleccion vs punteros (Coleccion de 10 vertices)\n");
	printf("Copiando coleccion: %d bytes\nUsando punteros a cada vertice: %d bytes\nahorro: %d bytes", colSize, ptrColSize, colSize - ptrColSize);

	getch();
	return 0;
}
