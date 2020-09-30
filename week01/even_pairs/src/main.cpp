#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cassert>

int calcCombinatorial(int n) {
  if (n < 2) return 0;
  else return n * (n - 1) / 2;
}

void handleTestcase() {
  int n;
  std::cin >> n;
  
  // setup data structure
  std::vector<int> partials(n, 0);
  int evenSums = 0;
  int oddSums = 0;

  // iterate over numbers
  for(int i = 0; i < n; ++i) {
    std::cin >> partials[i];
    if (i > 0) partials[i] = partials[i] + partials[i - 1];

    // increase set cound depending on even/odd of partial sum
    if (partials[i] % 2 == 0) ++evenSums;
    else ++oddSums;
  }

  // calculate number of even pairs
  long result = evenSums + calcCombinatorial(evenSums) + calcCombinatorial(oddSums);

  // output fallen dominos (indexing from 0!)
  std::cout << result << "\n";
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