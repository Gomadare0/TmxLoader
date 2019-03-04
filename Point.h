#pragma once

#include "Typedefs.h"
#include "Fwd.h"

namespace TmxLoader
{
	template<typename T = PositionType>
	struct Point
	{
		T x, y;
	};
}