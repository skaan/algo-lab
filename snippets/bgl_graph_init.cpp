// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> graph;
typedef boost::graph_traits<graph>::edge_iterator edge_it;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, // vertex property
  boost::property<boost::edge_weight_t, int>  // edge property
> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;

/** Predefined vertex properties
 * - vertex_degree_t
 * - vertex_name_t
 * - vertex_distance_t
*/

/** Predefined edge properties
 * - edge_weight_t
 * - edge_capacity_t
 * - edge_residual_capacity_t
 * - edge_reverse_t
*/

/** Common algorithms with BGL
 * - boost::breadth_first_search:   O(n + m)
 * - boost::depth_first_search:   O(n + m)
 * - boost::dijkstra_shortest_path:   O(n log n + m)
 * - boost::kruskal_minimum_spanning_tree:   O(m log m)
 * - boost::connected_components:   O(n + m)
 * - boost::strong_components:   O(n + m)
 * - boost::biconnected_components:   O(n + m)
 * - boost::articulation_points:   O(n + m)
 * - boost::edmonds_maximum_cardinality_matching:   O(mn · α(m, n))
 * - boost::is_bipartite:   O(n + m)
*/

void init_graph()
{
  graph G(4);

  boost::add_edge(0, 1, G);
  boost::add_edge(1, 2, G);
  boost::add_edge(2, 3, G);
  boost::add_edge(3, 0, G);
  boost::add_edge(0, 2, G);

  edge_it e_beg, e_end;
  for (boost::tie(e_beg, e_end) = boost::edges(G); e_beg != e_end; ++e_beg) {
    std::cout << boost::source(*e_beg, G) << " " << boost::target(*e_beg, G) << "\n";
  }

  out_edge_it oe_beg, oe_end;
  for (boost::tie(oe_beg, oe_end) = boost::out_edges(0, G); oe_beg != oe_end; ++oe_beg) {
    assert(boost::source(*oe_beg, G) == 0);
    std::cout << boost::target(*oe_beg, G) << "\n";
  }
} /* end of function init_graph */

void init_weighted_graph()
{
  weighted_graph G(4);
  weight_map weights = boost::get(boost::edge_weight, G);

  edge_desc e;
  e = boost::add_edge(0, 1, G).first; weights[e]=0;
  e = boost::add_edge(1, 2, G).first; weights[e]=2;
  e = boost::add_edge(2, 3, G).first; weights[e]=1;
  e = boost::add_edge(3, 0, G).first; weights[e]=3;
  e = boost::add_edge(0, 2, G).first; weights[e]=3;
}

int main()
{
  init_graph();
  init_weighted_graph();

  return 0;
}
