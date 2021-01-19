#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

bool my_sort(const std::pair<int, int> &i, const std::pair<int, int> &j)
{
  return i.second < j.second;
}

void testcase()
{
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> wizards(n);
  for (int i = 0; i < n; i++)
  {
    int l, p;
    std::cin >> l >> p;
    std::pair<int, int> wizard(l, p);
    wizards[i] = wizard;
  }

  std::sort(wizards.begin(), wizards.end(), my_sort);

  int counter = 1, pos = wizards[0].second;
  wizards.erase(wizards.begin());
  while (wizards.size() > 0)
  {
    int index = 0, best_index = 0, next_pos = std::max(wizards[index].first + pos, wizards[index].second);
    while (++index < (int)wizards.size() && next_pos > wizards[index].second)
    {
      int tmp = std::max(wizards[index].first + pos, wizards[index].second);
      if (tmp < next_pos)
      {
        next_pos = tmp;
        best_index = index;
      }
    }
    pos = next_pos;
    counter++;

    best_index++;
    while (best_index < (int)wizards.size() && wizards[best_index].second < pos)
      best_index++;
    wizards.erase(wizards.begin(), wizards.begin() + best_index);
  }

  std::cout << counter << "\n";
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