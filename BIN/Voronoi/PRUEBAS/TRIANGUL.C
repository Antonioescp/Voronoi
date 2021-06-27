#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <mouse.h>

#include <voronoi/geom.h>
#include <voronoi/ui.h>

#include <voronoi\trngltn.h>

#define COLOR_VERTICE WHITE

/* poniendo a prueba la triangulacion */

int main()
{
	int gd = DETECT, gm;

	/* elementos */

	/* limites del plano */
	int xMax, yMax, xMid, yMid, i;

	/* manejo de entrada */
	char input = '';
	char buffer[50];

	/* manejo de raton */
	Mouse raton;

	/* Coleccion de vertices agregados por el usuario */
	Vertices vertices;

	/* inicio aplicacion grafica */
	initgraph(&gd, &gm, "");
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

		switch(input)
		{
			case 'c':
				mocultar();

				sprintf(buffer, "Es monotono: %d", EsMonotono(&vertices));
				setcolor(WHITE);
				outtextxy(15, 15, buffer);

				DibujarPoligono(&vertices, WHITE);
				Cadenas(&vertices);
				for(i = 0; i <  vertices.longitud; i++)
				{
					if(vertices.elementos[i].opuesto)
						DibujarVertice(&vertices.elementos[i], RED);
					else
						DibujarVertice(&vertices.elementos[i], GREEN);
				}

				mver();
				input = '';
				break;
			case 'r':
				mocultar();

				cleardevice();
				RemoverVertices(&vertices);

				mver();
				input = '';
				break;
		}

		ActualizarMouse(&raton);

		/* manejando click izquierdo, agrega un vertice y lo dibuja */
		if(raton.clickIzquierdo == Presionado && raton.operacionClickIzquierdo == NoHecho)
		{
			AgregarVertice(&vertices, &raton.posicion);

			/* dibujando vertices */
			mocultar();
			DibujarVertice(&raton.posicion, COLOR_VERTICE);
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
			/* borrando de pantalla el vertice */
			mocultar();
			DibujarVertice(&vertices.elementos[vertices.longitud - 1], getbkcolor());
			mver();
			
			/* removiendo de coleccion */
			RemoverUltimoVertice(&vertices);

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