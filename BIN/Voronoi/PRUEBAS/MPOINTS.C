#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <mouse.h>
#include <stdio.h>

/* interfaz grafica */
#include <voronoi\ui.h>
/* convex hull */
#include <voronoi\ch.h>
/* geometric intersection */
#include <voronoi\geomint.h>
/* voronoi */
#include <voronoi\voro.h>
/* triangulacion monotona */
#include <voronoi\trngltn.h>

/* presentacion del programa */
#include <voronoi\logo.h>

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
	int xMax, yMax, xMid, yMid, i;

	/* manejo de entrada */
	char input;

	/* informacion en pantalla */
	char buffer[50];
	string integrantes[] = { "Marvin Alexander Sevilla Calero", 
							 "Harold Jason Moreno Rocha",
							 "Brayan Josue Potosme Rivera",
							 "Cristina Jamileth Lopez Flores",
							 "Pablo Isaias Alemán Mairena",
							 "Juan Antonio Perez Escorcia" };
	string opciones[] = { "W - Mostrar esto de nuevo",
						  "Mouse",
						  "Click Izquierdo - Colocar Punto",
						  "Click Derecho - Eliminar Ultimo Punto",
						  "Convex Hull",
						  "S - Puntos extremos",
						  "C - Por lados extremos",
						  "J - Jarvis March",
						  "G - Graham Scan",
						  "Interseccion Geometrica",
						  "I - SID fuerza bruta",
						  "Triangulacion",
						  "T - Triangulacion Monotona",
						  "Voronoi",
						  "V - Voronoi fuerza bruta",
						  "Otros",
						  "M - Modo Descriptivo",
						  "-/+ - Latencia de modo descriptivo",
						  "D - Distancia entre 2 puntos",
						  "F - Dibujar Poligono Libre",
						  "P - Poligono con respecto a punto medio",
						  "R - Borrar vertices y limpiar",
						  "Q - Salir",
						  };

	/* para mostrar descripciones una sola vez */
	bool descTriangulacion = false;
	bool descConvexHull = false;
	bool descInterseccion = false;

	/* manejo de raton */
	Mouse raton;

	/* Coleccion de vertices agregados por el usuario */
	Vertices vertices;
	Vertice puntoMedio;

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

	/* inicializando entrada, para evitar llamadas erroneas */
	input = '';

	/* presentacion del programa */
	presentacion();
	getch();
	

	/* mostrando integrantes */
	cleardevice();
	newMenu(xMid - 175, yMid - 50, 350, 100, "Integrantes", integrantes, WHITE, LIGHTGRAY, DARKGRAY, 6);
	getch();
	
	/* mostrando opciones del programa */
	cleardevice();
	newMenu(xMid - 175, yMid - 130, 350, 260, "Opciones", opciones, WHITE, LIGHTGRAY, DARKGRAY, 23);
	getch();

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
			/* muestra las opciones */
			case 'w':
				mocultar();
				
				cleardevice();
				newMenu(xMid - 175, yMid - 130, 350, 260, "Opciones", opciones, WHITE, LIGHTGRAY, DARKGRAY, 23);

				mver();
				input = '';
				break;
			/* triangula el poligono */
			case 't':
				mocultar();
				
				if(!descTriangulacion)
				{
					cleardevice();
					newMensaje(xMid - 175, yMid - 30, 350, 60, "Triangulacion", "En triangulacion se pintan blanco los puntos superior e inferior y las cadenas en rojo y verde", WHITE, LIGHTGRAY, DARKGRAY);
					getch();
					descTriangulacion = true;
				}

				cleardevice();
				puntoMedio = PuntoMedio(&vertices);

				/* pasos necesarios antes de triangular */
				OrdenarPorAnguloPolarWRTVertice(&vertices, &puntoMedio);
				
				DeterminarCadenas(&vertices);
				for(i = 0; i <  vertices.longitud; i++)
				{
					if(vertices.elementos[i].cadena == izquierda)
						DibujarVertice(&vertices.elementos[i], RED);
					else if(vertices.elementos[i].cadena == derecha)
						DibujarVertice(&vertices.elementos[i], GREEN);
					else if(vertices.elementos[i].cadena == ambas)
						DibujarVertice(&vertices.elementos[i], WHITE);
				}

				DibujarPoligono(&vertices, WHITE);

				sprintf(buffer, "%s", EsMonotono(&vertices) ? "Es monotono" : "No es monotono");
				setcolor(WHITE);
				outtextxy(15, 15, buffer);

				TriangulacionMonotona(&vertices);

				mver();
				input = '';
				break;
			/* diagrama de voronoi usando bruteForce */
			case 'v':
				mocultar();

				cleardevice();

				BruteVoronoi(&vertices);

				DibujarVertices(&vertices, VCOLOR_PUNTO);

				mver();
				input = '';
				break;
			/* imprime la distancia entre los dos primeros puntos */
			case 'd':
				mocultar();
				cleardevice();

				sprintf(buffer, "Distancia: %d", DistanciaEntrePuntos(&vertices.elementos[0], &vertices.elementos[1]));

				DibujarVertices(&vertices, VCOLOR_PUNTO);

				outtextxy(15, 15, buffer);

				mver();
				input = '';
				break;
			/* dibuja el poligono de manera libre, es decir, en el orden dado */
			case 'f':
				mocultar();

				cleardevice();

				DibujarPoligono(&vertices, VCOLOR_PUNTO);

				DibujarVertices(&vertices, VCOLOR_PUNTO_EXTREMO);

				mver();
				input = '';
				break;
			/* dibuja un poligo despues de ordenar en angulo polar los vertices, con
				respecto al punto mas bajo y mas a la izquierda (ltl) */
			case 'p':
				mocultar();

				cleardevice();

				puntoMedio = PuntoMedio(&vertices);

				OrdenarPorAnguloPolarWRTVertice(&vertices, &puntoMedio);

				DibujarPoligono(&vertices, VCOLOR_PUNTO);

				DibujarVertices(&vertices, VCOLOR_PUNTO_EXTREMO);

				mver();
				input = '';
				break;
			/* reporta intersecciones */
			case 'i':
				mocultar();

				if(!descInterseccion)
				{
					cleardevice();
					newMensaje(xMid - 175, yMid - 30, 350, 60, "Interseccion Geometrica", "En interseccion, se pintan rojo los puntos cuyos segmentos intersectan", WHITE, LIGHTGRAY, DARKGRAY);
					getch();
					descInterseccion = true;
				}

				cleardevice();
				DibujarVertices(&vertices, COLOR_VERTICE);

				sprintf(buffer, "Interseccioes: %d", BruteForceSID(&vertices));
				setcolor(WHITE);
				outtextxy(15, 15, buffer);

				mver();
				input = '';
				break;
			/* limpia memoria y sale del programa */
			case 'q':
				RemoverVertices(&vertices);
				break;
			/* utiliza el algoritmo de graham para dibujar la envolvente convexa */
			case 'g':
				mocultar();

				if(!descConvexHull)
				{
					cleardevice();
					newMensaje(xMid - 175, yMid - 50, 350, 100, "Convex Hull", "En el modo descriptivo, en convex hull, se pinta de color celeste el punto/lado/triangulo siendo analizado en ese momento y se dejan de ese color, en general se pinta de color cafe los lados extremos, de color rojo los puntos no extremos y verdes los puntos extremos.", WHITE, LIGHTGRAY, DARKGRAY);
					getch();
					descConvexHull = true;
				}

				cleardevice();
				DibujarVertices(&vertices, VCOLOR_PUNTO_DESCARTADO);

				GrahamScan(&vertices, modoDePresentacion, retraso);

				mver();

				input = '';
				break;
			/* utiliza el algoritmo de jarvis para dibujar la envolvente */
			case 'j':
				mocultar();

				if(!descConvexHull)
				{
					cleardevice();
					newMensaje(xMid - 175, yMid - 50, 350, 100, "Convex Hull", "En el modo descriptivo, en convex hull, se pinta de color celeste el punto/lado/triangulo siendo analizado en ese momento y se dejan de ese color, en general se pinta de color cafe los lados extremos, de color rojo los puntos no extremos y verdes los puntos extremos.", WHITE, LIGHTGRAY, DARKGRAY);
					getch();
					descConvexHull = true;
				}

				cleardevice();
				DibujarVertices(&vertices, VCOLOR_PUNTO_DESCARTADO);

				JarvisMarch(&vertices, modoDePresentacion, retraso);

				DibujarPuntosExtremos(&vertices, COLOR_CONVEX_HULL, COLOR_VERTICE_MEDIO);
				
				mver();

				input = '';
				break;
			/* para aumentar y disminuir el retraso +/- */
			/* + */
			case '+':
				cleardevice();
				DibujarVertices(&vertices, COLOR_VERTICE);

				retraso = retraso + 10 > 500 ? 0 : retraso + 10;

				sprintf(buffer, "Retraso: %dms", retraso);
				outtextxy(15, 15, buffer);
				input = '';
				break;
			/* - */
			case '-':
				mocultar();

				cleardevice();
				DibujarVertices(&vertices, COLOR_VERTICE);

				retraso = retraso - 10 < 0 ? 500 : retraso - 10 ;

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
				if(!descConvexHull)
				{
					cleardevice();
					newMensaje(xMid - 175, yMid - 50, 350, 100, "Convex Hull", "En el modo descriptivo, en convex hull, se pinta de color celeste el punto/lado/triangulo siendo analizado en ese momento y se dejan de ese color, en general se pinta de color cafe los lados extremos, de color rojo los puntos no extremos y verdes los puntos extremos.", WHITE, LIGHTGRAY, DARKGRAY);
					getch();
					descConvexHull = true;
				}
				
				cleardevice();
				DibujarVertices(&vertices, COLOR_VERTICE_MEDIO);
				LadosExtremos(&vertices, modoDePresentacion, retraso);
				DibujarPuntosExtremos(&vertices, COLOR_CONVEX_HULL, COLOR_VERTICE_MEDIO);

				mver();
				input = '';
				break;
			/* determina puntos extremos */
			case 's':
				mocultar();
				if(!descConvexHull)
				{
					cleardevice();
					newMensaje(xMid - 175, yMid - 50, 350, 100, "Convex Hull", "En el modo descriptivo, en convex hull, se pinta de color celeste el punto/lado/triangulo siendo analizado en ese momento y se dejan de ese color, en general se pinta de color cafe los lados extremos, de color rojo los puntos no extremos y verdes los puntos extremos.", WHITE, LIGHTGRAY, DARKGRAY);
					getch();
					descConvexHull = true;
				}

				cleardevice();
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
					mocultar();
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

					if(EnLaIzquierda(&vertices.elementos[0], &vertices.elementos[1], &vertices.elementos[2]))
						outtextxy(15, 75, "Esta en la izquierda");
					else
						outtextxy(15, 75, "No esta en la izquierda");

					DibujarVertices(&vertices, COLOR_VERTICE);
					mver();
				}
				input = '';
				break;
		}

		/* manejando click izquierdo, agrega un vertice y lo dibuja */
		if(raton.clickIzquierdo == Presionado && raton.operacionClickIzquierdo == NoHecho)
		{
			mocultar();
			cleardevice();
			AgregarVertice(&vertices, &raton.posicion);

			sprintf(buffer, "Puntos: %d", vertices.longitud);
			setcolor(WHITE);
			outtextxy(15, 15, buffer);

			/* dibujando vertices */
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
			mocultar();	
			/* removiendo de coleccion */
			RemoverUltimoVertice(&vertices);

			cleardevice();
			/* borrando de pantalla el vertice */
			
			DibujarVertices(&vertices, COLOR_VERTICE);
			

			sprintf(buffer, "Puntos: %d", vertices.longitud);
			setcolor(WHITE);
			outtextxy(15, 15, buffer);

			raton.operacionClickDerecho = Hecho;
			mver();
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