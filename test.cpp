
#include <iostream>
#include "vector.hpp"

using namespace VolHacks;

int main() {
    Vector my_vec = Vector::from_mag_and_degrees(10, 30);
    Vector la = Vector::from_components(2, 3);
    Vector le = Vector::from_components(5, 10);

    std::cout << my_vec.as_components() << '\n';
    std::cout << my_vec.as_mag_and_degrees() << '\n';
    std::cout << (la * 2).as_components() << '\n';
    return 0;
}