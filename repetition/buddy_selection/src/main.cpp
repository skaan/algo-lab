#include <iostream>
#include <algorithm>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef std::vector<std::string> VS;
typedef std::vector<VS> VVS;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

int num_matching_characteristics(const VS &mate_1, const VS &mate_2) {
  int counter = 0;
  int index_1 = 0, index_2 = 0;
  while(index_1 < mate_1.size() && index_2 < mate_2.size()) {
    if (mate_1[index_1] == mate_2[index_2]) {
      counter++;
      index_1++;
      index_2++;
    } else if (mate_1[index_1] < mate_2[index_2]) {
      index_1++;
    } else {
      index_2++;
    }
  }
  return counter;
}

void testcase() {
  int n, c, f; std::cin >> n >> c >> f;

  VVS characteristis(n);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < c; j++) {
      std::string string; std::cin >> string;
      characteristis[i].push_back(string);
    }
    std::sort(characteristis[i].begin(), characteristis[i].end());
  }

  // build graph
  graph G(n);
  std::vector<vertex_desc> mate_map(n);

  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      if (num_matching_characteristics(characteristis[i], characteristis[j]) > f) {
        boost::add_edge(i, j, G);
      }
    }
  }

  boost::edmonds_maximum_cardinality_matching(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  if (2*matching_size == n) {
    std::cout << "not optimal\n";
  } else {
    std::cout << "optimal\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while(t--) {
    testcase();
  }
  return 0;
}