#ifndef POTENTIAL_H_
#define POTENTIAL_H_

#include "starlibmath.h"

namespace StarLib
{

class Potential
{
public:
	Potential() {}
	virtual ~Potential() {}

	virtual Vec3 get_acceleration(const Vec3 &pos) = 0;
private:

};

}
#endif
