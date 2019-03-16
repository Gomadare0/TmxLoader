#pragma once

#include "Typedefs.h"
#include "Enums.h"
#include "Fwd.h"

#include "Property.h"
#include "Layer.h"
#include "Objectgroup.h"
#include "Imagelayer.h"

namespace TmxLoader
{
	struct Group
	{
		IdType id = 0;
		StringType name;
		PositionType offsetx = 0, offsety = 0;
		FloatingPoint opacity = 1.0f;
		bool visible = true;

		VectorType<Property> properties;
		VectorType<Layer> layers;
		VectorType<Objectgroup> objectgroups;
		VectorType<Imagelayer> imagelayers;
		VectorType<Group> groups; //group layer itself

		int layerOrder = 0; // The more this is small, the lower this is placed in layer hierarchy.

		// Setters which affect all child layers;
		void SetOffsetX(const int& value)
		{
			for (auto& i : layers)
			{
				i.offsetx = value;
			}
		}
		void SetOffsetY(const int& value)
		{
			for (auto& i : layers)
			{
				i.offsety = value;
			}
		}
		void SetOpacity(const FloatingPoint& value)
		{
			for (auto& i : layers)
			{
				i.opacity = value;
			}
		}
		void SetVisibility(const bool& value)
		{
			for (auto& i : layers)
			{
				i.visible = value;
			}
		}
	};
}