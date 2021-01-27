#include <iostream>
#include <vector>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void testcase() {
  int n; std::cin >> n;

  VVI M(n, VI(n));
  VVI pM(n + 1, VI(n + 1, 0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      std::cin >> M[i][j];
      pM[i + 1][j + 1] = pM[i+1][j] + pM[i][j+1] - pM[i][j] + M[i][j];
    }
  }

  int solution = 0;
  for(int i1 = 1; i1 <= n; i1++) {
    for(int i2 = 1; i2 <= n; i2++) {
      VI S(n + 1, 0);
      VI pS(n + 1, 0);

      int even = 0, odd = 0;
      for(int k = 1; k <= n; k++) {
        S[k] = pM[i2][k] - pM[i2][k - 1] - pM[i1][k] + pM[i1 - 1][k - 1];
        pS[k] = S[k + 1] + pS[k];

        if(pS[k] % 2 == 0) even++;
        else odd++;
      }

      solution += even;
      solution += (even * (even - 1)) / 2;
      solution += (odd * (odd - 1)) / 2;
    }
  }
  std::cout << solution << "\n";
}

int main() {
  int t; std::cin >> t;
  while(t--) {
    testcase();
  }
  return 0;
}