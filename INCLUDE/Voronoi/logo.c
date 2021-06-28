#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <voronoi\logo.h>

void presentacion(){
	colores colorBorde=blanco;

	circulo();

	poligono();

	relleno();

	internos();

	setcolor(colorBorde);

	settextstyle(6,0,1);
	outtextxy(295,230,"LIFE IS TECHNOLOGY");

	settextstyle(3,0,5);
	outtextxy(210,getmaxy()-130,"GITRICH Lab");
	/*
	settextstyle(2,0,5);
	outtextxy(290,getmaxy()-35,"LOADING.");

	barraDeCarga();*/

}

void barraDeCarga(){
	colores colorBorde=blanco, colorFondo=blanco;
	int i;
	setcolor(colorBorde);
/*
	line(0,getmaxy(),70,getmaxy()-70);
	line(getmaxx()-70,getmaxy()-70,getmaxx(),getmaxy());
	line(0,0,70,70);
	line(getmaxx(),0,getmaxx()-70,70);  210
	*/
	rectangle(290, getmaxy()-70, 345, getmaxy()-50);
	rectangle(345, getmaxy()-65, 350, getmaxy()-55);

	setfillstyle(SOLID_FILL, colorFondo);
	floodfill(347,getmaxy()-66,colorBorde);

	colorFondo=rojo2;
	for(i=0; i<46; i++){

		if(i%2==0){

			colorBorde=getbkcolor();
			setcolor(colorBorde);
			settextstyle(2,0,5);
			outtextxy(290,getmaxy()-35,"LOADING...");

			colorBorde=blanco;
			setcolor(colorBorde);
			settextstyle(2,0,5);
			outtextxy(290,getmaxy()-35,"LOADING..");

		}else{
			settextstyle(2,0,5);
			outtextxy(290,getmaxy()-35,"LOADING...");
		}


		setfillstyle(LTBKSLASH_FILL, colorFondo);
		bar(291, getmaxy()-69, 301+i, getmaxy()-51);

		delay(100);
	}
}

void circulo(){
	colores colorFondo=negro, colorBorde=blanco;

	setbkcolor(colorFondo);
	setcolor(colorBorde);
	setlinestyle(0,1,3);

	colorFondo=azul;
	setfillstyle(SOLID_FILL, colorFondo);
	circle(getmaxx()/2,(getmaxy()/2)-60, 160);
	floodfill(getmaxx()/2,(getmaxy()/2)-60, colorBorde);
}

void poligono(){
	colores colorBorde=blanco;
	setcolor(colorBorde);

	/* construccion del poligono */

	setlinestyle(0,1,3); /* exterior 1 */
	line(190,117,195,248);

	setlinestyle(0,1,3); /* exterior 2 */
	line(195,248,265,315);

	setlinestyle(0,1,3); /* exterior 3 */
	line(265,315,275,200);

	setlinestyle(0,1,3); /* exterior 4 */
	line(275,200,370,116);

	setlinestyle(0,1,3); /* exterior 5 */
	line(370,116,273,45);

	setlinestyle(0,1,3); /* exterior 6 */
	line(273,45, 190,117);


	/* triangulacion */
	setlinestyle(0,1,3); /* interior 1 */
	line(190,117, 275,200);

	setlinestyle(0,1,3); /* interior 2 */
	line(195,248,275,200);

	setlinestyle(0,1,3); /* interior 3 */
	line(275,200,273,45);

}

void relleno(){
	colores colorBorde=blanco, colorFondo;

	/* rellenado */
	colorFondo=verde;
	setfillstyle(SOLID_FILL, colorFondo);
	floodfill(193,122, colorBorde);

	colorFondo=verde;
	setfillstyle(SOLID_FILL, colorFondo);
	floodfill(275,50, colorBorde);

	colorFondo=verde2;
	setfillstyle(SOLID_FILL, colorFondo);
	floodfill(271,50, colorBorde);

	colorFondo=verde2;
	setfillstyle(SOLID_FILL, colorFondo);
	floodfill(273,205, colorBorde);
}

void internos(){

	colores colorBorde=blanco;

	/* re-triangulacion */
	colorBorde=azul;
	setcolor(colorBorde);

	setlinestyle(0,1,3); /* interior 1 */
	line(190,117, 275,200);

	setlinestyle(0,1,3); /* interior 2 */
	line(195,248,275,200);

	setlinestyle(0,1,3); /* interior 3 */
	line(275,200,273,45);
}

