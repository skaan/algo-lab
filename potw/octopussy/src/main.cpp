#include <iostream>
#include <utility>
#include <vector>

bool mysort(const std::pair<int, int> &i, const std::pair<int, int> &j) {
  return i.second < j.second;
}

bool will_be_diffused(vector<int> &bombs, int &time, vector<bool> &diffused,
                      int index, int treshold) {
  if (diffused[index]) return true;
  if (index >= treshold) {
    if (time < bombs[index]) {
      diffused[index] = true;
      time++;
      return true;
    }
    return false;
  }

  if (time >= bombs[index]) return false;

  if (will_he_make_it(bombs, time, diffused, index * 2 + 1, treshold) &&
      will_he_make_it(bombs, time, diffused, index * 2 + 2, treshold)) {
    if (time < bombs[index]) {
      diffused[index] = true;
      time++;
      return true;
    }
  }
  return false;
}

void testcase() {
  int n;
  std::cin >> n;

  // setup data containers
  std::vector<std::pair<int, int>> bombs(n);
  std::vector<int> bomb_time(n);
  std::vector<bool> diffused(n, false);

  // read bomb explosion times
  for (int i = 0; i < n; i++) {
    int time;
    std::cin >> time;
    bomb_time[i] = time;
    std::pair<int, int> bomb = std::make_pair<int, int>(i, time);
  }

  std::sort(bombs.begin(), bombs.end(), my_sort);

  bool check = true;
  int time;
  for (int i = 0; i < n; i++) {
    check = will_be_diffused(bombs_time, time, diffused, bombs[i].first,
                             (n - 1) / 2);
  }

  check ? std::cout << "yes\n" : std::cout << "no\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t--) {
    testcase();
  }
  return 0;
}