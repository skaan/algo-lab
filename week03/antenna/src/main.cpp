#include <iostream>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void testcase(int n)
{
  std::vector<P> points(n);
  for(int i = 0; i < n; i++) {
    int x, y;
    std::cin >> x >> y;
    points[i] = P(x, y);
  }
  std::random_shuffle(points.begin(), points.end());

  Min_circle mc(points.begin(), points.end(), true);
  Traits::Circle c = mc.circle();
  std::cout << std::fixed << std::setprecision(0) << std::ceil(std::sqrt(ceil_to_double(c.squared_radius()))) << "\n";
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