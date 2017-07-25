#pragma once

// forward declarations
template<typename T, size_t Size>
class Vector;

template<typename T>
class Vector_Expression;


// type trait to extract the underlying arithmetic type
template<typename T, typename Enable = void>
struct arithmetic_type
{
    using type = std::conditional_t<std::is_base_of_v<Vector_Expression<T>, T>, 
                                    typename T::value_type,
                                    void>;
};

template<typename T>
struct arithmetic_type<T, typename std::enable_if_t<std::is_arithmetic_v<T>>>
{
    using type = T;
};

template<typename T, size_t Size>
struct arithmetic_type<Vector<T, Size>>
{
    using type = typename Vector<T, Size>::value_type;
};

template<typename T>
using arithmetic_type_t = typename arithmetic_type<T>::type;


// is a type vector-like?
template<typename T>
struct is_vector : std::is_base_of<Vector_Expression<T>, T> { };

template<typename T, size_t Size>
struct is_vector<Vector<T, Size>> : std::true_type { };

template <typename T>
struct is_vector<const T> : is_vector<T> {};

template<typename T>
constexpr bool is_vector_v = is_vector<T>::value;