#pragma once

#include "Typedefs.h"
#include "Enums.h"
#include "Fwd.h"

#include "Property.h"
#include "Tileset.h"
#include "Layer.h"
#include "Objectgroup.h"
#include "Imagelayer.h"
#include "Group.h"

#include <vector>
#include <memory>

namespace TmxLoader
{
	struct Map
	{
		// TMX Format Version is stored like in this way.
		StringType version = "1.0";

		// Tiled Version is stored.
		StringType tiledversion = "1.0.1";

		// Orientation (since 0.11)
		Orientation orientation = Orientation::orthogonal;

		// Renderorder
		// The order in which tiles on tile layers are rendered.
		RenderOrder renderorder = RenderOrder::rightdown;

		SizeType width = 0, height = 0;
		SizeType tilewidth = 0, tileheight = 0;

		// Only for hexagonal maps.
		// Determines the width or height (depending on the staggered axis) of the tileÅfs edge, in pixels.
		SizeType hexsidelength = 0;

		// For staggered and hexagonal maps, determines which axis (ÅgxÅh or ÅgyÅh) is staggered. (since 0.11)
		// 0 is x, and 1 is y.
		int staggeraxis = 0;

		// For staggered and hexagonal maps, 
		// determines whether the ÅgevenÅh or ÅgoddÅh indexes along the staggered axis are shifted. (since 0.11)
		// 0 is even, and 1 is odd;
		int staggerindex = 0;

		// The background color of the map. (optional, may include alpha value since 0.15 in the form #AARRGGBB)
		// Stored in hex, but '#' is excluded in this library.
		StringType backgroundcolor = "FFFFFFFF";

		// Stores the next available ID for new layers. 
		// This number is stored to prevent reuse of the same ID after layers have been removed. (since 1.2)
		IdType nextlayerid = 0;

		// Stores the next available ID for new objects.
		// This number is stored to prevent reuse of the same ID after objects have been removed. (since 0.11)
		IdType nextobjectid = 0;

		VectorType<Property> properties;
		VectorType<Tileset> tilesets;
		VectorType<Layer> layers;
		VectorType<Objectgroup> objectgroups;
		VectorType<Imagelayer> imagelayers;
		VectorType<Group> groups;
	};
}