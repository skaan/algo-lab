#include <iostream>
#include <vector>
#include <algorithm>

void testcase()
{
  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<int> defence(n, -1);
  std::vector<int> defence_sum(n, 0);

  std::cin >> defence[0];
  defence_sum[0] = defence[0];
  for (int i = 1; i < n; ++i)
  {
    std::cin >> defence[i];
    defence_sum[i] = defence_sum[i - 1] + defence[i];
  }

  int start = 0, end = 0;
  std::vector<int> segment_values(n, 0);
  while (end < n)
  {
    int diff = defence_sum[end] - defence_sum[start] + defence[start];
    if (diff == k)
    {
      segment_values[end] = end - start + 1;
      end++;
      start++;
    }
    else if (diff < k)
    {
      end++;
    }
    else
    {
      start++;
    }
  }

  std::vector<std::vector<int>> DP(m + 1, std::vector<int>(n));
  for (int i = 0; i < n; i++)
  {
    DP[0][i] = 0;
  }

  for (int i = 1; i < m + 1; i++)
  {
    DP[i][0] = segment_values[0];
  }

  for (int i = 1; i < m + 1; i++)
  {
    for (int j = 1; j < n; j++)
    {
      DP[i][j] = std::max(segment_values[j] + DP[i - 1][j - segment_values[j]], DP[i][j - 1]);
    }
  }

  if (DP[m - 1][n - 1] != DP[m][n - 1])
    std::cout << DP[m][n - 1]
              << "\n";
  else
    std::cout << "fail"
              << "\n";
}

int main()
{
  std::ios_base::sync_with_stdio(false);

  // get number of test cases
  int numberTests;
  std::cin >> numberTests;

  // iterate over all test cases
  for (int i = 0; i < numberTests; i++)
  {
    testcase();
  }
}