
#include <stdio.h>
#include <stdlib.h>
#include "rpg/position.h"
#include <time.h>

int main(int argc, char *argv[]) {
  if (argc != 7) {
    fprintf(stderr, "Use: ./body_gen x1 y1 x2 y2 body_num output_filename\n");
    return -1;
  }
  srand(time(NULL));
  /* variables */
  Rect *range;
  int body_num;
  char *filename;
  FILE *fd;
  int i;

  range = malloc(sizeof(Rect));
  if (!range) {
    fprintf(stderr, "Error: fail to malloc.\n");
    return -1;
  }
  range->ll.x = atof(argv[1]);
  range->ll.y = atof(argv[2]);
  range->ur.x = atof(argv[3]);
  range->ur.y = atof(argv[4]);

  body_num = atoi(argv[5]);
  filename = argv[6];
  fd = fopen(filename, "w");

  fprintf(fd, "%d\n", body_num);
  for (i = 0; i < body_num; i++) {
    Point p;
    rand_pos_in_rect(range, 1000, &p, 0);
    fprintf(fd, "%f %f 1\n", p.x, p.y);
  }

  fclose(fd);
  return 0;
}
