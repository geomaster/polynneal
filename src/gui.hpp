#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>

#include "geo.hpp"
#include "line_shape.hpp"

class gui
{
public:
    gui(int _width, int _height, const std::vector<Point>& points);

    void set_best_poly(const Polygon& poly);
    void set_current_poly(const Polygon& poly);
    void set_metric(int i, const std::string& name, const std::string& value);

    void draw(sf::RenderWindow& window);

private:
    struct metric {
        sf::Text label;
        sf::Text value;
    };

    int width, height;

    std::vector<sf::CircleShape> point_shapes;
    std::vector<sf::LineShape> best_poly;
    std::vector<sf::LineShape> current_poly;
    std::unordered_map<int, metric> metrics;

    double center_x, center_y, scale_factor;
    sf::Vector2f transform_point(Point p);

    std::vector<sf::LineShape> lines_from_poly(const Polygon& poly);
};
