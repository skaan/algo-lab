#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

const int INF = 500 * 1024 + 1;

int maxWinnings(int i, int j, int n, int m, const VI &coins, VVI &dp)
{
  if (j < i)
    return 0;
  if (j - i < 1)
    return dp[i][j] = 0;
  if (dp[i][j] != -1)
    return dp[i][j];

  int winnings_kth_left = INF, winnings_kth_right = INF;
  for (int l = 0; l < m; ++l)
  {
    winnings_kth_left = std::min(
        winnings_kth_left,
        maxWinnings(i + l + 1, j - (m - l - 1), n, m, coins, dp));
    winnings_kth_right = std::min(
        winnings_kth_right,
        maxWinnings(i + l, j - (m - l), n, m, coins, dp));
  }
  dp[i][j] = std::max(coins[i] + winnings_kth_left, coins[j - 1] + winnings_kth_right);
  return dp[i][j];
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t;

  for (std::cin >> t; t > 0; --t)
  {
    int n, m, k;
    std::cin >> n >> m >> k;

    // Read in all the values of the coins.
    VI coins;
    coins.reserve(n);

    for (int i = 0; i < n; ++i)
    {
      int v;
      std::cin >> v;
      coins.push_back(v);
    }

    VVI dp(n + 1, VI(n + 1, -1));

    int maximal_winnings = INF;
    for (int i = 0; i <= k; ++i)
      maximal_winnings = std::min(
          maximal_winnings,
          maxWinnings(i, n - (k - i), n, m, coins, dp));

    std::cout << maximal_winnings << "\n";
  }
}