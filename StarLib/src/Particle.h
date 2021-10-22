#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <iostream>
#include <stdio.h>
#include "entt.hpp"


/** Particle is ment to be a entity in Entity Component System. Registry belongs
 * to Simulation. The Particle class is a wrapper for entt::entity
 */

namespace StarLib
{

class Particle
{
public:
    Particle() : entity_handle(entt::null), registry_handle(NULL)
    {
    }
    Particle(entt::entity handle, entt::registry *registry_handle)
        : entity_handle(handle), registry_handle(registry_handle)
    {
    }

    ~Particle();

	void destroy()
	{
		registry_handle->destroy(entity_handle);
	}

	Particle& get_parent();

    template <typename T>
	bool has_component()
    {
        return registry_handle->has<T>(entity_handle);
    }

    template <typename T, typename... Args>
	T &add_component(Args &&... args)
    {
        return registry_handle->emplace<T>(entity_handle,
                                                 std::forward<Args>(args)...);
    }

    template <typename T>
	T &get_component()
    {
        if (!has_component<T>())
		{
			// TODO add ERROR handler
            printf("Particle does not have this component");
		}
        return registry_handle->get<T>(entity_handle);
    }

    template <typename T>
	void remove_component()
    {
        if (!has_component<T>())
			return;
        registry_handle->remove<T>(entity_handle);
    }

    template <typename T>
	T& replace_component(T new_component)
    {
        registry_handle->replace<T>(entity_handle, new_component);
        return registry_handle->get<T>(entity_handle);
    }

    operator bool() const
    {
        return entity_handle != entt::null;
    }

    bool operator==(const Particle &other) const
    {
        return entity_handle == other.entity_handle &&
               registry_handle == other.registry_handle;
    }

    bool operator!=(const Particle &other) const
    {
        return !(*this == other);
    }


	entt::entity get_handle()
	{
		return entity_handle;
	}

	uint32_t get_uuid()
	{
		return (uint32_t)entity_handle;
	}
private:
    entt::entity entity_handle = entt::null;
    entt::registry *registry_handle;
};

}

#endif /* PARTICLE_H_ */
