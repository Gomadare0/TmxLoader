#include "Property.h"
#include <sstream>

using namespace TmxLoader;

StringType TmxLoader::Property::GetStringValue()
{
	return value;
}

int TmxLoader::Property::GetIntValue()
{
	int value_;
	auto stream = std::istringstream(value);
	return stream >> value_ ? value_ : 0;
}

FloatingPoint TmxLoader::Property::GetFloatValue()
{
	FloatingPoint value_;
	auto stream = std::istringstream(value);
	return stream >> value_ ? value_ : 0;
}

bool TmxLoader::Property::GetBoolValue()
{
	if (value == "true")
	{
		return true;
	}
	else
	{
		return false;
	}
}

StringType TmxLoader::Property::GetColorValue()
{
	return value;
}

StringType TmxLoader::Property::GetFileValue()
{
	return value;
}
