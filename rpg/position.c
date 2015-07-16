
#include "rpg/position.h"
#include <math.h>
#include <string.h>

#define RAND(precision) ((double) rand() / (precision))
#define RAND_ONE_DIM_IN_RECT(rand, dim, rect, precision) \
        RAND(precision);\
        while (rand##dim < (rect->ll).dim || rand##dim > (rect->ur).dim) {\
          rand##dim = RAND(precision);\
        }

#define SQUARE(x) ((x)*(x))
#define DISTANCE(x1, y1, x2, y2) \
        sqrt(SQUARE((x1)-(x2))+SQUARE((y1)-(y2)))

#define LEN_ONE_DIM(rect, dim, precision) \
        ((int) (((rect->ur).dim - (rect->ll).dim)) * precision )


void rand_pos_in_rect(Rect *rect, int precision, Point *result, int isdisplay) {
/*
  Generate a random position in rect with precision.
  precision may be 1, 10, 1000, 10000, 100000, ...
  we will generate a value divided by precision.
*/
  if (!rect) {
    fprintf(stderr, "Error: rect ptr is NULL\n");
    exit(1);
  }
  /* length * precision */
  int len_x = LEN_ONE_DIM(rect, x, precision);
  int len_y = LEN_ONE_DIM(rect, y, precision);
  int tmp_x = rand() % len_x;
  int tmp_y = rand() % len_y;
  double rand_x = (double) tmp_x / precision + (rect->ll).x;
  double rand_y = (double) tmp_y / precision + (rect->ll).y;
  
  /* output rand pos to result if not null ptr */
  if (result) {
    result->x = rand_x;
    result->y = rand_y;
  }
  /* dispaly to stdout */
  if (isdisplay) {
    fprintf(stdout, "%f\t%f", rand_x, rand_y);
  }
}

void rand_pos_in_circ(Circ *circ, int precision, Point *result, int isdisplay) {
/*
  Generate a random position in circle with precision.
  precision may be 1, 10, 1000, 10000, ....
  we will generate a value divided by precision.
*/
  if (!circ) {
    fprintf(stderr, "Error: circ ptr is NULL\n");
    exit(1);
  }
  /* radius * precision */
  int len_r = (int) (circ->r * precision);
  double rand_r = (double) (rand() % len_r) / precision;
  double radian = (double) rand();
  double rand_x = cos(radian) * rand_r + (circ->c).x;
  double rand_y = sin(radian) * rand_r + (circ->c).y;
  /* output rand pos to result if not null ptr */
  if (result) {
    result->x = rand_x;
    result->y = rand_y;
  }
  /* dispaly to stdout */
  if (isdisplay) {
    fprintf(stdout, "%f\t%f", rand_x, rand_y);
  }
}

void rand_pos_in_rect1_out_rect2(Rect *rect1, Rect *rect2, int precision, Point *result, int isdisplay) {
/*
  Generate a random position in rect1 but out of rect2
  precision may be 1, 10, 1000, 10000, ....
  we will generate a value divided by precision.
*/
  if (!rect1 || !rect2) {
    fprintf(stderr, "Error: rect1 or rect2 ptr is NULL\n");
    exit(1);
  }
  Point tmp_pos;
  /* generate a random position in rect1 */
  rand_pos_in_rect(rect1, precision, &tmp_pos, 0);

  /* check whether the position in rect2 */
  while (tmp_pos.x > (rect2->ll).x && tmp_pos.x < (rect2->ur).x &&
         tmp_pos.y > (rect2->ll).y && tmp_pos.y < (rect2->ur).y) {
    rand_pos_in_rect(rect1, precision, &tmp_pos, 0);
  }
  /* output rand pos to result if not null ptr */
  if (result) {
    result->x = tmp_pos.x;
    result->y = tmp_pos.y;
  }
  /* dispaly to stdout */
  if (isdisplay) {
    fprintf(stdout, "%f\t%f", tmp_pos.x, tmp_pos.y);
  }
}

void rand_pos_in_ring(Ring *ring, int precision, Point *result, int isdisplay) {
/*
  Generate a random position in ring
  precision may be 1, 10, 1000, 10000, ....
  we will generate a value divided by precision.
*/
  if (!ring) {
    fprintf(stderr, "Error: ring ptr is NULL\n");
    exit(1);
  }
  /* (outter radius - inner radius) * precision */
  int len_r = (int) ((ring->outr - ring->inr) * precision);
  double rand_r = (double) (rand() % len_r) / precision + ring->inr;
  double radian = (double) rand();
  double rand_x = cos(radian) * rand_r + (ring->c).x;
  double rand_y = sin(radian) * rand_r + (ring->c).y;
  /* output rand pos to result if not null ptr */
  if (result) {
    result->x = rand_x;
    result->y = rand_y;
  }
  /* dispaly to stdout */
  if (isdisplay) {
    fprintf(stdout, "%f\t%f", rand_x, rand_y);
  }

}

void rand_pos_n_id_in_rect(int sid, int num, Rect *rect, int precision, Point *result, int isdisplay) {
/*
  Generate num random positions with id in rect
  precision may be 1, 10, 1000, ...
  we will generate a value divided by precision.
  sid: start id
*/
  int i;
  for (i = 0; i < num; i++) {
    if (isdisplay) {
      fprintf(stdout, "%d\t", sid+i);
    }

    rand_pos_in_rect(rect, precision, result, isdisplay);

    if (isdisplay) {
      fprintf(stdout, "\n");
    }
    if (result) {
      result++;
    }
  }

}

void mesh_new(Mesh *mesh, int x_num, double *x, int y_num, double *y) {
  mesh->x_num = x_num;
  mesh->x = malloc(x_num*sizeof(double));
  memcpy(mesh->x, x, x_num*sizeof(double));
  mesh->y_num = y_num;
  mesh->y = malloc(y_num*sizeof(double));
  memcpy(mesh->y, y, y_num*sizeof(double));
  mesh->rect_num = (x_num - 1) * (y_num - 1);
  mesh->rect = malloc(mesh->rect_num * sizeof(Rect));
  int i;
  for (i = 0; i < mesh->rect_num; i++) {
    (mesh->rect[i]).ll.x = mesh->x[i / (y_num - 1)];
    (mesh->rect[i]).ll.y = mesh->y[i % (y_num - 1)];
    (mesh->rect[i]).ur.x = mesh->x[i / (y_num - 1) + 1];
    (mesh->rect[i]).ur.y = mesh->y[i % (y_num - 1) + 1];
  }
}

void mesh_free(Mesh *mesh) {
  if (!mesh) {
    fprintf(stderr, "Error: mesh ptr is NULL.\n");
    exit(1); 
  }
  if (mesh->x) {
    free(mesh->x);
    mesh->x = NULL;
  }
  if (mesh->y) {
    free(mesh->y);
    mesh->y = NULL;
  }
  if (mesh->rect) {
    free(mesh->rect);
    mesh->rect = NULL;
  }
}
