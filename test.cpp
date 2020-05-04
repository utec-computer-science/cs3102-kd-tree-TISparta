#include <gtest/gtest.h>

#include "utility/Random.hpp"
#include "traits/Trait.hpp"
#include "kdtree//KDTree.hpp"

const int MIN_VAL = -1000;
const int MAX_VAL = +1000;

TEST (KDTree, int_insert_print_and_find) {
  using value_t = int;
  using trait_t = Trait <value_t>;
  const std::size_t K = 2;
  KDTree <trait_t, K> tree;
  const int n_elements = 10;
  std::vector <std::vector <value_t>> values(n_elements, std::vector <value_t> (K));
  for (auto& point: values) {
    for (std::size_t d = 0; d < K; d++) {
      point[d] = Random::generate_value <value_t> (MIN_VAL, MAX_VAL);
    }
    tree.insert(point);
  }
  std::cout << tree;
  for (auto& value: values) {
    EXPECT_TRUE(tree.find(value));
  }
}

TEST (KDTree, nearest_neighbour) {
  using value_t = int;
  using trait_t = Trait <value_t>;
  using print_t = typename trait_t::print_t;
  print_t print;
  const std::size_t K = 3;
  KDTree <trait_t, K> tree;
  const int n_elements = 100;
  std::vector <std::vector <value_t>> values(n_elements, std::vector <value_t> (K));
  for (auto& point: values) {
    for (std::size_t d = 0; d < K; d++) {
      point[d] = Random::generate_value <value_t> (MIN_VAL, MAX_VAL);
    }
    tree.insert(point);
  }
  std::vector <value_t> nn = tree.nearest(std::vector <value_t> (K, 0));
  print(std::cout, nn);
}

int main (int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
