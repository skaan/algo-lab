#include <iostream>
#include <vector>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef std::vector<std::string> interests;

int common_interests(const interests &s1, const interests &s2)
{
  int i1 = 0, i2 = 0;
  int common = 0;

  while (i1 < s1.size() && i2 < s2.size())
  {
    if (s1[i1] == s2[i2])
    {
      common++;
      i1++;
      i2++;
    }
    else if (s1[i1] < s2[i2])
    {
      i1++;
    }
    else
    {
      i2++;
    }
  }
  return common;
}

void testcase()
{
  int n, c, f;
  std::cin >> n >> c >> f;

  // Construct a list of sorted interests for every buddy
  std::vector<interests> students(n);
  for (int i = 0; i < n; i++)
  {
    students[i].resize(c);
    for (int j = 0; j < c; j++)
    {
      std::cin >> students[i][j];
    }
    std::sort(students[i].begin(), students[i].end());
  }

  // Construct a graph with edges between buddies sharing more than ‘f‘ interests.
  graph G(n);
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (common_interests(students[i], students[j]) > f)
      {
        boost::add_edge(i, j, G);
      }
    }
  }

  // Compute maximum matching.
  std::vector<vertex_desc> mate(n);
  boost::edmonds_maximum_cardinality_matching(
      G, boost::make_iterator_property_map(
             mate.begin(), boost::get(boost::vertex_index, G)));

  // Compute the size of the maximum matching
  int matching_size = boost::matching_size(G, boost::make_iterator_property_map(
                                                  mate.begin(), boost::get(boost::vertex_index, G)));

  std::cout << (2 * matching_size == n ? "not optimal" : "optimal") << "\n";
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