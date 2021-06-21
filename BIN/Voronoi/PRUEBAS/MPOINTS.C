#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <mouse.h>
#include <stdio.h>

#include <voronoi\geom.h>
#include <voronoi\ui.h>

/* convexhull */
#include <voronoi\ch.h>

#define COLOR_VERTICE WHITE
#define COLOR_VERTICE_MEDIO RED
#define COLOR_CONVEX_HULL GREEN

int main()
{
	int gd = DETECT, gm;

	/* modo de graficos */
	Modo modoDePresentacion = rapido;
	/* velocidad en modo descriptivo */
	int retraso = 0;

	/* limites del plano */
	int xMax, yMax, xMid, yMid;

	/* manejo de entrada */
	char input;
	char buffer[50];

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
			/* utiliza el algoritmo de graham para dibujar la envolvente convexa */
			case 'g':
				mocultar();
				cleardevice();

				DibujarVertices(&vertices, VCOLOR_PUNTO_DESCARTADO);

				GrahamScan(&vertices, modoDePresentacion, retraso);

				mver();

				input = '';
				break;
			/* utiliza el algoritmo de jarvis para dibujar la envolvente */
			case 'j':
				mocultar();

				Jarvis(&vertices, modoDePresentacion, retraso);

				DibujarPuntosExtremos(&vertices, COLOR_CONVEX_HULL, COLOR_VERTICE_MEDIO);
				
				mver();

				input = '';
				break;
			/* para aumentar y disminuir el retraso */
			case 'p':
				cleardevice();
				DibujarVertices(&vertices, COLOR_VERTICE);

				retraso += retraso >= 500 ? 0 : 10 ;

				sprintf(buffer, "Retraso: %dms", retraso);
				outtextxy(15, 15, buffer);
				input = '';
				break;
			case 'o':
				mocultar();

				cleardevice();
				DibujarVertices(&vertices, COLOR_VERTICE);

				retraso -= retraso <= 0 ? 0 : 10 ;

				sprintf(buffer, "Retraso: %dms", retraso);
				outtextxy(15, 15, buffer);

				mver();
				input = '';
				break;
			/* Alterna el modo de presentacion de los algoritmos */
			case 'm':
				mocultar();
				cleardevice();
				DibujarVertices(&vertices, COLOR_VERTICE);
				if(modoDePresentacion == descriptivo)
				{
					modoDePresentacion = rapido;
					sprintf(buffer, "Modo rapido");
				}
				else
				{
					modoDePresentacion = descriptivo;
					sprintf(buffer, "Modo descriptivo");
				}

				setcolor(WHITE);
				outtextxy(15, 15, buffer);

				mver();
				input = '';
				break;
			/* determina lados extremos */
			case 'c':
				mocultar();
				
				DibujarVertices(&vertices, COLOR_VERTICE_MEDIO);
				LadosExtremos(&vertices, modoDePresentacion, retraso);
				DibujarPuntosExtremos(&vertices, COLOR_CONVEX_HULL, COLOR_VERTICE_MEDIO);

				mver();
				input = '';
				break;
			/* determina puntos extremos */
			case 's':
				mocultar();

				DibujarVertices(&vertices, COLOR_VERTICE_MEDIO);
				PuntosExtremosLento(&vertices, modoDePresentacion, retraso);

				cleardevice();
				DibujarPuntosExtremos(&vertices, COLOR_CONVEX_HULL, COLOR_VERTICE_MEDIO);

				mver();
				input = '';
				break;
			/* borra pantalla y vertices */
			case 'r':
				RemoverVertices(&vertices);
				mocultar();
				cleardevice();
				mver();
				input = '';
				break;
			/* muestra el area dada por los primeros 3 puntos */
			case 'a':
				if(vertices.longitud >= 3)
				{
					cleardevice();
					setcolor(WHITE);

					sprintf(buffer, "Area: %.2f", Area2(&vertices.elementos[0], &vertices.elementos[1], &vertices.elementos[2]));
					outtextxy(15, 15, buffer);

					sprintf(buffer, "A -> x: %d y: %d", vertices.elementos[0].x, vertices.elementos[0].y);
					outtextxy(15, 30, buffer);

					sprintf(buffer, "B -> x: %d y: %d", vertices.elementos[1].x, vertices.elementos[1].y);
					outtextxy(15, 45, buffer);

					sprintf(buffer, "C -> x: %d y: %d", vertices.elementos[2].x, vertices.elementos[2].y);
					outtextxy(15, 60, buffer);

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

			sprintf(buffer, "Puntos: %d", vertices.longitud);
			setcolor(WHITE);
			outtextxy(15, 15, buffer);

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

			sprintf(buffer, "Puntos: %d", vertices.longitud);
			setcolor(WHITE);
			outtextxy(15, 15, buffer);

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