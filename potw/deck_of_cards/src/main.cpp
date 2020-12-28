#include <iostream>
#include <vector>
#include <cmath>

void testcase() {
  
  int n; std::cin >> n;
  int k; std::cin >> k;

  std::vector<int> cards(n);
  for(int i = 0; i < n; i++)
    std::cin >> cards[i];

  int start = 0, end = 0, sum = cards[0];
  std::vector<int> result(3);

  // check end condition
  while(end < n) {
    if (sum == k) {
      result[0] = sum; result[1] = start; result[2] = end;
      break;
    } else {
      if (sum < k && end != n - 1) {
        end++;
        sum += cards[end];
      } else {
        sum -= cards[start];
        start++;
        if (start > end) {
          end = start;
          sum = cards[start];
        }

      }
      // keep track of best solution yet
      if (std::abs(sum - k) < std::abs(result[0] - k)) {
        result[0] = sum; result[1] = start; result[2] = end;
      }

    }
  }
  std::cout << result[1] << " " << result[2] << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;

  for(int i = 0; i < t; i++)
    testcase();
}