
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

typedef struct Canvas {
	int x;
	int y;
	char* data;
} Canvas;

void clear();
void render(Canvas*);
void subpixel_render(Canvas*);
void line(Canvas*, unsigned int, unsigned int, unsigned int, unsigned int);
void dot(Canvas*, const unsigned int, const unsigned int);

#endif
