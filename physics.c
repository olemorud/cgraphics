

#include "graphics.h"
#include <stdlib.h>
#include <string.h>

#define GRAVITY 0.01f
#define FRAMERATE 10

typedef struct Point{
	double x;
	double y;
	double px;
	double py;
	double fx;
	double fy;
} Point;

typedef struct Link {
	Point* a;
	Point* b;
	double length;
} Link;



void draw_link(Canvas* c, Link* l){
	line(c, l->a->x, l->a->y, l->b->x, l->b->y);
}

void update_point(Point* p){
	uint tempx = p->x;
	uint tempy = p->y;
	p->x += (p->x - p->px) + p->fx;
	p->y += (p->y - p->py) + p->fy;
	p->px = tempx;
	p->py = tempy;
}


int main(){
	char *data = malloc(40*40);
	Canvas c = {40, 40, data};

	Point a = { 10.0, 10.0,
				10.0, 10.0, 
				0.0, GRAVITY/FRAMERATE};

	Point b = { 20.0, 10.0,
				20.0, 10.0,
				0.0, GRAVITY/FRAMERATE};

	Link l_ab = {&a, &b, 10};
	
	while(1){
		// clear canvas, calculate next frame and draw
		memset(c.data, '.', c.x * c.y);
		draw_link(&c, &l_ab);
		update_point(&a);
		update_point(&b);

		// then render and wait
		render(&c);
		usleep(1000000/FRAMERATE);
	}



	return 0;
}


