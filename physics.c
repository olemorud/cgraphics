

#include "graphics.h"
#include <stdlib.h>
#include <string.h>

typedef struct Point{
	uint x;
	uint y;
	uint px;
	uint py;
	uint fx;
	uint fy;
} Point;

typedef struct Link {
	Point* a;
	Point* b;
	double length;
} Link;



void draw_link(Canvas* c, Link* l){
	line(&c, l->a->x, l->a->y, l->b->x, l->b->y);
}

void update_point(Point* p){
	uint tempx = p->x;
	uint tempy = p->y;
	p->x += (p->x - p->px) + fx;
	p->y += (p->y - p->py) + fy;
	p->px = tempx;
	p->py = tempy;
}


int main(){
	char *data = malloc(40*40);
	Canvas c = {40, 40, data};
	memset(c.data, '.', c.x * c.y);


	Point a = {10, 10, 10, 10, 0, 5};
	Point b = {20, 10, 10, 10, 0, 5};
	Link l_ab = {&a, &b, 10};

	//line(&c, 1, 1, 8, 8);
	//line(&c, 8, 8, 1, 1);
	//line(&c, 0, 5, 8, 8);
	
	for(int i=0; i<100; i++){
		draw_link(&c, &l_ab);
		update_point(&a);
		update_point(&b);
	}


	render(&c);

	return 0;
}


