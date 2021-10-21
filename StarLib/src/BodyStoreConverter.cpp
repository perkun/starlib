#include "BodyStoreConverter.h"

using namespace std;

namespace StarLib
{

BodyStoreConverter::BodyStoreConverter()
{
}


BodyStoreConverter::~BodyStoreConverter()
{
}

void BodyStoreConverter::copy_metadata(BodyStore &source, BodyStore &destination)
{

    ASSERT(source.bodies.size() == destination.bodies.size(),
           "Error while copying BodyStore metadata. numbers of bodies do not "
           "match");

    destination.group_refs = source.group_refs;

    for (int i = 0; i < source.bodies.size(); i++)
    {
		source.bodies[i].name = destination.bodies[i].name;
    }
}
}








