#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

void handleTestcase() {
  // get number of dominos
  int n;
  std::cin >> n;
  
  // setup data structure
  std::vector<int> arr(n, 1);

  // first domino falls down
  int maxIndexFallenDomino = 0;
  
  // iterate over dominos
  int currentDominoHeight;
  for(int i = 0; i < n; ++i) {
    std::cin >> currentDominoHeight;
    arr[i] = currentDominoHeight;

    int impactDistance = currentDominoHeight - 1;
    
    if (i <= maxIndexFallenDomino && i + impactDistance > maxIndexFallenDomino) {
      maxIndexFallenDomino = std::min(i + impactDistance, n - 1);
    }
  }

  // output fallen dominos (indexing from 0!)
  std::cout << maxIndexFallenDomino + 1 << "\n";
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