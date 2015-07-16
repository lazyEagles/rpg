/*
  mesh with 3*3 sub-rectangular
  generate random positions in each subrectangular
*/
#include "rpg/position.h"
#include <time.h>

int main (int argc, char *argv[]) {
  if (argc != 10) {
    fprintf(stderr, "Format: ./mpg num0 num1 ... num8\n");
    exit(1);
  }
  /* select seed for rand() */
  srand(time(NULL));
  int num[9]; /* number of positions in each subrectangular */
  int i;
  for (i = 0; i < 9; i++) {
    num[i] = atoi(argv[i+1]);
  }
  Mesh mesh;
  double xp[4] = {0, 167, 333, 500};
  double yp[4] = {0, 167, 333, 500};
  mesh_new(&mesh, 4, xp, 4, yp);
  int id = 0;
  for (i = 0; i < 9; i++) {
    rand_pos_n_id_in_rect(id, num[i], &mesh.rect[i], 1000, NULL, 1);
    id += num[i];
  }
  mesh_free(&mesh);
  return 0;
}
