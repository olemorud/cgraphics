
#include <unistd.h>
#include "graphics.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FRAMERATE 60
#define GRAVITY 0.001f

typedef struct Point{
	double 	 x,  y,
			px, py,
			fx, fy;
} Point;

typedef struct Link {
	Point* a;
	Point* b;
	double length;
} Link;


Link* link_points(Point* a, Point* b);
void draw_link(Canvas* c, Link* l);
void update_point(Point* p);



/*
 * Main
 */
int main(){
	char *data = malloc(40*40);
	Canvas cnv = {40, 40, data};

	// Add 4 points, link them, and add points and links to respective arrays
	Point a = { 10.0, 10.0,
				10.0, 10.0, 
				0.0, GRAVITY/FRAMERATE};

	Point b = { 20.0, 10.0,
				20.0, 10.0,
				0.0, GRAVITY/FRAMERATE};

	Point c = { 20.0, 20.0,
				20.0, 20.0,
				0.0, GRAVITY/FRAMERATE};

	Point d = { 10.0, 20.0,
				10.0, 20.0,
				0.0, GRAVITY/FRAMERATE};

	Link *l_ab = link_points(&a, &b);
	Link *l_bc = link_points(&b, &c);
	Link *l_cd = link_points(&c, &d);
	Link *l_ad = link_points(&a, &d);

	Point *points[] = {&a, &b, &c, &d};
	Link  *links[]  = {l_ab, l_bc, l_cd, l_ad};


	while(1){
		// clear canvas, calculate next frame and draw
		memset(cnv.data, '.', cnv.x * cnv.y);

		for(int i=0; i<4; i++)
			draw_link(&cnv, links[i]);

		for(int i=0; i<4; i++)
			update_point(points[i]);

		// then render and wait
		render(&cnv);
		usleep(1000000/FRAMERATE);
	}

	return 0;
}

/*
 * Returns a link between two points
 */
Link* link_points(Point* a, Point* b){
	Link *output = malloc(sizeof(Link));
	
	double dx = a->x - b->x;
	double dy = a->y - b->y;

	output->a = a;
	output->b = b;
	output->length = sqrt( dx*dx + dy*dy );

	return output;
}

/*
 * Draws a line between linked points
 */
void draw_link(Canvas* c, Link* l){
	line(c, l->a->x, l->a->y, l->b->x, l->b->y);
}

/*
 * Updates the position of a point
 * the update is based on its position, its position in the previous frame (px, py) and the forces acting upon it (fx,fy)
 */
void update_point(Point* p){
	uint tempx = p->x;
	uint tempy = p->y;
	p->x += (p->x - p->px) + p->fx;
	p->y += (p->y - p->py) + p->fy;
	p->px = tempx;
	p->py = tempy;
}

