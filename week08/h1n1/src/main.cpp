#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 P;

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t n; std::cin >> n;

  while (n != 0) {
    // handle testcase
    std::vector<P> infected(n);
    for (size_t i = 0; i < n; i++)
      cin >> infected[i];

    Triangulation t;
    t.insert(infected.begin(), infected.end());
    std::multiset<std::pair<Triangulation::Face_handle, K::FT>, pair_sorter> handles_edges;
    std::cin >> n;
  }
  return 0;
}