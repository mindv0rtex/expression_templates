#pragma once

#include <cassert>
#include <numeric>
#include <cmath>
#include <iostream>

#include "expression_template.h"

template<typename T, size_t Size>
class Vector
{
    static_assert(Size > 0, "Vector size has to be larger than zero");
    static_assert(std::is_arithmetic_v<T>, "Arithmetic type is expected");

public:
    using value_type = T;
    constexpr static size_t size = Size;

    Vector() = default;
    Vector(const Vector&) = default;
    Vector(Vector&&) = default;
    Vector& operator=(const Vector&) = default;
    Vector& operator=(Vector&&) = default;
    ~Vector() = default;

    template <typename ...Ts>
    explicit constexpr Vector(Ts&&... t) : data{ std::forward<T>(t)... }
    {
        static_assert(sizeof...(Ts) == size, "Number of arguments in the constructor does not match the vector size");
    }

    template <typename Expr>
    constexpr Vector(const Vector_Expression<Expr>& expression) : data{}
    {
        static_assert(Expr::size == size);
        for (auto i = size_t{ 0 }; i < size; ++i)
            data[i] = expression[i];
    }

    bool hasNaNs() const
    {
        bool result = false;
        for (const auto& el : data)
            result = result || std::isnan(el);
        return result;
    }

    constexpr const T& operator[](size_t i) const
    {
        assert(i < size);
        return data[i];
    }

    constexpr T& operator[](size_t i)
    {
        assert(i < size);
        return data[i];
    }


    template <typename Src>
    Vector& operator=(const Src& that)
    {
        static_assert(Src::size == size);
        for (auto i = size_t{ 0 }; i < size; ++i)
            data[i] = that[i];
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector<T, Size> &v)
    {
        bool first{ true };
        os << "[ ";
        for (const auto& el : v.data)
        {
            if (first) first = false;
            else os << ", ";
            os << el;
        }
        os << " ]";
        return os;
    }

private:
    T data[size];
};


template<typename T, size_t Size>
constexpr T dot(const Vector<T, Size>& v1, const Vector<T, Size>& v2)
{
    T result = T(0);
    for (auto i = size_t{ 0 }; i < Size; ++i)
        result += v1[i] * v2[i];
    return result;
}
