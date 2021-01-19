#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_capacity_t, long, boost::property<boost::edge_residual_capacity_t, long, boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder
{
  graph &G;

public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity)
  {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

int main(int argc, char const *argv[])
{
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t--)
  {
    int n, m, s;
    std::cin >> n >> m >> s;

    graph g(n);
    const vertex_desc source = boost::add_vertex(g);
    const vertex_desc target = boost::add_vertex(g);
    edge_adder adder(g);

    adder.add_edge(source, 0, s);
    for (int i = 0; i < s; i++)
    {
      int store;
      std::cin >> store;
      adder.add_edge(store, target, 1);
    }
    for (int i = 0; i < m; i++)
    {
      int from, to;
      std::cin >> from >> to;
      adder.add_edge(from, to, 1);
      adder.add_edge(to, from, 1);
    }

    long flow = boost::push_relabel_max_flow(g, source, target);
    flow == s ? std::cout << "yes\n" : std::cout << "no\n";
  }
}