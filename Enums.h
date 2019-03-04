#pragma once

namespace TmxLoader
{
	enum class Orientation
	{
		orthogonal,
		isometric,
		staggered,
		hexagonal,
	};

	enum class RenderOrder
	{
		rightdown,
		rightup,
		leftdown,
		leftup,
	};

	enum class HAlign
	{
		left,
		center,
		right,
		justify,
	};

	enum class VAlign
	{
		top,
		center,
		bottom,
	};

	enum class StoredObjectType
	{
		any,
		ellipse,
		point,
		polygon,
		polyline,
		text,
	};

	enum class DrawOrder
	{
		topdown,
		index
	};
}