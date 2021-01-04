#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Segment_2 S;
typedef K::Point_2 P;
typedef K::Ray_2 R;

void testcase(int n)
{
  // setup ray
  long x, y, a, b;
  std::cin >> x >> y >> a >> b;

  P start = P(x, y);
  P point = P(a, b);
  R ray = R(start, point);

  // setup n segments
  bool intersecting = false;
  for(int i = 0; i < n; i++) {
    long r, s, t, u;
    std::cin >> r >> s >> t >> u;
    if (!intersecting) {
      S segment = S(P(r, s), P(t, u));
      if (CGAL::do_intersect(ray, segment)) intersecting = true;
    }
  }

  if (intersecting)
    std::cout << "yes" << "\n";
  else
    std::cout << "no" << "\n";
}

int main()
{
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
  while (n != 0) {
    testcase(n);

    std::cin >> n;
  }
}