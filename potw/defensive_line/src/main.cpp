#include <iostream>
#include <vector>

void handleTestcase() {
  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<int> arr(n, -1);
  for(int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  
  std::cout << n << " " << m << " " << k << "\n";
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