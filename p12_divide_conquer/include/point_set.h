#pragma once
#include <vector>
#include <iostream>

namespace CyA
{
        /**
         * @brief 
         * 
         */
        typedef std::pair<double,double> point;
        /**
         * @brief 
         * 
         */
        typedef std::pair<point, point> line;
        /**
         * @brief 
         * 
         */
        typedef std::vector<point> point_vector;
        
        /**
         * @brief 
         * 
         */
        enum side
        {
                LEFT = -1,
                CENTER,
                RIGHT
        };
        
        /**
         * @brief 
         * 
         */
        class point_set : public point_vector
        {
        private:
                point_vector hull_; ///< 
 
        public:
                /**
                 * @brief Construct a new point set object
                 * 
                 * @param points 
                 */
                point_set(const vector<point> &points);
                /**
                 * @brief Destroy the point set object
                 * 
                 */
                ~point_set(void);

                /**
                 * @brief 
                 * 
                 */
                void quickHull(void);

                /**
                 * @brief 
                 * 
                 * @param os 
                 */
                void write_hull(std::ostream &os) const;

                /**
                 * @brief 
                 * 
                 * @param os 
                 */
                void write(std::ostream &os) const;

                /**
                 * @brief Get the hull object
                 * 
                 * @return const point_vector& 
                 */

                inline const point_vector& get_hull(void) const { return hull_; }
                /**
                 * @brief Get the points object
                 * 
                 * @return const point_vector& 
                 */
                inline const point_vector& get_points(void) const { return *this; }
 
        private:     
                /**
                 * @brief 
                 * 
                 * @param l 
                 * @param side 
                 */
                void quickHull(const line &l, int side);

                /**
                 * @brief 
                 * 
                 * @param l 
                 * @param p 
                 * @return double 
                 */
                double distance(const line &l, const point &p) const;

                /**
                 * @brief 
                 * 
                 * @param l 
                 * @param p 
                 * @return int 
                 */
                int find_side(const line &l, const point &p) const;
                
                /**
                 * @brief 
                 * 
                 * @param min_x 
                 * @param max_x 
                 */
                void x_bounds(point &min_x, point &max_x) const;

                /**
                 * @brief 
                 * 
                 * @param l 
                 * @param p 
                 * @return double 
                 */
                double point_2_line(const line &l, const point &p) const;

                /**
                 * @brief 
                 * 
                 * @param l 
                 * @param side 
                 * @param farthest 
                 * @return true 
                 * @return false 
                 */
                bool farthest_point(const line &l, int side, point &farthest) const;
        };
}