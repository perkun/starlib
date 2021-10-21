#include <iostream>
#include <stdio.h>
#include <gtest/gtest.h>
#include "starlibmath.h"
#include "Units.h"

using namespace std;
using namespace StarLib;

#define PRECISION (1e-15)

TEST(Vec2, constructors)
{
	Vec2 vec(10.1010, 20.2020);

	EXPECT_DOUBLE_EQ(vec.x, 10.1010);
	EXPECT_DOUBLE_EQ(vec.y, 20.2020);

	Vec2 vec2(vec);
	EXPECT_DOUBLE_EQ(vec2.x, 10.1010);
	EXPECT_DOUBLE_EQ(vec2.y, 20.2020);

	Vec2 vec3(123.4567);
	EXPECT_DOUBLE_EQ(vec3.x, 123.4567);
	EXPECT_DOUBLE_EQ(vec3.y, 123.4567);
}


TEST(iVec2, constructors)
{
	iVec2 vec(10.1010, 20.2020);

	EXPECT_EQ(vec.x, 10);
	EXPECT_EQ(vec.y, 20);

	iVec2 vec2(vec);
	EXPECT_EQ(vec2.x, 10);
	EXPECT_EQ(vec2.y, 20);

	iVec2 vec3(123.4567);
	EXPECT_EQ(vec3.x, 123);
	EXPECT_EQ(vec3.y, 123);
}

TEST(Vec2, arithmetic)
{
	Vec2 vec1(1., 2.);
	Vec2 vec2(10., 20.);

	Vec2 vec3 = vec1 + vec2;
	EXPECT_DOUBLE_EQ(vec3.x, 11.0);
	EXPECT_DOUBLE_EQ(vec3.y, 22.0);

	Vec2 vec4 = vec1 * 2.0;
	EXPECT_DOUBLE_EQ(vec4.x, 2.0);
	EXPECT_DOUBLE_EQ(vec4.y, 4.0);

	vec4 = 2.0 * vec1;
	EXPECT_DOUBLE_EQ(vec4.x, 2.0);
	EXPECT_DOUBLE_EQ(vec4.y, 4.0);

	vec4 = vec1 / 2.0;
	EXPECT_DOUBLE_EQ(vec4.x, 0.5);
	EXPECT_DOUBLE_EQ(vec4.y, 1.);


	// original vectors should stay the same
	EXPECT_DOUBLE_EQ(vec1.x, 1.0);
	EXPECT_DOUBLE_EQ(vec1.y, 2.0);

	EXPECT_DOUBLE_EQ(vec2.x, 10.0);
	EXPECT_DOUBLE_EQ(vec2.y, 20.0);
}


TEST(Vec2, normalization)
{
	Vec2 vec(1.0, 2.0);
	EXPECT_DOUBLE_EQ(vec.length(), 2.23606797749979);
	Vec2 vec2 = normalize(vec);
	EXPECT_DOUBLE_EQ(vec2.length(), 1.0);
}


TEST(Vec2, rotations)
{
	Vec2 vec(1.0, 0.);
	Vec2 vec2 = rotate(vec, M_PI/2.);

	EXPECT_LE(vec2.x, PRECISION);
	EXPECT_LE(fabs(vec2.y - 1.), PRECISION);

	vec2 = rotate(vec, 45 * UNITS::DEG);

	EXPECT_LE(fabs(vec2.x - 1./sqrt(2.)), PRECISION);
	EXPECT_LE(fabs(vec2.y - 1./sqrt(2.)), PRECISION);

}


TEST(Vec3, constructors)
{
	Vec3 a;
	EXPECT_DOUBLE_EQ(a.x, 0.0);
	EXPECT_DOUBLE_EQ(a.y, 0.0);
	EXPECT_DOUBLE_EQ(a.z, 0.0);

	Vec3 b(1, 2, 3);
	EXPECT_DOUBLE_EQ(b.x, 1.0);
	EXPECT_DOUBLE_EQ(b.y, 2.0);
	EXPECT_DOUBLE_EQ(b.z, 3.0);

	Vec3 c(4);
	EXPECT_DOUBLE_EQ(c.x, 4.0);
	EXPECT_DOUBLE_EQ(c.y, 4.0);
	EXPECT_DOUBLE_EQ(c.z, 4.0);

	Vec3 d(b);
	EXPECT_DOUBLE_EQ(d.x, 1.0);
	EXPECT_DOUBLE_EQ(d.y, 2.0);
	EXPECT_DOUBLE_EQ(d.z, 3.0);

	Vec2 v2(3, 4);
	Vec3 e(v2, 5);
	EXPECT_DOUBLE_EQ(e.x, 3.0);
	EXPECT_DOUBLE_EQ(e.y, 4.0);
	EXPECT_DOUBLE_EQ(e.z, 5.0);

	v2 = b.xy();
	EXPECT_DOUBLE_EQ(v2.x, 1.0);
	EXPECT_DOUBLE_EQ(v2.y, 2.0);
}


