
#ifndef RPG_POSITION_H
#define RPG_POSITION_H 1

#include <stdio.h>
#include <stdlib.h>

typedef struct point {
  double x;
  double y;
} Point;

typedef struct rectangular {
  Point ll; /* lower left point */
  Point ur; /* upper right point */
} Rect;

typedef struct circle {
  Point c; /* center of circle */
  double r; /* radius of circle */
} Circ;

typedef struct ring {
  Point c; /* center of ring */
  double inr; /* inner radius of ring */
  double outr; /* outer radius of ring */
} Ring;

typedef struct mesh {
  int x_num; /* number of points on x */
  double *x; /* points on x */
  int y_num; /* number of points on y */
  double *y; /* points on y */
  int rect_num; /* number of rect in mesh */
  Rect* rect; /* rect in mesh */
} Mesh;

void rand_pos_in_rect(Rect *rect, int precision, Point *result, int isdisplay);
void rand_pos_in_circ(Circ *circ, int precision, Point *result, int isdisplay);

void rand_pos_in_rect1_out_rect2(Rect *rect1, Rect *rect2, int precision, Point *result, int isdisplay); 
void rand_pos_in_ring(Ring *ring, int precision, Point *result, int isdisplay); 

void rand_pos_n_id_in_rect(int sid, int num, Rect *rect, int precision, Point *result, int isdisplay); 
void mesh_new(Mesh *mesh, int x_num, double *x, int y_num, double *y); 
void mesh_free(Mesh *mesh); 
#endif
