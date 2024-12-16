#include "point_set.h"

namespace CyA {

    void point_set::quickHull(const CyA::line &l, int side) {
        CyA::point farthest;

        if (farthest_point(l, side, farthest)) { 
            quickHull(CyA::line(l.first, farthest), -find_side(CyA::line(l.first, farthest), l.second));
            quickHull(CyA::line(farthest, l.second), -find_side(CyA::line(farthest, l.second), l.first));
        } else {
            hull_.push_back(l.first);
            hull_.push_back(l.second);
        }
    }

    void point_set::quickHull(const CyA::line &l, int side) {
        CyA::point farthest;

        if (farthest_point(l, side, farthest)) {
            quickHull(CyA::line(l.first, farthest), -find_side(CyA::line(l.first, farthest), l.second));
            quickHull(CyA::line(farthest, l.second), -find_side(CyA::line(farthest, l.second), l.first));
        } else { 
            hull_.push_back(l.first);
            hull_.push_back(l.second);
        }
    }

    bool point_set::farthest_point(const CyA::line &l, int side, CyA::point &farthest) const {
            farthest = CyA::point_vector::at(0);

            double max_dist = 0;

            bool found = false;

            for (const CyA::point &p : *this) {
                const double dist = distance(l, p);
                if (find_side(l, p) == side && dist > max_dist) {
                    farthest = p;
                    max_dist = dist;
                    found = true;
                }
            }
            return found;
        }    
}