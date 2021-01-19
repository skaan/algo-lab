#include <iostream>
#include <vector>
#include <utility>

void testcase()
{
  int n, m;
  std::cin >> n >> m;

  std::vector<std::pair<int, int>> jedis_a(n), jedis_b(n);
  for (int i = 0; i < n; i++)
  {
    int a, b;
    std::cin >> a >> b;
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
}