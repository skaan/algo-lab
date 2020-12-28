#include <iostream>

void handleTestcase() {
  // get number of terms in test case
  int n; 
  std::cin >> n;
  
  // sum over these terms
  int result = 0;
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    result += a;
  }
  
  // output sum
  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  // get number of test cases
  int numberTests;
  std::cin >> numberTests;
  
  // iterate over all tests
  for(int i = 0; i < numberTests; i++) {
    handleTestcase();
  }
}