#pragma once

#include <functional>
#include <memory>

#pragma warning(push, 0)
#include <Godot.hpp>
#include <Object.hpp>
#pragma warning(pop)

template <class GDN, class T>
class ClassWrapper : public godot::Object
{
	GODOT_CLASS(ClassWrapper, godot::Object);

public:

	T* object_ptr() { return object_.get(); }
	const T* object_ptr() const { return object_.get(); }
	T& object() { return *(object_.get()); }
	const T& object() const { return *(object_.get()); }

	T* operator->() { return object_.get(); }
	const T* operator->() const { return object_.get(); }
	T& operator*() { return *(object_.get()); }
	const T& operator*() const { return *(object_.get()); }

	static std::shared_ptr<GDN> make_shared()
	{
		const auto out = std::shared_ptr<GDN>(GDN::_new(), [](GDN* o) { o->free(); });

		out->construct();

		return out;
	}

	template <class ... Args>
	static std::shared_ptr<GDN> make_shared(Args... args)
	{
		const auto out = std::shared_ptr<GDN>(GDN::_new(), [](GDN* o) { o->free(); });

		out->construct(args...);

		return out;
	}

private:

	template <class ... Args>
	void construct(Args ... args)
	{
		object_ = std::make_unique<T>(args...);
	}

	std::unique_ptr<T> object_;
};
