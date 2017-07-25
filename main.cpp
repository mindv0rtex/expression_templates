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
    constexpr Vector<double, 3> v3{ 0., 0., 1. };
    constexpr Vector<double, 3> s = v1 + v2 + v3;

    std::cout << s << "\n";
}
