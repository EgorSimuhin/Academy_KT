#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();
  gmsh::model::add("tc");
  double lc = 1e-1;
  
  int a1 = gmsh::model::geo::addPoint(1, 0, 0, lc);
  int b1 = gmsh::model::geo::addPoint(0, 1, 0, lc);
  int c1 = gmsh::model::geo::addPoint(-1, 0, 0, lc);
  int d1 = gmsh::model::geo::addPoint(0, -1, 0, lc);
  int cen1= gmsh::model::geo::addPoint(0, 0, 0, lc);

  int A1 = gmsh::model::geo::addCircleArc(a1, cen1, b1);
  int B1 = gmsh::model::geo::addCircleArc(b1, cen1, c1);
  int C1 = gmsh::model::geo::addCircleArc(c1, cen1, d1);
  int D1 = gmsh::model::geo::addCircleArc(d1, cen1, a1);

  int a2 = gmsh::model::geo::addPoint(1, 0, 2, lc);
  int b2 = gmsh::model::geo::addPoint(0, 1, 2, lc);
  int c2 = gmsh::model::geo::addPoint(-1, 0, 2, lc);
  int d2 = gmsh::model::geo::addPoint(0, -1, 2, lc);
  int cen2 = gmsh::model::geo::addPoint(0, 0, 2, lc);

  int A2 = gmsh::model::geo::addCircleArc(a2, cen2, b2);
  int B2 = gmsh::model::geo::addCircleArc(b2, cen2, c2);
  int C2 = gmsh::model::geo::addCircleArc(c2, cen2, d2);
  int D2 = gmsh::model::geo::addCircleArc(d2, cen2, a2);

  int A3 = gmsh::model::geo::addLine(a1, a2);
  int B3 = gmsh::model::geo::addLine(b1, b2);
  int C3 = gmsh::model::geo::addLine(c1, c2);
  int D3 = gmsh::model::geo::addLine(d1, d2);

  int K1 = gmsh::model::geo::addCurveLoop({A1, B1, C1, D1});
  int K2 = gmsh::model::geo::addCurveLoop({A2, B2, C2, D2});
  int K3 = gmsh::model::geo::addCurveLoop({A1, B3, -A2, -A3});
  int K4 = gmsh::model::geo::addCurveLoop({B1, C3, -B2, -B3});
  int K5 = gmsh::model::geo::addCurveLoop({C1, D3, -C2, -C3});
  int K6 = gmsh::model::geo::addCurveLoop({D1, A3, -D2, -D3});


  int sigma1 = gmsh::model::geo::addPlaneSurface({K1});
  int sigma2 = gmsh::model::geo::addPlaneSurface({K2});
  int sigma3 = gmsh::model::geo::addSurfaceFilling({K3});
  int sigma4 = gmsh::model::geo::addSurfaceFilling({K4});
  int sigma5 = gmsh::model::geo::addSurfaceFilling({K5});
  int sigma6 = gmsh::model::geo::addSurfaceFilling({K6});
    

  int sigma = gmsh::model::geo::addSurfaceLoop({sigma1, sigma2, sigma3, sigma4, sigma5, sigma6});

  int volume = gmsh::model::geo::addVolume({sigma});
  gmsh::model::geo::synchronize();
  gmsh::model::mesh::generate(3);
  gmsh::write("cylinder.msh");
  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();
  gmsh::finalize();
  return 0;
}
