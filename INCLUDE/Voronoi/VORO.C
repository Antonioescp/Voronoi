#include <voronoi\voro.h>

/* dibuja el diagrama de voronoi con fuerza bruta */
void BruteVoronoi(Vertices *v)
{
	int x;
	int y;
	int k;
	int color;

	/* cada punto en x*/
	for(x = 0; x < getmaxx(); x++) 
	{
		/* cada punto en y */
		for(y = 0; y < getmaxy(); y++) 
		{
			color = 0;
			/* puntos ingresados por el usuario */
			for(k = 0; k < v->longitud; k++) 
			{
				if(DistanciaEntrePuntos2(x, y, v->elementos[k].x, v->elementos[k].y) <
					DistanciaEntrePuntos2(x, y, v->elementos[color].x, v->elementos[color].y))
					color = k;
			}
			putpixel(x, y, color + 1);
		}
	}
}
