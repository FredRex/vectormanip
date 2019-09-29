#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "vector.hpp"

using namespace VolHacks;

enum VectorState {
    Component,
    Degree,
    Radian,
    Invalid
};

VectorState parse_create(std::stringstream&, Vector&, char&);
bool load(std::map<char, Vector>& vectors, std::string fileName);
void write(std::string fileName, std::map<char, Vector>& vectors);

int main() {
    const std::string help = "Commands:\nq - quit\nc - create\nr - remove\nl - list\nw - write\nf - load file\na - assign\nd - dot product";
    bool error = false;

    std::map<char,Vector> vectors;

    std::cout << "Vector manipulator. Type h for help\n";
    while (true) {
        std::cout << '\n';
        if (error) {
            std::cout << "!> ";
        } else {
            std::cout << " > ";
        }
        error = false;
        std::string s;
        std::getline(std::cin, s);
        std::stringstream full_command(s);
        char command;
        full_command >> command;
        std::string first_arg;
        switch (command) {
            case 'q':
                return 0;
            case 'c':
                {
                    char vector_letter;
                    Vector vec;
                    VectorState state = parse_create(full_command, vec, vector_letter);
                    if (state == Invalid) {
                        error = true;
                        break;
                    }
                    vectors.insert(std::pair<char, Vector>(vector_letter, vec));
                }
                break;
            case 'r':
                char vector_letter;
                full_command >> vector_letter;
                if (full_command.fail() || !std::isupper(vector_letter)) {
                    error = true;
                    break;
                }
                if (!(vectors.find(vector_letter) == vectors.end()))
                    vectors.erase(vector_letter);
                else 
                    error = true;
                break;
            case 'l':
                for (auto& p : vectors) {
                    std::cout << p.first << ": "
                        << p.second.as_components() << " |"
                        << p.second.as_mag_and_degrees() << '\n';
                }
                break;
            case 'w':
                {
                    std::string fileName;
                    full_command >> fileName;
                    write(fileName, vectors);
                }
                break;
            case 'f':
                {
                    std::string fileName;
                    full_command >> fileName;
                    error = load(vectors, fileName);
                }
                break;
            case 'a': 
                {
                    Vector result = Vector::from_components(0.0, 0.0);
                    // make sure command is " <letter> "
                    if (full_command.get() != ' ') {
                        error = true;
                        break;
                    }
                    char vector_letter = full_command.get();
                    if (!std::isupper(vector_letter)) {
                        error = true;
                        break;
                    }
                    if (full_command.get() != ' ') {
                        error = true;
                        break;
                    }
                    // Loop until end for all terms
                    while (full_command.peek() != EOF) {
                        //Valid examples: -2B, +5.3C, -0.0002Y
                        double coefficient;
                        Vector term;
                        //Pull out sign, co-ef, and letter
                        char sign = full_command.get();
                        if (sign != '+' && sign != '-') {
                            error = true;
                            break;
                        }
                        full_command >> coefficient;
                        if (full_command.fail()) {
                            coefficient = 1.0;
                            full_command.clear();
                        }
                        char vector_letter = full_command.get();
                        if (!std::isupper(vector_letter)) {
                            error = true;
                            break;
                        }
                        
                        if (sign == '-') {
                            coefficient = -coefficient;
                        }
                        if (vectors.find(vector_letter) == vectors.end()) {
                            error = true;
                            break;
                        }
                        term = vectors[vector_letter];

                        result = result + term * coefficient;
                    }
                    if (!error) {
                        if (vectors.find(vector_letter) == vectors.end()) {
                            vectors.insert(std::pair<char, Vector>(vector_letter, result));
                        } else {
                            vectors[vector_letter] = result;
                        }
                    }

                }
                break;
            case 'd':
                if (full_command.get() != ' ') {
                    error = true;
                    break;
                }
                char a, b;
                a = full_command.get();
                b = full_command.get();
                if (full_command.fail()) {
                    error = true;
                    break;
                }
                if (std::isupper(a) && (vectors.find(a) != vectors.end()) &&
                    std::isupper(b) && (vectors.find(b) != vectors.end()))
                {
                    std::cout << "Dot Product: " << vectors[a] * vectors[b] << "\n";
                } else {
                    error = true;
                }
                break;
            case 'h':
                std::cout << help;
                break;
            default:
                error = true;
                break;
        }
    }
}

VectorState parse_create(std::stringstream& ss, Vector& ret, char& letter) {
    // Example valid commands
    // A 50.0i 125.21j
    // B 123 68.9d
    // V 29 28
    // E 1 1.038r
    // First letter is the vector letter
    VectorState state;
    if (ss.get() != ' ') return Invalid;
    letter = ss.get();
    if (!std::isupper(letter)) return Invalid;

    // Second letter should be a space
    if (ss.get() != ' ') return Invalid;
    double first_num, second_num;
    ss >> first_num;
    if (ss.fail()) return Invalid;
    char det = ss.get();
    if (det == 'i') {
        state = Component;
        if (ss.get() != ' ') return Invalid;
        ss >> second_num;
        if (ss.fail()) return Invalid;
        if (ss.get() != 'j') return Invalid;
        //if (!ss.eof()) return Invalid;
        ret = Vector::from_components(first_num, second_num);
        return state;
    // Magnitude and angle
    } else {
        if (det != ' ') return Invalid;
        ss >> second_num;
        if (ss.fail()) return Invalid;
        if (ss.eof()) {
            ret = Vector::from_mag_and_degrees(first_num, second_num);
            return Degree;
        } else if ((ss.get() == 'r') && ss.peek() == EOF) {
            ret = Vector::from_mag_and_radians(first_num, second_num);
            return Radian;
        } else {
            return Invalid;
        }
    }
}

bool load(std::map<char, Vector>& vectors, std::string fileName) {

    std::ifstream fd;
    fd.open(fileName.c_str());
    if (fd.is_open()) {
        vectors.clear();
        while (!fd.eof()) {
            std::string s;
            std::getline(fd, s);
            std::stringstream line(s);
            char key;
            double first_num;
            double second_num;
            (line >> key >> first_num).ignore(1) >> second_num;
            vectors.insert(std::pair<char, Vector>(key, Vector::from_components(first_num, second_num)));

        }
        return false;
    } else {
        return true;
    }

}

void write(std::string fileName, std::map<char, Vector>& vectors) {
    std::ofstream fout(fileName);
    std::stringstream ss;
    for (auto& p : vectors) {
        fout << p.first << "  " << p.second.as_components() << '\n';
    }
    fout.close();
    //fout << list(vectors);
}