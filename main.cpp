#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cctype>

#include "vector.hpp"

using std::cout;
using std::cin;

using namespace VolHacks;



enum VectorState {
    Component,
    Degree,
    Radian,
    Invalid
};


int main() {
    const std::string help = " >Commands:\nq - quit\nc - create\nr - remove\nl - list\nw -write\nf - load file\na - assign\n";
    bool error = false;

    std::map<char,Vector> vectors;

    cout << "Vector manipulator. Type h for help\n";
    while (true) {
        cout << " > ";
        std::string s;
        std::getline(cin, s);
        std::stringstream full_command(s);
        char command;
        full_command >> command;
        switch (command) {
            case 'q':
                return 0;
            case 'c':
                //Create a vector
                // Example command: > c A 50i 60j
                // > c B 50 30
                bool is_component;
                std::string first_arg;
                full_command >> first_arg; //"50i"
                for (unsigned int i = 0; i < first_arg.size(); ++i) {
                    if (i != (first_arg.size() - 1)) {
                        if (!std::isdigit(first_arg[i])) {
                            error = true;
                        }
                    } else {
                        //if (is(digitfirst_arg[i])
                    }
                }

                break;
        }
    }
}

VectorState parse_create(std::string& s) {
    // Example valid commands
    // A 50.0i 125.21j
    // B 123 68.9d
    // V 29 28
    // E 1 1.038r
    if (!std::isupper(s[0])) return Invalid;
    if (s[1] != ' ') return Invalid;

    

}




bool create(char vector, std::map<char, Vector>& vectors, Vector v) {
    vectors[vector] = v;
}

bool remove(int index, std::map<char, Vector>& vectors) {
    
}

std::string list(std::map<char, Vector>& vectors) {
    unsigned int i;
    std::stringstream ss;
    char key = 'A';
    for (i = 0; i < 26; i++) {
        ss << (key + i) << ' ' << vectors.at(i).x << "i " << vectors.at(i).y << "j\n";
    }
    return ss.str();
}

bool load(std::map<char, Vector>& vectors, std::string fileName) {
    std::ifstream fin(fileName);
    unsigned int i;
    std::stringstream ss;
    char key;
    std::string xs;
    std::string ys;
    double xd;
    double yd;
    for (i = 0; i < 26; i++) {
        fin >> key;
        fin >> xs;
        fin >> ys;
        xs.back() = '0';
        ys.back() = '0';
        xd = stod(xs);
        yd = stod(ys);
        Vector v = Vector::from_components(xd, yd);
        vectors.emplace(key, v);
    }
}

bool write(std::string fileName, std::map<char, Vector>& vectors) {
    std::ofstream fout(fileName);
    fout << list(vectors);
}