#pragma once

#include <vector>
#include <cassert>

template <typename T>
class Trait {
public:
  using value_t = T;
  using container_t = std::vector <value_t>;
  using iterator_t = typename container_t::iterator;

  /**
   * Square of eucledian distance between to points 
   */
  class Distance {
  public:
    long long operator () (const container_t& x, const container_t& y) const {
      assert (x.size() == y.size());
      long long distance2 = 0;
      for (size_t i = 0; i < x.size(); i++) {
        distance2 = 1LL * (x[i] - y[i]) * (x[i] - y[i]);
      }
      return distance2;
    }
  };

  class Equal {
  public:
    bool operator () (const container_t& x, const container_t& y) const {
      return x == y;
    }
  };

  class Print {
  public:
    void operator () (std::ostream& out, const container_t& x) const {
      out << '(';
      bool first = true;
      for (auto elem: x) {
        if (not first) {
          out << ", ";
        }
        out << elem;
        first = false;
      }
      out << ')' << std::endl;
    }
  };

  using distance_t = Distance;
  using equal_t = Equal;
  using print_t = Print;
};
