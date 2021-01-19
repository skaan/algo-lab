#include <CGAL/Gmpz.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>

#include <algorithm>
#include <iostream>
#include <vector>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
  std::ios_base::sync_with_stdio(false);
  int n, m;
  std::cin >> n >> m;

  while (n != 0 || m != 0) {
    Program lp(CGAL::SMALLER, true, 0, false, 0);

    for (int i = 0; i < n; i++) {
      int min, max;
      std::cin >> min >> max;
      lp.set_b(i, max);
      lp.set_b(n + i, -min);
    }

    for (int i = 0; i < m; i++) {
      int cost;
      std::cin >> cost;
      lp.set_c(i, cost);
      for (int j = 0; j < n; j++) {
        int nutrient;
        std::cin >> nutrient;
        lp.set_a(i, j, nutrient);
        lp.set_a(i, n + j, -nutrient);
      }
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_infeasible())
      std::cout << "No such diet.\n";
    else
      std::cout << std::floor(CGAL::to_double(s.objective_value())) << "\n";

    std::cin >> n >> m;
  }
}