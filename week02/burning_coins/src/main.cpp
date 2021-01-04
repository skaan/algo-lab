#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> v;
std::vector<std::vector<int>> memo;

int rec(int l, int r)
{
  if (r < l)
    return 0;
  else if (r == l)
    return v[l];
  else if (memo[l][r] != -1)
  {
    return memo[l][r];
  }
  else
  {
    int takeLeftCoin = v[l] + std::min(rec(l + 2, r), rec(l + 1, r - 1));
    int takeRightCoin = v[r] + std::min(rec(l + 1, r - 1), rec(l, r - 2));
    int val = std::max(takeLeftCoin, takeRightCoin);
    memo[l][r] = val;
    return val;
  }
}

void testcase()
{
  int n;
  std::cin >> n;
  v.clear();
  memo.clear();

  for (int i = 0; i < n; i++)
  {
    memo.push_back(std::vector<int>(n, -1));
  }
  for (int i = 0; i < n; i++)
  {
    int vi;
    std::cin >> vi;
    v.push_back(vi);
  }

  std::cout << rec(0, n - 1) << "\n";
}

int main()
{
  std::ios_base::sync_with_stdio(false);

  // get number of test cases
  int t;
  std::cin >> t;

  // iterate over all test cases
  for (int i = 0; i < t; i++)
  {
    testcase();
  }
}