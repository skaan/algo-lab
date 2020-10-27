#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <map>

int playAsHolmes(
  int n,
  int r,
  int b,
  int round,
  std::vector<std::vector<int>> &tr,
  std::map<std::tuple<int, int, int>, int> &maxMap,
  std::map<std::tuple<int, int, int>, int> &minMap);

int playAsMoriarty(
  int n,
  int r,
  int b,
  int round,
  std::vector<std::vector<int>> &tr,
  std::map<std::tuple<int, int, int>, int> &maxMap,
  std::map<std::tuple<int, int, int>, int> &minMap)
{
  if (r == n) return 0;
  else if (b == n) return 1;

  std::tuple<int, int, int> t(r, b, round % 2);

  if (maxMap.count(t) == 1) {
    return maxMap.at(t);
  } else {
    int res = -1;
    if (round % 2 == 1) {
      for(int i = 0; i < tr[b].size(); i++) {
        res = std::max(
          res,
          playAsHolmes(n, r, tr[b][i], round + 1, tr, maxMap, minMap)
        );
      }
    } else {
      for(int i = 0; i < tr[r].size(); i++) {
        res = std::max(
          res,
          playAsHolmes(n, tr[r][i], b, round + 1, tr, maxMap, minMap)
        );
      }
    }
    maxMap.insert(std::make_pair(t, res));
    return res;
  }
}

int playAsHolmes(
  int n,
  int r,
  int b,
  int round,
  std::vector<std::vector<int>> &tr,
  std::map<std::tuple<int, int, int>, int> &maxMap,
  std::map<std::tuple<int, int, int>, int> &minMap)
{
  if (r == n) return 0;
  else if (b == n) return 1;

  std::tuple<int, int, int> t(r, b, round % 2);

  if(minMap.count(t) == 1) {
    return minMap.at(t);
  } else {
    int res = 2;
    if (round % 2 == 1) {
      for(int i = 0; i < tr[r].size(); i++) {
        res = std::min(
          res,
          playAsMoriarty(n, tr[r][i], b, round, tr, maxMap, minMap)
        );
      }
    } else {
      for(int i = 0; i < tr[b].size(); i++) {
        res = std::min(
          res,
          playAsMoriarty(n, r, tr[b][i], round, tr, maxMap, minMap)
        );
      }
    }
    minMap.insert(std::make_pair(t, res));
    return res;
  }
}

void handleTestcase()
{
  int n, m;
  std::cin >> n;
  std::cin >> m;

  int r, b;
  std::cin >> r;
  std::cin >> b;
  
  // setup data structure
  std::vector<std::vector<int>> tr(n, std::vector<int>());

  // iterate over transitions and add to data structure
  for(int i = 0; i < m; ++i) {
    int trStart, trEnd;
    std::cin >> trStart;
    std::cin >> trEnd;

    tr[trStart].push_back(trEnd);
  }

  std::map<std::tuple<int, int, int>, int> maxMap;
  std::map<std::tuple<int, int, int>, int> minMap;

  std::cout << playAsHolmes(n, r, b, 1, tr, maxMap, minMap) << "\n";
}

int main() 
{
  std::ios_base::sync_with_stdio(false);
  
  // get number of test cases
  int t;
  std::cin >> t;

  // iterate over all test cases
  for(int i = 0; i < t; i++) {
    handleTestcase();
  }
}