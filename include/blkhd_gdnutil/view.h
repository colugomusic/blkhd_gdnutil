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

	float song_to_screen(int position) const
	{
		return (view_.elements[0][0] * position + view_.elements[1][0]) + view_.elements[2].x;
	}

	float song_to_screen(float position) const
	{
		return (view_.elements[0][0] * position + view_.elements[1][0]) + view_.elements[2].x;
	}

	double song_to_screen(double position) const
	{
		return (double(view_.elements[0][0]) * position + double(view_.elements[1][0])) + double(view_.elements[2].x);
	}

	float screen_to_song(int position) const
	{
		const auto inverse = view_.affine_inverse();

		return (inverse.elements[0][0] * position + inverse.elements[1][0]) + inverse.elements[2][0];
	}

	float screen_to_song(float position) const
	{
		const auto inverse = view_.affine_inverse();

		return (inverse.elements[0][0] * position + inverse.elements[1][0]) + inverse.elements[2][0];
	}

	double screen_to_song(double position) const
	{
		const auto inverse = view_.affine_inverse();

		return (double(inverse.elements[0][0]) * position + double(inverse.elements[1][0])) + double(inverse.elements[2][0]);
	}

	float basis_song_to_screen(int position) const
	{
		return view_.elements[0][0] * position + view_.elements[1][0];
	}

	float basis_song_to_screen(float position) const
	{
		return view_.elements[0][0] * position + view_.elements[1][0];
	}

	double basis_song_to_screen(double position) const
	{
		return double(view_.elements[0][0]) * position + double(view_.elements[1][0]);
	}

	float basis_screen_to_song(int position) const
	{
		const auto inverse = view_.affine_inverse();

		return inverse.elements[0][0] * position + inverse.elements[1][0];
	}

	float basis_screen_to_song(float position) const
	{
		const auto inverse = view_.affine_inverse();

		return inverse.elements[0][0] * position + inverse.elements[1][0];
	}

	double basis_screen_to_song(double position) const
	{
		const auto inverse = view_.affine_inverse();

		return double(inverse.elements[0][0]) * position + double(inverse.elements[1][0]);
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
