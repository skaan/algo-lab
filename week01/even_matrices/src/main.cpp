#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cassert>

void handleTestcase() {
  int n;
  std::cin >> n;
  
  // setup data structure
  std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

  int sum = 0;
  // iterate over numbers
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; j++) {
      std::cin >> matrix[i][j];

      if (i > 0) {
        if (j > 0) {
          matrix[i][j] = matrix[i][j] + matrix[i - 1][j] + matrix[i][j - 1] - matrix[i - 1][j - 1];
        } else {
          matrix[i][j] = matrix[i][j] + matrix[i - 1][j];
        }
      } else {
        if (j > 0) {
          matrix[i][j] = matrix[i][j] + matrix[i][j - 1];
        }
      }

      for(int rowTop = 0; rowTop < i; ++rowTop) {
        for(int colLeft = 0; colLeft < j; ++colLeft) {
          // calculate submatrix sum
          int result = matrix[i][j];
          if (rowTop > 0) result -= matrix[rowTop - 1][j];
          if (colLeft > 0) result -= matrix[i][colLeft - 1];
          if (rowTop > 0 && colLeft > 0) result += matrix[rowTop - 1][colLeft - 1];

          // increase even count
          if (result % 2 == 0) ++sum;
        }
      }
    }
  }

  std::cout << sum << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  // get number of test cases
  int numberTests;
  std::cin >> numberTests;

  // iterate over all test cases
  for(int i = 0; i < numberTests; i++) {
    handleTestcase();
  }
}