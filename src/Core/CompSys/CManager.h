/*
*iComponent manager class
*Handles the management of getComponents of an attached to gameObject
*in iComponent-System based architecture
*/


#pragma once

#include <list>
#include <memory>

namespace ooe
{
	template <class _comp_T>
	class ComponentManager
	{
	public:
		template <class _derive_T>
		std::shared_ptr<_derive_T> addComponent();

		template <class _derive_T>
		void disableComponent() const;

		template <class _derive_T>
		void enableComponent() const;

		template <class _derive_T>
		std::shared_ptr<_derive_T> getComponent() const;

		std::list<std::shared_ptr<_comp_T>>& getComponents() const;

		template <class _derive_T>
		bool hasComponent() const;

		template <class _derive_T>
		void removeComponent();
	private:
		std::list<std::shared_ptr<_comp_T>> component_list_;
	};



	/**********************************************
	*ComponentManager templated functions
	**********************************************/


	//allocate memory for a new base componentManager().getComponent type and add it to the manager
	//manager can only hold one of a iComponent type
	template <class _comp_T> template <class _derive_T>
	std::shared_ptr<_derive_T> ComponentManager<_comp_T>::
		addComponent()
	{
		if (hasComponent<_derive_T>()) return nullptr;

		std::shared_ptr<_derive_T> c(new _derive_T);
		component_list_.push_back(c);
		return c;
	}


	template <class _comp_T> template < class _derive_T >
	void ComponentManager<_comp_T>::
		disableComponent() const
	{
		getComponent<_derive_T>()->is_enabled_ = false;
	}


	template <class _comp_T> template < class _derive_T >
	void ComponentManager<_comp_T>::
		enableComponent() const
	{
		getComponent<_derive_T>()->is_enabled_ = true;
	}


	//grab a base or derived componentManager().getComponent type from the componentManager().getComponent manager
	template <class _comp_T> template <class _derive_T>
	std::shared_ptr<_derive_T> ComponentManager<_comp_T>::
		getComponent() const
	{
		for (auto component : component_list_)
		{
			if (typeid(*component) == typeid(_derive_T)) {
				return std::dynamic_pointer_cast<_derive_T>(component);
			}
		}
		return nullptr;
	}


	//get the entire componentManager().getComponent list
	template <class _comp_T>
	std::list<std::shared_ptr<_comp_T>>& ComponentManager<_comp_T>::
		getComponents() const
	{
		return component_list_;
	}


	template <class _comp_T> template <class _derive_T>
	bool ComponentManager<_comp_T>::
		hasComponent() const
	{
		if (getComponent<_derive_T>() != nullptr) return true;
		return false;
	}


	template <class _comp_T> template <class _derive_T>
	void ComponentManager<_comp_T>::
		removeComponent()
	{
		if (hasComponent<_derive_T>())
		{
			component_list_.remove(getComponent<_derive_T>());
		}
	}
}