TEST(Vec3, arithmetic)
{
	Vec3 vec1(1., 2., 3.);
	Vec3 vec2(10., 20., 30.);

	Vec3 a = vec1;
	EXPECT_DOUBLE_EQ(a.x, 1.0);
	EXPECT_DOUBLE_EQ(a.y, 2.0);
	EXPECT_DOUBLE_EQ(a.z, 3.0);

	a = vec1 + vec2;
	EXPECT_DOUBLE_EQ(a.x, 11.0);
	EXPECT_DOUBLE_EQ(a.y, 22.0);
	EXPECT_DOUBLE_EQ(a.z, 33.0);

	a = vec1 - vec2;
	EXPECT_DOUBLE_EQ(a.x, -9.0);
	EXPECT_DOUBLE_EQ(a.y, -18.0);
	EXPECT_DOUBLE_EQ(a.z, -27.0);

	Vec3 b = vec1 / 3.;
	EXPECT_DOUBLE_EQ(b.x, 1.0 / 3.0);
	EXPECT_DOUBLE_EQ(b.y, 2.0 / 3.0);
	EXPECT_DOUBLE_EQ(b.z, 3.0 / 3.0);

	Vec3 c = vec1 * 3.;
	EXPECT_DOUBLE_EQ(c.x, 1.0 * 3.0);
	EXPECT_DOUBLE_EQ(c.y, 2.0 * 3.0);
	EXPECT_DOUBLE_EQ(c.z, 3.0 * 3.0);

	Vec3 d = vec1;
	d /= 4;
	EXPECT_DOUBLE_EQ(d.x, 1.0 / 4.0);
	EXPECT_DOUBLE_EQ(d.y, 2.0 / 4.0);
	EXPECT_DOUBLE_EQ(d.z, 3.0 / 4.0);


	// DOT product
	EXPECT_DOUBLE_EQ(dot(vec1, vec2), 140.);

	// CROSS
	Vec3 e = cross(Vec3(1,2,3), Vec3(2,3,1));
	EXPECT_DOUBLE_EQ(e.x, -7.0);
	EXPECT_DOUBLE_EQ(e.y, 5.0);
	EXPECT_DOUBLE_EQ(e.z, -1.0);



	// original vectors should stay the same
	EXPECT_DOUBLE_EQ(vec1.x, 1.0);
	EXPECT_DOUBLE_EQ(vec1.y, 2.0);
	EXPECT_DOUBLE_EQ(vec1.z, 3.0);

	EXPECT_DOUBLE_EQ(vec2.x, 10.0);
	EXPECT_DOUBLE_EQ(vec2.y, 20.0);
	EXPECT_DOUBLE_EQ(vec2.z, 30.0);
}


TEST(Vec3, rotations)
{
	Vec3 vec(1, 2, 3);

	Vec3 a = rotate_x(vec, -7.073163980890013 * UNITS::DEG);

	EXPECT_LE(fabs(vec.length() - a.length()), PRECISION);
	EXPECT_DOUBLE_EQ(a.x, 1.);
	EXPECT_LE(fabs(a.y - 2.35418947577697), PRECISION*50);
	EXPECT_LE(fabs(a.z - 2.7308958076318), PRECISION*50);


	a = rotate_y(vec, 31.12364038930145 * UNITS::DEG);
	EXPECT_LE(fabs(a.x - 2.40671363753051), PRECISION*50);
	EXPECT_DOUBLE_EQ(a.y, 2.);
	EXPECT_LE(fabs(a.z - 2.05127508319207), PRECISION*50);

	a = rotate_z(vec, 253.8775990224678 * UNITS::DEG);
	EXPECT_LE(fabs(a.x - 1.643651048881018), PRECISION*50);
	EXPECT_LE(fabs(a.y + 1.516051196204248), PRECISION*50);
	EXPECT_DOUBLE_EQ(a.z, 3.);



}


int main(int argc, char *argv[])
{
	struct Dupa
	{
		double a;
		std::string napis;
	};


	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

