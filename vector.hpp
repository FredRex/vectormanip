#pragma once
#include <string>

namespace VolHacks {
    class Vector {
        public:
            double x;
            double y;
            static Vector from_components(double x, double y);
            static Vector from_mag_and_degrees(double mag, double angle);
            static Vector from_mag_and_radians(double mag, double angle);
            Vector operator+(Vector& a);
            Vector operator-(Vector& a);
            Vector operator*(double scale);
            //Dot Product
            double operator*(Vector& a);

            std::string as_components();
            std::string as_mag_and_radians();
            std::string as_mag_and_degrees();

        
        
            Vector(double x, double y) : x(x), y(y) {}
    };
}
