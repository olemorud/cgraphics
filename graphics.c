
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
#ifndef abs
#define abs(x) ((x<0)?(-x):(x))
	int dx = abs(end_x - start_x);
	int dy = abs(end_y - start_y);

	int direction_x = start_x < end_x ? 1 : -1;
	int direction_y = start_y < end_y ? 1 : -1;

	printf("dx:%i dy:%i direction:%i,%i  \n", dx, dy, direction_x, direction_y);

	if(dx>=dy){
		float small = direction_y * (float)dy/(float)dx;
		
		for(int i=0; i<dx+1; i++){
			dot(c, start_x + i*direction_x, start_y + i*small);
		}
	}else{
		float small = direction_x * (float)dx/(float)dy;
		
		for(int i=0; i<dy+1; i++){
			dot(c, start_x + i*small, start_y + i*direction_y);
		}
	}

#undef abs
#endif
}


int main(){
	char data[] =
		"----------"
		"----------"
		"----------"
		"----------"
		"----------"
		"----------"
		"----------"
		"----------"
		"----------"
		"----------";

	Canvas a = {10, 10, data};

	//line(&a, 1, 1, 8, 8);
	line(&a, 8, 8, 1, 1);
	//line(&a, 5, 5, 8, 8);

	dot(&a, 0, 0);
	dot(&a, 9, 9);

	render(&a);

	return 0;
}
