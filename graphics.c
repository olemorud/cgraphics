
#include <stdio.h>

#define uint unsigned int
#define ON 'x'
#define OFF '-'

typedef struct Canvas {
	int x;
	int y;
	char* data;
} Canvas;

/*
 * Draws an x*y rectangle with the characters in canvas* c
 */
void render(Canvas* c){
	putchar('\n');

	for(int i=0; i < c->y; i++){
		for(int j=0; j < c->x; j++){
			putchar(c->data[i*(c->x)+j]);	
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
#ifndef abs
#define abs(x) ((x<0)?(-x):(x))

	
	int dx = abs(end_x - start_x);
	int dy = abs(end_y - start_y);

	int direction_x = start_x < end_x ? 1 : -1;
	int direction_y = start_y < end_y ? 1 : -1;

	printf("dx:%i dy:%i direction:%i,%i", dx, dy, direction_x, direction_y);

	if(dx>dy){
		for(int i=0; i<dx; i++){
			dot(c, start_x+i*direction_x, start_y+(dy/(i+1))*direction_y);
		}
	}else{
		for(int i=0; i<dy; i++){
			dot(c, start_x+(dx/(i+1))*direction_x, start_y+i*direction_y);
		}
	}

#undef abs
#endif
}


int main(){
	char data[] =
		"---"
		"---"
		"---";

	Canvas a = {3, 3, data};

	//line(&a, 0, 0, 3, 3);

	dot(&a, 0, 0);
	dot(&a, 2, 2);

	render(&a);

	return 0;
}
