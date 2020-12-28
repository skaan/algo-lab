#include <iostream>
#include <vector>
#include <algorithm>

void insertToData(std::vector<int> &bestLocations, int coordSum) {
  if(coordSum % 2 != 0) {
    if(coordSum > 0) {
      bestLocations.push_back(coordSum/2);
      bestLocations.push_back((coordSum/2)+1);
    }
    else {
      bestLocations.push_back((coordSum/2) - 1);
      bestLocations.push_back(coordSum/2);
    }
  } else bestLocations.push_back(coordSum/2);
}

void testcase() 
{
  int n; std::cin >> n;
  
  // setup data structure
  std::vector<int> parasols(n, 0);

  // iterate over numbers
  for(int i = 0; i < n; ++i) {
    std::cin >> parasols[i];
  }
  std::sort(parasols.begin(), parasols.end());

  std::vector<int> bestLocations;
  int start = 0, minDistance = 0, maxParasols = 0;
  for(int end = 1; end < n; end++) {
    while(start < end && parasols[end] - parasols[start] > 200) start++;

    int coordSum = parasols[end] + parasols[start];
    int newDistance = std::max(std::abs(parasols[end] - coordSum/2), std::abs(coordSum/2 - parasols[start]));

    if((end - start + 1 > maxParasols) || (end - start + 1 == maxParasols && minDistance > newDistance)) {
      maxParasols = end - start + 1;
      bestLocations.clear();
      minDistance = newDistance;
      insertToData(bestLocations, coordSum);
    } else if(end - start + 1 == maxParasols && minDistance == newDistance) {
      insertToData(bestLocations, coordSum);
    }
  }

  std::cout << maxParasols << " " << minDistance << "\n";
  for(int i = 0; i < (int)bestLocations.size(); i++) {
      std::cout << bestLocations[i];
      if(i != (int)bestLocations.size() - 1) std::cout << " ";
  }
  std::cout << "\n";
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  
  // get number of test cases
  int t; std::cin >> t;

  // iterate over all test cases
  for(int i = 0; i < t; i++) {
    testcase();
  }
}