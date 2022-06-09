#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "config.h"
#include <locale.h>

#define uint unsigned int

typedef struct Canvas {
	int x;
	int y;
	char* data;
} Canvas;



// Function Declarations
void clear();
void render(Canvas* c);
void line(Canvas* c, uint start_x, uint start_y, uint end_x, uint end_y);
void dot(Canvas* c, const uint x, const uint y);
void subpixel(int m1, int m2, int n1, int n2);


/*
 * Renders canvas* c on screen and adds line numbers on left and bottom
 */
void render(Canvas* c){
	clear();
	putchar('\n');

	for(int i=0; i < c->y; i++){
#if LINENUMBERS
		printf("%2i ", i); //horizontal line numbers
#endif
		
		for(int j=0; j < c->x; j++){
			putchar(c->data[i*(c->x)+j]);
			putchar(' ');
		}
		putchar('\n');
	}
	
#if LINENUMBERS
	// vertical line numbers
	for(int i=0; i<(c->x); i+=2){
		printf("  %2i", i);
	}
#endif
}


/*
 *	Renders canvas with subpixel rendering
 * */
void subpixel_render(Canvas* c){
	setlocale(LC_ALL, "C.UTF-8");
	clear();
	putchar('\n');

	for(int i=0; i < c->y; i+=2){
#if LINENUMBERS
		printf("%2i ", i*2); // horizontal line numbers
#endif
		for(int j=0; j < c->x; j+=2){
			subpixel( 	c->data[i*(c->x) + j] == ON,     c->data[i*(c->x) + j+1] == ON,
						c->data[(i+1)*(c->x) + j] == ON, c->data[(i+1)*(c->x) + j+1] == ON);
			putchar(' ');
		}
		putchar('\n');
	}

#if 0
	// vertical line numbers
	for(int i=0; i<(c->x) / 2; i+=2){
		printf("  %2i", i*2);
	}
#endif
}


/*
 * Sets pixel at x,y to ON
 */
void dot(Canvas* c, const uint x, const uint y){
	c->data[ y*(c->x) + x] = ON;
}


/*
 * Draws a line from (start_x, start_y) to (end_x, end_y)
 * This is the naive line drawing algorithm and is sub-optimal due to the use of floating point calculations
 */
void line(Canvas* c, uint start_x, uint start_y, uint end_x, uint end_y){
	int dx = end_x - start_x;
	int dy = end_y - start_y;
	if (dx<0) dx *= -1;
	if (dy<0) dy *= -1;

	if((dx>=dy && start_x>end_x) || ( dx<dy && start_y>end_y)){
			int temp;

			temp = end_x;
			end_x = start_x;
			start_x = temp;
			
			temp = end_y;
			end_y = start_y;
			start_y = temp;
	}

	int direction_x = start_x < end_x ? 1 : -1;
	int direction_y = start_y < end_y ? 1 : -1;

	if(dx>=dy){
		float small = direction_y * (float)dy/(float)dx;
		
		for(int i=0; i<dx; i++){
			dot(c, start_x + i*direction_x, start_y + nearbyintf(i*small));
		}
	}else{
		float small = direction_x * (float)dx/(float)dy;
		
		for(int i=0; i<dy; i++){
			dot(c, start_x + nearbyintf(i*small), start_y + i*direction_y);
		}
	}

	dot(c, end_x, end_y);
}


/*
 * Clears terminal (for ANSI like terminal emulation)
 */
void clear(){
	printf("\033[2;2H");	
}

/*
 * Print 4 pixels as unicode character
 * pixel arrangement is like this:
 * m1,m2           1  0
 * n1,n2, example: 0  1  =  '▚'
 */
void subpixel(int m1, int m2, int n1, int n2){	
	const wchar_t *quads[] = 
	{
	/*       00,  01,  10,  11*/
	/*00*/	L" ", L"▝", L"▘", L"▀",
	/*01*/	L"▗", L"▐", L"▚", L"▜",
	/*10*/	L"▖", L"▞", L"▌", L"▛",
	/*11*/	L"▄", L"▟", L"▙", L"█",
	};

	int x = !!m2 + (!!m1<<1); 
	int y = !!n2 + (!!n1<<1);

	printf("%ls", quads[y*4 + x]);
	printf("%s", "" );
}

