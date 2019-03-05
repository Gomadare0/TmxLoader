#include "TmxLoader.h"
#include "Utilities.h"
#include "tinyxml2/tinyxml2.h"
#include "TmxLoader_detail.h"

using namespace TmxLoader;

Map TmxLoader::ParseTMX(const StringType& filepath)
{
	// Load Map
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filepath.c_str());
	if (doc.Error())
	{
		Map dummy;
		return Map();
	}
	
	// Set Map Parameters
	tinyxml2::XMLElement* root = doc.FirstChildElement("map");
	if (root == nullptr)
	{
		return Map();
	}

	Map map;
	map.version = root->Attribute("version");
	map.tiledversion = root->Attribute("tiledversion");

	auto orientation = root->Attribute("orientation");
	if (compareString(orientation, "orthogonal"))
	{
		map.orientation = Orientation::orthogonal;
	}
	else if (compareString(orientation, "isometric"))
	{
		map.orientation = Orientation::isometric;
	}
	else if (compareString(orientation, "staggered"))
	{
		map.orientation = Orientation::staggered;
	}
	else if (compareString(orientation, "hexagonal"))
	{
		map.orientation = Orientation::hexagonal;
	}

	auto renderorder = root->Attribute("renderorder");
	if (compareString(renderorder, "right-down"))
	{
		map.renderorder = RenderOrder::rightdown;
	}
	else if (compareString(renderorder, "right-up"))
	{
		map.renderorder = RenderOrder::rightup;
	}
	else if (compareString(renderorder, "left-down"))
	{
		map.renderorder = RenderOrder::leftdown;
	}
	else if (compareString(renderorder, "left-up"))
	{
		map.renderorder = RenderOrder::leftup;
	}

	map.width = root->IntAttribute("width", 0);
	map.height = root->IntAttribute("height", 0);
	map.tilewidth = root->IntAttribute("tilewidth", 0);
	map.tileheight = root->IntAttribute("tileheight", 0);
	map.hexsidelength = root->IntAttribute("hexsidelength", 0);
	map.staggeraxis = root->IntAttribute("staggeraxis", 0) == 1 ? 1 : 0;
	map.staggerindex = compareString(root->Attribute("staggerindex"), "odd") ? 1 : 0;
	map.backgroundcolor = AttDefault(root->Attribute("backgroundcolor"), "FFFFFF");
	map.nextlayerid = root->IntAttribute("nextlayerid", 0);
	map.nextobjectid = root->IntAttribute("nextobjectid", 0);

	// Child node parsing	
	auto* child = root->FirstChildElement();

	while (child != nullptr)
	{
		if (compareString(child->Name(), "properties"))
		{
			map.properties = Detail::ParseProperties(child);
		}
		else if (compareString(child->Name(), "tileset"))
		{
			map.tilesets.push_back(Detail::ParseTileset(child));
		}
		else if (compareString(child->Name(), "layer"))
		{
			map.layers.push_back(Detail::ParseLayer(child));
		}
		else if (compareString(child->Name(), "objectgroup"))
		{
			map.objectgroups.push_back(Detail::ParseObjectgroup(child));
		}
		else if (compareString(child->Name(), "imagelayer"))
		{
			map.imagelayers.push_back(Detail::ParseImagelayer(child));
		}
		else if (compareString(child->Name(), "group"))
		{
			map.groups.push_back(Detail::ParseGroup(child));
		}

		child = child->NextSiblingElement();
	}

	return map;
}

Tileset TmxLoader::ParseTSX(const StringType& filepath)
{
	// Load Tileset
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filepath.c_str());
	if (doc.Error())
	{
		Tileset dummy;
		return Tileset();
	}

	tinyxml2::XMLElement* root = doc.FirstChildElement("tileset");
	if (root == nullptr)
	{
		return Tileset();
	}

	return Detail::ParseTileset(root);
}
