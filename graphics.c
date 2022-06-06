#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define uint unsigned int
#define ON 'x'
#define OFF '-'

typedef struct Canvas {
	int x;
	int y;
	char* data;
} Canvas;



// DECLARATIONS
void render(Canvas* c);
void line(Canvas* c, uint start_x, uint start_y, uint end_x, uint end_y);
void dot(Canvas* c, uint x, uint y);


/*
 * main
 */
int main(){
	Canvas a = {40, 40, malloc(40*40)};
	memset(a.data, OFF, a.x * a.y);

	//line(&a, 1, 1, 8, 8);
	//line(&a, 8, 8, 1, 1);
	//line(&a, 0, 5, 8, 8);
	line(&a, 8, 8, 0, 5);


	render(&a);

	return 0;
}



/*
 * Draws an x*y rectangle with the characters in canvas* c
 */
void render(Canvas* c){
	putchar('\n');

	for(int i=0; i < c->y; i++){
		for(int j=0; j < c->x; j++){
			putchar(c->data[i*(c->x)+j]);
			putchar(' ');
		}
		putchar('\n');
	}
}

/*
 * Sets pixel at x,y to ON
 */
void dot(Canvas* c, uint x, uint y){	
	c->data[ y*(c->x) + x] = ON;
}

/*
 * Draws a line from (start_x, start_y) to (end_x, end_y)
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

