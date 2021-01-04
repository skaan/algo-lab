#include <iostream>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Segment_2 S;
typedef K::Point_2 P;
typedef K::Ray_2 R;

double floor_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase(int n)
{
  // setup ray
  long x, y, a, b;
  std::cin >> x >> y >> a >> b;

  P start(x, y), point(a, b);
  R ray = R(start, point);
  S raySegment;

  // setup n segments
  std::vector<S> segments;
  for(int i = 0; i < n; i++) {
    long r, s, t, u;
    std::cin >> r >> s >> t >> u;
    segments.push_back(S(P(r, s), P(t, u)));
  }
  std::random_shuffle(segments.begin(), segments.end());

  bool hasIntersected = false;
  K::FT bestDistance = -1;
  for(int i = 0; i < n; i++) {
    S segment = segments[i];

    bool isIntersecting = false;
    if (hasIntersected) isIntersecting = CGAL::do_intersect(raySegment, segment);
    else isIntersecting = CGAL::do_intersect(ray, segment);

    if (isIntersecting){
      hasIntersected = true;
      auto o = CGAL::intersection(ray, segment);

      P intersection;
      if (const P* op = boost::get<P>(&*o)) {
        intersection = *op;
      } else if (const S* os = boost::get<S>(&*o)) {
        if(CGAL::squared_distance(start, os->source()) < CGAL::squared_distance(start, os->target())) {
          intersection = os->source();
        } else{
          intersection = os->target();
        }
      }

      if(CGAL::squared_distance(intersection, start) < bestDistance || bestDistance == -1) {
        bestDistance = CGAL::squared_distance(intersection, start);
        raySegment = S(start, intersection);
      }
    }
  }

  if(!hasIntersected) std::cout << "no\n";
  else {
    std::cout << std::setiosflags(std::ios::fixed)
              << std::setprecision(0)
              << floor_to_double(raySegment.target().x())
              << " "
              << floor_to_double(raySegment.target().y())
              << "\n";
  }
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