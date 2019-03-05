#pragma once

#include "Typedefs.h"
#include "Enums.h"
#include "Point.h"
#include "Fwd.h"

namespace TmxLoader
{
	struct Grid
	{
		// Orientation of the grid for the tiles in this tileset (orthogonal or isometric)
		Orientation orientation = Orientation::orthogonal;

		SizeType width = 0, height = 0;
	};

	struct Image
	{
		StringType format;

		// Deprecated. Used in old Tiled.
		IdType id = 0;

		StringType source;

		// Color used as transparent mask.
		StringType trans;

		int width = 0, height = 0; // Optional

		std::unique_ptr<Data> data;
	};

	struct Terrain
	{
		StringType name;

		// The local tile-id of the tile that represents the terrain visually.
		IdType tile = 0;

		VectorType<Property> properties;
	};

	struct Frame
	{
		// The local ID of a tile within the parent <tileset>.
		IdType tileid = 0;

		// How long (in milliseconds) this frame should be displayed before advancing to the next frame.
		int duration = 0;
	};


	struct Wangset
	{
		StringType name;

		// The tile ID of the tile representing this Wang set.
		IdType tile = 0;

		VectorType<Wangcornercolor> wangcornercolor;
		VectorType<Wangedgecolor> wangedgecolor;
		VectorType<Wangtile> wangtile;
	};

	struct WangColorBase
	{
		// The name of this color.
		StringType name;

		// The color in #RRGGBB format (example: #c17d11).
		StringType color;

		// The tile ID of the tile representing this color.
		IdType tile = 0;

		// The relative probability that this color is chosen over others in case of multiple options.
		FloatingPoint probability = 1.0f;
	};

	struct Wangcornercolor : public WangColorBase {};
	struct Wangedgecolor : public WangColorBase {};

	struct Wangtile
	{
		IdType tileid = 0;

		// The Wang ID, which is a 32-bit unsigned integer stored in the format 0xCECECECE
		// (where each C is a corner color and each E is an edge color,
		// from right to left clockwise, starting with the top edge)
		unsigned int wangid = 0x00000000;
	};

	struct Tile
	{
		// The local tile ID within its tileset.
		IdType id = 0;

		// The type of the tile. Refers to an object type and is used by tile objects. (optional) (since 1.0)
		StringType type;

		// Defines the terrain type of each corner of the tile,
		// given as comma-separated indexes in the terrain types array
		// in the order top-left, top-right, bottom-left, bottom-right.
		// Leaving out a value means that corner has no terrain. (optional)
		VectorType<IdType> terrain;

		// A percentage indicating the probability
		// that this tile is chosen when it competes with others while editing with the terrain tool. (optional)
		FloatingPoint probability = 1.0f;

		std::unique_ptr<Image> image;
		std::unique_ptr<Objectgroup> objectgroup;

		VectorType<Property> properties;
		VectorType<Frame> animation;
		VectorType<Wangset> wangsets;
	};

	struct Tileset
	{
		// The first global tile ID of this tileset (this global ID maps to the first tile in this tileset).
		IdType firstgid = 0;

		// If this tileset is stored in an external TSX (Tile Set XML) file,
		// this attribute refers to that file.
		StringType source;

		// The name of this tileset.
		StringType name;

		// The (maximum) width of the tiles in this tileset.
		SizeType tilewidth = 0;

		// The (maximum) height of the tiles in this tileset.
		SizeType tileheight = 0;

		// The spacing in pixels between the tiles in this tileset (applies to the tileset image).
		SizeType spacing = 0;

		// The margin around the tiles in this tileset (applies to the tileset image).
		SizeType margin = 0;

		// The number of tiles in this tileset. (since 0.13)
		int tilecount = 0;

		// The number of tile columns in the tileset.
		// For image collection tilesets it is editable and is used when displaying the tileset.(since 0.15)
		int columns = 0;

		Point<> tileoffset = {0, 0};
		std::unique_ptr <Grid> grid;
		std::unique_ptr <Image> image;

		VectorType<Property> properties;
		VectorType<Terrain> terraintypes;
		VectorType<Wangset> wangsets;
		VectorType<Tile> tiles;
	};
}