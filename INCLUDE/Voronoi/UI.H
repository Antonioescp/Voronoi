#ifndef _UI
#define _UI

/**************************************************************
 * Esta biblioteca es para el manejo de estados del mouse
 * y para otros elementos de interfaz de usuario como mensajes
 * y menus
 * ************************************************************/

/* biblioteca base de elementos geometricos y herramientas fundamentales */
#include <voronoi\geom.h>
/* mensajes y menus para el usuario */
#include <voronoi\msgs.h>

/* representa los estados de las operaciones asignadas a un click 
   sirve para tener un control sobre las operaciones asignadas a 
   cada click */
typedef enum
{
	Hecho,
	NoHecho
} EstadoDeOperacion;

/* representa si un boton esta siendo presionado o no */
typedef enum
{
	Presionado,
	NoPresionado
} EstadoDeBoton;

/* estructura del mouse en si y toda su informacion */
typedef struct
{
	Vertice posicion;
	EstadoDeOperacion operacionClickIzquierdo, operacionClickDerecho;
	EstadoDeBoton clickIzquierdo, clickDerecho;
} Mouse;

/* actualiza toda la informacion del mouse */
void ActualizarMouse(Mouse *mouse);
/* inicializa un mouse */
Mouse newMouse(void);

#include <voronoi\ui.c>

#endif

