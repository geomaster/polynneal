#include <string>
#include <sstream>

#include "geo.hpp"
#include "gui.hpp"
#include "polynneal.hpp"

using namespace std;

bool csv = false;
bool png = false;
string png_prefix = "";

const int WINDOW_SIZE = 600;
const int ITERS_BATCH = 1000;

int run = 1;

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
    cerr << "Run #" << run << " Iteration #" << sinisha.get_iteration() << endl;
    cerr << "   Current area: " << sinisha.get_current_area() << endl;
    cerr << "   Best area:    " << sinisha.get_best_area() << endl;
    cerr << "   Temperature:  " << sinisha.get_temperature() << endl << endl;

    if (csv) {
        cout << run << ',' << sinisha.get_iteration() << ',' << sinisha.get_current_area() << ',' << sinisha.get_best_area() << ',' << sinisha.get_temperature() << endl;
    }
}

void update_gui(gui& g, const polynneal& sinisha)
{
    g.set_best_poly(sinisha.get_best().perm);
    g.set_current_poly(sinisha.get_current().perm);
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
    if (argc < 1 + 4) {
        cerr << "Usage: " << argv[0] << " <runs> <alpha> <T0> <iters> ['csv']" << endl;
        return -1;
    }
    if (argc >= 1 + 5 && string(argv[5]) == "csv") {
        csv = true;
    }
    if (argc >= 1 + 6) {
        png_prefix = argv[6];
        png = true;
    }

    int runs = str_to_int(argv[1]);

    if (csv) {
        cout << "Run,Iteration,Area,BestArea,Temperature" << endl;
    }

    vector<Point> poly = read_polygon(cin);
    gui g(WINDOW_SIZE, WINDOW_SIZE, poly);
    sf::Texture tex;
    tex.create(WINDOW_SIZE, WINDOW_SIZE);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "polynneal",
            sf::Style::Default, settings);

    for (run = 1; run <= runs; run++) {
        polynneal sinisha(poly, str_to_double(argv[2]), str_to_double(argv[3]), str_to_int(argv[4]));
        update_gui(g, sinisha);
        while (window.isOpen()) {
            sf::Event ev;
            while (window.pollEvent(ev)) {
                if (ev.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear(sf::Color(0x3a3a3aff));
            g.draw(window);
            window.display();

            if (!sinisha.kali(ITERS_BATCH)) {
                cerr << "Run #" << run << " finished" << endl;
                cerr << "    Best solution: " << endl;
                cerr << "        P = (";
                vector<int> perm = sinisha.get_best().perm;
                for (int i = 0; i < perm.size(); i++) {
                    cerr << (perm[i] + 1) << (i == perm.size() - 1 ? "" : ", ");
                }
                cerr << ')' << endl;
                cerr << "        A = " << sinisha.get_best_area() << endl;
                cerr << "***" << endl << endl;

                if (png) {
                    string png_filename = png_prefix + "_" + to_string(run) + ".png";
                    tex.update(window);
                    sf::Image img = tex.copyToImage();
                    img.saveToFile(png_filename);
                }

                break;
            }
            update_gui(g, sinisha);
            print_stats(sinisha);
        }
    }

    return 0;
}
