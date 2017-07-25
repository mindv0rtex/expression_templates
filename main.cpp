#include <iostream>
#include <boost/type_index.hpp>

#include "vector.h"

template<typename T>
void print_type(T)
{
    std::cout << boost::typeindex::type_id<T>().pretty_name() << "\n";
}

int main()
{
    constexpr Vector<double, 3> v1{ 1., 0., 0. };
    constexpr Vector<double, 3> v2{ 0., 1., 0. };
    constexpr Vector<double, 3> v3{ 0., 1., 1. };
    constexpr Vector<double, 3> v4{ 0., 5., 2. };
    constexpr Vector<double, 3> s = v1 * 10.0 + v2 * dot(v3, v4) + v3 - cross(v1, v2);
    std::cout << s << "\n";
}
