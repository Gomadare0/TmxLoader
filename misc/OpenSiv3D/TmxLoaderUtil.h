#pragma once

#include <Siv3D.hpp>
#include <filesystem>

#include "../../TmxLoader.h"

namespace TmxLoader
{
	namespace Util
	{
		auto GetAbsolutePath(std::filesystem::path relative, std::filesystem::path base)->std::filesystem::path;

		// ParseTSX function which can be passed a relative path for argument.
		inline Tileset ParseTSX(std::filesystem::path tsxpath, std::filesystem::path tmxpath)
		{
			Tileset ret = TmxLoader::ParseTSX(GetAbsolutePath(tsxpath, tmxpath).string());
			return ret;
		}

		inline s3d::Image GetImageFromTileset(const Tileset& tileset, std::filesystem::path tsxPath = "")
		{
			return s3d::Image(GetAbsolutePath(tileset.image->source, tsxPath).u32string());
		}

		// TODO : Add support for <tile>, base64 and compression
		//
		s3d::Image GetWholeMapImage(const Map& map, const Tileset& tileset, s3d::Image& tilesetImage);
	}
}