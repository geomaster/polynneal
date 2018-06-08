#include "polynneal.hpp"
#include <cstdlib>
#include <limits>
#include <cmath>

using namespace std;

polynneal::polynneal(const vector<Point>& points, double _a, double T0, int num_iters) :
    k(0), a(_a), T(T0), k_max(num_iters)
{
    s = initial_solution(points);
    best_area = area = abs(s.area());
    best_solution = s;
}

polynneal::solution_t polynneal::get_best() const
{
    return best_solution;
}

double polynneal::get_best_area() const
{
    return best_area;
}

polynneal::solution_t polynneal::get_current() const
{
    return s;
}

double polynneal::get_current_area() const
{
    return area;
}

double polynneal::get_temperature() const
{
    return T;
}

bool polynneal::iteration()
{
    if (k >= k_max) {
        return false;
    }

    T *= a;
    solution_t s_new = neighbor(s);
    double rnd = (double)rand() / RAND_MAX;
    double new_area = abs(s_new.area());

    double P = acceptance_probability(area, new_area, T);
    if (P >= rnd) {
        s = s_new;
        area = new_area;
        if (new_area < best_area) {
            best_area = new_area;
            best_solution = s;
        }
    }

    k++;

    return true;
}

double polynneal::acceptance_probability(double e_old, double e_new, double T)
{
    if (e_new < e_old) {
        return 1.0;
    } else {
        return exp((e_old - e_new) / T);
    }
}

polynneal::solution_t polynneal::neighbor(const solution_t& s_old)
{
    solution_t s = s_old;
    int n = s.poly.size();
    int i = rand() % n, j = rand() % n;
    s.swap(i, j);

    while (!CGAL::is_simple_2(s.poly.begin(), s.poly.end(), Miroljub())) {
        // Swap back
        s.swap(i, j);

        // Try again
        i = rand() % n;
        j = rand() % n;
        s.swap(i, j);
    }

    return s;
}

polynneal::solution_t polynneal::initial_solution(const vector<Point>& points)
{
    Point first = points[0];
    double min_x = first.x(), max_x = first.x(), min_y = first.y(), max_y = first.y();
    for (Point p : points) {
        double x = p.x(), y = p.y();
        if (x < min_x) {
            min_x = x;
        }
        if (y < min_y) {
            min_y = y;
        }
        if (x > max_x) {
            max_x = x;
        }
        if (y > max_y) {
            max_y = y;
        }
    }

    double cx = (min_x + max_x) / 2.0, cy = (min_y + max_y) / 2.0;

    vector<pair<Point, int>> sorted;
    for (int i = 0; i < points.size(); i++) {
        sorted.push_back({ points[i], i });
    }

    sort(sorted.begin(), sorted.end(), [cx, cy] (const auto& ap, const auto& bp) -> bool {
        const auto& a = ap.first;
        const auto& b = bp.first;

        double a1 = atan2(a.y() - cy, a.x() - cx);
        double a2 = atan2(b.y() - cy, b.x() - cx);
        if (abs(a1 - a2) < 1e-6) {
            double dax = a.x() - cx;
            double day = a.y() - cy;
            double dbx = b.x() - cx;
            double dby = b.y() - cy;
            double magn_a = dax * dax + day * day;
            double magn_b = dbx * dbx + dby * dby;

            return magn_a < magn_b;
        } else {
            return a1 < a2;
        }
    });

    vector<Point> poly(sorted.size());
    vector<int> perm(sorted.size());
    for (int i = 0; i < sorted.size(); i++) {
        poly[i] = sorted[i].first;
        perm[i] = sorted[i].second;
    }

    return { poly, perm };
}

bool polynneal::kali(int num_iters)
{
    while (num_iters--) {
        if (!iteration()) {
            return false;
        }
    }

    return true;
}

int polynneal::get_iteration() const
{
    return k;
}
