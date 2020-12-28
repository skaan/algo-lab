#include <iostream>
#include <vector>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void handleTestcase() {
  int n;
  std::cin >> n;
  
  // setup data structure
  VVI M(n + 1, VI(n + 1));
  VVI pM(n + 1, VI(n + 1));

  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
      std::cin >> M[i][j];

  for(int k = 0; k <= n; k++) {
    pM[0][k] = 0;
    pM[k][0] = 0;
  }

  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
      pM[i][j] = M[i][j] + pM[i - 1][j] + pM[i][j - 1] - pM[i - 1][j - 1];

  int solution = 0;
  for(int i1 = 1; i1 <= n; i1++) {
    for(int i2 = i1; i2 <= n; i2++) {
      VI S(n + 1);
      VI pS(n + 1);

      pS[0] = 0;
      for(int k = 1; k <= n; k++) {
        S[k] = pM[i2][k] - pM[i2][k - 1] - pM[i1 - 1][k] + pM[i1 - 1][k - 1];
        pS[k] = S[k] + pS[k - 1];
      }

      int even = 0, odd = 0;
      for (int j = 1; j <= n; ++j) {
        if (pS[j] % 2 == 0) ++even;
        else ++odd;
      }

      solution += even * (even - 1) / 2;
      solution += odd * (odd - 1) / 2;
      solution += even;
    }
  }

  std::cout << solution << std::endl;
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