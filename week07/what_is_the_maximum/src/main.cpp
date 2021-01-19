#include <CGAL/Gmpz.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>

#include <iostream>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase(int p) {
  int a, b;
  std::cin >> a >> b;

  Program lp1(CGAL::SMALLER, true, 0, false, 0),
      lp2(CGAL::SMALLER, false, 0, true, 0);

  const int X = 0;
  const int Y = 1;
  const int Z = 2;

  Solution s;

  switch (p) {
    case 1:
      lp1.set_a(X, 0, 1);
      lp1.set_a(Y, 0, 1);
      lp1.set_b(0, 4);
      lp1.set_a(X, 1, 4);
      lp1.set_a(Y, 1, 2);
      lp1.set_b(1, a * b);
      lp1.set_a(X, 2, -1);
      lp1.set_a(Y, 2, 1);
      lp1.set_b(2, 1);
      lp1.set_c(X, a);
      lp1.set_c(Y, -b);
      s = CGAL::solve_linear_program(lp1, ET());
      break;
    case 2:
      lp2.set_a(X, 0, -1);
      lp2.set_a(Y, 0, -1);
      lp2.set_b(0, 4);
      lp2.set_a(X, 1, -4);
      lp2.set_a(Y, 1, -2);
      lp2.set_a(Z, 1, -1);
      lp2.set_b(1, a * b);
      lp2.set_a(X, 2, 1);
      lp2.set_a(Y, 2, -1);
      lp2.set_b(2, 1);
      lp2.set_c(X, a);
      lp2.set_c(Y, b);
      lp2.set_c(Z, 1);
      s = CGAL::solve_linear_program(lp2, ET());
      break;
    default:
      break;
  }

  if (s.is_infeasible())
    std::cout << "no\n";
  else {
    int value = std::ceil(CGAL::to_double(s.objective_value()));
    if (p == 1) value *= -1;
    std::cout << std::fixed << std::setprecision(0) << value << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int p;
  std::cin >> p;
  while (p != 0) {
    testcase(p);
    std::cin >> p;
  }
}