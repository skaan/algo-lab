#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>

int rec(
  std::vector<int> v,
  std::vector<std::vector<int>> &maxVector,
  std::vector<std::vector<int>> &minVector,
  int l,
  int r,
  bool ownTurn)
{
  if (l <= r) {
    // maximize own pick
    if (ownTurn) {
      if (maxVector[l][r] != 0) {
        return maxVector[l][r];
      } else {
        int maxValue = std::max(
          v[l] + rec(v, maxVector, minVector, l + 1, r, !ownTurn),
          v[r] + rec(v, maxVector, minVector, l, r - 1, !ownTurn)
        );
        maxVector[l][r] = maxValue;
        return maxValue;
      }
    // maximize friend pick (minimize own future)
    } else {
      if (minVector[l][r] != 0) {
        return minVector[l][r];
      } else {
        int minValue = std::min(
          rec(v, maxVector, minVector, l + 1, r, !ownTurn),
          rec(v, maxVector, minVector, l, r - 1, !ownTurn)
        );
        minVector[l][r] = minValue;
        return minValue;
      } 
    }
  }
  return 0;
}

void handleTestcase() 
{
  int n;
  std::cin >> n;
  
  // setup data structure
  std::vector<int> v(n, 0);

  // iterate over numbers
  for(int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }

  // setup data structure for dp problem
  std::vector<std::vector<int>> maxVector(n, std::vector<int>(n, 0));
  std::vector<std::vector<int>> minVector(n, std::vector<int>(n, 0));

  std::cout << rec(v,  maxVector, minVector, 0, n - 1, true) << "\n";
}

int main() 
{
  std::ios_base::sync_with_stdio(false);
  
  // get number of test cases
  int t;
  std::cin >> t;

  // iterate over all test cases
  for(int i = 0; i < t; i++) {
    handleTestcase();
  }
}