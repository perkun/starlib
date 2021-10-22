#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include "StateVector.h"

namespace StarLib
{

class StateComponent
{
public:
    StateComponent(StateVector &sv) : state(sv) {}
    ~StateComponent() {}

    StateVector state;
};


class MassComponent
{
public:
    MassComponent(double mass) : mass(mass) {}
    ~MassComponent() {}

    double mass;
};


class NameComponent
{
public:
    NameComponent(std::string name) : name(name) {}
    ~NameComponent() {}

    std::string name;
};


} // namespace StarLib

#endif /* COMPONENTS_H_ */
