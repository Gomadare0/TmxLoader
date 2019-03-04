#include "TmxLoader_detail.h"

#include "Group.h"
#include "Imagelayer.h"
#include "Layer.h"
#include "Objectgroup.h"
#include "Property.h"
#include "Tileset.h"

using namespace TmxLoader;
using namespace TmxLoader::Detail;

Property TmxLoader::Detail::ParseProperty(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Property();
	}
	Property result;
	result.name = node->Attribute("name", "");
	result.value = node->Attribute("value", "");

	auto type = node->Attribute("type", "string");

	if (::strcmp(type, "string") == 0)
	{
		result.type = PropertyType::string_;
	}
	else if (::strcmp(type, "int") == 0)
	{
		result.type = PropertyType::int_;
	}
	else if (::strcmp(type, "float") == 0)
	{
		result.type = PropertyType::float_;
	}
	else if (::strcmp(type, "bool") == 0)
	{
		result.type = PropertyType::bool_;
	}
	else if (::strcmp(type, "color") == 0)
	{
		result.type = PropertyType::color_;
	}
	else if (::strcmp(type, "file") == 0)
	{
		result.type = PropertyType::file_;
	}

	return result;
}

VectorType<Property> TmxLoader::Detail::ParseProperties(tinyxml2::XMLElement* node)
{
	VectorType<Property> result;
	while (node != nullptr)
	{
		auto* propertyNode = node->FirstChildElement();
		while (propertyNode != nullptr)
		{
			result.push_back(ParseProperty(propertyNode));
			propertyNode = propertyNode->NextSiblingElement();
		}
	}
	return result;
}

Tileset TmxLoader::Detail::ParseTileset(tinyxml2::XMLElement* node)
{
	if (node = nullptr)
	{
		return Tileset();
	}
	Tileset result;
	result.firstgid = node->IntAttribute("firstgid", 0);
	result.source = node->Attribute("source", "");
	result.name = node->Attribute("name", "");
	result.tilewidth = node->IntAttribute("tilewidth", 0);
	result.tileheight = node->IntAttribute("tileheight", 0);
	result.spacing = node->IntAttribute("spacing", 0);
	result.margin = node->IntAttribute("margin", 0);
	result.tilecount = node->IntAttribute("tilecount", 0);
	result.columns = node->IntAttribute("columns", 0);

	// Some initialization
	{
		Point<> offset;
		offset.x = 0; offset.y = 0;
		result.tileoffset = std::move(offset);
	}

	// Parse Childnodes
	auto* child = node->FirstChildElement();
	while (child != nullptr)
	{
		if (::strcmp(child->Name(), "tileoffset"))
		{
			Point<> offset;
			offset.x = child->IntAttribute("x", 0);
			offset.y = child->IntAttribute("y", 0);
			result.tileoffset = std::move(offset);
		}
		else if (::strcmp(child->Name(), "grid"))
		{
			Grid grid;
			grid.width = child->IntAttribute("width", 0);
			grid.height = child->IntAttribute("height", 0);

			auto orientation = node->Attribute("orientation", "orthogonal");

			if (::strcmp(orientation, "orthogonal") == 0)
			{
				grid.orientation = Orientation::orthogonal;
			}
			else if (::strcmp(orientation, "isometric") == 0)
			{
				grid.orientation = Orientation::isometric;
			}
			
			result.grid = std::make_unique<Grid>(grid);
		}
		else if (::strcmp(child->Name(), "image"))
		{
			result.image = std::make_unique<Image>(ParseImage(child));
		}
		else if (::strcmp(child->Name(), "terraintypes"))
		{
			// Parse Childnodes
			auto* grandson = child->FirstChildElement();
			while (grandson != nullptr)
			{	
				result.terraintypes.push_back(ParseTerrain(grandson));
				grandson = grandson->NextSiblingElement();
			}
		}
		else if (::strcmp(child->Name(), "tile"))
		{
			result.tiles.push_back(ParseTile(child));
		}
		else if (::strcmp(child->Name(), "wangsets"))
		{
			result.wangsets.push_back(ParseWangset(child));
		}
		child = child->NextSiblingElement();
	}

	return result;
}

Image TmxLoader::Detail::ParseImage(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Image();
	}
	Image result;
	result.format = node->Attribute("format", "");
	result.id = node->IntAttribute("id", 0);
	result.source = node->Attribute("source", "");
	result.trans = node->Attribute("trans", "");
	result.width = node->IntAttribute("width", 0);
	result.height = node->IntAttribute("height", 0);

	// Parse Childnodes
	auto* child = node->FirstChildElement();
	if (child != nullptr)
	{
		// Image -> Data
		result.data = std::make_unique<Data>(ParseData(child));
	}
	return result;
}

