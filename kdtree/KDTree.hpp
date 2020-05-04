#pragma once

#include "KDNode.hpp"

template <typename Trait, std::size_t K>
class KDTree {
public:
  using value_t = typename Trait::value_t;
  using container_t = typename Trait::container_t;
  using distance_t = typename Trait::distance_t;
  using equal_t = typename Trait::equal_t;
  using print_t = typename Trait::print_t;
  using node = KDNode <Trait, K>;

  KDTree () {
    root = nullptr;
  }

  void insert (const container_t& point) {
    assert (point.size() == K);
    insert(&root, point, 0);
  }

  bool find (const container_t& point) const {
    assert (point.size() == K);
    return find(root, point, 0);
  }

  friend std::ostream& operator << (std::ostream& out, KDTree tree) {
    tree.print_tree(out);
    return out;
  }

  container_t nearest (const container_t& point) const {
    assert (root);
    return nearest(root, point, 0);
  }

private:
  node* root;
  equal_t equal;
  distance_t distance;
  print_t print;

  void insert (node** pnode, const container_t& point, std::size_t dimension) {
    if (not (*pnode)) {
      (*pnode) = new node(point);
      return;
    }
    if (point[dimension] <= (*pnode)->point[dimension]) {
      insert(&(*pnode)->left, point, (dimension + 1) % K);
    } else {
      insert(&(*pnode)->right, point, (dimension + 1) % K);
    }
  }

  bool find (node* pnode, const container_t& point, std::size_t dimension) const {
    if (not pnode) {
      return false;
    }
    if (equal(point, pnode->point)) {
      return true;
    }
    if (point[dimension] <= pnode->point[dimension]) {
      return find(pnode->left, point, (dimension + 1) % K);
    }
    return find(pnode->right, point, (dimension + 1) % K);
  }

  void print_tree (std::ostream& out) const {
    print_tree(root, 0, out);
  }

  int print_tree (node* pnode, int level, std::ostream& out) const {
    if (not pnode) {
      return 0;
    }
    int count = print_tree(pnode->right, level + 1, out);
    std::cout << std::string(6 * level, ' ');
    print(out, pnode->point);
    count += print_tree(pnode->left, level + 1, out);
    return 1 + count;
  }

  container_t nearest (node* pnode, const container_t& point, std::size_t dimension) const {
    node* first_option = nullptr;
    node* second_option = nullptr;
    if (point[dimension] <= pnode->point[dimension]) {
      first_option = pnode->left;
      second_option = pnode->right;
    } else {
      first_option = pnode->right;
      second_option = pnode->left;
    }
    if (first_option) {
      container_t result1 = nearest(first_option, point, (dimension + 1) % K);
      if (distance(result1, point) < distance(pnode->point, point)) {
        return result1;
      }
    }
    if (second_option) {
      container_t result2 = nearest(second_option, point, (dimension + 1) % K);
      if (distance(result2, point) < distance(pnode->point, point)) {
        return result2;
      }
    }
    return pnode->point;
  }

};
