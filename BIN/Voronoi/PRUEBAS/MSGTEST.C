#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <voronoi\msgs.h>

int main()
{
	int gd = DETECT, gm;

	string opciones[] = {"-Opcion 1", "-Opcion 2", "-Opcion 3"};
	char test[50];

	initgraph(&gd, &gm, "");
	cleardevice();

	newMensaje(getmaxx()/2 - 125, getmaxy()/2 - 50, 250, 100, "Menu", "Prueba", WHITE, LIGHTGRAY, DARKGRAY);
	getch();

	cleardevice();

	newMenu(getmaxx()/2 - 125, getmaxy()/2 - 50, 250, 100, "Menu", opciones, WHITE, LIGHTGRAY, DARKGRAY, 3);

	getch();
	closegraph();
	return 0;
}