Terrain TmxLoader::Detail::ParseTerrain(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Terrain();
	}
	Terrain result;
	result.name = node->Attribute("name", "");
	result.tile = node->IntAttribute("tile", 0);
	
	auto properties = node->NextSiblingElement("properties");
	result.properties = ParseProperties(properties);

	return result;
}

Tile TmxLoader::Detail::ParseTile(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Tile();
	}	
	Tile result;
	result.id = node->IntAttribute("id", 0);
	result.type = node->Attribute("type", "");
	result.probability = node->FloatAttribute("probability", 0.0f);
	
	std::string terraintypes = node->Attribute("terrain", "");
	if (terraintypes.size() != 0)
	{
		int cache = 0;
		for (const auto& i : terraintypes)
		{
			if (std::isdigit(i))
			{
				cache = cache * 10 + (i - '0');
			}
			else if (i == ',')
			{
				result.terrain.push_back(cache);
				cache = 0;
			}
		}
	}

	auto* child = node->FirstChildElement();
	while (child != nullptr)
	{
		if (::strcmp(child->Name(), "propetries") == 0)
		{
			result.properties = ParseProperties(child);
		}
		else if (::strcmp(child->Name(), "image") == 0)
		{
			result.image = std::make_unique<Image>(ParseImage(child));
		}
		else if (::strcmp(child->Name(), "objectgroup") == 0)
		{
			result.objectgroup = std::make_unique<Objectgroup>(ParseObjectgroup(child));
		}
		else if (::strcmp(child->Name(), "animation") == 0)
		{
			auto* grandson = child->NextSiblingElement();
			while (grandson != nullptr)
			{
				result.animation.push_back(ParseFrame(grandson));
			}			
		}
	}

	return result;
}

Frame TmxLoader::Detail::ParseFrame(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Frame();
	}
	Frame result;
	result.tileid = node->IntAttribute("tileid", 0);
	result.duration = node->IntAttribute("duration", 0);

	return result;
}

Wangset TmxLoader::Detail::ParseWangset(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Wangset();
	}
	Wangset result;
	result.name = node->Attribute("name", "");
	result.tile = node->IntAttribute("tile", 0);

	auto* child = node->FirstChildElement();
	while (child != nullptr)
	{
		if (::strcmp(child->Name(), "wangcornercolor") == 0)
		{
			auto color = ParseWangColorBase(child);
			result.wangcornercolor.push_back(*static_cast<Wangcornercolor*>(&color));
		}
		else if (::strcmp(child->Name(), "wangedgecolor") == 0)
		{
			auto color = ParseWangColorBase(child);
			result.wangedgecolor.push_back(*static_cast<Wangedgecolor*>(&color));
		}
		else if (::strcmp(child->Name(), "wangtile") == 0)
		{
			result.wangtile.push_back(ParseWangeTile(child));
		}

		child = child->NextSiblingElement();
	}

	return result;
}

WangColorBase TmxLoader::Detail::ParseWangColorBase(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return WangColorBase();
	}
	WangColorBase result;
	result.name = node->Attribute("name", "");
	result.color = node->Attribute("color", "");
	result.tile = node->IntAttribute("tile", 0);
	result.probability = node->FloatAttribute("probability", 0.0f);

	return result;
}

Wangtile TmxLoader::Detail::ParseWangeTile(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Wangtile();
	}
	Wangtile result;
	result.tileid = node->IntAttribute("tileid", 0);
	result.wangid = node->IntAttribute("wangid", 0);

	return result;
}

Layer TmxLoader::Detail::ParseLayer(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Layer();
	}
	Layer result;
	result.id = node->IntAttribute("id", 0);
	result.name = node->Attribute("name", "");
	result.x = node->IntAttribute("x", 0);
	result.y = node->IntAttribute("y", 0);
	result.width = node->IntAttribute("width", 0);
	result.height = node->IntAttribute("height", 0);
	result.opacity = node->FloatAttribute("opacity", 0.0f);
	result.visible = node->BoolAttribute("visible", true);
	result.offsetx = node->IntAttribute("offsetx", 0);
	result.offsety = node->IntAttribute("offsety", 0);

	// Parse Children
	auto* child = node->FirstChildElement();
	while (child != nullptr)
	{
		if (::strcmp(child->Name(), "properties") == 0)
		{
			result.properties = ParseProperties(child);
		}
		else if (::strcmp(child->Name(), "data") == 0)
		{
			result.data = std::make_unique<Data>(ParseData(child));
		}

		child = child->NextSiblingElement();
	}

	return result;
}

Tile_Layer TmxLoader::Detail::ParseTileLayer(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Tile_Layer();
	}
	Tile_Layer result;	
	result.gid = node->IntAttribute("gid", 0);
	return result;
}

