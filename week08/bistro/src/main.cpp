#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <algorithm>
#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;

int main(int argc, char const *argv[]) {
  std::ios_base::sync_with_stdio(false);

  size_t n;
  std::cin >> n;

  while (n > 0) {
    std::vector<K::Point_2> pts;
    pts.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      K::Point_2 p;
      std::cin >> p;
      pts.push_back(p);
    }

    Triangulation t;
    t.insert(pts.begin(), pts.end());

    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
      K::Point_2 new_location;
      std::cin >> new_location;
      std::cout << std::fixed << std::setprecision(0)
                << CGAL::squared_distance(
                       new_location, t.nearest_vertex(new_location)->point())
                << "\n";
    }

    std::cin >> n;
  }
}