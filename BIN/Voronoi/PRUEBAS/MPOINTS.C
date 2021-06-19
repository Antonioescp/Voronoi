#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <mouse.h>
#include <stdio.h>

#include <voronoi\geom.h>
#include <voronoi\ui.h>

#define COLOR_VERTICE WHITE
#define COLOR_VERTICE_MEDIO RED
#define COLOR_CONVEX_HULL GREEN

int main()
{
	int gd = DETECT, gm;

	/* limites del plano */
	int xMax, yMax, xMid, yMid;

	/* manejo de entrada */
	char input;
	char numeroDePuntos[50];
	char area[50];
	char v1[50];
	char v2[50];
	char v3[50];

	/* manejo de raton */
	Mouse raton;

	/* Coleccion de vertices agregados por el usuario */
	Vertices vertices;

	/* inicio aplicacion grafica */
	initgraph(&gd, &gm, "C:\\tc20\\BIN");
	cleardevice();

	/* limites del plano */
	xMax = getmaxx();
	xMid = xMax / 2;
	yMax = getmaxy();
	yMid = yMax / 2;

	/* inicializando coleccion de vertices */
	vertices = newVertices(0);

	/* inicializando raton */
	raton = newMouse();
	mver();

	/* manejando entrada */
	do
	{
		if(kbhit())
			input = getch();

		ActualizarMouse(&raton);

		/* manejando entrada de teclado */
		switch(input)
		{
			case 'c':
				mocultar();

				DibujarVertices(&vertices, COLOR_VERTICE_MEDIO);
				EnvolventeConvexaLento(&vertices, descriptivo);

				cleardevice();
				DibujarPuntosExtremos(&vertices, COLOR_CONVEX_HULL, COLOR_VERTICE_MEDIO);

				mver();
				input = '';
				break;
			case 'r':
				RemoverVertices(&vertices);
				mocultar();
				cleardevice();
				mver();
				input = '';
				break;
			case 'a':
				if(vertices.longitud >= 3)
				{
					setcolor(WHITE);

					sprintf(area, "Area: %.2f", Area2(&vertices.elementos[0], &vertices.elementos[1], &vertices.elementos[2]));
					sprintf(v1, "A -> x: %d y: %d", vertices.elementos[0].x, vertices.elementos[0].y);
					sprintf(v2, "B -> x: %d y: %d", vertices.elementos[1].x, vertices.elementos[1].y);
					sprintf(v3, "C -> x: %d y: %d", vertices.elementos[2].x, vertices.elementos[2].y);
					cleardevice();
					outtextxy(15, 15, area);
					outtextxy(15, 30, v1);
					outtextxy(15, 45, v2);
					outtextxy(15, 60, v3);
					DibujarVertices(&vertices, COLOR_VERTICE);
				}
				input = '';
				break;
		}

		/* manejando click izquierdo, agrega un vertice y lo dibuja */
		if(raton.clickIzquierdo == Presionado && raton.operacionClickIzquierdo == NoHecho)
		{
			cleardevice();
			AgregarVertice(&vertices, &raton.posicion);

			sprintf(numeroDePuntos, "Puntos: %d", vertices.longitud);
			setcolor(WHITE);
			outtextxy(15, 15, numeroDePuntos);

			/* dibujando vertices */
			mocultar();
			DibujarVertices(&vertices, COLOR_VERTICE);
			mver();

			/* actualizando estado de operacion */
			raton.operacionClickIzquierdo = Hecho;
		}

		/* actualizando estado de operacion */
		if(raton.clickIzquierdo == NoPresionado && raton.operacionClickIzquierdo == Hecho)
		{
			raton.operacionClickIzquierdo = NoHecho;
		}

		/* manejando click derecho, elimina el ultimo vertice en la coleccion */
		if(raton.clickDerecho == Presionado && raton.operacionClickDerecho == NoHecho)
		{			
			/* removiendo de coleccion */
			RemoverUltimoVertice(&vertices);

			cleardevice();
			/* borrando de pantalla el vertice */
			mocultar();
			DibujarVertices(&vertices, COLOR_VERTICE);
			mver();

			sprintf(numeroDePuntos, "Puntos: %d", vertices.longitud);
			setcolor(WHITE);
			outtextxy(15, 15, numeroDePuntos);

			raton.operacionClickDerecho = Hecho;
		}

		/* actualizando estado de operacion */
		if(raton.clickDerecho == NoPresionado && raton.operacionClickDerecho == Hecho )
		{
			raton.operacionClickDerecho = NoHecho;
		}

	}while(input != 'q');

	closegraph();
	return 0;
}

