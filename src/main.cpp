#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <string>
#include <sstream>

#include "geo.hpp"
#include "gui.hpp"
#include "polynneal.hpp"

bool csv = false;

const int WINDOW_SIZE = 800;
const int ITERS_BATCH = 1000;

using namespace std;

vector<Point> read_polygon(istream& s)
{
    int n;
    s >> n;
    vector<Point> res;
    res.reserve(n);
    while (n--) {
        double x, y;
        s >> x >> y;
        res.push_back(Point(x, y));
    }

    return res;
}

void print_stats(const polynneal& sinisha) {
    cerr << "Iteration #" << sinisha.get_iteration() << endl;
    cerr << "   Current area: " << sinisha.get_current_area() << endl;
    cerr << "   Best area:    " << sinisha.get_best_area() << endl;
    cerr << "   Temperature:  " << sinisha.get_temperature() << endl << endl;

    if (csv) {
        cout << sinisha.get_iteration() << ',' << sinisha.get_current_area() << ',' << sinisha.get_best_area() << ',' << sinisha.get_temperature() << endl;
    }
}

void update_gui(gui& g, const polynneal& sinisha)
{
    g.set_best_poly(sinisha.get_best());
    g.set_current_poly(sinisha.get_current());
}

double str_to_double(string s)
{
    istringstream str(s);
    double d;
    str >> d;
    return d;
}

int str_to_int(string s)
{
    istringstream str(s);
    int i;
    str >> i;
    return i;
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    if (argc < 1 + 3) {
        cerr << "Usage: " << argv[0] << "<alpha> <T0> <iters>" << endl;
        return -1;
    }
    if (argc >= 1 + 4 && string(argv[4]) == "csv") {
        csv = true;
    }

    if (csv) {
        cout << "Iteration,Area,BestArea,Temperature" << endl;
    }

    vector<Point> poly = read_polygon(cin);
    gui g(WINDOW_SIZE, WINDOW_SIZE, poly);
    polynneal sinisha(poly, str_to_double(argv[1]), str_to_double(argv[2]), str_to_int(argv[3]));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "polynneal",
            sf::Style::Default, settings);

    update_gui(g, sinisha);
    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        g.draw(window);
        window.display();

        if (!sinisha.kali(ITERS_BATCH)) {
            break;
        }
        update_gui(g, sinisha);
        print_stats(sinisha);
    }

    return 0;
}
