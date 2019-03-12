#pragma once

#include "Utilities.h"
#include "MapData.h"

namespace TmxLoader
{
	Map ParseTMX(const StringType& filepath);

	Tileset ParseTSX(const StringType& filepath);

	Object ExpandTemplate(Object object);
}