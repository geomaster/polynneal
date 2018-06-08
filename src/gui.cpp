#ifndef HEADLESS
#include "gui.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

const double WINDOW_PADDING = 60.0;
const double VERTEX_CIRCLE_RADIUS = 4.0;
const double LINE_THICKNESS = 2.5;

const sf::Color VERTEX_COLOR = sf::Color::White;
const sf::Color BEST_POLY_COLOR = sf::Color(0xefa60790);
const sf::Color PREV_CURR_POLY_COLOR = sf::Color(0x4488e230);
const sf::Color CURR_POLY_COLOR = sf::Color(0x4488e27a);

gui::gui(int _width, int _height, const vector<Point>& points) :
    width(_width), height(_height)
{
    Point first = points[0];
    double min_x = first.x(), min_y = first.y(), max_x = first.x(), max_y = first.y();

    for (Point p : points) {
        double x = p.x(), y = p.y();
        if (x < min_x) {
            min_x = x;
        }
        if (x > max_x) {
            max_x = x;
        }
        if (y < min_y) {
            min_y = y;
        }
        if (y > max_y) {
            max_y = y;
        }
    }

    double cx = (max_x + min_x) / 2.0, cy = (max_y + min_y) / 2.0;
    double extent = max(max_x - min_x, max_y - min_y);
    double screen_extent = max(width, height) - 2 * WINDOW_PADDING;
    double scale_factor = screen_extent / extent;

    center_x = cx;
    center_y = cy;
    this->scale_factor = scale_factor;

    for (Point p : points) {
        sf::CircleShape c(VERTEX_CIRCLE_RADIUS);
        c.setFillColor(VERTEX_COLOR);
        c.setOrigin(VERTEX_CIRCLE_RADIUS, VERTEX_CIRCLE_RADIUS);
        c.setPosition(transform_point(p));
        point_shapes.push_back(c);
    }
}

void gui::set_current_poly(const vector<int>& permutation)
{
    prev_current_poly = current_poly;
    for (auto& l : prev_current_poly) {
        l.setFillColor(PREV_CURR_POLY_COLOR);
    }

    current_poly = lines_from_permutation(permutation);
    for (auto& l : current_poly) {
        l.setFillColor(CURR_POLY_COLOR);
    }
}

void gui::set_best_poly(const vector<int>& permutation)
{
    best_poly = lines_from_permutation(permutation);
    for (auto& l : best_poly) {
        l.setFillColor(BEST_POLY_COLOR);
    }
}

vector<sf::LineShape> gui::lines_from_permutation(const vector<int>& permutation)
{
    vector<sf::LineShape> result;
    for (int i = 0; i < permutation.size(); i++) {
        sf::Vector2f current = point_shapes[permutation[i]].getPosition();
        sf::Vector2f next = point_shapes[permutation[(i + 1) % permutation.size()]].getPosition();

        auto l = sf::LineShape(current, next);
        l.setThickness(LINE_THICKNESS);
        result.push_back(l);
    }

    return result;
}

void gui::draw(sf::RenderWindow& window)
{
    for (auto& l : prev_current_poly) {
        window.draw(l);
    }
    for (auto& l : current_poly) {
        window.draw(l);
    }
    for (auto& l : best_poly) {
        window.draw(l);
    }
    for (auto& c : point_shapes) {
        window.draw(c);
    }
}

sf::Vector2f gui::transform_point(Point p)
{
    double x = p.x(), y = p.y();
    x -= center_x;
    y -= center_y;
    x *= scale_factor;
    y *= scale_factor;
    x += width / 2;
    y += height / 2;

    return sf::Vector2f(x, y);
}

#endif // HEADLESS
