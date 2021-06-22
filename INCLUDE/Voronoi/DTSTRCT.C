#include <voronoi\dtstrct.h>

/* crea un stack listo para copiar cualquier indice de
	la collecion de vertice dada, solamente usa un arreglo de
	int, usa menos memoria que copiar cada elemento de v */
StackPunto newStackPunto(Vertices *v)
{
	StackPunto s;

	s.vacio = true;
	s.longitud = 0;
	s.indices = calloc(v->longitud, sizeof(int));

	s.elementos = v->elementos;

	return s;
}

/*	Agrega un indice al stack */
void StackPuntoPush(StackPunto *sp, int indice)
{
	int i;
	int temp;

	sp->longitud++;
	sp->vacio = false;
	sp->indices = realloc(sp->indices, sizeof(int) * sp->longitud);

	sp->indices[sp->longitud - 1] = indice;

	if(sp->longitud > 1)
	{
		for(i = sp->longitud - 1; i > 0; i--)
		{
			temp = sp->indices[i - 1];
			sp->indices[i - 1] = sp->indices[i];
			sp->indices[i] = temp;
		}
	}
}

/* retorna el indice del elemento eliminado del stack */
int StackPuntoPop(StackPunto *sp)
{
	int i;
	int temp;
	int indice;

	if(!sp->vacio)
	{
		indice = sp->indices[0];
		for(i = 0; i < sp->longitud; i++)
		{
			temp = sp->indices[i];
			sp->indices[i] = sp->indices[i + 1];
			sp->indices[i + 1] = temp;
		}

		sp->longitud--;

		sp->indices = realloc(sp->indices, sizeof(int) * sp->longitud);
	}

	if(sp->longitud <= 0)
		sp->vacio = true;
	
	return indice;
}

