#ifndef BODYSTORECONVERTER_H_
#define BODYSTORECONVERTER_H_

#include <iostream>
#include <stdio.h>
#include <utility>
#include "Bodies.h"
#include "Assert.h"


namespace StarLib
{

class BodyStoreConverter
{
public:
    BodyStoreConverter();
    ~BodyStoreConverter();


	template<typename T, typename Func>
	static std::vector<T> get_collection_of(Func getter, BodyStore &store)
	{
		std::vector<T> returnee;
		returnee.reserve(store.bodies.size());

		for (Body &body: store.bodies)
			returnee.push_back(getter(body));
		return returnee;
	}

	// getters
	static double get_mass(Body &body) { return body.mass; }
	static Vec3 get_position(Body &body) { return body.state.position; }
	static Vec3 get_velocitiy(Body &body) { return body.state.velocity; }
	static std::string get_name(Body &body) { return body.name; }


	static void copy_metadata(BodyStore &source, BodyStore &destination);
};



}

#endif /* BODYSTORECONVERTER_H_ */
