#pragma once

#include <memory>

namespace blkhd_gdnutil {
namespace memory {

// Less horrible alternative to using godot::Reference and godot::Ref<T>
// T should be derived from godot::Object
// 
template <class T>
std::shared_ptr<T> make_new()
{
	return std::shared_ptr<T>(T::_new(), [](T* o) { o->free(); });
}

template <class T, class ... Args>
std::shared_ptr<T> make_new(Args... args)
{
	const auto out = std::shared_ptr<T>(T::_new(), [](T* o) { o->free(); });

	out->construct(args...);

	return out;
}

}}