Data TmxLoader::Detail::ParseData(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Data();
	}
	Data result;
	result.encoding = node->Attribute("encoding", "");
	result.compression = node->Attribute("compression", "");
	result.storeddata = node->GetText();
	
	auto* child = node->FirstChildElement();
	while (child != nullptr)
	{
		if (::strcmp(child->Name(), "tile"))
		{
			// Parse Tile
			Tile_Layer tile;
			tile.gid = child->IntAttribute("gid", 0);
			result.tile.push_back(std::move(tile));
		}
		else if (::strcmp(child->Name(), "chunk"))
		{
			// Parse Chunk
			result.chunk.push_back(ParseChunk(child));
		}
		child = child->NextSiblingElement();
	}

	return result;
}

Chunk TmxLoader::Detail::ParseChunk(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Chunk();
	}
	Chunk result;
	result.x = node->IntAttribute("x", 0);
	result.y = node->IntAttribute("y", 0);
	result.width = node->IntAttribute("width", 0);
	result.height = node->IntAttribute("height", 0);
	result.storeddata = node->GetText();
	
	// Parse Tile
	auto* child = node->FirstChildElement();
	while (child != nullptr)
	{
		if (::strcmp(child->Name(), "tile"))
		{
			Tile_Layer tile;
			tile.gid = child->IntAttribute("gid", 0);
			result.tile.push_back(std::move(tile));
		}
		child = child->NextSiblingElement();
	}

	return result;
}

Objectgroup TmxLoader::Detail::ParseObjectgroup(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Objectgroup();
	}
	Objectgroup result;
	result.id = node->IntAttribute("id", 0);
	result.name = node->Attribute("name", "");
	result.color = node->Attribute("color","");
	result.x = node->IntAttribute("x", 0);
	result.y = node->IntAttribute("y", 0);
	result.width = node->IntAttribute("width", 0);
	result.height = node->IntAttribute("height", 0);
	result.opacity = node->FloatAttribute("opacity", 0.0f);
	result.visible = node->BoolAttribute("visible", true);
	result.offsetx = node->IntAttribute("offsetx", 0);
	result.offsety = node->IntAttribute("offsety", 0);

	auto draworder = node->Attribute("draworder", "topdown");

	if (::strcmp(draworder, "topdown") == 0)
	{
		result.draworder = DrawOrder::topdown;
	}
	else if (::strcmp(draworder, "index") == 0)
	{
		result.draworder = DrawOrder::index;
	}

	// Parse Childnodes
	auto* child = node->FirstChildElement();

	while (child != nullptr)
	{
		if (::strcmp(child->Name(), "properties") == 0)
		{
			result.properties = ParseProperties(child);
		}
		else if (::strcmp(child->Name(), "object") == 0)
		{
			auto* objectNode = child->FirstChildElement();
			while (objectNode != nullptr)
			{
				result.objects.push_back(ParseObject(objectNode));
			}
		}

		child = child->NextSiblingElement();
	}

	return result;
}

Object TmxLoader::Detail::ParseObject(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Object();
	}
	Object result;
	result.id = node->IntAttribute("id", 0);
	result.name = node->Attribute("name", "");
	result.type = node->Attribute("type", "");
	result.x = node->IntAttribute("x", 0);
	result.y = node->IntAttribute("y", 0);
	result.width = node->IntAttribute("width", 0);
	result.height = node->IntAttribute("height", 0);
	result.rotation = node->FloatAttribute("rotation", 0.0f);
	result.gid = node->IntAttribute("gid", 0);
	result.visible = node->BoolAttribute("visible", true);
	result.templateFile = node->Attribute("template", "");

	// Pointlist Parsing
	auto m_parsePoint = [](std::string str) -> VectorType<Point<>>
	{
		bool isX = true;
		int cache = 0;
		VectorType<Point<>> pointlist;
		Point<> pointcache;
		for (const auto& i : str)
		{
			if (std::isdigit(i))
			{
				cache = cache * 10 + (i - '0');
			}
			else if (i == ',')
			{
				pointcache.x = cache;
				cache = 0;
				bool isX = false;
			}
			else if (i == ' ')
			{
				pointcache.y = cache;
				cache = 0;
				pointlist.push_back(pointcache);
			}
		}
		return pointlist;
	};

	// Parse Childnodes
	auto* child = node->FirstChildElement();

	while (child != nullptr)
	{
		if (::strcmp(child->Name(), "properties") == 0)
		{
			result.properties = ParseProperties(child);
		}
		else if (::strcmp(child->Name(), "ellipse") == 0)
		{
			result.objectTypeTag = StoredObjectType::ellipse;
		}
		else if (::strcmp(child->Name(), "point") == 0)
		{
			result.objectTypeTag = StoredObjectType::point;
		}
		else if (::strcmp(child->Name(), "polygon") == 0)
		{
			result.objectTypeTag = StoredObjectType::polygon;
			result.pointlists = m_parsePoint(child->Attribute("points", ""));
		}
		else if (::strcmp(child->Name(), "polyline") == 0)
		{
			result.objectTypeTag = StoredObjectType::polyline;
			result.pointlists = m_parsePoint(child->Attribute("points", ""));
		}
		else if (::strcmp(child->Name(), "text") == 0)
		{
			result.objectTypeTag = StoredObjectType::text;
			result.text = std::make_unique<Text>(ParseText(child));
		}

		child = child->NextSiblingElement();
	}

	return result;
}

