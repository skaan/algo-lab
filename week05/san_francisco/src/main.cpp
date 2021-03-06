#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>

typedef std::pair<int, int> edge;

long dp(std::vector<std::vector<long>> &memo, const std::vector<std::vector<edge>> &edges, int position, int moves)
{
  if (memo[position][moves] != -1)
    return memo[position][moves];
  long max_points = std::numeric_limits<long>::min();
  for (int i = 0; i < (int)edges[position].size(); i++)
  {
    if (edges[position][i].second == -1)
      max_points = std::max(max_points, dp(memo, edges, 0, moves));
    else
      max_points = std::max(max_points, edges[position][i].second + dp(memo, edges, edges[position][i].first, moves - 1));
  }
  memo[position][moves] = max_points;
  return max_points;
}

void testcase()
{
  int n, m, k;
  long x;
  std::cin >> n >> m >> x >> k;

  // setup data structure
  std::vector<std::vector<edge>> edges(n, std::vector<edge>());
  for (int i = 0; i < m; i++)
  {
    int u, v, p;
    std::cin >> u >> v >> p;
    edges[u].push_back(std::make_pair(v, p));
  }
  for (int i = 0; i < n; i++)
    if (edges[i].size() == 0)
      edges[i].push_back(std::make_pair(0, -1));

  std::vector<std::vector<long>> memo(n, std::vector<long>(k + 1, -1));
  for (int i = 0; i < n; i++)
  {
    memo[i][0] = 0;
  }

  bool possible = false;
  for (int i = 1; i <= k; i++)
  {
    if (dp(memo, edges, 0, i) >= x)
    {
      std::cout << i << "\n";
      possible = true;
      i = k;
    }
  }
  if (!possible)
  {
    std::cout << "Impossible\n";
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  while (t--)
  {
    testcase();
  }

  return 0;
}