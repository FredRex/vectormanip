#include "vector.hpp"

#include <sstream>
#include <cmath>
#include <iomanip>

using namespace VolHacks;

Vector Vector::from_components(double x, double y) {
    return Vector(x, y);
}

Vector Vector::from_mag_and_degrees(double mag, double angle) {
    return Vector(
        mag * std::cos(angle * M_PI / 180.0),
        mag * std::sin(angle * M_PI / 180.0)
    );
}

Vector Vector::from_mag_and_radians(double mag, double angle) {
    return Vector(
        mag * std::cos(angle),
        mag * std::sin(angle)
    );
}

Vector Vector::operator+(Vector& a) {
    return Vector::from_components(
        x + a.x,
        y + a.y
    );
}

Vector Vector::operator-(Vector& a) {
    return Vector::from_components(
        x - a.x,
        y - a.y
    );
}

Vector Vector::operator*(double scale) {
    return Vector::from_components(
        x * scale,
        y * scale
    );
}

double Vector::operator*(Vector& a) {
    return x * a.x + y * a.y;
}


// Return "xxx.xxxxxxxxi yyy.yyyyyyyyj"
std::string Vector::as_components() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(7) << x << "i " << y << "j";
    return ss.str();
}

//Return "000.0000000 at 000.0000000rad"
std::string Vector::as_mag_and_radians() {
    double mag = std::sqrt(pow(x,2) + pow(y,2));
    std::stringstream ss;
    ss << std::fixed << std::setprecision(7) << mag << " at " << std::atan2(y, x) << "rad";
    return ss.str();
}

//Return "000.0000000 at 000.0000000deg"
std::string Vector::as_mag_and_degrees() {
    double mag = std::sqrt(pow(x,2) + pow(y,2));
    double angle = std::atan2(y, x) * 180 / M_PI;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(7) << mag << " at " << angle << "deg";
    return ss.str();
}
