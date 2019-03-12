#pragma once

#include <string>

namespace TmxLoader {
	
	namespace Base64 {

		template<typename T = unsigned char>
		static std::vector<T> DecodeAsByteArray(std::string value)
		{
			static const char decodingTable[]
				= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

			std::vector<T> ret;

			T cache = 0;
			int cacheBitCount = 0;

			unsigned long overflowingBit = 0;
			int overflowingBitCount = 0;

			auto readingPos = value.begin();

			while (true)
			{
				if (readingPos != value.end() && *readingPos == '=')
				{
					readingPos = value.end();
				}

				if (readingPos == value.end() && overflowingBitCount == 0)
				{
					if (cacheBitCount != 0)
					{
						ret.push_back(cache << (sizeof(T) * CHAR_BIT - cacheBitCount));
					}
					break;
				}
				
				if (cacheBitCount == (sizeof(T) * CHAR_BIT))
				{
					// If cache is filled with bit, push it to ret.
					ret.push_back(cache);
					cache = 0;
					cacheBitCount = 0;
				}
				else
				{
					// If cache is not filled.
					if (overflowingBitCount == 0)
					{
						// If there is no bit in overflowingBit.

						for (int i = 0; i < 63; ++i)
						{
							// Find Character.
							if (readingPos != value.end() && decodingTable[i] == *readingPos)
							{
								if (*readingPos == '=')
								{
									break;
								}
								overflowingBit <<= 6;
								overflowingBit |= i;
								overflowingBitCount += 6;
								++readingPos;

								break;
							}
						}
					}

					// push overflownBits to cache.
					int space = (sizeof(T) * CHAR_BIT) - cacheBitCount;
					
					for (int i = 0; i < space; ++i)
					{
						if (overflowingBitCount == 0)
						{
							break;
						}

						unsigned long bitmask = 1;

						bitmask <<= overflowingBitCount - 1;

						//push the highest valid overflowingBit to the lowest bit of cache using bitmask
						cache <<= 1;
						cache |= (overflowingBit & bitmask) != 0 ? 1 : 0;
						
						//set the highest valid overflowingBit 0
						overflowingBit &= ~bitmask;

						overflowingBitCount--;
						cacheBitCount++;
					}
				}
			}

			return ret;

		}

	}
}