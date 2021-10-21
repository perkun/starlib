#ifndef VECTOR2_H_
#define VECTOR2_H_


#include "vector.h"
#include "Assert.h"

namespace StarLib
{


template <typename T>
class Vector<T, 2>
{
public:
    Vector();
    Vector(const Vector<T, 2> &vec);
    Vector(T x, T y);
    Vector(T val);
    ~Vector()
    {
    }

    union
    {
        T x, u, a;
    };
    union
    {
        T y, v, b;
    };


    Vector<T, 2> &operator=(const Vector<T, 2> &other);
    T &operator[](std::size_t idx);
    const T &operator[](std::size_t idx) const;

    Vector<T, 2> &operator+=(const Vector<T, 2> &rhs);
    Vector<T, 2> &operator-=(const Vector<T, 2> &rhs);
    Vector<T, 2> &operator*=(T scalar);
    Vector<T, 2> &operator/=(T scalar);

    double length() const
    {
        return sqrt(x * x + y * y);
    }

    std::string str(int precision = 15) const
    {
        if (precision > 20)
            precision = 20;
        if (precision < 0)
            precision = 0;

        int total = 7 + precision;

        char fmt[200];
        sprintf(fmt, "%%%d.%dlf  %%%d.%dlf", total, precision, total,
                precision);

        char text[200];
        sprintf(text, fmt, x, y);
        return std::string(text);
    }

    void print(int precision = 15)
    {
		std::string text = str(precision);
		std::cout << text << std::endl;
    }
};

template <typename T>
Vector<T, 2>::Vector()
{
	x = 0.;
	y = 0.;
}

template <typename T>
Vector<T, 2>::Vector(T val) : x(val), y(val)
{
}

template <typename T>
Vector<T, 2>::Vector(T x, T y) : x(x), y(y)
{
}

template <typename T>
Vector<T, 2>::Vector(const Vector<T, 2> &vec)
{
    this->x = vec.x;
    this->y = vec.y;
}


template <typename T>
Vector<T, 2>& Vector<T, 2>::operator=(const Vector<T, 2> &other)
{
    // Guard self assignment
    if (this == &other)
        return *this;

	this->x = other.x;
	this->y = other.y;

	return *this;
}

template <typename T>
T& Vector<T, 2>::operator[](std::size_t idx)
{
	ASSERT(idx >= 0 && idx <= 2, "Vec2 index out of bounds");
    switch (idx)
    {
    case 0:
        return x;
    case 1:
        return y;
	}
	return x;
}


template <typename T>
const T& Vector<T, 2>::operator[](std::size_t idx) const
{
	ASSERT(idx >= 0 && idx <= 2, "Vec2 index out of bounds");
    switch (idx)
    {
    case 0:
        return x;
    case 1:
        return y;
	}
	return x;
}


template <typename T>
Vector<T, 2>& Vector<T, 2>::operator+=(const Vector<T, 2> &rhs)
{
    /* addition of rhs to *this takes place here */
	this->x += rhs.x;
	this->y += rhs.y;

    return *this; // return the result by reference
}


template <typename T>
Vector<T, 2>& Vector<T, 2>::operator-=(const Vector<T, 2> &rhs)
{
    /* addition of rhs to *this takes place here */
	this->x -= rhs.x;
	this->y -= rhs.y;

    return *this; // return the result by reference
}


template <typename T>
Vector<T, 2> &Vector<T, 2>::operator*=(T scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}


template <typename T>
Vector<T, 2> &Vector<T, 2>::operator/=(T scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	return *this;
}


template <typename T>
Vector<T, 2> rotate(const Vector<T, 2> &vec, double angle)
{
	Vector<T, 2> out;
    out.x = vec.x * cos(angle) - vec.y * sin(angle);
    out.y = vec.x * sin(angle) + vec.y * cos(angle);
	return out;
}




} // namespace StarLib

#endif
