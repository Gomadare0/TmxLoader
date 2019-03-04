#pragma once

#include <iostream>

namespace TmxLoader
{
	class LoggerClass
	{
	public:
		void operator<<(const char* val)
		{
#ifdef _DEBUG
			std::cout << val << std::endl;
#endif
		}
	};

	static LoggerClass Log;
}