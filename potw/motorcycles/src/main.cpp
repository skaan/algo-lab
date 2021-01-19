#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Ray_2 Ray;
typedef K::Point_2 Point;
typedef std::tuple<Ray, int, float> Biker;

bool mysort_position(const Biker &i, const Biker &j)
{
  return std::get<0>(i).source().y() > std::get<0>(j).source().y();
}

bool mysort_index(const Biker &i, const Biker &j)
{
  return std::get<1>(i) < std::get<1>(j);
}

void testcase()
{
  int n;
  std::cin >> n;

  std::vector<Biker> bikers(n);
  for (int i = 0; i < n; i++)
  {
    long y0, x1, y1;
    std::cin >> y0 >> x1 >> y1;

    Ray biker(Point(0, y0), Point(x1, y1));
    float slope = (y1 - y0) / x1;
    bikers[i] = {biker, i, slope};
  }

  std::sort(bikers.begin(), bikers.end(), mysort_position);

  std::vector<Biker> winners;
  Biker best_biker = bikers[0];
  winners.push_back(bikers[0]);

  for (int i = 1; i < n; i++)
  {
    if (std::get<2>(bikers[i]) <= std::get<2>(best_biker))
    {
      winners.push_back(bikers[i]);
      best_biker = bikers[i];
      continue;
    }
    if (std::abs(std::get<2>(bikers[i])) <= std::abs(std::get<2>(best_biker)))
    {
      int start_to_delete = (int)winners.size();
      while (start_to_delete > 0 && CGAL::do_intersect(std::get<0>(bikers[i]), std::get<0>(winners[start_to_delete - 1])) && std::abs(std::get<2>(bikers[i])) <= std::abs(std::get<2>(winners[start_to_delete - 1])))
        start_to_delete--;
      winners.erase(winners.begin() + start_to_delete, winners.end());
      if (start_to_delete == 0 || std::get<2>(bikers[i]) <= std::get<2>(winners[start_to_delete - 1]))
      {
        winners.push_back(bikers[i]);
        best_biker = bikers[i];
      }
    }
  }

  // sort and output solution
  std::sort(winners.begin(), winners.end(), mysort_index);
  for (int i = 0; i < (int)winners.size(); i++)
  {
    std::cout << std::get<1>(winners[i]) << " ";
  }
  std::cout << "\n";
}

int main()
{
  std::ios_base::sync_with_stdio(false);

  // iterate through testcases
  int t;
  std::cin >> t;
  for (int i = 0; i < t; i++)
  {
    testcase();
  }
}