#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;

void testcase() {
  size_t n, m, k;
  long s;

  std::cin >> n >> m >> s >> k;

  std::vector<P> trees(n);
  for(size_t i = 0; i < n; i++) {
    std::cin >> trees(i);
  }

  Triangulation tri;
  tri.insert(trees.begin(), trees.end());

  std::vector<P> bones(m);
  for(int i = 0; i < m; i++) {
    std::cin >> bones(i);
  }
  std::cout << 0 << " " << 1 << "\n";
}

int main() {
  int t;

  for(std::cin >> t; t > 0; t--) {
    testcase();
  }
}