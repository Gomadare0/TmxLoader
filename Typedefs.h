#pragma once

#include <string>
#include <vector>

namespace TmxLoader
{
	using FloatingPoint = float;

	using IdType = int;
	using PositionType = int;
	using PrecisePosType = FloatingPoint;
	using SizeType = int;
	using PreciseSizeType = FloatingPoint;
	using AngleType = FloatingPoint;

	// Notice : StringType needs to be defined operator==
	using StringType = std::string;

	template<class T>
	using VectorType = std::vector<T, std::allocator<T>>;
}