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
		PositionType x = 0, y = 0;
		SizeType width = 0, height = 0;

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

		//----------------------------

		void ConvertStoredDataIntoTiles();
	};

	struct Layer
	{
		// Unique ID of the layer. Each layer that added to a map gets a unique id.
		// Even if a layer is deleted, no layer ever gets the same ID. Can not be changed in Tiled.
		// (since Tiled 1.2)
		IdType id = 0;

		StringType name;

		PositionType x = 0, y = 0;
		SizeType width = 0, height = 0;
		FloatingPoint opacity = 1.0f;
		bool visible = true;
		PositionType offsetx = 0, offsety = 0;

		int layerOrder = 0; // The more this is small, the lower this is placed in layer hierarchy.

		VectorType<Property> properties;

		std::unique_ptr<Data> data;
	};
}