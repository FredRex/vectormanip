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

            Vector operator+(Vector);
            Vector operator-(Vector);
            Vector operator*(double);
            //Dot Product
            double operator*(Vector);

            std::string as_components();
            std::string as_mag_and_radians();
            std::string as_mag_and_degrees();

            Vector(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    };
}
