#include <stdio.h>
#include <conio.h>

/* calcula el doble del area de un triangulo utilizando la determinante */
long int Area2V(int ax, int ay, int bx, int by, int cx, int cy)
{
	printf("A: %d %d\nB: %d %d\nC: %d %d\n", ax, ay, bx, by, cx, cy);

	int op = ax * by;
	return 	(ax * by - ay * bx + bx * cy - by * cx + cx * ay - cy * ax);
}

/*********************************
 * En este archivo se intenta calcular el area de una triangulo usando la determinante *
 * *************************************************************/

int main()
{
	clrscr();
	printf("Area: %ld", Area2V(548, 125, 544, 344, 68, 209));

	getch();
	return 0;
}
