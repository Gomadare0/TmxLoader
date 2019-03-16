#include "TmxLoaderUtil.h"

auto TmxLoader::Util::GetAbsolutePath(std::filesystem::path relative, std::filesystem::path base) -> std::filesystem::path
{
	std::filesystem::path previousPath = std::filesystem::current_path();

	std::filesystem::current_path(base.remove_filename());

	auto ret = std::filesystem::absolute(relative);

	std::filesystem::current_path(previousPath);
	return ret;
}

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

	using LayerReference = std::reference_wrapper<const TmxLoader::Layer>;
	std::vector<LayerReference> layerRef;

	//
	// Lambda - group full search
	//
	std::function<void(const TmxLoader::Group&)> Func_GroupSearch = [&](const TmxLoader::Group& group)
	{
		for (const auto& layer : group.layers)
		{
			layerRef.push_back(layer);
		}

		for (const auto& childGroup : group.groups)
		{
			Func_GroupSearch(childGroup);
		}
	};

	// Add layers to layerRef.
	for (const auto& layer : map.layers)
	{
		layerRef.push_back(layer);
	}
	for (const auto& group : map.groups)
	{
		Func_GroupSearch(group);
	}

	// Sort by ID
	std::sort(layerRef.begin(), layerRef.end(), [](LayerReference left, LayerReference right)
	{
		return left.get().layerOrder < right.get().layerOrder;
	});

	//
	// Lambda - paint layers
	//
	auto Func_PaintLayer = [&](const TmxLoader::Layer& layer)
	{
		if (layer.data->storeddata.size() != 0)
		{
			layer.data->ConvertStoredDataIntoTiles();
		}

		// Draw Layer
		for (auto h : Range(0, map.height - 1))
		{
			for (auto w : Range(0, map.width - 1))
			{
				int currentIndex = h * map.height + w;
				int currentTile = 0;

				if ((layer.data->tile.size() - 1) >= currentIndex)
				{
					if (map.infinite == false)
					{
						const auto& tileElement = layer.data->tile[currentIndex];
						currentTile = tileElement.gid - minimumFirstGid;
					}
					else
					{
						currentTile = -1;
					}
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
	};

	// Paint!!
	for (auto& i : layerRef)
	{
		Func_PaintLayer(i.get());
	}


	return mapimage;
}
