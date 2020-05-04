#pragma once

template <typename Trait, std::size_t K>
class KDNode {
public:
  using value_t = typename Trait::value_t;
  using container_t = typename Trait::container_t;
  using iterator_t = typename Trait::iterator_t;
  
  KDNode* left = 0;
  KDNode* right = 0;
  container_t point;

  KDNode (const container_t& point): point(point) {
    left = nullptr;
    right = nullptr;
  }

};
