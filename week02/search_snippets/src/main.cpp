#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

bool pairSort(std::pair<int, int> const &i, std::pair<int, int> const &j)
{
  return i.first < j.first;
}

void testcase()
{
  int n;
  std::cin >> n;

  std::vector<int> wordCounts(n, -1);

  // setup wordCounts array
  for (int i = 0; i < n; i++)
  {
    std::cin >> wordCounts[i];
  }

  // setup document data structure and sort accoring to occurence location
  std::vector<std::pair<int, int>> document;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < wordCounts[i]; j++)
    {
      std::pair<int, int> currWord(-1, i);
      std::cin >> currWord.first;
      document.push_back(currWord);
    }
  }
  std::sort(document.begin(), document.end(), pairSort);

  // set initial state
  unsigned int start = 0, end = 0;
  std::vector<int> wordOccurenceInContext(n, 0);
  int diffWordsInContext = 1;
  wordOccurenceInContext[document[start].second] = 1;
  int maxDistance = document[document.size() - 1].first - document[0].first + 1;

  /**
   * keep updating sliding window until end reaches document end or 
   * start cannot be moved anymore (e.g. context does not contain all words)
   */
  while (end < document.size() - 1 || diffWordsInContext == n)
  {
    // move start reference (context containing all words)
    if (diffWordsInContext == n)
    {
      wordOccurenceInContext[document[start].second] -= 1;

      // if removed word was used only once in context, decrease counter
      if (wordOccurenceInContext[document[start].second] == 0)
      {
        diffWordsInContext -= 1;
      }
      start += 1;
    }
    // move end reference (context not containing all words)
    else
    {
      end += 1;
      wordOccurenceInContext[document[end].second] += 1;

      // if added word is new (e.g. not in word bag)
      if (wordOccurenceInContext[document[end].second] == 1)
      {
        diffWordsInContext += 1;
      }
    }

    if (diffWordsInContext == n && document[end].first - document[start].first + 1 < maxDistance)
    {
      maxDistance = document[end].first - document[start].first + 1;
    }
  }
  std::cout << maxDistance << "\n";
}

int main()
{
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;

  for (int i = 0; i < t; i++)
  {
    testcase();
  }
}