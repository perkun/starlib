#ifndef BODIES_H_
#define BODIES_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "StateVector.h"

namespace StarLib
{

struct Body
{
	std::string name;
	double mass;
	StarLib::StateVector state;
};


struct GroupRef
{
	std::string name;
	int first_id;
	int length;
};


class BodyStore
{
public:
	friend class BodyStoreConverter;

    BodyStore();
    ~BodyStore();

	GroupRef add_group(std::string group_name, std::vector<Body> &group_members);
	std::vector<Body> get_group(const GroupRef &ref);
	std::string get_group_name(const GroupRef &ref);

	int size() { return bodies.size(); }


	void clear()
	{
		bodies.clear();
		group_refs.clear();
	}

private:
	std::vector<Body> bodies;
	std::vector<GroupRef> group_refs;
};

} // namespace StarLib
#endif /* BODIES_H_ */
