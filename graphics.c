#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define uint unsigned int
#define ON 'x'
#define OFF '.'

typedef struct Canvas {
	int x;
	int y;
	char* data;
} Canvas;



// Function Declarations
void clear();
void render(Canvas* c);
void line(Canvas* c, uint start_x, uint start_y, uint end_x, uint end_y);
void dot(Canvas* c, uint x, uint y);


/*
 * main
 */
int main(){
	char *data = malloc(40*40);
	Canvas c = {40, 40, data};
	memset(c.data, OFF, c.x * c.y);

	//line(&c, 1, 1, 8, 8);
	//line(&c, 8, 8, 1, 1);
	//line(&c, 0, 5, 8, 8);
	line(&c, 8, 8, 35, 39);


	render(&c);

	return 0;
}



/*
 * Renders canvas* c on screen and adds line numbers on left and bottom
 */
void render(Canvas* c){
	clear();
	putchar('\n');

	for(int i=0; i < c->y; i++){
		printf("%2i ", i); //horizontal line numbers
		
		for(int j=0; j < c->x; j++){
			putchar(c->data[i*(c->x)+j]);
			putchar(' ');
		}
		putchar('\n');
	}
	
	// vertical line numbers
	printf("  ");
	for(int i=0; i<(c->x); i+=2){
		printf("%2i  ", i);
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


//TODO: find escape sequence for clearing screen
void clear(){
	printf("function clear() not implemented yet");
}

