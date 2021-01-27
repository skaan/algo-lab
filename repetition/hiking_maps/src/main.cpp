#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::Triangle_2 Triangle;

void testcase() {
  int m, n; std::cin >> m >> n;

  std::vector<Point> path(m);
  for(int i = 0; i < m; i++) {
    std::cin >> path[i];
  }

  for (int i = 0; i < n; ++i) {
    std::vector<Point> t;
    for (int j = 0; j < 6; j++) {
      int x, y; std::cin >> x >> y;
      t.push_back(Point(x,y));
    }

    for (int j = 0; j < 6; j+=2) {
      if (CGAL::right_turn(t[j], t[j+1], t[(j+2)%6])) std::swap(t[j],t[j+1]);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) {
    testcase();
  }
  return 0;
}