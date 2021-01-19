#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

// BGL typedefs
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, Traits::edge_descriptor>>>>
    Graph;
typedef boost::property_map<Graph, boost::edge_capacity_t>::type EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type ReverseEdgeMap;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

// Custom EdgeAdder class
class EdgeAdder
{
  Graph &G;
  EdgeCapacityMap &capacitymap;
  ReverseEdgeMap &revedgemap;

public:
  // to initialize the Object
  EdgeAdder(Graph &G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap) : G(G), capacitymap(capacitymap), revedgemap(revedgemap) {}
  // to use the Function (add an edge)
  void addEdge(int from, int to, long capacity)
  {
    Edge e, reverseE;
    bool success;
    tie(e, success) = boost::add_edge(from, to, G);
    tie(reverseE, success) = boost::add_edge(to, from, G);
    capacitymap[e] = capacity;
    capacitymap[reverseE] = 0;
    revedgemap[e] = reverseE;
    revedgemap[reverseE] = e;
  }
};

// Function for a single testcase
void testcases()
{
  // Graph
  int l, p;
  std::cin >> l >> p;

  Graph G(l);
  Vertex src = boost::add_vertex(G);
  Vertex sink = boost::add_vertex(G);

  // Maps & custom EdgeAdder
  EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
  ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
  EdgeAdder eaG(G, capacitymap, revedgemap);

  // supplies & demands
  long totaldemand = 0;
  for (int i = 0; i < l; ++i)
  {
    long gi, di;
    std::cin >> gi >> di;
    eaG.addEdge(src, i, gi);
    eaG.addEdge(i, sink, di);
    totaldemand += di;
  }

  // paths and capacities
  long totalmincap = 0;
  for (int j = 0; j < p; ++j)
  {
    int fj, tj;
    long mincj, maxCj;
    std::cin >> fj >> tj >> mincj >> maxCj;
    eaG.addEdge(src, tj, mincj);
    eaG.addEdge(fj, sink, mincj);
    eaG.addEdge(fj, tj, maxCj - mincj);
    totalmincap += mincj;
  }

  // check whether demands and minimum capacities are satisfied
  long flow = push_relabel_max_flow(G, src, sink);
  if (flow >= totaldemand + totalmincap)
    std::cout << "yes\n";
  else
    std::cout << "no\n";
}

// Main function, looping over the testcases
int main()
{
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  for (; T > 0; --T)
    testcases();
  return 0;
}