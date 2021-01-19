#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_data_structure_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Triangulation_vertex_base_with_info_2<IK::FT, IK> vertex_t;
typedef CGAL::Triangulation_face_base_2<IK> face_t;
typedef CGAL::Triangulation_data_structure_2<vertex_t, face_t> triangulation_t;
typedef CGAL::Delaunay_triangulation_2<IK, triangulation_t> delaunay_t;

double ceil_to_double(EK::FT const& x) {
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a - 1 >= x) a -= 1;
  return a;
}