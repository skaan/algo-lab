#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;

int main() {
  // read in number of segments
  int n; std::cin >> n;

  std::vector<S> segments(n);
  for(int i = 0; i < n; i++) {
    P start, end;
    std::cin >> start >> end;
    segments[i] = S(start, end);
  }

  for (int i = 0; i < segments.size(); ++i)
    for (int j = i+1; j < segments.size(); ++j)

      // if segments do intersect, construct intersection (point or segment)
      if (CGAL::do_intersect(segments[i], segments[j])) {
        auto o = CGAL::intersection(segments[i], segments[j]);
        if (const P *op = boost::get<P>(&*o))
          std::cout << "point: " << *op << "\n";
        else if (const S *os = boost::get<S>(&*o))
          std::cout << "segment: " << os->source() << " " 
                    << os->target() << "\n";
        else
          throw std::runtime_error("strange segment intersection");
      } else
        std::cout << "no intersection\n";
}
