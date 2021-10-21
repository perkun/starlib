#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <string>
#include <math.h>

namespace StarLib
{

template <typename T, int SIZE> class Vector;


////////////////////////////////////////////////////////////////////////////////
//// Operators
////////////////////////////////////////////////////////////////////////////////


template <typename T, int SIZE>
std::ostream &operator<<(std::ostream &os, const Vector<T, SIZE> &vec)
{
	os << vec.str();
	return os;
}


template <typename T, int SIZE>
Vector<T, SIZE> operator+(Vector<T, SIZE> lhs, const Vector<T, SIZE> &rhs)
{
    return lhs += rhs; // return the result by value (uses move constructor)
}


template <typename T, int SIZE>
Vector<T, SIZE> operator-(Vector<T, SIZE> lhs, const Vector<T, SIZE> &rhs)
{
    return lhs -= rhs; // return the result by value (uses move constructor)
}


template <typename T, int SIZE>
Vector<T, SIZE> operator*(T scalar, Vector<T, SIZE> vec)
{
	return vec *= scalar;
}


template <typename T, int SIZE>
Vector<T, SIZE> operator*(Vector<T, SIZE> vec, T scalar)
{
	return vec *= scalar;
}


template <typename T, int SIZE>
Vector<T, SIZE> operator/(Vector<T, SIZE> vec, T scalar)
{
	return vec /= scalar;
}


template <typename T, int SIZE>
Vector<T, SIZE> normalize(const Vector<T, SIZE> &vec)
{
	Vector<T, SIZE> v2 = vec;
	return v2 / v2.length();
}


template <typename T, int SIZE>
Vector<T, SIZE> normalize(Vector<T, SIZE> &vec)
{
	Vector<T, SIZE> out = vec / vec.length();
	return out;
}

} // namespace StarLib

#endif /* VECTOR_H_ */
