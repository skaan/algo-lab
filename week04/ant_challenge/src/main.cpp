#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;

int dijkstra_dist(const weighted_graph &G, int s, int t)
{
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(G, s,
                                 boost::distance_map(boost::make_iterator_property_map(
                                     dist_map.begin(), boost::get(boost::vertex_index, G))));
  return dist_map[t];
}

void kruskal(const weighted_graph &G, weight_map &G_map, weighted_graph &final_g, weight_map &final_map)
{
  std::vector<edge_desc> mst;
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it)
  {
    auto p = boost::add_edge(boost::source(*it, G), boost::target(*it, G), final_g);
    final_map[p.first] = G_map[*it];
  }
}

void testcase()
{
  int n, e, s, a, b;
  std::cin >> n >> e >> s >> a >> b;

  // setup data structure
  std::vector<weighted_graph> networks(s, weighted_graph(n));
  std::vector<weight_map> weight_maps(s);

  for (int i = 0; i < s; i++)
  {
    weight_maps[i] = boost::get(boost::edge_weight, networks[i]);
  }

  for (int i = 0; i < e; i++)
  {
    int t1, t2;
    std::cin >> t1 >> t2;

    for (int j = 0; j < s; j++)
    {
      int weight;
      std::cin >> weight;
      edge_desc e = boost::add_edge(t1, t2, networks[j]).first;
      weight_maps[j][e] = weight;
    }
  }

  weighted_graph final_g(n);
  weight_map final_g_map = boost::get(boost::edge_weight, final_g);
  for (int i = 0; i < s; i++)
  {
    int to_waste;
    std::cin >> to_waste;
    kruskal(networks[i], weight_maps[i], final_g, final_g_map);
  }

  std::cout << dijkstra_dist(final_g, a, b) << "\n";
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