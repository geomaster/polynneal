#pragma once
#include <vector>
#include "geo.hpp"

class polynneal
{
public:
    struct solution_t {
        std::vector<Point> poly;
        std::vector<int> perm;

        void swap(int i, int j) {
            std::swap(poly[i], poly[j]);
            std::swap(perm[i], perm[j]);
        }

        double area() {
            return CGAL::polygon_area_2(poly.begin(), poly.end(), Miroljub());
        }
    };

    polynneal(const std::vector<Point>& points, double _a, double _T0, int num_iters);

    bool iteration();
    bool kali(int num_iters);

    solution_t get_best() const;
    double get_best_area() const;

    solution_t get_current() const;
    double get_current_area() const;

    double get_temperature() const;

    int get_iteration() const;

private:

    double acceptance_probability(double e_old, double e_new, double T);
    solution_t neighbor(const solution_t& s_old);
    solution_t initial_solution(const std::vector<Point>& points);

    double a;
    solution_t s;
    double area;

    int k;
    int k_max;

    double T;

    double best_area;
    solution_t best_solution;
};
