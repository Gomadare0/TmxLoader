#include "Layer.h"
#include "Base64.h"

#include <sstream>
#include <cstdint>

void TmxLoader::Data::ConvertStoredDataIntoTiles()
{
	if (encoding == "")
	{
		// xml
		return;
	}
	else if (encoding == "csv")
	{
		if (compression == "")
		{
			std::istringstream stream(storeddata);

			while (stream)
			{
				std::string temp;
				if (!getline(stream, temp, ','))
				{
					break;
				}
				tile.push_back(Tile_Layer{ std::stoi(temp) }); // firstgid is global id offset in tileset
			}
		}
	}
	if (encoding == "base64")
	{
		std::string decoded = storeddata;

		// Remove \n and space.
		for (auto itr = decoded.begin(); itr != decoded.end();)
		{
			if ((*itr == '\n') || (*itr == ' '))
			{
				itr = decoded.erase(itr);
				if (itr == decoded.end())
				{
					break;
				}
			}
			else
			{
				++itr;
			}
		}

		// Base64 Interpreting
		auto rawData = Base64::DecodeAsByteArray<unsigned int>(decoded);

		if (compression == "zlib")
		{
		}
		else if (compression == "gzip")
		{
		}

		// Big endian to Little endian
		for (auto& i : rawData)
		{
			unsigned int buffer = 0;
			for (int k = 0; k < sizeof(unsigned int) - 1; ++k)
			{
				buffer |= (i & 0xFF);
				buffer <<= CHAR_BIT;
				i >>= CHAR_BIT;
			}
			buffer |= (i & 0xFF);
			i = buffer;
		}

		for (const auto& i : rawData)
		{
			tile.push_back(Tile_Layer{static_cast<int>(i)});
		}
	}
}
