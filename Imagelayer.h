#pragma once

#include "Typedefs.h"
#include "Fwd.h"

namespace TmxLoader
{
	struct Imagelayer
	{
		IdType id = 0;
		StringType name;
		PositionType offsetx = 0, offsety = 0;
		PositionType x = 0, y = 0; // (deprecated since 0.15)
		FloatingPoint opacity = 1.0f;
		bool visible = true;

		int layerOrder = 0; // The more this is small, the lower this is placed in layer hierarchy.

		VectorType<Property> properties;
		std::unique_ptr<Image> image;
	};
}