Text TmxLoader::Detail::ParseText(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Text();
	}
	Text result;
	result.fontfamily = node->Attribute("fontfamily", "");
	result.pixelsize = node->IntAttribute("pixelsize", 16);
	result.wrap = node->IntAttribute("wrap", 0);
	result.color = node->Attribute("color", "#000000");
	result.bold = node->IntAttribute("bold", 0);
	result.italic = node->IntAttribute("italic", 0);
	result.underline = node->IntAttribute("underline", 0);
	result.strikeout = node->IntAttribute("strikeout", 0);
	result.kerning = node->IntAttribute("kerning", 1);

	// HAlign Enum
	//
	auto halign = node->Attribute("haligh", "left");

	if (::strcmp(halign, "left") == 0)
	{
		result.halign = HAlign::left;
	}
	else if (::strcmp(halign, "center") == 0)
	{
		result.halign = HAlign::center;
	}
	else if (::strcmp(halign, "right") == 0)
	{
		result.halign = HAlign::right;
	}
	else if (::strcmp(halign, "justify") == 0)
	{
		result.halign = HAlign::justify;
	}

	// VAlign Enum
	//
	auto valign = node->Attribute("valign", "top");

	if (::strcmp(valign, "top") == 0)
	{
		result.valign = VAlign::top;
	}
	else if (::strcmp(valign, "center") == 0)
	{
		result.valign = VAlign::center;
	}
	else if (::strcmp(valign, "bottom") == 0)
	{
		result.valign = VAlign::bottom;
	}

	return result;
}

Imagelayer TmxLoader::Detail::ParseImagelayer(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Imagelayer();
	}
	Imagelayer result;
	result.id = node->IntAttribute("id", 0);
	result.name = node->Attribute("name", "");
	result.offsetx = node->IntAttribute("offsetx", 0);
	result.offsety = node->IntAttribute("offsety", 0);
	result.x = node->IntAttribute("x", 0);
	result.y = node->IntAttribute("y", 0);
	result.opacity = node->FloatAttribute("opacity", 0.0f);
	result.visible = node->BoolAttribute("visible", true);

	// Parse Childnodes
	auto* child = node->FirstChildElement();

	while (child != nullptr)
	{
		if (::strcmp(child->Name(), "properties") == 0)
		{
			result.properties = ParseProperties(child);
		}
		else if (::strcmp(child->Name(), "image") == 0)
		{
			result.image = std::make_unique<Image>(ParseImage(child));
		}

		child = child->NextSiblingElement();
	}

	return result;
}

Group TmxLoader::Detail::ParseGroup(tinyxml2::XMLElement* node)
{
	if (node == nullptr)
	{
		return Group();
	}
	Group result;

	result.id = node->IntAttribute("id", 0);
	result.name = node->Attribute("name", "");
	result.opacity = node->FloatAttribute("opacity", 0.0f);
	result.visible = node->BoolAttribute("visible", true);
	result.offsetx = node->IntAttribute("offsetx", 0);
	result.offsety = node->IntAttribute("offsety", 0);

	// Parse Childnodes
	auto* child = node->FirstChildElement();

	while (child != nullptr)
	{
		if (::strcmp(child->Name(), "properties") == 0)
		{
			result.properties = ParseProperties(child);
		}
		else if (::strcmp(child->Name(), "layer") == 0)
		{
			result.layers.push_back(ParseLayer(child));
		}
		else if (::strcmp(child->Name(), "objectgroup") == 0)
		{
			result.objectgroups.push_back(ParseObjectgroup(child));
		}
		else if (::strcmp(child->Name(), "imagelayer") == 0)
		{
			result.imagelayers.push_back(ParseImagelayer(child));
		}
		else if (::strcmp(child->Name(), "group") == 0)
		{
			result.groups.push_back(ParseGroup(child));
		}

		child = child->NextSiblingElement();
	}

	return result;
}
