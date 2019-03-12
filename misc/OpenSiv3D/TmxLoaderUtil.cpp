#include "TmxLoaderUtil.h"

auto TmxLoader::Util::GetAbsolutePath(std::filesystem::path relative, std::filesystem::path base) -> std::filesystem::path
{
	std::filesystem::path previousPath = std::filesystem::current_path();

	std::filesystem::current_path(base.remove_filename());

	auto ret = std::filesystem::absolute(relative);

	std::filesystem::current_path(previousPath);
	return ret;
}

// TODO : Add support of multiple tilesets.
//
s3d::Image TmxLoader::Util::GetWholeMapImage(const Map& map, const Tileset& tileset, s3d::Image& tilesetImage)
{
	s3d::Image mapimage;

	const int& tileSize = map.tilewidth;
	const int& tilerow = tileset.columns;
	const int& margin = tileset.margin;
	const int& spacing = tileset.spacing;
	const auto& offset = tileset.tileoffset;

	mapimage.resize(map.width * tileSize, map.height * tileSize);
	mapimage.fill(Palette::White);

	int minimumFirstGid = map.tilesets.begin()->firstgid;

	for (auto& layer : map.layers)
	{
		layer.data->ConvertStoredDataIntoTiles();

		// Draw Layer
		for (auto h : Range(0, map.height - 1))
		{
			for (auto w : Range(0, map.width - 1))
			{
				int currentIndex = h * map.height + w;
				int currentTile = 0;

				if ((layer.data->tile.size() - 1) >= currentIndex)
				{
					currentTile = layer.data->tile[currentIndex].gid - minimumFirstGid;
				}
				else
				{
					currentTile = -1;
				}

				if (currentTile >= 0 && layer.visible)
				{
					int tileX = currentTile % tilerow;
					int tileY = static_cast<int>(std::trunc(static_cast<float>(currentTile) / static_cast<float>(tilerow)));

					auto clipped = tilesetImage.clipped(
						RectF(
							  tileX * tileSize + offset.x + margin + spacing * tileX
							, tileY * tileSize + offset.y + margin + spacing * tileY
							, tileSize
							, tileSize
						)
					);
					clipped.paint(mapimage, w * tileSize, h * tileSize);
				}
			}

		}
	}

	return mapimage;
}
