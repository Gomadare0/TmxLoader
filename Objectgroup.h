#pragma once

#include "Typedefs.h"
#include "Enums.h"
#include "Fwd.h"
#include "Point.h"

namespace TmxLoader
{
	struct Text
	{
		StringType fontfamily;
		SizeType pixelsize;
		bool wrap;
		StringType color;
		bool bold;
		bool italic;
		bool underline;
		bool strikeout;
		bool kerning;
		HAlign halign = HAlign::left;
		VAlign valign = VAlign::top;
	};

	struct Object
	{
		IdType id;
		StringType name;
		StringType type;
		PositionType x, y;
		SizeType width, height;
		AngleType rotation;
		
		// A reference to a tile (optional).
		IdType gid;
		bool visible;
		StringType templateFile;

		StoredObjectType objectTypeTag = StoredObjectType::any;

		VectorType<Property> properties;

		// Points of polygon or polyline.
		VectorType<Point<>> pointlists;
		std::unique_ptr<Text> text;
	};

	struct Objectgroup
	{
		IdType id;
		StringType name;
		StringType color;
		PositionType x = 0, y = 0; // always 0.
		SizeType width, height; // meaningless.
		FloatingPoint opacity;
		bool visible;
		PositionType offsetx, offsety;
		DrawOrder draworder = DrawOrder::topdown;

		VectorType<Property> properties;
		VectorType<Object> objects;
	};
}