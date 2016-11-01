#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>

#include "mesh.h"
#include "parse_stl.h"

using namespace stl;

void visualize_polydata(vtkSmartPointer<vtkPolyData> polyData) {
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData); //Connection(polyData->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green
 
  renderWindow->Render();
  renderWindowInteractor->Start();
}

vtkSmartPointer<vtkPolyData>
polydata_from_triangular_mesh(const triangular_mesh& mesh) {
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  for (auto pt : mesh.vertexes) {
    points->InsertNextPoint(pt.x, pt.y, pt.z);
  }

  vtkSmartPointer<vtkCellArray> triangles =
    vtkSmartPointer<vtkCellArray>::New();

  
  for (auto t : mesh.triangles) {
    vtkSmartPointer<vtkTriangle> triangle =
      vtkSmartPointer<vtkTriangle>::New();
    
    triangle->GetPointIds()->SetId(0, t.vertexes[0]);

    triangle->GetPointIds()->SetId(1, t.vertexes[1]);

    triangle->GetPointIds()->SetId(2, t.vertexes[2]);

    triangles->InsertNextCell(triangle);
  }
 
  // Create a polydata object
  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
 
  // Add the geometry and topology to the polydata
  polyData->SetPoints ( points );
  polyData->SetPolys ( triangles );

  return polyData;
}

triangular_mesh
triangle_list_to_triangular_mesh(const std::vector<triangle>& tris) {
  std::vector<triangle_points> triangles;
  std::vector<point> vertexes;

  for (auto t : tris) {
    vertexes.push_back(t.v1);
    vertexes.push_back(t.v2);
    vertexes.push_back(t.v3);

    triangle_points tri(vertexes.size() - 3, vertexes.size() - 2, vertexes.size() - 1);

    triangles.push_back(tri);
  }

  return triangular_mesh{vertexes, triangles};
}

int main(int argc, char* argv[]) {
  assert(argc == 2);

  auto file = argv[1];
  auto stl_triangles = parse_stl(file).triangles;
  triangular_mesh m = triangle_list_to_triangular_mesh(stl_triangles);

  auto polyData = polydata_from_triangular_mesh(m);

  visualize_polydata(polyData);
 
  return EXIT_SUCCESS;
}
