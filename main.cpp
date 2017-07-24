#include <iostream>
#include "vector.h"

int main()
{
    constexpr Vector<double, 3> v1{ 1., 0., 0. };
    constexpr Vector<double, 3> v2{ 0., 1., 0. };

    constexpr Vector<double, 3> s = v1 - v2;
    std::cout << s << "\n";
}
