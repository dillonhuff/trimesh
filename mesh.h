
#include "parse_stl.h"

using namespace stl;

struct triangle_points {
  int vertexes[3];

  triangle_points(int v0, int v1, int v2) {
    vertexes[0] = v0;
    vertexes[1] = v1;
    vertexes[2] = v2;
  }

};

// The mesh class
class triangular_mesh {
public:

  std::vector<point> vertexes;
  std::vector<triangle_points> triangles;
  
};
