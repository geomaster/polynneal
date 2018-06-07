#pragma once
#include <vector>
#include "geo.hpp"

class polynneal
{
public:
    polynneal(const std::vector<Point>& points, double _a, double _T0, int num_iters);

    bool iteration();
    bool kali(int num_iters);

    Polygon get_best() const;
    double get_best_area() const;

    Polygon get_current() const;
    double get_current_area() const;

    double get_temperature() const;

    int get_iteration() const;

private:
    double acceptance_probability(double e_old, double e_new, double T);
    Polygon neighbor(const Polygon& s);
    Polygon initial_polygon(const std::vector<Point>& points);

    double a;
    Polygon s;
    double area;

    int k;
    int k_max;

    double T;

    double best_area;
    Polygon best_poly;
};
