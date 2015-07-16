
#include "rpg/position.h"
#include <time.h>

int main() {
  srand(time(NULL));
  Mesh mesh;
  double x[4] = {0, 167, 333, 500};
  double y[4] = {0, 167, 333, 500};
  int users[9] = {100, 43, 43, 43, 43, 42, 43, 42, 42};
  mesh_new(&mesh, 4, x, 4, y);
/*
  printf("%d\t%d\t%d\n", mesh.x_num, mesh.y_num, mesh.rect_num);
  int i;
  for (i = 0; i < mesh.rect_num; i++) {
    printf("%f\t%f\n", mesh.rect[i].ll.x, mesh.rect[i].ll.y);
    printf("%f\t%f\n", mesh.rect[i].ur.x, mesh.rect[i].ur.y);
  }
*/
  int i;
  int id = 0;
  for (i = 0; i < mesh.rect_num; i++) {
    rand_pos_n_id_in_rect(id, users[i], &(mesh.rect)[i], 1000, NULL, 1);
    id += users[i];
  }
  mesh_free(&mesh);
  return 0;
}
