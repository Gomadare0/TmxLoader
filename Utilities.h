#pragma once

#include <iostream>
#include <cstring>

namespace TmxLoader
{
	inline bool compareString(const char* left, const char* right)
	{
		if (left != 0 && right != 0)
		{
			return ::strcmp(left, right) == 0;
		}
		else
		{
			return false;
		}
	}

	inline const char* AttDefault(const char* value, const char* defaultvalue = "")
	{
		if (value == NULL)
		{
			return defaultvalue;
		}
		else
		{
			return value;
		}
	}
}