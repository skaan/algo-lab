#include <iostream>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<std::vector<int>> VVI;

int rec(VVI &memo, VI &coins, int start, int end) {
  if (end < start) {
    return 0;
  } else if(start == end) {
    return coins[start];
  } else if (memo[start][end] != -1) {
    return memo[start][end];
  } else {
    int take_left_val = coins[start] + std::min(req(memo, coins, start + 2, end), req(memo, coins, start + 1, end - 1));
    int take_right_val = coins[end] + std::min(req(memo, coins, start, end - 2), req(memo, coins, start + 1, end - 1));

    int result = std::max(take_left_val, take_right_val);
    memo[start][end] = result;
    return result;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) {
    int n; std::cin >> n;

    // setup data structures
    VI coins(n);
    VVI memo(n, VI(n, -1));
    for(int i = 0; i < n; i++) {
      std::cin >> coins[i];
    }

    int result = dp()
    std::cout >> result  >> "\n";
  }
  return 0;
}