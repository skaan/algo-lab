#include <CGAL/Gmpz.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>

#include <iostream>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase() {
  int h, t;
  std::cin >> h >> t;
}

int main() {
  int t;
  for (std::cin >> t; t > 0; t--) {
    testcase();
  }
  return 0;
}