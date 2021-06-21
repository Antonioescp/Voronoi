#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>

/* convexhull */
#include <voronoi\ch.h>

/****************************************************************
 * Este archivo pone a prueba el ordenamiento por angulo polar
 * ******************************************************************/

Vertice PuntoAleatorio(const int maxX, const int maxY)
{
	return newVertice( rand() % maxX + 1, rand() % maxY + 1 );
}

void MostrarVertices(Vertices *v)
{
	int i;
	char buffer[4];
	for(i = 0; i < v->longitud; i++)
	{
		DibujarVertice(&v->elementos[i], i + 1);
		sprintf(buffer, "%d", i + 1);
		setcolor(WHITE);
		outtextxy(v->elementos[i].x, v->elementos[i].y, buffer);
	}
}

/* agregar vertice sin tener que tener una variable de tipo vertice */
void AV(Vertices *v, Vertice v1)
{
	if(v->longitud <= 0)
	{
		v->longitud = 1;
		v->elementos = calloc(1, sizeof(Vertice));
	}
	else
	{
		v->longitud += 1;
		v->elementos = realloc(v->elementos, sizeof(Vertice) * v->longitud);
	}

	if(v->elementos == NULL)
		v->longitud = 0;
	else
		v->elementos[v->longitud - 1] = v1;
}

void Shuffle(Vertices *v, int n)
{
	int i;
	RemoverVertices(v);

	for(i = 0; i < n; i++)
		AV(v, PuntoAleatorio(getmaxx(), getmaxy()));
}

int main()
{
	int gd = DETECT, gm;

	Vertices v;
	char input = '';
	int numeroDePuntos = 1;

	srand(time(NULL));

	initgraph(&gd, &gm, "");

	v = newVertices(0);

	AV(&v, newVertice(10 + getmaxx() / 2, -50 + getmaxy() / 2));
	AV(&v, newVertice(-20 + getmaxx() / 2, 90 + getmaxy() / 2));
	AV(&v, newVertice(30 + getmaxx() / 2, 40 + getmaxy() / 2));
	AV(&v, newVertice(-40 + getmaxx() / 2, -70 + getmaxy() / 2));
	AV(&v, newVertice(50 + getmaxx() / 2, 80 + getmaxy() / 2));
	AV(&v, newVertice(-60 + getmaxx() / 2, 90 + getmaxy() / 2));
	AV(&v, newVertice(70 + getmaxx() / 2, -60 + getmaxy() / 2));
	AV(&v, newVertice(-80 + getmaxx() / 2, 65 + getmaxy() / 2));
	AV(&v, newVertice(90 + getmaxx() / 2, 95 + getmaxy() / 2));

	MostrarVertices(&v);
	getch();

	cleardevice();

	OrdenarPorAnguloPolar(&v);
	MostrarVertices(&v);

	getch();

	while(input != 'q')
	{
		cleardevice();

		OrdenarPorAnguloPolar(&v);
		MostrarVertices(&v);

		input = getch();

		if(input == 's')
		{
			Shuffle(&v, numeroDePuntos++);
		}
	}

	
	closegraph();
	return 0;
}

