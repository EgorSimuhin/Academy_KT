#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();

  gmsh::model::add("t2");

  double lc = 1e-1;
  gmsh::model::geo::addPoint(0, 0, 0, lc, 4);
  gmsh::model::geo::addPoint(1, 0, 0, lc, 1);
  gmsh::model::geo::addPoint(1, 1, 0, lc, 2);
  gmsh::model::geo::addPoint(0, 1, 0, lc, 3);
  gmsh::model::geo::addPoint(0, 0, 1, lc, 5);
  gmsh::model::geo::addPoint(0, 1, 1, lc, 6);
  gmsh::model::geo::addPoint(1, 1, 1, lc, 7);
  gmsh::model::geo::addPoint(1, 0, 1, lc, 8);

  gmsh::model::geo::addLine(1, 2, 1);
  gmsh::model::geo::addLine(2, 3, 2);
  gmsh::model::geo::addLine(3, 4, 3);
  gmsh::model::geo::addLine(4, 1, 4);

  gmsh::model::geo::addLine(8, 7, 5);
  gmsh::model::geo::addLine(7, 6, 6);
  gmsh::model::geo::addLine(6, 5, 7);
  gmsh::model::geo::addLine(5, 8, 8);


  gmsh::model::geo::addLine(1, 8, 9);
  gmsh::model::geo::addLine(2, 7, 10);
  gmsh::model::geo::addLine(3, 6, 11);
  gmsh::model::geo::addLine(4, 5, 12);

//  for(int i = 0; i < 3; i++)
//   gmsh::model::geo::addLine(i + 1, 4, i + 4);

  gmsh::model::geo::addCurveLoop({1, 2, 3, 4}, 1);
  gmsh::model::geo::addPlaneSurface({1}, 1);

  gmsh::model::geo::addCurveLoop({5, 6, 7, 8}, 2);
  gmsh::model::geo::addPlaneSurface({2}, 2);

  gmsh::model::geo::addCurveLoop({1, 10, -5, -9}, 3);
  gmsh::model::geo::addPlaneSurface({3}, 3);

  gmsh::model::geo::addCurveLoop({2, 11, -6, -10}, 4);
  gmsh::model::geo::addPlaneSurface({4}, 4);

  gmsh::model::geo::addCurveLoop({3, 12, -7, -11}, 5);
  gmsh::model::geo::addPlaneSurface({5}, 5);
  
  gmsh::model::geo::addCurveLoop({4, 9,  -8, -12}, 6);
  gmsh::model::geo::addPlaneSurface({6}, 6);
  

  gmsh::model::geo::addSurfaceLoop({1, 2, 3, 4, 5, 6}, 1);
  gmsh::model::geo::addVolume({1});

  gmsh::model::geo::synchronize();

  gmsh::model::mesh::generate(3);

  gmsh::write("cub.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}

