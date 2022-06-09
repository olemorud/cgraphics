
//#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"
#include "config.h"

/* 
 * Points store position, position in previous frame and forces
 * velocity is calculated from the distance between (x,y) and (px,py)
 */
typedef struct Point{
	double 	 x,  y,
			px, py,
			fx, fy;
} Point;

/*
 * Links connect two points such that their distance is constant
 * these can be used to make rigid bodies
 */
typedef struct Link {
	Point* a;
	Point* b;
	double length;
} Link;


/*
 * Function declarations
 */
double distance(Point* a, Point* b);
Point* unit_vec(Point* a, Point* b);
Link* link_points(Point* a, Point* b);
void draw_link(Canvas* c, Link* l);
void update_point(Point* p);
void update_link(Link* l);


/*
 * Main
 */
int main(){
	char *data = malloc(WIDTH*HEIGHT);
	Canvas cnv = {WIDTH, HEIGHT, data};

	// Add 4 points, link them, and add points and links to respective arrays
	Point a = { 20.0, 10.0,
				21.0, 10.0, 
				0.0, GRAVITY/(FRAMERATE*FRAMERATE)};

	Point b = { 40.0, 10.0,
				40.0, 10.0,
				0.0, GRAVITY/(FRAMERATE*FRAMERATE)};

	Point c = { 40.0, 30.0,
				39.0, 30.0,
				0.0, GRAVITY/(FRAMERATE*FRAMERATE)};

	Point d = { 20.0, 30.0,
				20.0, 30.0,
				0.0, GRAVITY/(FRAMERATE*FRAMERATE)};

	Link *l_ab = link_points(&a, &b);
	Link *l_bc = link_points(&b, &c);
	Link *l_cd = link_points(&c, &d);
	Link *l_ad = link_points(&a, &d);
	Link *l_ac = link_points(&a, &c);
	Link *l_bd = link_points(&b, &d);

	Point *points[] = {&a, &b, &c, &d};
	Link  *links[]  = {l_ab, l_bc, l_cd, l_ad, l_ac, l_bd};


	while(1){
		// clear canvas, calculate next frame and draw
		memset(cnv.data, OFF, cnv.x * cnv.y);
	

		for(int i=0; i<6; i++)
			draw_link(&cnv, links[i]);

		for(int i=0; i<4; i++){	
			update_point(points[i]);
		}
		
		for(int i=0; i<6; i++){	
			update_link(links[i]);
		}

		// then render and wait
		subpixel_render(&cnv);
		usleep(1000000/FRAMERATE);
	}

	return 0;
}

/*
 * Returns distance of two points
 */
double distance(Point* a, Point* b){
	double dx = a->x - b->x;
	double dy = a->y - b->y;
	
	return sqrt(dx*dx + dy*dy);
}


/*
 * Returns a link between two points
 */
Link* link_points(Point* a, Point* b){
	Link *output = malloc(sizeof(Link));

	output->a = a;
	output->b = b;
	output->length = distance(a, b);

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
 * The update is based on its position (x,y), its position in the previous frame (px, py)
 * and the forces acting upon it (fx,fy)
 */
void update_point(Point* p){
	double tempx = p->x;
	double tempy = p->y;
	p->x += (p->x - p->px) + p->fx;
	p->y += (p->y - p->py) + p->fy;
	p->px = tempx;
	p->py = tempy;
}


/*
 * Moves points in link l such that their distance becomes l.length
 */
void update_link(Link* l){
	double cur_dist = distance(l->a, l->b);
	double delta = (l->length - cur_dist)/2.0f;

	double nx = (l->b->x - l->a->x)/cur_dist;
	double ny = (l->b->y - l->a->y)/cur_dist;
	
	l->a->x -= nx * delta;
	l->a->y -= ny * delta;
	l->b->x += nx * delta;
	l->b->y += ny * delta;
}

