#pragma once

#include "Fwd.h"
#include "Typedefs.h"
#include "tinyxml2/tinyxml2.h"

namespace TmxLoader{
	
	namespace Detail
	{
		Property        ParseProperty       (tinyxml2::XMLElement*);
		VectorType<Property> ParseProperties(tinyxml2::XMLElement*);

		Tileset         ParseTileset        (tinyxml2::XMLElement*);
		Image           ParseImage          (tinyxml2::XMLElement*);
		Terrain         ParseTerrain        (tinyxml2::XMLElement*);
		Tile            ParseTile           (tinyxml2::XMLElement*);
		Frame           ParseFrame          (tinyxml2::XMLElement*);
		Wangset         ParseWangset        (tinyxml2::XMLElement*);
		WangColorBase   ParseWangColorBase  (tinyxml2::XMLElement*);
		//Wangcornercolor ParseWangCornerColor(tinyxml2::XMLElement*);
		//Wangedgecolor   ParseWangEdgeColor  (tinyxml2::XMLElement*);
		Wangtile        ParseWangeTile      (tinyxml2::XMLElement*);

		Layer           ParseLayer          (tinyxml2::XMLElement*);
		Tile_Layer      ParseTileLayer      (tinyxml2::XMLElement*);
		Data            ParseData           (tinyxml2::XMLElement*);
		Chunk           ParseChunk          (tinyxml2::XMLElement*);

		Objectgroup     ParseObjectgroup    (tinyxml2::XMLElement*);
		Object          ParseObject         (tinyxml2::XMLElement*);
		Text            ParseText           (tinyxml2::XMLElement*);

		Imagelayer      ParseImagelayer     (tinyxml2::XMLElement*);

		Group           ParseGroup          (tinyxml2::XMLElement*);
	}
}