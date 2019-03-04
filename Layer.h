#pragma once

#include "Typedefs.h"
#include "Fwd.h"

namespace TmxLoader
{
	struct Tile_Layer
	{
		// The global tile ID (default: 0).
		IdType gid = 0;
	};

	struct Chunk
	{
		PositionType x, y;
		SizeType width, height;

		StringType storeddata;

		VectorType<Tile_Layer> tile;
	};

	struct Data
	{
		StringType encoding;
		StringType compression;

		StringType storeddata;

		VectorType<Tile_Layer> tile;
		VectorType<Chunk> chunk;
	};

	struct Layer
	{
		// Unique ID of the layer. Each layer that added to a map gets a unique id.
		// Even if a layer is deleted, no layer ever gets the same ID. Can not be changed in Tiled.
		// (since Tiled 1.2)
		IdType id;

		StringType name;

		PositionType x, y;
		SizeType width, height;
		FloatingPoint opacity;
		bool visible;
		PositionType offsetx, offsety;

		VectorType<Property> properties;

		std::unique_ptr<Data> data;
	};
}