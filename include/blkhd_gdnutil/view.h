#pragma once

#include <cstdint>

#pragma warning(push, 0)
#include <Transform2D.hpp>
#include <Vector2.hpp>
#pragma warning(pop)

namespace blkhd_gdnutil {
namespace view {

class View
{

public:

	std::uint32_t get_age() const { return age_; }
	const godot::Transform2D& get_view() const { return view_; }

	const godot::Transform2D& operator*() const { return get_view(); }
	const godot::Transform2D* operator->() const { return &view_; }

	void set_view(const godot::Transform2D& view)
	{
		view_ = view;
		age_++;
	}

	template <class T>
	T song_to_screen(T position) const
	{
		return T(view_.xform(godot::Vector2(1, 1) * real_t(position)).x);
	}

	template <class T>
	T screen_to_song(T position) const
	{
		return T(view_.affine_inverse().xform(godot::Vector2(1, 1) * real_t(position)).x);
	}

	template <class T>
	T basis_song_to_screen(T position) const
	{
		return T(view_.basis_xform(godot::Vector2(1, 1) * real_t(position)).x);
	}

	template <class T>
	T basis_screen_to_song(T position) const
	{
		return T(view_.affine_inverse().basis_xform(godot::Vector2(1, 1) * real_t(position)).x);
	}

	godot::Vector2 song_to_screen(godot::Vector2 p) const
	{
		return view_.xform(p);
	}

	godot::Vector2 screen_to_song(godot::Vector2 p) const
	{
		return view_.affine_inverse().xform(p);
	}

	godot::Vector2 basis_song_to_screen(godot::Vector2 p) const
	{
		return view_.basis_xform(p);
	}

	godot::Vector2 basis_screen_to_song(godot::Vector2 p) const
	{
		return view_.affine_inverse().basis_xform(p);
	}

private:

	godot::Transform2D view_;
	std::uint32_t age_ = 1;
};

} // namespace view
} // namespace blkhd_gdnutil
