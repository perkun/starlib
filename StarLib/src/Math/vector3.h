#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "vector.h"
#include "Assert.h"

namespace StarLib
{


template <typename T>
class Vector<T, 3>
{
public:
    Vector();
    Vector(const Vector<T, 3> &vec);
    Vector(const Vector<T, 2> &vec, T z);
    Vector(T x, T y, T z);
    Vector(T val);
    ~Vector()
    {
    }

    union
    {
        T x, u, r;
    };
    union
    {
        T y, v, g;
    };
    union
    {
        T z, t, b;
    };


    Vector<T, 3> &operator=(const Vector<T, 3> &other);
    T &operator[](std::size_t idx);
    const T &operator[](std::size_t idx) const;

    Vector<T, 3> &operator+=(const Vector<T, 3> &rhs);
    Vector<T, 3> &operator-=(const Vector<T, 3> &rhs);
    Vector<T, 3> &operator*=(T scalar);
    Vector<T, 3> &operator/=(T scalar);

	Vector<T, 2> xy();

	double length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	std::string str(int precision = 15) const
	{
        if (precision > 20)
            precision = 20;
        if (precision < 0)
            precision = 0;

        int total = 7 + precision;

        char fmt[200];
        sprintf(fmt, "%%%d.%dlf  %%%d.%dlf  %%%d.%dlf", total, precision,
                total, precision, total, precision);
		char text[200];
        sprintf(text, fmt, x, y, z);
		return std::string(text);
	}

    void print(int precision = 15)
    {
		std::string text = str(precision);
		std::cout << text << std::endl;
    }

};

template <typename T>
Vector<T, 3>::Vector()
{
	x = 0.;
	y = 0.;
	z = 0.;
}

template <typename T>
Vector<T, 3>::Vector(T val) : x(val), y(val), z(val)
{
}

template <typename T>
Vector<T, 3>::Vector(T x, T y, T z) : x(x), y(y), z(z)
{
}

template <typename T>
Vector<T, 3>::Vector(const Vector<T, 3> &vec)
{
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
}


template <typename T>
Vector<T, 3>::Vector(const Vector<T, 2> &vec, T val)
{
    this->x = vec.x;
    this->y = vec.y;
    this->z = val;
}

template <typename T>
Vector<T, 3>& Vector<T, 3>::operator=(const Vector<T, 3> &other)
{
    // Guard self assignment
    if (this == &other)
        return *this;

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}

template <typename T>
T& Vector<T, 3>::operator[](std::size_t idx)
{
	ASSERT(idx >= 0 && idx <= 3, "Vec3 index out of bounds");
    switch (idx)
    {
    case 0:
        return x;
    case 1:
        return y;
	case 2:
		return z;
	}
	return x;
}


template <typename T>
const T& Vector<T, 3>::operator[](std::size_t idx) const
{
	ASSERT(idx >= 0 && idx <= 3, "Vec3 index out of bounds");
    switch (idx)
    {
    case 0:
        return x;
    case 1:
        return y;
	case 2:
		return z;
	}
	return x;
}


template <typename T>
Vector<T, 3>& Vector<T, 3>::operator+=(const Vector<T, 3> &rhs)
{
    /* addition of rhs to *this takes place here */
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;

    return *this; // return the result by reference
}


template <typename T>
Vector<T, 3>& Vector<T, 3>::operator-=(const Vector<T, 3> &rhs)
{
    /* addition of rhs to *this takes place here */
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;

    return *this; // return the result by reference
}


template <typename T>
Vector<T, 3> &Vector<T, 3>::operator*=(T scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;

	return *this;
}


template <typename T>
Vector<T, 3> &Vector<T, 3>::operator/=(T scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;

	return *this;
}


template <typename T>
Vector<T, 2> Vector<T, 3>::xy()
{
	return Vector<T, 2>(x, y);
}


template <typename T>
Vector<T, 3> rotate_x(const Vector<T, 3> &vec, double angle)
{
    Vector<T, 3> out(vec.x,
					 vec.y * cos(angle) - vec.z * sin(angle),
                     vec.y * sin(angle) + vec.z * cos(angle));
    return out;
}


template <typename T>
Vector<T, 3> rotate_y(const Vector<T, 3> &vec, double angle)
{
    Vector<T, 3> out(vec.x * cos(angle) + vec.z * sin(angle),
					 vec.y,
                    -vec.x * sin(angle) + vec.z * cos(angle));
    return out;
}


template <typename T>
Vector<T, 3> rotate_z(const Vector<T, 3> &vec, double angle)
{
    Vector<T, 3> out(vec.x * cos(angle) - vec.y * sin(angle),
                     vec.x * sin(angle) + vec.y * cos(angle),
					 vec.z);
    return out;
}


template <typename T>
double dot(const Vector<T, 3>& vec1, const Vector<T, 3> &vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

template <typename T>
Vector<T, 3> cross(const Vector<T, 3>& vec1, const Vector<T, 3> &vec2)
{
    return Vector<T, 3>(vec1.y * vec2.z - vec1.z * vec2.y,
                vec1.z * vec2.x - vec1.x * vec2.z,
                vec1.x * vec2.y - vec1.y * vec2.x);
}


} // namespace StarLib

#endif
