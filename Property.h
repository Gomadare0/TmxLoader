#pragma once

#include "Typedefs.h"
#include "Fwd.h"

namespace TmxLoader
{
	enum class PropertyType
	{
		string_,
		int_,
		float_,
		bool_,
		color_,
		file_,
	};
	struct Property
	{
		StringType name;
		PropertyType type = PropertyType::string_;

		StringType value;

		StringType GetStringValue();
		int GetIntValue();
		FloatingPoint GetFloatValue();
		bool GetBoolValue();
		StringType GetColorValue();
		StringType GetFileValue();
	};
}