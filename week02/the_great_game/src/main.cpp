#include <iostream>
#include <vector>

typedef std::vector<int> VI;
const int MAX_N = 50001;

int testcase()
{
  int n, m; std::cin >> n >> m;
  int r, b; std::cin >> r >> b;

  // setup data structure for transitions
  std::vector<VI> graph(n + 1, VI());

  // iterate over transitions and add to data structure
  for(int i = 0; i < m; ++i) {
    int u, v; std::cin >> u >> v;
    graph[u].push_back(v);
  }

  // setup data structure for already computed results
  VI mini(n + 1, MAX_N);
  VI maxi(n + 1, -1);

  mini[n] = 0;
  maxi[n] = 0;

  for(int i = n - 1; i >= 1; i--) {
    for(int v: graph[i]) {
      mini[i] =  std::min(mini[i], maxi[v] + 1);
      maxi[i] = std::max(maxi[i], mini[v] + 1);
    }
  }

  int sherlock = mini[r];
  int moriarty = mini[b];

  if (sherlock < moriarty) return 0;
  if (moriarty < sherlock) return 1;
  if (sherlock % 2 == 1) return 0;
  return 1;
}

int main() 
{
  std::ios_base::sync_with_stdio(false);
  
  // get number of test cases
  int t;
  std::cin >> t;

  // iterate over all test cases
  for(int i = 0; i < t; i++) {
    std::cout << testcase() << "\n";
  }
}