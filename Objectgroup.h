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
		SizeType pixelsize = 16;
		bool wrap = false;
		StringType color = "000000";
		bool bold = false;
		bool italic = false;
		bool underline = false;
		bool strikeout = false;
		bool kerning = true;
		HAlign halign = HAlign::left;
		VAlign valign = VAlign::top;
	};

	struct Object
	{
		IdType id = 0;
		StringType name;
		StringType type;
		PositionType x = 0, y = 0;
		SizeType width = 0, height = 0;
		AngleType rotation = 0.0f;
		
		// A reference to a tile (optional).
		IdType gid = 0;
		bool visible = true;
		StringType templateFile;

		StoredObjectType objectTypeTag = StoredObjectType::any;

		VectorType<Property> properties;

		// Points of polygon or polyline.
		VectorType<Point<>> pointlists;
		std::unique_ptr<Text> text;
	};

	struct Objectgroup
	{
		IdType id = 0;
		StringType name;
		StringType color = "FFFFFF";
		PositionType x = 0, y = 0; // always 0.
		SizeType width = 0, height = 0; // meaningless.
		FloatingPoint opacity = 1.0f;
		bool visible = true;
		PositionType offsetx = 0, offsety = 0;
		DrawOrder draworder = DrawOrder::topdown;

		VectorType<Property> properties;
		VectorType<Object> objects;
	};
}