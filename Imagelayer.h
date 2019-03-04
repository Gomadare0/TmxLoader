#pragma once

#include "Typedefs.h"
#include "Fwd.h"

namespace TmxLoader
{
	struct Imagelayer
	{
		IdType id;
		StringType name;
		PositionType offsetx, offsety;
		PositionType x, y; // (deprecated since 0.15)
		FloatingPoint opacity;
		bool visible;

		VectorType<Property> properties;
		std::unique_ptr<Image> image;
	};
}