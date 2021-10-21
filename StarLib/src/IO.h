#ifndef IO_H_
#define IO_H_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <deque>
#include "Orbit.h"
#include "Units.h"
#include "StateVector.h"

namespace StarLib
{
namespace IO
{

std::deque<Orbit> parse_horizons_elements(std::string filename);
std::deque<StateVector> parse_horizons_vectors(std::string filename);


}
} // namespace StarLIb

#endif /* IO_H_ */
