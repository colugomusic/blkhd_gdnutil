#pragma once

#include <functional>
#include <memory>

#pragma warning(push, 0)
#include <Godot.hpp>
#include <Object.hpp>
#pragma warning(pop)

template <class T>
class ClassWrapper : public godot::Object
{
	GODOT_CLASS(ClassWrapper, godot::Object);

public:

	template <class ... Args>
	void construct(Args ... args)
	{
		object_ = std::make_unique<T>(args...);
	}

	T* object_ptr() { return object_.get(); }
	const T* object_ptr() const { return object_.get(); }
	T& object() { return *(object_.get()); }
	const T& object() const { return *(object_.get()); }

	T* operator->() { return object_.get(); }
	const T* operator->() const { return object_.get(); }
	T& operator*() { return *(object_.get()); }
	const T& operator*() const { return *(object_.get()); }

private:

	std::unique_ptr<T> object_;
};