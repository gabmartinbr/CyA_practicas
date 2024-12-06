#include "emst.h"

#include <iomanip>
#include <algorithm>
#include <utility>

namespace EMST {
  sub_tree::sub_tree(void) :
    arcs(), points(), cost(0) {}

  sub_tree::~sub_tree(void) {}

  void sub_tree::add_arc(const CyA::arc &a) {
    arcs_.push_back(a);

    points_.insert(a.first);
    points_.insert(a.second);
  }

  void sub_tree::add_point(const CyA::point &p) {
    points_.insert(p);
  }

  bool sub_tree::contains(const CyA::point &p) {
    return points_.find(p) != points_.end();
  }

  void sub_tree::merge(const sub_tree &st, const CyA::weighted_arc &a) {
    arcs_.insert(arcs_.end(), st.arcs_.begin(), st.arcs_.end());
    arcs_.push_back(a.second);

    points_.insert(st.points_.begin(), st.points_.end());

    cost_ += a.first() + st.get_cost();
  }

}
