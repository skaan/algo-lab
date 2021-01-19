#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>>
    graph;
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
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

// mapping coordinates of a vertex to its index in G
int index(int x, int y, int m, int n, bool in)
{
  return y + n * x + in * m * n;
}

void solve()
{
  int m, n, k, c;
  std::cin >> m >> n >> k >> c;

  graph G(2 * m * n);
  edge_adder adder(G);

  // Add special vertices source and sink
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc sink = boost::add_vertex(G);

  // Configure outgoing edges from the source
  for (int i = 0; i < k; ++i)
  {
    int x, y;
    std::cin >> x >> y;
    adder.add_edge(source, index(x, y, m, n, true), 1);
  }

  int dx[4] = {0, 1, 0, -1};
  int dy[4] = {1, 0, -1, 0};

  for (int x = 0; x < m; ++x)
  {
    for (int y = 0; y < n; ++y)
    {
      // Configure the capcity for vertex (x, y)
      adder.add_edge(index(x, y, m, n, true), index(x, y, m, n, false), c);
      for (int i = 0; i < 4; ++i)
      {
        int newx = x + dx[i];
        int newy = y + dy[i];

        // Configure the segments (excluding ending segments)
        if (newx >= 0 && newx < m && newy >= 0 && newy < n)
        {
          adder.add_edge(index(x, y, m, n, false), index(newx, newy, m, n, true), 1);
        }
      }

      // Configure the ending segments
      if (x == 0 || x == m - 1)
      {
        adder.add_edge(index(x, y, m, n, false), sink, 1);
      }

      if (y == 0 || y == n - 1)
      {
        adder.add_edge(index(x, y, m, n, false), sink, 1);
      }
    }
  }
  long flow = boost::push_relabel_max_flow(G, source, sink);
  //long flow = boost::edmonds_karp_max_flow(G, source, sink);
  std::cout << flow << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;

  while (t--)
  {
    solve();
  }
  return 0;
}