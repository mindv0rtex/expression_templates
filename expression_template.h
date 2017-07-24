#pragma once

#include <type_traits>
#include "vector_traits.h"

template<typename T>
class Vector_Expression
{
public:
    constexpr auto operator[](size_t i) const
    {
        return static_cast<T const&>(*this)[i];
    }
};


template <typename Arg1, typename Arg2, typename BinaryOperator>
class Binary_Expression : public Vector_Expression<Binary_Expression<Arg1, Arg2, BinaryOperator>>
{
public:
    using value_type = std::common_type_t<arithmetic_type_t<Arg1>, arithmetic_type_t<Arg2>>;
    
    constexpr static size_t size = Arg1::size;

    constexpr Binary_Expression(const Arg1& v1, const Arg2& v2, BinaryOperator bop)
        : v1{ v1 }, v2{ v2 }, bop{ bop } {}

    constexpr value_type operator[](const size_t& i) const { return bop(v1, v2, i); }

private:
    const Arg1& v1;
    const Arg2& v2;
    BinaryOperator bop;
};

/* Vector Sum */
template <typename V1, typename V2>
constexpr auto operator+(const V1& x, const V2& y)
{
    static_assert(is_vector_v<V1> && is_vector_v<V2> && V1::size == V2::size);
    constexpr auto sum = [](auto v1, auto v2, size_t i) { return v1[i] + v2[i]; };
    return Binary_Expression{ x, y, sum };
}


/* Vector Subtraction */
template <typename V1, typename V2>
constexpr auto operator-(const V1& x, const V2& y)
{
    static_assert(is_vector_v<V1> && is_vector_v<V2> && V1::size == V2::size);
    constexpr auto subtract = [](auto v1, auto v2, size_t i) { return v1[i] - v2[i]; };
    return Binary_Expression{ x, y, subtract };
}


/* Cross Product */
template <typename V1, typename V2>
constexpr auto cross(const V1& x, const V2& y)
{
    static_assert(is_vector_v<V1> && is_vector_v<V2> && V1::size == 3 && V1::size == V2::size);
    constexpr auto cross_product = [](auto v1, auto v2, size_t i) 
    {
        size_t idx1 = (i + 1) % 3, idx2 = (i + 2) % 3;
        return v1[idx1] * v2[idx2] - v1[idx2] * v2[idx1];
    };
    return Binary_Expression{ x, y, cross_product };
}


/* Scalar-Vector Product */
template <typename V1, typename S2>
constexpr auto operator*(const V1& x, const S2& y)
{
    static_assert(is_vector_v<V1> && std::is_arithmetic_v<S2>);
    constexpr auto scalar_product = [](auto v1, auto s2, size_t i) { return v1[i] * s2; };
    return Binary_Expression{ x, y, scalar_product };
}
