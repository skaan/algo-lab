#include <CGAL/Gmpz.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>

#include <cmath>
#include <iostream>
#include <stdexcept>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
  std::ios_base::sync_with_stdio(false);

  int n;
  for (std::cin >> n; n > 0; std::cin >> n) {
    int d;
    std::cin >> d;

    Program lp(CGAL::SMALLER, false, 0, false, 0);
    for (int i = 0; i < n; ++i) {
      int norm2 = 0;
      for (int j = 0; j < d; ++j) {
        IT ai;
        std::cin >> ai;
        norm2 += ai * ai;
        lp.set_a(j, i, ai);
      }

      // check that the norm is indeed an integer
      int norm = std::floor(std::sqrt(norm2));
      if (norm2 != norm * norm)
        throw std::runtime_error("Error:␣norm2!=␣norm*norm.\n");

      lp.set_a(d, i, norm);
      IT bi;
      std::cin >> bi;
      lp.set_b(i, bi);
    }
    lp.set_c(d, -1);
    lp.set_l(d, true, 0);

    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_infeasible())
      std::cout << "none\n";
    else if (s.is_unbounded())
      std::cout << "inf\n";
    else
      std::cout << -(s.objective_value().numerator() /
                     s.objective_value().denominator())
                << "\n";
  }
}