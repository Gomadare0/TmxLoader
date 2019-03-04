#include "TmxLoader.h"
#include "Utilities.h"
#include "tinyxml2/tinyxml2.h"
#include "TmxLoader_detail.h"

using namespace TmxLoader;

Map TmxLoader::ParseTMX(const StringType& filepath)
{
	// Initial Message
	Log << "[ TmxLoader :) ] Parser::TMX has called.";

	// Load Map
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filepath.c_str());
	if (doc.Error())
	{
		Log << "[ TmxLoader :( ] Error occured when parsing file. «";
		Log << doc.ErrorStr();

		Map dummy;
		return Map();
	}
	
	// Set Map Parameters
	tinyxml2::XMLElement* root = doc.RootElement();
	if (::strcmp(root->Name(), "map") != 0)
	{
		Log << "[ TmxLoader :( ] Root Element is not ""Map"". ";
		return Map();
	}

	Map map;
	map.version = root->Attribute("version", "1.0");
	map.tiledversion = root->Attribute("tiledversion", "1.0");

	auto orientation = root->Attribute("orientation","orthogonal");
	if (::strcmp(orientation, "orthogonal") == 0)
	{
		map.orientation = Orientation::orthogonal;
	}
	else if (::strcmp(orientation, "isometric") == 0)
	{
		map.orientation = Orientation::isometric;
	}
	else if (::strcmp(orientation, "staggered") == 0)
	{
		map.orientation = Orientation::staggered;
	}
	else if (::strcmp(orientation, "hexagonal") == 0)
	{
		map.orientation = Orientation::hexagonal;
	}

	auto renderorder = root->Attribute("renderorder", "right-down");
	if (::strcmp(renderorder, "right-down") == 0)
	{
		map.renderorder = RenderOrder::rightdown;
	}
	else if (::strcmp(renderorder, "right-up") == 0)
	{
		map.renderorder = RenderOrder::rightup;
	}
	else if (::strcmp(renderorder, "left-down") == 0)
	{
		map.renderorder = RenderOrder::leftdown;
	}
	else if (::strcmp(renderorder, "left-up") == 0)
	{
		map.renderorder = RenderOrder::leftup;
	}

	map.width = root->IntAttribute("width", 0);
	map.height = root->IntAttribute("height", 0);
	map.tilewidth = root->IntAttribute("tilewidth", 0);
	map.tileheight = root->IntAttribute("tileheight", 0);
	map.hexsidelength = root->IntAttribute("hexsidelength", 0);
	map.staggeraxis = root->IntAttribute("staggeraxis", 0) == 1 ? 1 : 0;
	map.staggerindex = ::strcmp(root->Attribute("staggerindex", "even"), "odd") == 0 ? 1 : 0;
	map.backgroundcolor = root->Attribute("backgroundcolor", "#00000000");
	map.nextlayerid = root->IntAttribute("nextlayerid", 0);
	map.nextobjectid = root->IntAttribute("nextobjectid", 0);

	// Child node parsing
	Log << "[ TmxLoader :) ] Start Child Node Parsing (while-loop is running).";
	
	auto* child = root->FirstChildElement();

	while (child != nullptr)
	{
		if (::strcmp(child->Name(), "properties") == 0)
		{
			map.properties = Detail::ParseProperties(child);
		}
		else if (::strcmp(child->Name(), "tileset") == 0)
		{
			map.tilesets.push_back(Detail::ParseTileset(child));
		}
		else if (::strcmp(child->Name(), "layer") == 0)
		{
			map.layers.push_back(Detail::ParseLayer(child));
		}
		else if (::strcmp(child->Name(), "objectgroup") == 0)
		{
			map.objectgroups.push_back(Detail::ParseObjectgroup(child));
		}
		else if (::strcmp(child->Name(), "imagalayer") == 0)
		{
			map.imagelayers.push_back(Detail::ParseImagelayer(child));
		}
		else if (::strcmp(child->Name(), "group") == 0)
		{
			map.groups.push_back(Detail::ParseGroup(child));
		}

		child = child->NextSiblingElement();
	}

	Log << "[ TmxLoader :) ] Child Node Parsing Finished.";

	return map;
}