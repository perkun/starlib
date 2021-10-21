#include "Bodies.h"


namespace StarLib
{

BodyStore::BodyStore()
{
}


BodyStore::~BodyStore()
{
}

GroupRef BodyStore::add_group(std::string group_name,
                              std::vector<Body> &group_members)
{

	GroupRef gr{group_name, (int)bodies.size(), (int)group_members.size()};
	bodies.insert(bodies.end(), group_members.begin(), group_members.end());
	group_refs.push_back(gr);
	return gr;
}

std::vector<Body> BodyStore::get_group(const GroupRef &ref)
{
    std::vector<Body>::const_iterator first = bodies.begin() + ref.first_id;
    std::vector<Body>::const_iterator last =
        bodies.begin() + ref.first_id + ref.length;
    return std::vector<Body>(first, last);
}

std::vector<Body> BodyStore::get_group(int nr)
{
	const GroupRef &ref = group_refs[nr];
	return get_group(ref);
}

std::string BodyStore::get_group_name(int nr)
{
	return group_refs[nr].name;
}

} // namespace StarLib




