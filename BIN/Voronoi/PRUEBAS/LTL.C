#include <stdio.h>
#include <conio.h>

#include <voronoi\geom.h>

int main()
{

	Vertices v = newVertices(0);

	Vertice v1 = newVertice(1, 4);
	Vertice v2 = newVertice(2, 4);
	Vertice v3 = newVertice(-3, 4);
	Vertice v4 = newVertice(4, 4);
	Vertice v5 = newVertice(5, 4);
	Vertice v6 = newVertice(6, 1);
	Vertice v7 = newVertice(-7, 4);
	Vertice v8 = newVertice(8, 4);
	Vertice v9 = newVertice(-9, 4);

	AgregarVertice(&v, &v1);
	AgregarVertice(&v, &v2);
	AgregarVertice(&v, &v3);
	AgregarVertice(&v, &v4);
	AgregarVertice(&v, &v5);
	AgregarVertice(&v, &v6);
	AgregarVertice(&v, &v7);
	AgregarVertice(&v, &v8);
	AgregarVertice(&v, &v9);

	clrscr();
	printf("%d", LTL(&v));
	getch();
	return 0;
}
