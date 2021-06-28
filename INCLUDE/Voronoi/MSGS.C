#include <voronoi\msgs.h>

/* para mostrar mensajes */
void newMensaje(int x, int y, int ancho, int alto, char *titulo, char *contenido, short texto, short borde, short relleno){
	/* para mas facil manejo de coordenadas y color de borde exterior*/
	int x2 = x + ancho, y2 = y + alto, colorBordeExt = DARKGRAY;
	short i;

	/* para construir una cadena con sus respectivos saltos de linea */
	char *mensaje = NULL;
	char charActual[2] = {'', '\0'};
	short charPorLinea, mover = 0;

	/* determina los caracteres por linea dependiendo del ancho de la ventana del mensaje */
	if(ancho > getmaxx()/2)
		charPorLinea = (int)(ancho * 0.12);
	else
		charPorLinea = (int)(ancho * 0.11);
	
	/* limpiando mensaje anterior */
	setfillstyle(SOLID_FILL, BLACK);
	setcolor(colorBordeExt);
	rectangle(x, y, x2, y2);
	floodfill(x + 1, y + 1, colorBordeExt);

	/* dibujando nueva ventana, relleno */
	setfillstyle(SOLID_FILL, relleno);
	floodfill(x + 1, y + 1, colorBordeExt);

	/* dibujando contenedor */
	setcolor(borde);
	rectangle(x + 5, y + 15, x2 - 5, y2 - 5);

	/* escribiendo el titulo */
	setcolor(texto);
	outtextxy(x + 10, y + 5, titulo);

	/* para construir mensaje con su saltos de linea */
	mensaje = (char *) calloc(strlen(contenido), sizeof(char));
	if(mensaje == NULL){
		cleardevice();
		outtextxy(0, 0, "No se pudo asignar memoria al puntero");
		delay(2000);
		exit(1);
	}

	/* escribiendo mensaje */
	for(i = 0; i < strlen(contenido); i++){
		/* para concatenar solamente un caracter */
		charActual[0] = contenido[i];
		charActual[1] = '\0';

		strcat(mensaje, &charActual[0]);

		/* si estamos en una posicion diferente a la inicial y hemos llegado a los caracteres por linea en cada linea, 
		simular salto de linea o si llegamos al final de la cadena */
		if(i != 0 && i % charPorLinea == 0 || i == strlen(contenido) - 1){
			/* mostrando mensaje */
			outtextxy(x + 10, y + 20 + mover, mensaje);
			free(mensaje);

			/* asignando memoria necesaria para la cadena restante -i para asignar el tama;o de la cadena menos los elementos ya
			tratados */
			mensaje = (char *) calloc(strlen(contenido) - i, sizeof(char));
			if(mensaje == NULL){
				cleardevice();
				outtextxy(0, 0, "No se pudo asignar memoria al puntero");
				delay(2000);
				exit(1);
			}

			strcpy(mensaje, "");
			mover += 10;
		}
	}

	free(mensaje);
}

/* lo mismo que el de arriba pero mas apropiado para un menu */
void newMenu(int x, int y, int ancho, int alto, char *titulo, string opciones[], short texto, short borde, short relleno, short cantidadDeOpciones)
{
	/* para mas facil manejo de coordenadas y color de borde exterior*/
	int x2 = x + ancho, y2 = y + alto, colorBordeExt = DARKGRAY;
	short i;

	/* limpiando mensaje anterior */
	setfillstyle(SOLID_FILL, BLACK);
	setcolor(colorBordeExt);
	rectangle(x, y, x2, y2);
	floodfill(x + 1, y + 1, colorBordeExt);

	/* dibujando nueva ventana, relleno */
	setfillstyle(SOLID_FILL, relleno);
	floodfill(x + 1, y + 1, colorBordeExt);

	/* dibujando contenedor */
	setcolor(borde);
	rectangle(x + 5, y + 15, x2 - 5, y2 - 5);

	/* escribiendo el titulo */
	setcolor(texto);
	outtextxy(x + 10, y + 5, titulo);

	/* escribiendo opciones */
	for(i = 0; i < cantidadDeOpciones; i++)
	{
		/* dibujando opciones en el panel */
		outtextxy(x + 10, y + 20 + i * 10, opciones[i]);
	}
}
