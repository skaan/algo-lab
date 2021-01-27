#include <iostream>
#include <vector>

void testcase() {
  int n; std::cin >> n;

  std::vector<int> parasols(n);

  // iterate over numbers
  for(int i = 0; i < n; ++i) {
    std::cin >> parasols[i];
  }
  std::sort(parasols.begin(), parasols.end());

  int start = 0, end = 0;
  int count = 1, max_count = 1;

  while(start != n) {
    if (parasols[end] - parasols[start] < 200) {
      end += 1;

      // add new parasol to count if within range
      if (parasols[end] - parasols[start] < 200) {
        count += 1;

        if (count >= max_count) {
          // set new max count
          // set new min distance
        }
      }
    } else {
      start += 1;
      count -= 1;
    }
  }
}

int main() {
  int t; std::cin >> t;
  while(t--) {
    testcase();
  }
  return 0;
}